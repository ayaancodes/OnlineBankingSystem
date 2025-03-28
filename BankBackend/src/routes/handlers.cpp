#include "../../include/routes/handlers.hpp"
#include "../../include/db.hpp"
#include <sstream>
#include <iostream> // For logging

namespace http = boost::beast::http;

void handle_request(const http::request<http::string_body>& req,
                    http::response<http::string_body>& res) {
    // Log the incoming target for debugging
    std::string target(req.target());
    std::cout << "[DEBUG] Received target: " << target << std::endl;
    
    // Instantiate DB
    DB db;

    if (req.method() == http::verb::get && target.find("/balance") != std::string::npos) {
        int userId = 1;
        double balance = db.getBalance(userId);
        std::stringstream ss;
        ss << "{\"balance\": " << balance << "}";
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = ss.str();
    } else if (req.method() == http::verb::post && target.find("/deposit") != std::string::npos) {
        int userId = 1;         // placeholder
        double amount = 100.0;    // placeholder
        bool success = db.deposit(userId, amount);
        res.result(success ? http::status::ok : http::status::bad_request);
        res.body() = success ? "Deposit successful" : "Deposit failed";
    } else if (req.method() == http::verb::post && target.find("/withdraw") != std::string::npos) {
        int userId = 1;         // placeholder
        double amount = 50.0;    // placeholder
        bool success = db.withdraw(userId, amount);
        res.result(success ? http::status::ok : http::status::bad_request);
        res.body() = success ? "Withdrawal successful" : "Withdrawal failed";
    } else {
        res.result(http::status::not_found);
        res.body() = "Endpoint not found";
    }
    
    res.prepare_payload();
}
