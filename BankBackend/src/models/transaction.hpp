#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

struct Transaction {
    int id;
    int user_id;
    double amount;
    std::string type;
    std::string timestamp;

    Transaction(int id, int user_id, double amount, const std::string& type, const std::string& timestamp);
};

#endif
