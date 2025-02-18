//
// Created by letit6E on 19.12.2023.
//

#include "tick_aggregator.h"

TickBarAggregator::TickBarAggregator(long long bar_length)
    : bar_length(bar_length), last_timestamp(-1) {}

void TickBarAggregator::receive(const Trade &trade) {
    if (trade.get_timestamp() < last_timestamp) {
        throw std::invalid_argument(
            "Bar aggregator receives trades only increasing over timestamp");
    }
    last_timestamp = trade.get_timestamp();
    if (cur_bar.get_length() == bar_length) {
        bar_queue.push(cur_bar);
        cur_bar = Bar();
    }
    cur_bar.add_trade(trade);
}
