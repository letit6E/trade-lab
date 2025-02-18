//
// Created by letit6E on 19.12.2023.
//

#include "time_aggregator.h"

TimeBarAggregator::TimeBarAggregator(long long duration)
    : bar_duration(duration), last_timestamp(-1) {}

void TimeBarAggregator::receive(const Trade &trade) {
    if (trade.get_timestamp() < last_timestamp) {
        throw std::invalid_argument(
            "Bar aggregator receives trades only increasing over timestamp");
    }
    last_timestamp = trade.get_timestamp();
    if (trade.get_timestamp() > cur_bar.get_startstamp() + bar_duration &&
        cur_bar.get_open() > 0) {
        if (cur_bar.get_open() <= 0) {
            cur_bar = Bar(last_bar.get_close(), last_bar.get_close(),
                          last_bar.get_close(), last_bar.get_close(), 0, 0, 0,
                          0, 0, 0, last_bar.get_close(),
                          last_bar.get_stopstamp(), last_timestamp,
                          last_timestamp - last_bar.get_stopstamp(), 0);
        }
        bar_queue.push(cur_bar);
        last_bar = cur_bar;
        cur_bar = Bar();
    }
    cur_bar.add_trade(trade);
}
