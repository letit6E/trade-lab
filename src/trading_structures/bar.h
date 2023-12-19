//
// Created by letit6E on 04.12.2023.
//

#ifndef TRADE_LAB_BAR_H
#define TRADE_LAB_BAR_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <algorithm>
#include "trade.h"

class Bar {
private:
    double open;               // Open price
    double close;              // Close price
    double high;               // Max price
    double low;                // Min price
    double volume;             // Trade volumes sum
    double size;               // Trade sizes sum
    double signed_volume;      // Signed volumes sum
    double signed_size;        // Signed sizes sum
    double directed_volume;    // Signed by direction volumes sum
    double directed_size;      // Signed by direction sizes sum
    double vwap;               // Volume weighted average price
    long long startstamp;      // First trade unix timestamp
    long long stopstamp;       // Last trade unix timestamp
    long long duration;        // First and last timestamps duration
    unsigned int length;       // Number of trades

    double price_volume_sum;   // Volume weighted price

public:
    Bar(double o, double c, double h, double l, double vol, double sz,
        double s_vol, double s_sz, double d_vol, double d_sz, double vw, long long ss, long long es, long long dr,
        unsigned int len)
            : open(o), close(c), high(h), low(l), volume(vol), size(sz),
              signed_volume(s_vol), signed_size(s_sz), directed_volume(d_vol), directed_size(d_sz), vwap(vw),
              startstamp(ss), stopstamp(es),
              duration(dr), length(len) {
        price_volume_sum = vw * len;
    }

    Bar() : Bar(-1., -1., -1., DBL_MAX, 0, 0, 0, 0, 0, 0, 0, -1., -1., 0, 0) {};

    explicit Bar(const std::vector<Trade> &trades);

    friend std::istream &operator>>(std::istream &is, Bar &bar);

    friend std::ostream &operator<<(std::ostream &os, const Bar &bar);

    double get_open() const { return open; }

    double get_close() const { return close; }

    double get_high() const { return high; }

    double get_low() const { return low; }

    double get_volume() const { return volume; }

    double get_size() const { return size; }

    double get_signed_volume() const { return signed_volume; }

    double get_signed_size() const { return signed_size; }

    double get_directed_volume() const { return directed_volume; }

    double get_directed_size() const { return directed_size; }

    double get_vwap() const { return vwap; }

    long long get_startstamp() const { return startstamp; }

    long long get_stopstamp() const { return stopstamp; }

    long long get_duration() const { return duration; }

    unsigned int get_length() const { return length; }

    void add_trade(const Trade& trade);
};


#endif //TRADE_LAB_BAR_H
