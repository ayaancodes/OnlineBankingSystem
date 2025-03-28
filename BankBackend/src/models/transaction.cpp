#include "../models/transaction.hpp"

Transaction::Transaction(int id, int user_id, double amount, const std::string& type, const std::string& timestamp)
    : id(id), user_id(user_id), amount(amount), type(type), timestamp(timestamp) {}




