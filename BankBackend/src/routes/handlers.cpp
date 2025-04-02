#include "../../include/routes/handlers.hpp"
#include "../../include/db.hpp"
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp> // JSON library

namespace http = boost::beast::http;
using json = nlohmann::json;

// Utility function to extract a specific query parameter from a URL query string
std::string getQueryParam(const std::string &query, const std::string &key)
{
    std::size_t keyPos = query.find(key + "=");
    if (keyPos == std::string::npos)
        return ""; // Return empty string if key is not found
    std::size_t valueStart = keyPos + key.length() + 1;
    std::size_t valueEnd = query.find("&", valueStart);
    if (valueEnd == std::string::npos)
        valueEnd = query.length(); // Use end of string if no further parameters
    return query.substr(valueStart, valueEnd - valueStart);
}

// Main request handler function to process incoming HTTP requests and generate responses
void handle_request(const http::request<http::string_body> &req,
                    http::response<http::string_body> &res)
{

    std::string target(req.target());
    std::cout << "[DEBUG] Received target: " << target << std::endl;

    DB db;

    // Handle GET request to retrieve user balance
    if (req.method() == http::verb::get && target.find("/balance") != std::string::npos)
    {
        std::string fullTarget = std::string(req.target());
        std::size_t queryStart = fullTarget.find("?");
        int userId = 1;

        // Parse query string for userId parameter
        if (queryStart != std::string::npos)
        {
            std::string queryStr = fullTarget.substr(queryStart + 1);
            std::string userIdStr = getQueryParam(queryStr, "userId");
            try
            {
                userId = std::stoi(userIdStr); // Convert userId from string to int
            }
            catch (...)
            {
                res.result(http::status::bad_request);
                res.body() = "Invalid or missing userId";
                res.prepare_payload();
                return;
            }
        }

        double balance = db.getBalance(userId); // Fetch balance from database
        std::stringstream ss;
        ss << "{\"balance\": " << balance << "}"; // Construct JSON response
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = ss.str();
    }

    // Handle POST request to deposit funds into a user's account
    else if (req.method() == http::verb::post && target.find("/deposit") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            int userId = body.at("userId").get<int>();
            double amount = body.at("amount").get<double>();

            bool success = db.deposit(userId, amount); // Attempt deposit in database
            json resBody;
            resBody["status"] = success ? "success" : "fail";
            resBody["message"] = success ? "Deposit successful" : "Deposit failed";
            res.result(success ? http::status::ok : http::status::bad_request);
            res.set(http::field::content_type, "application/json");
            res.body() = resBody.dump();
        }
        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload";
        }
    }

    // Handle POST request to withdraw funds from a user's account
    else if (req.method() == http::verb::post && target.find("/withdraw") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            int userId = body.at("userId").get<int>();
            double amount = body.at("amount").get<double>();

            bool success = db.withdraw(userId, amount); // Attempt withdrawal
            json resBody;
            resBody["status"] = success ? "success" : "fail";
            resBody["message"] = success ? "Withdrawal successful" : "Withdrawal failed";

            res.result(success ? http::status::ok : http::status::bad_request);
            res.set(http::field::content_type, "application/json");
            res.body() = resBody.dump();
        }

        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload";
        }
    }

    // Handle POST request to transfer funds between users
    else if (req.method() == http::verb::post && (target == "/transfer" || target.find("/transfer") != std::string::npos))
    {
        std::cerr << "[DEBUG] Hit /transfer endpoint\n";
        std::cerr << "[DEBUG] Raw body: " << req.body() << std::endl;

        try
        {
            json body = json::parse(req.body());
            int senderId = body.at("senderId").get<int>();
            int receiverId = body.at("receiverId").get<int>();
            double amount = body.at("amount").get<double>();

            bool success = db.transfer(senderId, receiverId, amount);
            json resBody;
            resBody["status"] = success ? "success" : "fail";
            resBody["message"] = success ? "Transfer successful" : "Transfer failed";

            res.result(success ? http::status::ok : http::status::bad_request);
            res.set(http::field::content_type, "application/json");
            res.body() = resBody.dump();
        }
        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error (transfer): " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload";
        }
    }

    // Handle GET request to retrieve a user's transaction history
    else if (req.method() == http::verb::get && target.find("/transactions") != std::string::npos)
    {
        std::string fullTarget = std::string(req.target());
        std::size_t queryStart = fullTarget.find("?");
        int userId = 1;

        if (queryStart != std::string::npos)
        {
            std::string queryStr = fullTarget.substr(queryStart + 1);
            std::string userIdStr = getQueryParam(queryStr, "userId");
            try
            {
                userId = std::stoi(userIdStr);
            }
            catch (...)
            {
                res.result(http::status::bad_request);
                res.body() = "Invalid or missing userId";
                res.prepare_payload();
                return;
            }
        }

        std::vector<Transaction> transactions = db.getTransactions(userId);
        json jsonArray = json::array();
        for (const auto &tx : transactions)
        {
            // Construct JSON object for each transaction
            jsonArray.push_back({{"id", tx.id},
                                 {"userId", tx.user_id},
                                 {"amount", tx.amount},
                                 {"type", tx.type},
                                 {"timestamp", tx.timestamp}});
        }

        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = jsonArray.dump();
    }

    // Handle POST request to register a new user with a password
    else if (req.method() == http::verb::post && target.find("/register") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            std::string name = body.at("name").get<std::string>();
            std::string password = body.at("password").get<std::string>();
            double balance = body.value("initialBalance", 0.0);

            bool success = db.registerUser(name, password, balance);
            json resBody = {
                {"status", success ? "success" : "fail"},
                {"message", success ? "User registered" : "Registration failed"}};

            res.result(success ? http::status::ok : http::status::bad_request);
            res.set(http::field::content_type, "application/json");
            res.body() = resBody.dump();
        }
        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error (register): " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload for registration";
        }
    }

    // Handle POST request to authenticate a user
    else if (req.method() == http::verb::post && target.find("/login") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            std::string name = body.at("name").get<std::string>();
            std::string password = body.at("password").get<std::string>();

            int userId = db.loginUser(name, password);
            json resBody;
            if (userId != -1)
            {
                resBody = {{"status", "success"}, {"userId", userId}};
                res.result(http::status::ok);
            }
            else
            {
                resBody = {{"status", "fail"}, {"message", "Invalid credentials"}};
                res.result(http::status::unauthorized);
            }
            res.set(http::field::content_type, "application/json");
            res.body() = resBody.dump();
        }
        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error (login): " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload for login";
        }
    }

    // Handle POST request to create a user without a password
    else if (req.method() == http::verb::post && target.find("/createUser") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            std::string name = body.at("name").get<std::string>();
            double initialBalance = body.at("initialBalance").get<double>();
            bool success = db.createUser(name, initialBalance);
            json resBody;
            resBody["status"] = success ? "success" : "fail";
            resBody["message"] = success ? "User created successfully" : "Failed to create user";

            res.result(success ? http::status::ok : http::status::bad_request);
            res.set(http::field::content_type, "application/json");
            res.body() = resBody.dump();
        }
        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error (createUser): " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload for user creation";
        }
    }

    // Fallback for unmatched endpoints
    else
    {
        std::cerr << "[DEBUG] No matching endpoint for: " << target << std::endl;
        res.result(http::status::not_found);
        res.body() = "Endpoint not found";
    }

    res.prepare_payload(); // Finalize response headers and body
}

