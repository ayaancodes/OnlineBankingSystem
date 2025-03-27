# BankBackend/Makefile

# Use g++ as the compiler
CXX = g++
# Use C++17, enable warnings and add pkg-config cflags for libpqxx
CXXFLAGS = -std=c++17 -Wall $(shell pkg-config --cflags libpqxx)
# Get the required libraries from pkg-config for libpqxx
LDLIBS = $(shell pkg-config --libs libpqxx)

# List of test executables to build
TESTS = create_user_test deposit_test get_transactions_test withdraw_test

all: $(TESTS)

# Build create_user_test
create_user_test: tests/create_user_test.cpp db/db.cpp models/user.cpp models/transaction.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)
	
clean:
	rm -f $(TESTS)
