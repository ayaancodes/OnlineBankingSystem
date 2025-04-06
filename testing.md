# Backend Testing Documentation: Online Banking System

**Team Amber**  
**Contributors:** Ayaan Munshi, Utkarsh Sharma, Yusra Khan, Abdul Rahman

## Introduction
This document outlines the comprehensive testing strategy for the Online Banking System backend written in modern C++17. The goal is to verify correctness, concurrency safety, and performance reliability for all core banking operations such as deposits, withdrawals, transfers, and transaction logging.

The backend integrates with PostgreSQL using `libpqxx` and is designed with scalability and maintainability in mind. Testing is executed on a **separate test database** to isolate effects from production and maintain data integrity.

![Unit Testing Output](../images/unitTestOutput.png)

---

## What Was Implemented
| Testing Type       | Tools Used                  | Goal                                          |
|--------------------|-----------------------------|-----------------------------------------------|
| Unit Testing       | Doctest (C++)               | Test individual `DB` methods in isolation     |
| Functional Testing | Bash + cURL                 | Test REST API behavior end-to-end             |
| Performance Testing| Python + requests + ThreadPool | Measure concurrency, latency, and robustness |

All test phases share a common principle: **never interfere with production data**. Each is designed to test features in controlled environments.

---

## Scope of Testing
| Testing Level      | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| Unit Testing       | Test the C++ logic of `DB` class functions (e.g., deposit, withdraw)        |
| Functional Testing | Simulate API endpoint behavior through a scripted test runner with live server |
| Performance Testing| Simulate real-world concurrent users to benchmark throughput and latency     |

### Future Directions
- Integration & E2E testing
- Docker-based parallel test environments
- Test coverage reporting & CI integration

---

## Unit Testing

### Description
Unit tests are written using the **Doctest** framework and are isolated from the main app logic. The tests run against a **dedicated `bankapp_test` PostgreSQL instance** and validate key banking operations.

### Test Case Table
| Test Case            | Functionality                                | Expected Behavior                             |
|----------------------|----------------------------------------------|------------------------------------------------|
| Register + Deposit   | `registerUser(...)` + `deposit(...)`         | Account balance increases accordingly         |
| Register + Withdraw  | `registerUser(...)` + `withdraw(...)`        | Balance decreases if funds are sufficient     |
| Register + Transfer  | `transfer(senderId, receiverId, amount)`     | Sender balance decreases, receiver increases  |
| Create user only     | `createUser(...)`                            | New user created with initial balance         |

### Why It Matters
- Prevents regressions
- Ensures correctness at method-level
- Enables safe refactors
- Fast local test loop

### Sample Output
```text
[doctest] test cases:  4 |  4 passed | 0 failed | 0 skipped
[doctest] assertions: 12 | 12 passed | 0 failed |
[doctest] Status: SUCCESS!
```

![Unit Test Output](../images/unitTestOutput.png)

---

## Functional API Testing

### Description
A shell script (`api_test.sh`) uses `curl` to hit each major REST endpoint on a running server. This validates full-stack behavior (HTTP -> JSON -> C++ -> DB).

### Test Case Table
| API Endpoint       | Action                  | Expected Output                     |
|--------------------|-------------------------|-------------------------------------|
| `/register`        | Register a new user     | Success response with user ID       |
| `/login`           | Log in with credentials | Valid token and user ID             |
| `/deposit`         | Add funds               | Updated balance confirmation        |
| `/withdraw`        | Remove funds            | Balance adjusted if valid           |
| `/getBalance`      | Fetch balance           | Returns current amount              |
| `/getTransactions` | Retrieve history        | JSON array of transactions          |

### Sample Output
```text
Logged in as userId=3
Deposit and withdrawal success
Balance matches expected
Transactions returned correctly
```

![Functional Test Output](../images/functionalTestOutput.png)

---

## Performance Testing (Load & Concurrency)

### Description
To simulate **real-world concurrent banking usage**, we used a **Python-based load test** script that fires off `POST` requests in parallel using `ThreadPoolExecutor`.

### Concurrency Control
All database methods are guarded using a **global `std::mutex` lock** (see `db.cpp`) to ensure **atomic and thread-safe DB access**. This prevents race conditions under high load.

### Test Case Table
| Load Profile             | Goal                                  | Validation                                 |
|--------------------------|---------------------------------------|---------------------------------------------|
| 100 concurrent requests  | Stress test deposit/withdraw endpoints | No race conditions, consistent balances     |
| Mixed deposits & withdrawals | Simulate transaction loads         | Response time < 1s, 100% success rate       |
| Concurrency safety       | Verify mutex protection                | All operations atomic, DB integrity preserved |

### Example Metrics
| Metric           | Value           |
|------------------|-----------------|
| Total Requests   | 100             |
| Successful       | 100             |
| Failed           | 0               |
| Time Taken       | ~0.14 seconds   |
| Throughput       | ~739 requests/sec |

### Test Methodology
```bash
python3 tests/performance/performance_test.py
```
This test alternates `deposit` and `withdraw` requests, and aggregates status codes to calculate performance and errors.

![Performance Test Output](../images/performanceTestOutput.png)

---

## File Structure
```text
/tests/unit/db_test.cpp               <-- Unit tests using Doctest
/tests/functional/api_test.sh        <-- Functional endpoint test script
/tests/performance/performance_test.py <-- Python load test script
/tests/doctest.h                     <-- Doctest header
/build/unit_tests                    <-- CMake build for unit tests
/images/unitTestOutput.png           <-- Sample test run screenshot
/images/functionalTestOutput.png     <-- API test screenshot
/images/performanceTestOutput.png    <-- Load test screenshot
```

---

## Summary
This backend test suite validates the **reliability, correctness, and scalability** of the Online Banking System. By isolating test environments, thoroughly verifying each function and endpoint, and simulating real-world concurrency, this test suite gives developers and stakeholders confidence in the system's integrity.

All tests are designed to mirror real-world use cases and have been engineered to scale with future functionality. Our concurrency tests, combined with mutex-guarded operations, affirm the backend’s stability under simultaneous access patterns, making it robust enough for production deployment.

---

*Prepared by Team Amber — April 2025*

