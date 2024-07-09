<<<<<<< HEAD
#include <chrono>
#include <iostream>
=======
#include <fstream>
>>>>>>> temp
#include <pqxx/pqxx>

#include "collectors/exchange.h"
#include "db-connectors/postgres_connector.h"

int main() {
    Exchange bybit{"bybit", "stream-testnet.bybit.com"};

    unsigned int count = 0, limit = 100;
    std::string file_name = "trades.csv";
    std::ofstream trades(file_name);
    trades << std::fixed << std::setprecision(20);
    try {
        bybit.init_webSocket("stream-testnet.bybit.com", "443",
                             "/v5/public/linear");
        if (bybit.is_socket_open()) {
            std::string subscription_message =
                R"({"op": "subscribe", "args":
                                ["orderbook.50.BTCUSDT"]})";
            bybit.write_Socket(subscription_message);
        }

        auto start = std::chrono::high_resolution_clock::now();
        while (true) {
            bybit.read_Socket();
            auto vec = bybit.get_socket_trades();
            for (const auto& tr : vec) {
                ++count;
                trades << tr << '\n';
            }

            bybit.buffer_clear();
            if (count > limit) break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << trades.size() / duration.count() << std::endl;
        bybit.webSocket_close();
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    //    PostgresConnector connector("postgres", "postgres", "postgres");
    //    connector.insert_trades("trades", trades);

    trades.close();
    return 0;
}