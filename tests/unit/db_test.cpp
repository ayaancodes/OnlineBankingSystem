#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../../BankBackend/include/db.hpp"

// Connect to test DB
DB db("dbname=bankapp_test user=ayaanmunshi hostaddr=127.0.0.1 port=5432");

// Create a helper to wipe the DB (you must have added this to DB class!)
void wipeTestDatabase() {
    db.executeRaw("DELETE FROM transactions;");
    db.executeRaw("DELETE FROM users;");
}

TEST_CASE("Create user and verify initial balance") {
    wipeTestDatabase();
    bool created = db.createUser("UnitUser1", 1000.0);
    CHECK(created == true);
}

TEST_CASE("Deposit increases balance correctly") {
    wipeTestDatabase();
    db.registerUser("DepositUser", "pass123", 500.0);
    int userId = db.loginUser("DepositUser", "pass123");
    REQUIRE(userId > 0);

    bool success = db.deposit(userId, 250.0);
    CHECK(success == true);

    double balance = db.getBalance(userId);
    CHECK(balance == doctest::Approx(750.0));
}

TEST_CASE("Withdraw subtracts correctly") {
    wipeTestDatabase();
    db.registerUser("WithdrawUser", "pass123", 600.0);
    int userId = db.loginUser("WithdrawUser", "pass123");
    REQUIRE(userId > 0);

    bool success = db.withdraw(userId, 100.0);
    CHECK(success == true);

    double balance = db.getBalance(userId);
    CHECK(balance == doctest::Approx(500.0));
}

TEST_CASE("Transfer between two users works correctly") {
    wipeTestDatabase();
    db.registerUser("Sender", "pass123", 1000.0);
    db.registerUser("Receiver", "pass456", 200.0);

    int senderId = db.loginUser("Sender", "pass123");
    int receiverId = db.loginUser("Receiver", "pass456");

    REQUIRE(senderId > 0);
    REQUIRE(receiverId > 0);

    bool success = db.transfer(senderId, receiverId, 300.0);
    CHECK(success == true);

    double senderBalance = db.getBalance(senderId);
    double receiverBalance = db.getBalance(receiverId);

    CHECK(senderBalance == doctest::Approx(700.0));
    CHECK(receiverBalance == doctest::Approx(500.0));
}
