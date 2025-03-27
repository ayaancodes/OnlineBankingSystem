#include "../db/db.hpp"
#include <iostream>

int main() {
    DB db;
    if (!db.isConnected()) {
        std::cerr << "DB not connected.\n";
        return 1;
    }

    int userId = 1; // replace with actual test user id
    bool success = db.deposit(userId, 250.0);

    if (success) {
        std::cout << "✅ Deposit successful\n";
        std::cout << "New Balance: " << db.getBalance(userId) << "\n";
    } else {
        std::cout << "❌ Deposit failed\n";
    }

    return 0;
}
