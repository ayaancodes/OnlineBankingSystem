#ifndef DB_HPP
#define DB_HPP

#include <pqxx/pqxx>
#include <string>
#include <vector>
#include "../src/models/transaction.hpp" 
// bool registerUser(const std::string &name, const std::string &password, double initialBalance);
// int loginUser(const std::string &name, const std::string &password);

class DB {
private:
    pqxx::connection* conn;

public:
    DB();
    ~DB();

    bool isConnected();
    pqxx::connection* getConn();

    // 1) Create a new user
    bool createUser(const std::string &name, double initialBalance);

    // 2) Get current balance
    double getBalance(int userId);

    // 3) Deposit
    bool deposit(int userId, double amount);

    // 4) Withdraw
    bool withdraw(int userId, double amount);

    // 5) Transfer money between two suers atomically
    bool transfer(int senderId, int receiverId, double amount);

    //6) Register functionality
    bool registerUser(const std::string &name, const std::string &password, double initialBalance);

    //7) Login functionality
    int loginUser(const std::string &name, const std::string &password);


std::vector<Transaction> getTransactions(int userId);
};

#endif
