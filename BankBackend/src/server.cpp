#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>
#include "../include/routes/handlers.hpp"

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

void do_session(tcp::socket socket)
{
    try
    {
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        http::response<http::string_body> res;
        handle_request(req, res);
        http::write(socket, res);
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Session error: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        std::cerr << "🔥 MAIN() REACHED 🔥\n";
        boost::asio::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}};

        std::cout << "🚀 Server running on http://localhost:8080\n";

        for (;;)
        {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread([sock = std::move(socket)]() mutable
                        { do_session(std::move(sock)); })
                .detach();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Server error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
