//
// Created by letit6E on 13.01.2024.
//

#include "exchange.h"

#include <iostream>

Exchange::Exchange(std::string name, const std::string &http_host)
    : m_name(std::move(name)) {
    init_http(http_host);
}

void Exchange::init_http(std::string const &host) {
    const auto results{resolver.resolve(host, "443")};
    get_lowest_layer(stream).connect(results);
    // Set SNI Hostname (many hosts need this to handshake successfully)
    if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
        boost::system::error_code ec{static_cast<int>(::ERR_get_error()),
                                     boost::asio::error::get_ssl_category()};
        throw boost::system::system_error{ec};
    }
    stream.handshake(ssl::stream_base::client);
}

void Exchange::init_webSocket(std::string const &host, std::string const &port,
                              const char *p = "") {
    // Set SNI Hostname (many hosts need this to handshake successfully)
    if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(),
                                  host.c_str()))
        throw beast::system_error(
            beast::error_code(static_cast<int>(::ERR_get_error()),
                              net::error::get_ssl_category()),
            "Failed to set SNI Hostname");
    auto const results = resolver_webSocket.resolve(host, port);
    net::connect(ws.next_layer().next_layer(), results.begin(), results.end());
    ws.next_layer().handshake(ssl::stream_base::client);

    ws.handshake(host, p);
}

void Exchange::read_Socket() { ws.read(buffer); }

bool Exchange::is_socket_open() { return ws.is_open(); }

void Exchange::write_Socket(const std::string &text) {
    ws.write(net::buffer(text));
}

simdjson::dom::element Exchange::get_socket_data() {
    simdjson::dom::element result =
        parser_json.parse(beast::buffers_to_string(buffer.data()));
    return result;
}

void Exchange::add_socket_trades(simdjson::dom::element json,
                                 std::vector<Trade> &vec, int direction,
                                 int64_t timestamp) {
    for (simdjson::dom::element record : json.get<simdjson::dom::array>()) {
        std::vector<std::string> record_data;
        for (simdjson::dom::element data : record.get<simdjson::dom::array>()) {
            record_data.push_back(std::string(data));
        }

        std::string price = record_data[0];
        double new_size = std::stod(record_data[1]);

        if (bid_buffer.find(price) == bid_buffer.cend()) {
            bid_buffer[price] = new_size;
            continue;
        }

        double diff_size = bid_buffer[price] - new_size;

        if (new_size == 0.0) {
            bid_buffer.erase(price);
        } else {
            bid_buffer[price] = new_size;
        }

        double trade_price = std::stod(price), trade_size = diff_size,
               trade_volume = trade_price * trade_size;
        vec.emplace_back(timestamp, trade_price, trade_size, trade_volume,
                         direction);
    }
}

std::vector<Trade> Exchange::get_socket_trades() {
    std::vector<Trade> result;
    auto json = get_socket_data();

    int64_t timestamp;
    if (json["ts"].get(timestamp) != simdjson::SUCCESS) return result;

    add_socket_trades(json["data"]["b"], result, 1, timestamp);
    add_socket_trades(json["data"]["a"], result, -1, timestamp);
    return result;
}

void Exchange::buffer_clear() { buffer.clear(); }

void Exchange::webSocket_close() { ws.close(websocket::close_code::none); }