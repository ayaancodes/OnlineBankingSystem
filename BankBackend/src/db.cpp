#include "../include/db.hpp"
#include <iostream>

// Constructor / Destructor remain the same:
DB::DB() {
    try {
        conn = new pqxx::connection("dbname=bankapp user=ayaanmunshi hostaddr=127.0.0.1 port=5432");
        if (conn->is_open()) {
            std::cout << "✅ Connected to database: " << conn->dbname() << std::endl;
        } else {
            std::cerr << "❌ Connection failed." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "❌ DB Constructor Error: " << e.what() << std::endl;
        conn = nullptr;
    }
}

DB::~DB() {
    if (conn) {
        delete conn;
        std::cout << "🔌 Disconnected from database." << std::endl;
    }
}

// 7) Transfer between users with transaction logging - Abdul
bool DB::transfer(int senderId, int receiverId, double amount) {
    if (!isConnected()) {
        std::cerr << "❌ Not connected to DB.\n";
        return false;
    }

    if (amount <= 0) {
        std::cerr << "⚠️ Invalid transfer amount: " << amount << std::endl;
        return false;
    }

    std::lock_guard<std::mutex> lock(dbMutex);  // -Abdul

    try {
        pqxx::work txn(*conn);

        // 7a) Check sender's balance
        pqxx::result senderRes = txn.exec_params("SELECT balance FROM users WHERE id = $1", senderId);
        if (senderRes.empty()) {
            std::cerr << "❌ Sender not found.\n";
            return false;
        }
        double senderBalance = senderRes[0][0].as<double>();
        if (senderBalance < amount) {
            std::cerr << "❌ Insufficient funds for transfer.\n";
            return false;
        }

        // 7b) Check receiver exists
        pqxx::result receiverRes = txn.exec_params("SELECT id FROM users WHERE id = $1", receiverId);
        if (receiverRes.empty()) {
            std::cerr << "❌ Receiver not found.\n";
            return false;
        }

        // 7c) Perform balance updates
        txn.exec_params("UPDATE users SET balance = balance - $1 WHERE id = $2", amount, senderId);
        txn.exec_params("UPDATE users SET balance = balance + $1 WHERE id = $2", amount, receiverId);

        // 7d) Log transactions
        txn.exec_params("INSERT INTO transactions (user_id, amount, type) VALUES ($1, $2, 'transfer_sent')", senderId, amount);
        txn.exec_params("INSERT INTO transactions (user_id, amount, type) VALUES ($1, $2, 'transfer_received')", receiverId, amount);

        txn.commit();
        std::cout << "✅ Transfer of $" << amount << " from user " << senderId << " to " << receiverId << " complete.\n";
        return true;

    } catch (const std::exception &e) {
        std::cerr << "❌ Transfer failed: " << e.what() << std::endl;
        return false;
    }
}

bool DB::isConnected() {
    return conn && conn->is_open();
}

pqxx::connection* DB::getConn() {
    return conn;
}

// 1) Create a new user in 'users' table
bool DB::createUser(const std::string &name, double initialBalance) {
    if (!isConnected()) return false;
    
    std::lock_guard<std::mutex> lock(dbMutex);  

    try {
        pqxx::work txn(*conn);
        txn.exec_params(
            "INSERT INTO users (name, balance) VALUES ($1, $2)",
            name, initialBalance
        );
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "❌ createUser Error: " << e.what() << std::endl;
        return false;
    }
}

// 2) Get a user's current balance
double DB::getBalance(int userId) {
    if (!isConnected()) return -1.0;
    std::lock_guard<std::mutex> lock(dbMutex);  
    try {
        pqxx::work txn(*conn);
        pqxx::result r = txn.exec_params(
            "SELECT balance FROM users WHERE id = $1",
            userId
        );

        // If user not found
        if (r.empty()) {
            std::cerr << "⚠️ No user found with id: " << userId << std::endl;
            return -1.0;
        }

        double balance = r[0][0].as<double>();
        txn.commit();
        return balance;
    } catch (const std::exception &e) {
        std::cerr << "❌ getBalance Error: " << e.what() << std::endl;
        return -1.0;
    }
}

// 3) Deposit -> also record transaction in 'transactions' table
bool DB::deposit(int userId, double amount) {
    if (!isConnected()) return false;
    if (amount <= 0) {
        std::cerr << "⚠️ Deposit amount must be > 0\n";
        return false;
    }
    std::lock_guard<std::mutex> lock(dbMutex);  

    try {
        pqxx::work txn(*conn);

        // 3a) Update user balance
        txn.exec_params(
            "UPDATE users SET balance = balance + $1 WHERE id = $2",
            amount, userId
        );

        // 3b) Insert into transactions
        txn.exec_params(
            "INSERT INTO transactions (user_id, amount, type) VALUES ($1, $2, 'deposit')",
            userId, amount
        );

        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "❌ deposit Error: " << e.what() << std::endl;
        return false;
    }
}

// 4) Withdraw -> also record transaction
bool DB::withdraw(int userId, double amount) {
    if (!isConnected()) return false;
    if (amount <= 0) {
        std::cerr << "⚠️ Withdraw amount must be > 0\n";
        return false;
    }

    std::lock_guard<std::mutex> lock(dbMutex);  
    try {
        pqxx::work txn(*conn);

        // 4a) Check current balance
        pqxx::result r = txn.exec_params(
            "SELECT balance FROM users WHERE id = $1",
            userId
        );
        if (r.empty()) {
            std::cerr << "❌ No user found with id: " << userId << std::endl;
            return false;
        }
        double currentBalance = r[0][0].as<double>();
        if (currentBalance < amount) {
            std::cerr << "❌ Insufficient funds. Current balance: " << currentBalance << std::endl;
            return false;
        }

        // 4b) Deduct from user balance
        txn.exec_params(
            "UPDATE users SET balance = balance - $1 WHERE id = $2",
            amount, userId
        );

        // 4c) Insert into transactions
        txn.exec_params(
            "INSERT INTO transactions (user_id, amount, type) VALUES ($1, $2, 'withdrawal')",
            userId, amount
        );

        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "❌ withdraw Error: " << e.what() << std::endl;
        return false;
    }
}

// 5) (Optional) Return list of transactions as strings
std::vector<Transaction> DB::getTransactions(int userId) {
    std::vector<Transaction> transactions;
    if (!isConnected()) return transactions;

    std::lock_guard<std::mutex> lock(dbMutex);  
    try {
        pqxx::work txn(*conn);
        pqxx::result r = txn.exec_params(
            "SELECT id, user_id, amount, type, timestamp FROM transactions WHERE user_id = $1 ORDER BY id",
            userId
        );

        for (auto row : r) {
            Transaction tx(
                row["id"].as<int>(),
                row["user_id"].as<int>(),
                row["amount"].as<double>(),
                row["type"].as<std::string>(),
                row["timestamp"].c_str()
            );
            transactions.push_back(tx);
        }

        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "❌ getTransactions Error: " << e.what() << std::endl;
    }

    return transactions;
}

// 6) Register User DB Functionality
bool DB::registerUser(const std::string &name, const std::string &password, double initialBalance) {
    if (!isConnected()) return false;
    std::lock_guard<std::mutex> lock(dbMutex);  
    try {
        pqxx::work txn(*conn);
        txn.exec_params("INSERT INTO users (name, password, balance) VALUES ($1, $2, $3)",
                        name, password, initialBalance);
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "❌ registerUser Error: " << e.what() << std::endl;
        return false;
    }
}

//DB Functionality to check login feature
int DB::loginUser(const std::string &name, const std::string &password) {
    if (!isConnected()) return -1;
    std::lock_guard<std::mutex> lock(dbMutex);  
    try {
        pqxx::work txn(*conn);
        pqxx::result r = txn.exec_params("SELECT id FROM users WHERE name = $1 AND password = $2",
                                         name, password);
        if (r.empty()) return -1; // Login failed
        return r[0][0].as<int>();
    } catch (const std::exception &e) {
        std::cerr << "❌ loginUser Error: " << e.what() << std::endl;
        return -1;
    }
}
