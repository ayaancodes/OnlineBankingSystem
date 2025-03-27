#include "../db/db.hpp"
#include <iostream>

int main() {
    DB db;
    if (!db.isConnected()) {
        std::cerr << "DB not connected.\n";
        return 1;
    }

    bool created = db.createUser("TestUser3", 1200.0);
    if (created) {
        std::cout << "✅ User created successfully\n";
    } else {
        std::cout << "❌ Failed to create user\n";
    }

    return 0;
}
