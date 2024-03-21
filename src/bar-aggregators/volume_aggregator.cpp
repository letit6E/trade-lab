//
// Created by letit6E on 10.05.2024.
//

#include "volume_aggregator.h"

VolumeBarAggregator::VolumeBarAggregator(double volume_duration)
    : volume_duration(volume_duration), last_timestamp(-1) {}

void VolumeBarAggregator::receive(const Trade &trade) {
    if (trade.timestamp < last_timestamp) {
        throw std::invalid_argument(
            "Bar aggregator receives trades only increasing over timestamp");
    }
    last_timestamp = trade.timestamp;
    if (trade.volume + cur_bar.get_volume() > volume_duration &&
        cur_bar.get_open() > 0) {
        bar_queue.push(cur_bar);
        cur_bar = Bar();
    }
    cur_bar.add_trade(trade);
}

bool VolumeBarAggregator::ready() { return !bar_queue.empty(); }

Bar VolumeBarAggregator::publish() {
    if (ready()) {
        Bar published_bar = bar_queue.front();
        bar_queue.pop();
        return published_bar;
    }

    if (cur_bar.get_open() >
        0) {  // user don't check ready(), force publish cur_bar
        Bar result = cur_bar;
        cur_bar = Bar();
        return result;
    }

    throw std::runtime_error("There are no ready bars to publish.");
}
