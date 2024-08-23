//
// Created by letit6E on 23.08.2024.
//

#ifndef AGGREGATOR_RULE_H
#define AGGREGATOR_RULE_H

#include "bar.h"
#include "trade.h"

class AggregatorRule {
   public:
    virtual bool is_addable(const Trade& trade) const = 0;
    virtual bool prepare_to_addition(const Trade& trade) = 0;
    virtual void update_on_bar_feed(const Trade& trade) = 0;
    virtual void update_on_bar_close(const Bar& bar) = 0;
    virtual ~AggregatorRule() = default;
};

class AdditiveAggregatorRule : public AggregatorRule {
   public:
    enum ClosePosition { OnVolumeThreshold, OnTimeInterval };

   private:
    ClosePosition close_position;
    double volume_threshold;
    double accumulated_volume;
    long long time_interval;
    long long last_timestamp;

   public:
    AdditiveAggregatorRule(ClosePosition cp, double vol_thresh = 0,
                           long long time_int = 0);

    bool is_addable(const Trade& trade) const override;
    bool prepare_to_addition(const Trade& trade) override;
    void update_on_bar_feed(const Trade& trade) override;
    void update_on_bar_close(const Bar& bar) override;
};

class InformationalAggregatorRule : public AggregatorRule {
   private:
    // Configuration parameters for the rule
    double price_threshold;  // Price change threshold
    double last_price;
    bool bar_ready;

   public:
    InformationalAggregatorRule(double price_thresh);

    bool is_addable(const Trade& trade) const override;
    bool prepare_to_addition(const Trade& trade) override;
    void update_on_bar_feed(const Trade& trade) override;
    void update_on_bar_close(const Bar& bar) override;
};

class IntervalAggregatorRule : public AggregatorRule {
   private:
    long long interval_duration;
    long long interval_start_time;
    bool bar_ready;

   public:
    IntervalAggregatorRule(long long duration);

    bool is_addable(const Trade& trade) const override;
    bool prepare_to_addition(const Trade& trade) override;
    void update_on_bar_feed(const Trade& trade) override;
    void update_on_bar_close(const Bar& bar) override;
};

#endif  // AGGREGATOR_RULE_H