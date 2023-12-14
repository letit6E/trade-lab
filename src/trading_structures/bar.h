//
// Created by letit6E on 04.12.2023.
//

#ifndef TRADE_LAB_BAR_H
#define TRADE_LAB_BAR_H

#include <iostream>
#include <sstream>
#include <vector>
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

    Bar(double o, double c, double h, double l, double vol, double sz,
        double s_vol, double s_sz, double d_vol, double d_sz, double vw, long long ss, long long es, long long dr,
        unsigned int len)
            : open(o), close(c), high(h), low(l), volume(vol), size(sz),
              signed_volume(s_vol), signed_size(s_sz), directed_volume(d_vol), directed_size(d_sz), vwap(vw),
              startstamp(ss), stopstamp(es),
              duration(dr), length(len) {
        price_volume_sum = vw * len;
    }

    Bar(const std::vector<Trade> &trades) {
        if (trades.empty()) {
            throw std::invalid_argument("Trades list cannot be empty");
        }

        auto timestamp_comp = [](const Trade &a, const Trade &b) {
            return a.timestamp <= b.timestamp;
        };

        if (!std::is_sorted(trades.begin(), trades.end(), timestamp_comp)) {
            throw std::invalid_argument("Trades list must be sorted by timestamp");
        }

        auto price_comp = [](const Trade &a, const Trade &b) {
            return a.price < b.price;
        };

        open = trades.front().price;
        close = trades.back().price;
        high = std::max_element(trades.begin(), trades.end(), price_comp)->price;
        low = std::min_element(trades.begin(), trades.end(), price_comp)->price;
        volume = 0.0;
        size = 0.0;
        signed_volume = 0.0;
        signed_size = 0.0;
        directed_volume = 0.0;
        directed_size = 0.0;
        price_volume_sum = 0.0;

        double last_price = -1;
        for (const Trade &trade: trades) {
            volume += trade.volume;
            size += trade.size;
            price_volume_sum += trade.price * trade.volume;

            directed_volume += trade.direction * trade.volume;
            directed_size += trade.direction * trade.size;

            if (last_price >= 0 && trade.price != last_price) {
                int sign = (trade.price > last_price) ? 1 : -1;
                signed_volume += sign * trade.volume;
                signed_size += sign * trade.size;
            }
            last_price = trade.price;
        }

        vwap = price_volume_sum / volume;
        startstamp = trades.front().timestamp;
        stopstamp = trades.back().timestamp;
        duration = stopstamp - startstamp;
        length = trades.size();
    }

    friend std::istream &operator>>(std::istream &is, Bar &bar);

    friend std::ostream &operator<<(std::ostream &os, const Bar &bar);
};


#endif //TRADE_LAB_BAR_H
