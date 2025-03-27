#include "db/db.hpp"
#include <iostream>
#include <vector>

// main.cpp
int main() {
    DB db;
    if (!db.isConnected()) return 1;

    int choice;
    while (true) {
        std::cout << "\n1. Create User\n2. Deposit\n3. Withdraw\n4. Balance\n5. Transactions\n0. Exit\n> ";
        std::cin >> choice;
        if (choice == 0) break;

        // switch-case for each operation calling db.<function>()
    }
}
