#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>
#include <json/json.h>
#include <functional>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class connection_metadata {
public:
    typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

    connection_metadata(websocketpp::connection_hdl hdl, std::string uri)
            : m_hdl(hdl), m_status("Connecting"), m_uri(uri), m_server("N/A") {}

    void on_open(client* c, websocketpp::connection_hdl hdl) {
        m_status = "Open";
        std::cout << "> Connection opened to: " << m_uri << std::endl;

        // Subscribe to trade topic
        std::string msg = "{\"op\":\"subscribe\",\"args\":[\"trade.BTCUSDT\"]}";
        c->send(hdl, msg, websocketpp::frame::opcode::text);
    }

    void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
        if (msg->get_opcode() == websocketpp::frame::opcode::text) {
            std::cout << "Received message: " << msg->get_payload() << std::endl;
        }
    }

    websocketpp::connection_hdl get_hdl() const {
        return m_hdl;
    }

    std::string get_status() const {
        return m_status;
    }

private:
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
};

int main(int argc, char* argv[]) {
    client c;

    std::string uri = "wss://stream.bybit.com/realtime_public"; // api key needed

    try {
        c.set_access_channels(websocketpp::log::alevel::all);
        c.clear_access_channels(websocketpp::log::alevel::frame_payload);

        c.init_asio();

        sockaddr metadata = sockaddr();
        c.set_open_handler(bind(&connection_metadata::on_open, &metadata, &c, ::_1));
        c.set_message_handler(bind(&connection_metadata::on_message, &metadata, ::_1, ::_2));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(uri, ec);

        if (ec) {
            std::cout << "> Connect initialization error: " << ec.message() << std::endl;
            return -1;
        }

        c.connect(con);
        c.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
    return 0;
}