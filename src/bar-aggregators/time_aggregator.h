//
// Created by letit6E on 19.12.2023.
//

#ifndef TRADE_LAB_TIME_AGGREGATOR_H
#define TRADE_LAB_TIME_AGGREGATOR_H

#include "bar_aggregator.h"

class TimeBarAggregator : public BarAggregator {
   private:
    long long bar_duration;
    long long last_timestamp;
    Bar cur_bar;
    Bar last_bar;

   public:
    explicit TimeBarAggregator(long long duration);

    void receive(const Trade &trade) override;

    bool ready() override;

    Bar publish() override;
};

#endif  // TRADE_LAB_TIME_AGGREGATOR_H
