//
// Created by letit6E on 04.12.2023.
//

#ifndef TRADE_LAB_BAR_H
#define TRADE_LAB_BAR_H

#include <algorithm>
#include <cfloat>
#include <iostream>
#include <sstream>
#include <vector>

#include "trade.h"

class Bar {
   private:
    double open;             // Open price
    double close;            // Close price
    double high;             // Max price
    double low;              // Min price
    double volume;           // Trade volumes sum
    double size;             // Trade sizes sum
    double signed_volume;    // Signed volumes sum
    double signed_size;      // Signed sizes sum
    double directed_volume;  // Signed by direction volumes sum
    double directed_size;    // Signed by direction sizes sum
    double vwap;             // Volume weighted average price
    long long startstamp;    // First trade unix timestamp
    long long stopstamp;     // Last trade unix timestamp
    long long duration;      // First and last timestamps duration
    unsigned int length;     // Number of trades

    double price_volume_sum;  // Volume weighted price

   public:
    Bar(double o, double c, double h, double l, double vol, double sz,
        double s_vol, double s_sz, double d_vol, double d_sz, double vw,
        long long ss, long long es, long long dr, unsigned int len);

    Bar();

    explicit Bar(const std::vector<Trade>& trades);

    friend std::istream& operator>>(std::istream& is, Bar& bar);

    friend std::ostream& operator<<(std::ostream& os, const Bar& bar);

    double get_open() const;

    double get_close() const;
    double get_high() const;

    double get_low() const;

    double get_volume() const;

    double get_size() const;

    double get_signed_volume() const;

    double get_signed_size() const;

    double get_directed_volume() const;

    double get_directed_size() const;

    double get_vwap() const;

    long long get_startstamp() const;

    long long get_stopstamp() const;

    long long get_duration() const;

    unsigned int get_length() const;

    void add_trade(const Trade& trade);
};

class BarBuilder {
   private:
    double open, close, high, low, volume, size, signed_volume, signed_size,
        directed_volume, directed_size, vwap;
    long long startstamp, stopstamp, duration;
    unsigned int length;

   public:
    BarBuilder& set_open(double o);
    BarBuilder& set_close(double c);
    BarBuilder& set_high(double h);
    BarBuilder& set_low(double l);
    BarBuilder& set_volume(double vol);
    BarBuilder& set_size(double sz);
    BarBuilder& set_signed_volume(double s_vol);
    BarBuilder& set_signed_size(double s_sz);
    BarBuilder& set_directed_volume(double d_vol);
    BarBuilder& set_directed_size(double d_sz);
    BarBuilder& set_vwap(double vw);
    BarBuilder& set_startstamp(long long ss);
    BarBuilder& set_stopstamp(long long es);
    BarBuilder& set_duration(long long dr);
    BarBuilder& set_length(unsigned int len);

    Bar build();
};

#endif  // TRADE_LAB_BAR_H
