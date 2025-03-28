#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

void handle_request(const http::request<http::string_body>& req,
                    http::response<http::string_body>& res);

#endif
