//
// Created by letit6E on 19.12.2023.
//

#include "time_aggregator.h"

void TimeBarAggregator::receive(const Trade &trade) {
    if (trade.timestamp < cur_bar.get_stopstamp()) {
        throw std::invalid_argument("Bar aggregator receives trades only increasing over timestamp");
    }
    if (trade.timestamp > cur_bar.get_startstamp() + bar_duration) {
        if (cur_bar.get_open() <= 0) {
            cur_bar = last_bar;
        }
        bar_queue.push(cur_bar);
        last_bar = cur_bar;
        cur_bar = Bar();
    }
    cur_bar.add_trade(trade);
}

bool TimeBarAggregator::ready() {
    return !bar_queue.empty() || cur_bar.get_open() > 0;
}

Bar TimeBarAggregator::publish() {
    if (ready()) {
        Bar published_bar;
        if (!bar_queue.empty()) {
            published_bar = bar_queue.front();
            bar_queue.pop();
        } else {
            published_bar = cur_bar;
        }
        return published_bar;
    } else {
        throw std::runtime_error("There are no ready bars to publish.");
    }
}
