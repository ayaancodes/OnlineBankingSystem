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
- Running a multithreaded HTTP server on port 8080 using Boost.Beast

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
├── build/                         # CMake build artifacts
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

3. **Set Up Schema**:

```bash
psql -d bankapp -f BankBackend/schema.sql
```

This will create the required tables:

- `users (id SERIAL PRIMARY KEY, name TEXT, balance REAL)`
- `transactions (id SERIAL, user_id INTEGER, type TEXT, amount REAL, timestamp TIMESTAMP)`

---

## Building the Project

Navigate to the project root and run:

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

Once built, run the server:

```bash
./build/server
```

Server will be available at: `http://localhost:8080`

---

## Running Tests

Each test is compiled independently (to be re-integrated as part of future work).

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

Stored in the `users` table. Each user has:

- ID (Primary Key)
- Name (Text)
- Balance (Real number)

### Transaction

Stored in the `transactions` table. Each transaction includes:

- ID (Primary Key)
- User ID (Foreign Key)
- Type (`deposit` or `withdrawal`)
- Amount (Real number)
- Timestamp (auto-generated)

---

## Makefile Usage (Deprecated in favor of CMake)

Sample legacy rule:

```makefile
create_user_test:
	g++ -std=c++17 $(shell pkg-config --cflags libpqxx) \
	  tests/create_user_test.cpp db/db.cpp models/user.cpp models/transaction.cpp \
	  -o create_user_test $(shell pkg-config --libs libpqxx)
```

---

## Dependencies

Ensure the following are installed:

- **g++** with C++17 support
- **PostgreSQL** (v13 or higher)
- **libpqxx** (C++ PostgreSQL client)
- **Boost (Beast, Asio)**
- **pkg-config** (used by CMake)

Install dependencies on macOS:

```bash
brew install boost libpqxx pkg-config cmake
```

---

## Future Improvements

- ✅ Refactor to use Boost.Beast HTTP server
- 🧠 Add support for dynamic JSON body parsing
- 🔒 Add authentication with hashed passwords
- 🔁 Support account-to-account transfers
- 🌐 Build full REST API
- 🧪 Reintroduce & expand testing framework
- 🐳 Containerize with Docker

---

## License

This project is open source and available under the MIT License.

