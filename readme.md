# Online Banking System Backend

This project is a C++ backend for an online banking system that simulates essential banking operations such as user account creation, deposits, withdrawals, transfers, and transaction history tracking using PostgreSQL. It emphasizes modular design, transaction safety (ACID), and concurrency with thread-safe multithreading using `std::mutex`.

---

## Table of Contents

1. [Overview](#overview)
2. [Code Structure](#code-structure)
3. [Database Setup](#database-setup)
4. [Building the Project](#building-the-project)
5. [Running the Server](#running-the-server)
6. [Running Tests](#running-tests)
7. [Interacting with the API (Test Suite)](#interacting-with-the-api-test-suite)
8. [Using psql](#using-psql)
9. [Model Design](#model-design)
10. [Makefile Usage](#makefile-usage)
11. [Dependencies](#dependencies)
12. [Future Improvements](#future-improvements)
13. [License](#license)

---

## Overview

The system is written in C++17 and communicates with a PostgreSQL database via the `libpqxx` library. It supports:

- Creating users
- Logging in with credentials
- Depositing and withdrawing funds
- Transferring funds between accounts
- Retrieving transaction histories
- Thread-safe multithreading via `std::thread` and `std::mutex`
- Serving a RESTful HTTP API via Boost.Beast

---

## Code Structure

```
OnlineBankingSystem/
├── BankBackend/
│   ├── include/
│   │   ├── db.hpp
│   │   └── routes/
│   │       └── handlers.hpp
│   ├── schema.sql
│   └── src/
│       ├── db.cpp
│       ├── models/
│       │   ├── transaction.cpp
│       │   └── transaction.hpp
│       ├── routes/
│       │   └── handlers.cpp
│       └── server.cpp
├── CMakeLists.txt
└── readme.md
```

---

## Database Setup

1. **Install PostgreSQL**:

```bash
brew install postgresql
brew services start postgresql
```

2. **Create Database**:

```bash
createdb bankapp
```

3. **Apply Schema**:

```bash
psql -d bankapp -f BankBackend/schema.sql
```

This creates the following tables:

- `users (id SERIAL PRIMARY KEY, name TEXT, password TEXT, balance REAL)`
- `transactions (id SERIAL, user_id INTEGER, type TEXT, amount REAL, timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP)`

---

## Building the Project

```bash
cmake -Bbuild
cmake --build build
```

To clean:

```bash
rm -rf build/
```

---

## Running the Server

```bash
./build/server
```

Visit `http://localhost:8080`

---

## Running Tests

Manually test endpoints using the following `curl` requests:

### ✅ Registration
```bash
curl -X POST http://localhost:8080/register \
  -H "Content-Type: application/json" \
  -d '{"name": "TestUser", "password": "abc123", "initialBalance": 1000}'
```

### ✅ Login
```bash
curl -X POST http://localhost:8080/login \
  -H "Content-Type: application/json" \
  -d '{"name": "TestUser", "password": "abc123"}'
```

### ✅ Deposit
```bash
curl -X POST http://localhost:8080/deposit \
  -H "Content-Type: application/json" \
  -d '{"userId": 1, "amount": 100}'
```

### ✅ Withdraw
```bash
curl -X POST http://localhost:8080/withdraw \
  -H "Content-Type: application/json" \
  -d '{"userId": 1, "amount": 50}'
```

### ✅ Transfer
```bash
curl -X POST http://localhost:8080/transfer \
  -H "Content-Type: application/json" \
  -d '{"senderId": 1, "receiverId": 2, "amount": 100}'
```

### ✅ Get Balance
```bash
curl "http://localhost:8080/balance?userId=1"
```

### ✅ View Transaction History
```bash
curl "http://localhost:8080/transactions?userId=1"
```

---

## Interacting with the API (Test Suite)

To simulate **multithreaded operations**, run concurrent curl commands:

```bash
# Simultaneous Deposits
curl -X POST http://localhost:8080/deposit -H "Content-Type: application/json" -d '{"userId": 1, "amount": 100}' &
curl -X POST http://localhost:8080/deposit -H "Content-Type: application/json" -d '{"userId": 1, "amount": 200}' &
curl -X POST http://localhost:8080/deposit -H "Content-Type: application/json" -d '{"userId": 1, "amount": 300}' &

# Simultaneous Withdrawals
curl -X POST http://localhost:8080/withdraw -H "Content-Type: application/json" -d '{"userId": 1, "amount": 50}' &
curl -X POST http://localhost:8080/withdraw -H "Content-Type: application/json" -d '{"userId": 1, "amount": 75}' &
```

Use `curl http://localhost:8080/balance?userId=1` to confirm expected results.

---

## Using psql

Start:
```bash
psql -d bankapp
```

Useful queries:
```sql
SELECT * FROM users;
SELECT * FROM transactions;
```

Exit:
```sql
\q
```

---

## Model Design

### User
- `id SERIAL PRIMARY KEY`
- `name TEXT`
- `password TEXT`
- `balance REAL`

### Transaction
- `id SERIAL`
- `user_id INTEGER`
- `amount REAL`
- `type TEXT` (`deposit`, `withdrawal`, `transfer_sent`, `transfer_received`)
- `timestamp TIMESTAMP`

---

## Makefile Usage (Deprecated)

Use CMake instead. Legacy rule:

```makefile
create_user_test:
	g++ -std=c++17 $(shell pkg-config --cflags libpqxx) \
	  tests/create_user_test.cpp db/db.cpp models/user.cpp models/transaction.cpp \
	  -o create_user_test $(shell pkg-config --libs libpqxx)
```

---

## Dependencies

Ensure:
- `g++` (C++17)
- PostgreSQL
- `libpqxx`
- Boost (Beast, Asio)
- `pkg-config`
- CMake

macOS install:
```bash
brew install boost libpqxx pkg-config cmake
```

---

## Future Improvements

- ✅ Add multithreading support using `std::thread`
- ✅ Protect DB calls using `std::mutex`
- 🔒 Add secure password hashing (optional future)
- 🧪 Add integration tests
- 🐳 Dockerize project for easier onboarding

---

## Help?
Ask Ayaan :D

