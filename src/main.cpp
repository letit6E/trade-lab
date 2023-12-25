#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <functional>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "trade.h"

class BybitWebSocketClient {
private:
    client m_client;
    websocketpp::connection_hdl m_hdl;
    std::vector<Trade> m_trades;

public:
    BybitWebSocketClient() {
        m_client.init_asio();
        m_client.set_tls_init_handler(bind(&BybitWebSocketClient::on_tls_init, this, ::_1));
        m_client.set_message_handler(bind(&BybitWebSocketClient::on_message, this, ::_1, ::_2));
    }

    void connect(const std::string& uri) {
        websocketpp::lib::error_code ec;
        client::connection_ptr con = m_client.get_connection(uri, ec);
        if (ec) {
            throw std::runtime_error("Failed to get connection: " + ec.message());
        }

        m_hdl = con->get_handle();
        m_client.connect(con);
        m_client.run();
    }

    void disconnect() {
        m_client.close(m_hdl, websocketpp::close::status::normal, "Client disconnecting");
    }

    std::vector<Trade> get_trades() const {
        return m_trades;
    }

private:
    void on_tls_init(websocketpp::connection_hdl hdl) {
        client::connection_ptr con = m_client.get_con_from_hdl(hdl);
        con->set_tls_init_handler(bind(&BybitWebSocketClient::on_tls_init_handler, this, ::_1));
    }

    void on_tls_init_handler(websocketpp::connection_hdl hdl) {
        // TODO: Implement TLS initialization if needed
    }

    void on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
        std::istringstream iss(msg->get_payload());
        Trade trade;
        if (iss >> trade) {
            m_trades.push_back(trade);
        }
    }
};

int main() {

}