// Database method to transfer funds between two users
bool DB::transfer(int senderId, int receiverId, double amount)
{
    if (!isConnected())
    {
        std::cerr << "[ERROR] Not connected to DB.\n";
        return false;
    }
    if (amount <= 0)
    {
        std::cerr << "[ERROR] Invalid transfer amount: " << amount << std::endl;
        return false;
    }

    try
    {
        pqxx::work txn(*conn);

        // Verify sender exists and has sufficient funds
        pqxx::result senderRes = txn.exec_params(
            "SELECT balance FROM users WHERE id = $1", senderId);
        if (senderRes.empty())
        {
            std::cerr << "[ERROR] Sender does not exist.\n";
            return false;
        }

        double senderBalance = senderRes[0][0].as<double>();
        std::cerr << "[DEBUG] Sender balance: " << senderBalance << std::endl;

        if (senderBalance < amount)
        {
            std::cerr << "[ERROR] Insufficient funds: trying to send " << amount << ", but only " << senderBalance << " available.\n";
            return false;
        }

        // Verify receiver exists
        pqxx::result receiverRes = txn.exec_params(
            "SELECT id FROM users WHERE id = $1", receiverId);
        if (receiverRes.empty())
        {
            std::cerr << "[ERROR] Receiver does not exist.\n";
            return false;
        }

        // Update sender and receiver balances
        txn.exec_params(
            "UPDATE users SET balance = balance - $1 WHERE id = $2",
            amount, senderId);
        txn.exec_params(
            "UPDATE users SET balance = balance + $1 WHERE id = $2",
            amount, receiverId);

        // Record the transaction for both sender and receiver
        txn.exec_params(
            "INSERT INTO transactions (user_id, amount, type) VALUES ($1, $2, 'transfer_sent')",
            senderId, amount);
        txn.exec_params(
            "INSERT INTO transactions (user_id, amount, type) VALUES ($1, $2, 'transfer_received')",
            receiverId, amount);

        txn.commit();

        std::cerr << "[INFO] Transfer of $" << amount << " from User " << senderId << " to User " << receiverId << " complete.\n";
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR] Transfer Exception: " << e.what() << std::endl;
        return false;
    }
}