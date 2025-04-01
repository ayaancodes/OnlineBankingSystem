

-- Drop tables if they exist (for re-runs during dev)
DROP TABLE IF EXISTS transactions; -- Remove transactions table if it exists
DROP TABLE IF EXISTS users; -- Remove users table if it exists

CREATE TABLE users (
  id SERIAL PRIMARY KEY, -- Auto-incrementing user ID
  name TEXT NOT NULL, -- User's name
  password TEXT, -- User's password - Abdul
  balance NUMERIC NOT NULL DEFAULT 0 -- Account balance with default 0
);

CREATE TABLE transactions (
  id SERIAL PRIMARY KEY, -- Auto-incrementing transaction ID
  user_id INT NOT NULL REFERENCES users(id) ON DELETE CASCADE, -- Linked user ID
  amount NUMERIC NOT NULL, -- Transaction amount
  type TEXT CHECK (type IN ('deposit', 'withdrawal', 'transfer_sent', 'transfer_received')), -- Abdul
  timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- Time the transaction occurred
);


