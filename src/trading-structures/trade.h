#ifndef TRADE_LAB_TRADE_H
#define TRADE_LAB_TRADE_H

#include <iostream>
#include <sstream>
#include <string>

class Trade {
   public:
    long long timestamp;  // Unix timestamp
    double price;
    double size;
    double volume;
    int direction;

    Trade(long long t, double p, double s, double v, int d);
    Trade();

    friend std::istream& operator>>(std::istream& is, Trade& tr);
    friend std::ostream& operator<<(std::ostream& os, const Trade& tr);
};

class TradeBuilder {
   private:
    long long timestamp;  // Unix timestamp
    double price;
    double size;
    double volume;
    int direction;

   public:
    TradeBuilder& set_timestamp(long long ts);
    TradeBuilder& set_price(double p);
    TradeBuilder& set_size(double sz);
    TradeBuilder& set_volume(double vlm);
    TradeBuilder& set_direction(int drct);

    Trade build();
};

#endif  // TRADE_LAB_TRADE_H
