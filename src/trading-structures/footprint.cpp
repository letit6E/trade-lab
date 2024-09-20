//
// Created by letit6E on 12.08.2024.
//

#include "footprint.h"

std::istream &operator>>(std::istream &is, Footprint &fp) {
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    char sep;

    if (!(iss >> fp.id >> sep >> fp.price_min >> sep >> fp.price_max >> sep >>
          fp.buy_volume >> sep >> fp.sell_volume >> sep >> fp.buy_ticks >>
          sep >> fp.sell_ticks)) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Footprint &fp) {
    char sep = ',';

    os << fp.get_id() << sep << fp.get_price_min() << sep << fp.get_price_max()
       << sep << fp.get_buy_volume() << sep << fp.get_sell_volume() << sep
       << fp.get_buy_ticks() << sep << fp.get_sell_ticks();
    return os;
}

Footprint::Footprint(long long id, double p_min, double p_max, double buy_v,
                     double sell_v, unsigned buy_t, unsigned sell_t)
    : id(id),
      price_min(p_min),
      price_max(p_max),
      buy_volume(buy_v),
      sell_volume(sell_v),
      buy_ticks(buy_t),
      sell_ticks(sell_t) {}

Footprint::Footprint() : Footprint(0, 0, 0, 0, 0, 0, 0) {}

// Getters
long long Footprint::get_id() const { return id; }

double Footprint::get_price_min() const { return price_min; }

double Footprint::get_price_max() const { return price_max; }

double Footprint::get_buy_volume() const { return buy_volume; }

double Footprint::get_sell_volume() const { return sell_volume; }

unsigned Footprint::get_buy_ticks() const { return buy_ticks; }

unsigned Footprint::get_sell_ticks() const { return sell_ticks; }

FootprintBuilder &FootprintBuilder::set_id(long long id) {
    this->id = id;
    return *this;
}

FootprintBuilder &FootprintBuilder::set_price_min(double p_min) {
    price_min = p_min;
    return *this;
}

FootprintBuilder &FootprintBuilder::set_price_max(double p_max) {
    price_max = p_max;
    return *this;
}

FootprintBuilder &FootprintBuilder::set_buy_volume(double buy_v) {
    buy_volume = buy_v;
    return *this;
}

FootprintBuilder &FootprintBuilder::set_sell_volume(double sell_v) {
    sell_volume = sell_v;
    return *this;
}

FootprintBuilder &FootprintBuilder::set_buy_ticks(unsigned buy_t) {
    buy_ticks = buy_t;
    return *this;
}

FootprintBuilder &FootprintBuilder::set_sell_ticks(unsigned sell_t) {
    sell_ticks = sell_t;
    return *this;
}

Footprint FootprintBuilder::build() {
    return Footprint(id, price_min, price_max, buy_volume, sell_volume,
                     buy_ticks, sell_ticks);
}