#include "../db/db.hpp"
#include "../models/transaction.hpp"
#include <iostream>
#include <vector>

int main() {
    DB db;

    if (!db.isConnected()) {
        std::cerr << "❌ DB connection failed.\n";
        return 1;
    }

    int userId = 1; // Use a valid ID from your DB

    std::vector<Transaction> transactions = db.getTransactions(userId);

    if (transactions.empty()) {
        std::cout << "ℹ️ No transactions found for user " << userId << ".\n";
    } else {
        std::cout << "📄 Transaction history:\n";
        for (const auto& tx : transactions) {
            std::cout << "TX #" << tx.id 
                      << " | " << tx.type 
                      << " | " << tx.amount 
                      << " | " << tx.timestamp << "\n";
        }
    }

    return 0;
}
