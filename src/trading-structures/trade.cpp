//
// Created by letit6E on 03.12.2023.
//
#include "trade.h"

std::istream &operator>>(std::istream &is, Trade &tr) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    char sep;

    if (!(iss >> tr.timestamp >> sep >> tr.price >> sep >>
          tr.size >> sep >> tr.direction)) {
        is.setstate(std::ios::failbit);
    } else {
		tr.volume = tr.price * tr.size;
	}

    return is;
}

std::ostream &operator<<(std::ostream &os, const Trade &tr) {
    char sep = ',';

    os << tr.timestamp << sep << tr.price << sep << tr.size << sep << tr.volume
       << sep << (tr.direction == 1 ? "1" : "-1");
    return os;
}

Trade::Trade(long long t, double p, double s, double v, int d)
    : timestamp(t), price(p), size(s), volume(v), direction(d) {}

Trade::Trade() : Trade(0, 0, 0, 0, 0) {}

TradeBuilder &TradeBuilder::set_timestamp(long long int ts) {
    timestamp = ts;
    return *this;
}

TradeBuilder &TradeBuilder::set_size(double sz) {
    size = sz;
    return *this;
}

TradeBuilder &TradeBuilder::set_price(double p) {
    price = p;
    return *this;
}

TradeBuilder &TradeBuilder::set_volume(double vlm) {
    volume = vlm;
    return *this;
}

TradeBuilder &TradeBuilder::set_direction(int drct) {
    direction = drct;
    return *this;
}

Trade TradeBuilder::build() {
    return Trade(timestamp, price, size, volume, direction);
}
