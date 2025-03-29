#include "../../include/routes/handlers.hpp"
#include "../../include/db.hpp"
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp> // JSON library

namespace http = boost::beast::http;
using json = nlohmann::json;

std::string getQueryParam(const std::string &query, const std::string &key)
{
    std::size_t keyPos = query.find(key + "=");
    if (keyPos == std::string::npos)
        return "";
    std::size_t valueStart = keyPos + key.length() + 1;
    std::size_t valueEnd = query.find("&", valueStart);
    if (valueEnd == std::string::npos)
        valueEnd = query.length();
    return query.substr(valueStart, valueEnd - valueStart);
}

void handle_request(const http::request<http::string_body> &req,
                    http::response<http::string_body> &res)
{

    std::string target(req.target());
    std::cout << "[DEBUG] Received target: " << target << std::endl;

    DB db;

    if (req.method() == http::verb::get && target.find("/balance") != std::string::npos)
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

        double balance = db.getBalance(userId);
        std::stringstream ss;
        ss << "{\"balance\": " << balance << "}";
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = ss.str();
    }

    else if (req.method() == http::verb::post && target.find("/deposit") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            int userId = body.at("userId").get<int>();
            double amount = body.at("amount").get<double>();

            bool success = db.deposit(userId, amount);
            res.result(success ? http::status::ok : http::status::bad_request);
            res.body() = success ? "Deposit successful" : "Deposit failed";
        }
        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload";
        }
    }
    else if (req.method() == http::verb::post && target.find("/withdraw") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            int userId = body.at("userId").get<int>();
            double amount = body.at("amount").get<double>();

            bool success = db.withdraw(userId, amount);
            res.result(success ? http::status::ok : http::status::bad_request);
            res.body() = success ? "Withdrawal successful" : "Withdrawal failed";
        }
        catch (const std::exception &e)
        {
            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload";
        }
    }
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
    else if (req.method() == http::verb::post && target.find("/createUser") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            std::string name = body.at("name").get<std::string>();
            double initialBalance = body.at("initialBalance").get<double>();

            bool success = db.createUser(name, initialBalance);
            res.result(success ? http::status::ok : http::status::bad_request);
            res.body() = success ? "User created successfully" : "Failed to create user";
        }
        catch (const std::exception &e)
        {
            std::cerr << "❌ JSON Parse Error (createUser): " << e.what() << std::endl;
            res.result(http::status::bad_request);
            res.body() = "Invalid JSON payload for user creation";
        }
    }

    else
    {
        res.result(http::status::not_found);
        res.body() = "Endpoint not found";
    }

    res.prepare_payload();
}
