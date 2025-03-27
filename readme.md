# Online Banking System Backend

This project is a C++ backend for an online banking system that simulates essential banking operations such as user account creation, deposits, withdrawals, and transaction history tracking using PostgreSQL. It emphasizes modular design, transaction safety (ACID), and testability.

---

## Table of Contents

1. [Overview](#overview)
2. [Code Structure](#code-structure)
3. [Database Setup](#database-setup)
4. [Building the Project](#building-the-project)
5. [Running Tests](#running-tests)
6. [Using psql to Interact with the Database](#using-psql-to-interact-with-the-database)
7. [Model Design](#model-design)
8. [Makefile Usage](#makefile-usage)
9. [Dependencies](#dependencies)
10. [Future Improvements](#future-improvements)
11. [License](#license)

---

## Overview

The system is written in C++17 and communicates with a PostgreSQL database via the libpqxx library. It supports:

- Creating new users with balances
- Performing deposits and withdrawals
- Logging and retrieving transaction histories
- Unit testing of each core functionality

---

## Code Structure

```
OnlineBankingSystem/
└── BankBackend/
    ├── Makefile                # Build rules for core and tests
    ├── db/
    │   ├── db.cpp             # Database operations
    │   └── db.hpp             # DB class interface
    ├── include/               # (Optional) Shared headers
    ├── main.cpp               # CLI entry point for app testing
    ├── models/
    │   ├── user.cpp           # User logic (if needed)
    │   ├── user.hpp           # User model definition
    │   ├── transaction.cpp    # Transaction logic (optional)
    │   └── transaction.hpp    # Transaction model definition
    ├── schema.sql             # SQL file for DB initialization
    ├── src/                   # (Unused or expandable source dir)
    └── tests/
        ├── create_user_test.cpp
        ├── deposit_test.cpp
        ├── get_transactions_test.cpp
        └── withdraw_test.cpp
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

3. **Set Up Schema**:

   ```bash
   psql -d bankapp -f BankBackend/schema.sql
   ```

   This will create the required tables:

   - `users (id SERIAL PRIMARY KEY, name TEXT, balance REAL)`
   - `transactions (id SERIAL, user_id INTEGER, type TEXT, amount REAL, timestamp TIMESTAMP)`

---

## Building the Project

Navigate to the `BankBackend/` directory:

```bash
cd BankBackend
make
```

This will compile the main backend program using the specified source files.

To clean:

```bash
make clean
```

---

## Running Tests

Each test is compiled independently. For example:

```bash
make create_user_test
./create_user_test
```

Other targets:

```bash
make deposit_test
make withdraw_test
make get_transactions_test
```

To run all:

```bash
make all_tests
```

---

## Using psql to Interact with the Database

Start psql:

```bash
psql -d bankapp
```

Common queries:

```sql
SELECT * FROM users;
SELECT * FROM transactions;
```

Exit psql:

```sql
\q
```

---

## Model Design

### User

Defined in `user.hpp`. Represents a bank user with:

- ID
- Name
- Balance

### Transaction

Defined in `transaction.hpp`. Represents:

- ID
- User ID (foreign key)
- Type (deposit/withdrawal)
- Amount
- Timestamp

---

## Makefile Usage

Sample rules in `Makefile`:

```makefile
create_user_test:
	g++ -std=c++17 $(shell pkg-config --cflags libpqxx) \
	  tests/create_user_test.cpp db/db.cpp models/user.cpp models/transaction.cpp \
	  -o create_user_test $(shell pkg-config --libs libpqxx)
```

Run with:

```bash
make create_user_test
```

---

## Dependencies

Ensure the following are installed:

- **g++** (C++17 support)
- **PostgreSQL** (>= 13)
- **libpqxx** (C++ client for PostgreSQL)
- **pkg-config** (for flag resolution)

Install on macOS:

```bash
brew install libpqxx
```

---

## Future Improvements

- Add authentication with hashed passwords
- Extend transactions to support transfers
- Build a REST API with C++ (e.g., using Pistache or Crow)
- Add multi-threaded request handling
- Containerize with Docker

---

## License



