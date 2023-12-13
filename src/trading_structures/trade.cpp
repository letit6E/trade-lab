//
// Created by letit6E on 03.12.2023.
//
#include "trade.h"

std::istream& operator>>(std::istream& is, Trade& tr) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    char delimiter;

    if (!(iss >> tr.timestamp >> delimiter
          && delimiter == ','
          && iss >> tr.price >> delimiter
          && delimiter == ','
          && iss >> tr.size >> delimiter
          && delimiter == ','
          && iss >> tr.volume >> delimiter
          && delimiter == ','
          && iss >> tr.direction)) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Trade& tr) {
    os << tr.timestamp << ','
       << tr.price << ','
       << tr.size << ','
       << tr.volume << ','
       << (tr.direction == 1 ? "1" : "-1");
    return os;
}