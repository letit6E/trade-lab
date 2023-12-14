//
// Created by letit6E on 04.12.2023.
//

#ifndef TRADE_LAB_BAR_H
#define TRADE_LAB_BAR_H

#include <vector>
#include <algorithm>
#include "trade.h"

class Bar {
public:
    double open, close, high, low;
    double volume, size, signed_volume, signed_size, vwap;
    long long startstamp, stopstamp, duration;
    size_t length;

    Bar() : open(0), close(0), high(0), low(0), volume(0), size(0),
            signed_volume(0), signed_size(0), vwap(0),
            startstamp(0), stopstamp(0), duration(0), length(0) {}

    Bar(const std::vector<Trade>& trades) {
        if (trades.empty()) {
            throw std::invalid_argument("Trades vector cannot be empty");
        }

        high = std::max_element(trades.begin(), trades.end(),
                                [](const Trade& a, const Trade& b) {
                                    return a.price < b.price; })->price;
        low = std::min_element(trades.begin(), trades.end(),
                               [](const Trade& a, const Trade& b) {
                                   return a.price < b.price; })->price;
        open = trades.front().price;
        close = trades.back().price;

        volume = 0;
        size = 0;
        signed_volume = 0;
        signed_size = 0;
        double price_volume_total = 0;

        for (const Trade& trade : trades) {
            volume += trade.size;
            signed_volume += trade.size * trade.direction;
            size += trade.volume;
            signed_size += trade.volume * trade.direction;
            price_volume_total += trade.price * trade.size;
        }

        vwap = price_volume_total / volume;

        startstamp = trades.front().timestamp;
        stopstamp = trades.back().timestamp;
        duration = stopstamp - startstamp;
        length = trades.size();
    }

    friend std::istream& operator>>(std::istream& is, Bar& tr);
    friend std::ostream& operator<<(std::ostream& os, const Bar& tr);
};

#endif //TRADE_LAB_BAR_H
