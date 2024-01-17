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

    Trade(long long t, double p, double s, double v, int d)
        : timestamp(t), price(p), size(s), volume(v), direction(d) {}

    Trade() : Trade(0, 0, 0, 0, 0) {}

    friend std::istream& operator>>(std::istream& is, Trade& tr);
    friend std::ostream& operator<<(std::ostream& os, const Trade& tr);
};

#endif  // TRADE_LAB_TRADE_H
