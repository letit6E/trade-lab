//
// Created by letit6E on 13.01.2024.
//

#ifndef TRADE_LAB_EXCHANGE_H
#define TRADE_LAB_EXCHANGE_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

#include "json/json.h"

namespace net = boost::asio;
namespace ssl = net::ssl;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;

using tcp = net::ip::tcp;
using Request = http::request<http::string_body>;
using Stream = beast::ssl_stream<beast::tcp_stream>;
using Response = http::response<http::dynamic_body>;

class Exchange {
   public:
    Exchange(std::string name, const std::string &http_host);

    void init_http(std::string const &host);
    void init_webSocket(std::string const &host, std::string const &port,
                        const char *p);

    void read_Socket();

    bool is_socket_open();

    void write_Socket(const std::string &text);

    Json::Value get_socket_data();

    void buffer_clear();

    void webSocket_close();

   private:
    std::string m_name;
    net::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    tcp::resolver resolver{ioc};
    Stream stream{ioc, ctx};
    std::string m_web_socket_host;
    std::string m_web_socket_port;
    beast::flat_buffer buffer;
    net::io_context ioc_webSocket;
    ssl::context ctx_webSocket{ssl::context::tlsv12_client};
    tcp::resolver resolver_webSocket{ioc_webSocket};
    websocket::stream<beast::ssl_stream<tcp::socket>> ws{ioc_webSocket,
                                                         ctx_webSocket};
};

#endif  // TRADE_LAB_EXCHANGE_H
