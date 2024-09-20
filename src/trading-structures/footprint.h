//
// Created by letit6E on 12.08.2024.
//

#ifndef TRADE_LAB_FOOTPRINT_H

#include <iostream>
#include <sstream>
#include <string>

class Footprint {
   private:
    long long id;  // timestamp or another
    double price_min;
    double price_max;
    double buy_volume;
    double sell_volume;
    unsigned buy_ticks;
    unsigned sell_ticks;

   public:
    Footprint(long long id, double p_min, double p_max, double buy_v,
              double sell_v, unsigned buy_t, unsigned sell_t);
    Footprint();

    long long get_id() const;
    double get_price_min() const;
    double get_price_max() const;
    double get_buy_volume() const;
    double get_sell_volume() const;
    unsigned get_buy_ticks() const;
    unsigned get_sell_ticks() const;

    friend std::istream& operator>>(std::istream& is, Footprint& fp);
    friend std::ostream& operator<<(std::ostream& os, const Footprint& fp);
};

class FootprintBuilder {
   private:
    long long id;
    double price_min;
    double price_max;
    double buy_volume;
    double sell_volume;
    unsigned buy_ticks;
    unsigned sell_ticks;

   public:
    FootprintBuilder& set_id(long long id);
    FootprintBuilder& set_price_min(double p_min);
    FootprintBuilder& set_price_max(double p_max);
    FootprintBuilder& set_buy_volume(double buy_v);
    FootprintBuilder& set_sell_volume(double sell_v);
    FootprintBuilder& set_buy_ticks(unsigned buy_t);
    FootprintBuilder& set_sell_ticks(unsigned sell_t);

    Footprint build();
};

#define TRADE_LAB_FOOTPRINT_H

#endif  // TRADE_LAB_FOOTPRINT_H
