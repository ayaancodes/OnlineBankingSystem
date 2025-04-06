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
12. [Frontend Testing Instructions](#frontend-testing-instructions)
13. [Future Improvements](#future-improvements)
14. [License](#license)

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
├── Frontend/
│   ├── index.html
│   ├── dashboard.html
│   ├── deposit.html
│   ├── withdraw.html
│   ├── transfer.html
│   ├── transactions.html
│   ├── script.js
│   └── style.css
├── build/
├── tests/
│   ├── unit/
│   │   └── db_test.cpp
│   ├── performance/
│   │   └── performance_test.py
│   └── functional/
│       └── api_test.sh
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

Unit tests use [doctest](https://github.com/doctest/doctest). A separate test database `bankapp_test` is used to avoid interfering with the production database.

1. Ensure you've created the test DB:

```bash
createdb bankapp_test
psql -d bankapp_test -f BankBackend/schema.sql
```

2. Run tests:

```bash
./build/unit_tests
```

3. You can view output logs and assertions for test cases:
- Creating users
- Deposits
- Withdrawals
- Transfers between users

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

## Frontend Testing Instructions

To serve the static frontend:

1. From the root project folder:

```bash
cd Frontend
python3 -m http.server 8000
```

2. Visit `http://localhost:8000/index.html` in your browser.

3. The frontend supports:
- Registering and logging in users
- Viewing dashboards and balances
- Depositing and withdrawing funds
- Transferring money
- Viewing transactions

Make sure the backend is running at `localhost:8080` in parallel.

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

