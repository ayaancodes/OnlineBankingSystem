#!/bin/bash

echo "🔁 Functional API Testing..."

# Register a user
curl -s -X POST http://localhost:8080/register \
  -H "Content-Type: application/json" \
  -d '{"name": "apiUser1", "password": "test123", "initialBalance": 1000}'

# Login
response=$(curl -s -X POST http://localhost:8080/login \
  -H "Content-Type: application/json" \
  -d '{"name": "apiUser1", "password": "test123"}')

userId=$(echo $response | grep -o '"userId":[0-9]*' | cut -d ':' -f 2)

echo "✅ Logged in as userId=$userId"

# Deposit
curl -s -X POST http://localhost:8080/deposit \
  -H "Content-Type: application/json" \
  -d "{\"userId\": $userId, \"amount\": 200}"

# Withdraw
curl -s -X POST http://localhost:8080/withdraw \
  -H "Content-Type: application/json" \
  -d "{\"userId\": $userId, \"amount\": 50}"

# Get balance
curl -s "http://localhost:8080/balance?userId=$userId"

# Transaction history
curl -s "http://localhost:8080/transactions?userId=$userId"

echo -e "\n✅ Functional API test completed.\n"
