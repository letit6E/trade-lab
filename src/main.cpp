#include <iostream>

#include "collectors/exchange.h"

int main() {
    Exchange bybit{"bybit", "stream-testnet.bybit.com"};

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
                std::cout << tr << std::endl;
            }

            bybit.buffer_clear();
        }
        bybit.webSocket_close();
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
