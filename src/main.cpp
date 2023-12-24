#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <functional>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

typedef websocketpp::client<websocketpp::config::asio_client> WebSocketClient;
typedef WebSocketClient::message_ptr MessagePtr;

class BybitWsClient {
public:
    BybitWsClient(const std::string& uri) : m_uri(uri), m_isConnected(false), m_thread(nullptr) {}

    ~BybitWsClient() {
        stop();
    }

    void start() {
        m_client->init_asio();
        m_client->start_perpetual();

        m_client->set_open_handler(std::bind(&BybitWsClient::on_open, this, std::placeholders::_1));
        m_client->set_message_handler(std::bind(&BybitWsClient::on_message, this, std::placeholders::_1, std::placeholders::_2));
        m_client->set_close_handler(std::bind(&BybitWsClient::on_close, this, std::placeholders::_1));

        websocketpp::lib::error_code ec;
        WebSocketClient::connection_ptr conn_ptr;

        if (ec) {
            std::cerr << "> Connect initialization error: " << ec.message() << std::endl;
            return;
        }

        m_isConnected = true;
        m_thread = new std::thread([this](){ m_client->run(); });
    }

    void stop() {
        m_client->stop_perpetual();

        if (m_thread) {
            if (m_isConnected) {
                websocketpp::lib::error_code ec;
                //m_client->close(m_hdl, websocketpp::close::status::going_away, "", ec);
            }
            m_thread->join();
            delete m_thread;
            m_thread = nullptr;
        }
    }

    std::string get_trades() {
        std::unique_lock<std::mutex> lock(m_tradeMutex);
        m_condVar.wait(lock, [&](){ return !m_trades.empty(); });

        std::string trade = m_trades.front();
        m_trades.pop();

        return trade;
    }

private:
    WebSocketClient* m_client;
    std::string m_uri;
    std::thread* m_thread;
    websocketpp::connection_hdl m_hdl;
    bool m_isConnected;

    std::queue<std::string> m_trades;
    std::mutex m_tradeMutex;
    std::condition_variable m_condVar;

    void on_open(websocketpp::connection_hdl hdl) {
        m_hdl = hdl;
        // Subscribe to trade channel (replace "trade.BTCUSD" with actual channel)
        m_client->send(hdl, R"({"op":"subscribe","args":["trade.BTCUSD"]})", websocketpp::frame::opcode::text);
    }

    void on_message(websocketpp::connection_hdl, MessagePtr message) {
        std::lock_guard<std::mutex> lock(m_tradeMutex);
        m_trades.push(message->get_payload());
        m_condVar.notify_one();
    }

    void on_close(websocketpp::connection_hdl) {
        m_isConnected = false;
    }
};

int main() {
    BybitWsClient wsClient("wss://stream.bybit.com/realtime");
    wsClient.start();

    // Get trades in a loop for demonstration purposes
    for (int i = 0; i < 10; ++i) {
        std::string trade = wsClient.get_trades();
        std::cout << "Trade: " << trade << std::endl;
    }

    wsClient.stop();
    return 0;
}