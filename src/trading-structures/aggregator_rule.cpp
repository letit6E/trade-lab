//
// Created by letit6E on 23.08.2024.
//

#include "aggregator_rule.h"

AdditiveAggregatorRule::AdditiveAggregatorRule(ClosePosition cp,
                                               double vol_thresh,
                                               long long time_int)
    : close_position(cp),
      volume_threshold(vol_thresh),
      accumulated_volume(0),
      time_interval(time_int),
      last_timestamp(0) {}

bool AdditiveAggregatorRule::is_addable(const Trade& trade) const {
    return true;
}

bool AdditiveAggregatorRule::prepare_to_addition(const Trade& trade) {
    if (close_position == OnVolumeThreshold) {
        accumulated_volume += trade.get_volume();
        return accumulated_volume >= volume_threshold;
    } else if (close_position == OnTimeInterval) {
        if (last_timestamp == 0) last_timestamp = trade.get_timestamp();
        return (trade.get_timestamp() - last_timestamp) >= time_interval;
    }
    return false;
}

void AdditiveAggregatorRule::update_on_bar_feed(const Trade& trade) {
    if (close_position == OnVolumeThreshold) {
        accumulated_volume += trade.get_volume();
    }
}

void AdditiveAggregatorRule::update_on_bar_close(const Bar& bar) {
    accumulated_volume = 0;
    last_timestamp = 0;
}

InformationalAggregatorRule::InformationalAggregatorRule(double price_thresh)
    : price_threshold(price_thresh), last_price(0.0), bar_ready(false) {}

bool InformationalAggregatorRule::is_addable(const Trade& trade) const {
    return true;
}

bool InformationalAggregatorRule::prepare_to_addition(const Trade& trade) {
    if (last_price == 0.0) {
        last_price = trade.get_price();
        bar_ready = false;
        return false;
    }

    double price_change = std::abs(trade.get_price() - last_price);
    if (price_change >= price_threshold) {
        bar_ready = true;
    } else {
        bar_ready = false;
    }
    return bar_ready;
}

void InformationalAggregatorRule::update_on_bar_feed(const Trade& trade) {
    last_price = trade.get_price();
}

void InformationalAggregatorRule::update_on_bar_close(const Bar& bar) {
    // reset state
    last_price = 0.0;
    bar_ready = false;
}

IntervalAggregatorRule::IntervalAggregatorRule(long long duration)
    : interval_duration(duration), interval_start_time(0), bar_ready(false) {}

bool IntervalAggregatorRule::is_addable(const Trade& trade) const {
    return true;
}

bool IntervalAggregatorRule::prepare_to_addition(const Trade& trade) {
    if (interval_start_time == 0) {
        // initialize interval_start_time
        interval_start_time = trade.get_timestamp();
        bar_ready = false;
        return false;
    }

    if ((trade.get_timestamp() - interval_start_time) >= interval_duration) {
        // interval has elapsed
        bar_ready = true;
    } else {
        bar_ready = false;
    }
    return bar_ready;
}

void IntervalAggregatorRule::update_on_bar_feed(const Trade& trade) {}

void IntervalAggregatorRule::update_on_bar_close(const Bar& bar) {
    interval_start_time = 0;
    bar_ready = false;
}