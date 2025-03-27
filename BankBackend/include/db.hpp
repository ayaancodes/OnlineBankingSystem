#ifndef DB_HPP
#define DB_HPP

#include <pqxx/pqxx>
#include <string>
#include <vector>

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

    // 5) (Optional) Transaction history
    // We'll store data in a struct or just return text for now
    std::vector<std::string> getTransactions(int userId);
};

#endif
