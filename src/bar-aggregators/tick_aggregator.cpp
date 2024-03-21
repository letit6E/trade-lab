//
// Created by letit6E on 19.12.2023.
//

#include "tick_aggregator.h"

TickBarAggregator::TickBarAggregator(long long bar_length)
    : bar_length(bar_length), last_timestamp(-1) {}

void TickBarAggregator::receive(const Trade &trade) {
    if (trade.timestamp < last_timestamp) {
        throw std::invalid_argument(
            "Bar aggregator receives trades only increasing over timestamp");
    }
    last_timestamp = trade.timestamp;
    if (cur_bar.get_length() == bar_length) {
        bar_queue.push(cur_bar);
        cur_bar = Bar();
    }
    cur_bar.add_trade(trade);
}

bool TickBarAggregator::ready() {
    return !bar_queue.empty() || cur_bar.get_length() == bar_length;
}

Bar TickBarAggregator::publish() {
    if (ready()) {
        Bar published_bar;
        if (bar_queue.empty()) {
            published_bar = cur_bar;
            cur_bar = Bar();
        } else {
            published_bar = bar_queue.front();
            bar_queue.pop();
        }
        return published_bar;
    } else {
        throw std::runtime_error("There are no ready bars to publish.");
    }
}