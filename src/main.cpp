#include <iostream>
#include <pqxx/pqxx>

#include "collectors/exchange.h"
#include "db-connectors/postgres_connector.h"

int main() {
    Exchange bybit{"bybit", "stream-testnet.bybit.com"};

    std::vector<Trade> trades;
    try {
        bybit.init_webSocket("stream-testnet.bybit.com", "443",
                             "/v5/public/linear");
        if (bybit.is_socket_open()) {
            std::string subscription_message =
                R"({"op": "subscribe", "args":
                                ["orderbook.50.BTCUSDT"]})";
            bybit.write_Socket(subscription_message);
        }
        while (true) {
            bybit.read_Socket();
            auto vec = bybit.get_socket_trades();
            for (const auto& tr : vec) {
                trades.push_back(tr);
            }

            bybit.buffer_clear();
            if (trades.size() > 10) break;
        }
        bybit.webSocket_close();
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    PostgresConnector connector("postgres", "postgres", "postgres");
    connector.insert_trades("trades", trades);

    return 0;
}
