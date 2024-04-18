//
// Created by letit6E on 04.12.2023.
//

#include "bar.h"

Bar::Bar(double o, double c, double h, double l, double vol, double sz,
         double s_vol, double s_sz, double d_vol, double d_sz, double vw,
         long long ss, long long es, long long dr, unsigned int len)
    : open(o),
      close(c),
      high(h),
      low(l),
      volume(vol),
      size(sz),
      signed_volume(s_vol),
      signed_size(s_sz),
      directed_volume(d_vol),
      directed_size(d_sz),
      vwap(vw),
      startstamp(ss),
      stopstamp(es),
      duration(dr),
      length(len) {
    price_volume_sum = vw * len;
}

Bar::Bar() : Bar(-1., -1., -1., DBL_MAX, 0, 0, 0, 0, 0, 0, 0, -1., -1., 0, 0){};

std::istream& operator>>(std::istream& in, Bar& bar) {
    char sep;

    if (!(in >> bar.open >> sep >> bar.close >> sep >> bar.high >> sep >>
          bar.low >> sep >> bar.volume >> sep >> bar.size >> sep >>
          bar.signed_volume >> sep >> bar.signed_size >> sep >>
          bar.directed_volume >> sep >> bar.directed_size >> sep >> bar.vwap >>
          sep >> bar.startstamp >> sep >> bar.stopstamp >> sep >>
          bar.duration >> sep >> bar.length)) {
        in.setstate(std::ios::failbit);
    }

    bar.price_volume_sum = bar.vwap * bar.length;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Bar& bar) {
    char sep = ',';

    out << bar.open << sep << bar.close << sep << bar.high << sep << bar.low
        << sep << bar.volume << sep << bar.size << sep << bar.signed_volume
        << sep << bar.signed_size << sep << bar.directed_volume << sep
        << bar.directed_size << sep << bar.vwap << sep << bar.startstamp << sep
        << bar.stopstamp << sep << bar.duration << sep << bar.length;

    return out;
}

Bar::Bar(const std::vector<Trade>& trades) : Bar() {
    if (trades.empty()) {
        throw std::invalid_argument("Trades list cannot be empty");
    }

    auto timestamp_comp = [](const Trade& a, const Trade& b) {
        return a.timestamp <= b.timestamp;
    };
    if (!std::is_sorted(trades.begin(), trades.end(), timestamp_comp)) {
        throw std::invalid_argument("Trades list must be sorted by timestamp");
    }

    for (const Trade& trade : trades) {
        add_trade(trade);
    }
}

void Bar::add_trade(const Trade &trade) {
    if (trade.timestamp < stopstamp) {
        throw std::invalid_argument(
            "Trade must be completed later than last trade in bar");
    }

    if (close >= 0 && trade.price != close) {
        int sign = (trade.price > close) ? 1 : -1;
        signed_volume += sign * trade.volume;
        signed_size += sign * trade.size;
    }
    if (open < 0) {
        open = trade.price;
    }
    close = trade.price;
    volume += trade.volume;
    size += trade.size;
    price_volume_sum += trade.price * trade.volume;
    directed_volume += trade.direction * trade.volume;
    directed_size += trade.direction * trade.size;
    high = std::max(high, trade.price);
    low = std::min(low, trade.price);
    ++length;
    vwap = price_volume_sum / length;
    if (startstamp < 0) {
        startstamp = trade.timestamp;
    }
    stopstamp = trade.timestamp;
    duration = stopstamp - startstamp;
}