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

    // ✅ Add CORS headers to every response -Abdul
    res.set(http::field::access_control_allow_origin, "*");
    res.set(http::field::access_control_allow_methods, "GET, POST, OPTIONS");
    res.set(http::field::access_control_allow_headers, "Content-Type");

    // ✅ Handle CORS preflight requests -Abdul
    if (req.method() == http::verb::options) {
        res.result(http::status::no_content); // 204
        res.prepare_payload();
        return;
    }

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

    else if (req.method() == http::verb::post && target.find("/withdraw") != std::string::npos)
    {
        try
        {
            json body = json::parse(req.body());
            int userId = body.at("userId").get<int>();
            double amount = body.at("amount").get<double>();

            bool success = db.withdraw(userId, amount);
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

    else
    {
        std::cerr << "[DEBUG] No matching endpoint for: " << target << std::endl;
        res.result(http::status::not_found);
        res.body() = "Endpoint not found";
    }

    res.prepare_payload();
}
