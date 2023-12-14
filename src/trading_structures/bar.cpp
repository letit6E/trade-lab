//
// Created by letit6E on 04.12.2023.
//

#include "bar.h"

std::istream &operator>>(std::istream &in, Bar &bar) {
    char sep;

    if (!(in >> bar.open >> sep
       >> bar.close >> sep
       >> bar.high >> sep
       >> bar.low >> sep
       >> bar.volume >> sep
       >> bar.size >> sep
       >> bar.signed_volume >> sep
       >> bar.signed_size >> sep
       >> bar.directed_volume >> sep
       >> bar.directed_size >> sep
       >> bar.vwap >> sep
       >> bar.startstamp >> sep
       >> bar.stopstamp >> sep
       >> bar.duration >> sep
       >> bar.length)) {
        in.setstate(std::ios::failbit);
    }

    bar.price_volume_sum = bar.vwap * bar.length;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Bar &bar) {
    char sep = ',';

    out << bar.open << sep
       << bar.close << sep
       << bar.high << sep
       << bar.low << sep
       << bar.volume << sep
       << bar.size << sep
       << bar.signed_volume << sep
       << bar.signed_size << sep
       << bar.directed_volume << sep
       << bar.directed_size << sep
       << bar.vwap << sep
       << bar.startstamp << sep
       << bar.stopstamp << sep
       << bar.duration << sep
       << bar.length;

    return out;
}

Bar::Bar(const std::vector<Trade> &trades) {
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

    length = trades.size();
    vwap = price_volume_sum / length;
    startstamp = trades.front().timestamp;
    stopstamp = trades.back().timestamp;
    duration = stopstamp - startstamp;
}