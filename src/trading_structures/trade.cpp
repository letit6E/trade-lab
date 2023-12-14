//
// Created by letit6E on 03.12.2023.
//
#include "trade.h"

std::istream &operator>>(std::istream &is, Trade &tr) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    char sep;

    iss >> tr.timestamp >> sep
        >> tr.price >> sep
        >> tr.volume >> sep
        >> tr.direction;

    return is;
}

std::ostream &operator<<(std::ostream &os, const Trade &tr) {
    char sep = ',';

    os << tr.timestamp << sep
       << tr.price << sep
       << tr.size << sep
       << tr.volume << sep
       << (tr.direction == 1 ? "1" : "-1");
    return os;
}