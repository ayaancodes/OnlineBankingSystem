#include "include/db.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        DB db;
        if (!db.isConnected()) {
            std::cerr << "DB not connected.\n";
            return 1;
        }

        // 1) Create user
        db.createUser("Ayaan", 500.0);

        // 2) Check balance
        double bal = db.getBalance(1);
        std::cout << "Ayaan's balance: " << bal << "\n";

        // 3) Deposit
        db.deposit(1, 200.0);
        bal = db.getBalance(1);
        std::cout << "Balance after deposit: " << bal << "\n";

        // 4) Withdraw
        db.withdraw(1, 100.0);
        bal = db.getBalance(1);
        std::cout << "Balance after withdrawal: " << bal << "\n";

        // 5) Show transactions
        auto txList = db.getTransactions(1);
        for (auto &tx : txList) {
            std::cout << tx << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "❌ Exception in main: " << e.what() << std::endl;
    }

    return 0;
}
