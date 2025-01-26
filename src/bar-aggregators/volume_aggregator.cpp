//
// Created by letit6E on 24.03.2024.
//

#include "volume_aggregator.h"

VolumeBarAggregator::VolumeBarAggregator(double volume_duration)
    : volume_duration(volume_duration), last_timestamp(-1) {}

void VolumeBarAggregator::receive(const Trade &trade) {
    if (trade.get_timestamp() < last_timestamp) {
        throw std::invalid_argument(
            "Bar aggregator receives trades only increasing over timestamp");
    }
    last_timestamp = trade.get_timestamp();
    if (trade.get_volume() + cur_bar.get_volume() > volume_duration &&
        cur_bar.get_open() > 0) {
        bar_queue.push(cur_bar);
        cur_bar = Bar();
    }
    cur_bar.add_trade(trade);
}
