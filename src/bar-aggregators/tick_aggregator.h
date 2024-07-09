//
// Created by letit6E on 19.12.2023.
//

#ifndef TRADE_LAB_TICK_AGGREGATOR_H
#define TRADE_LAB_TICK_AGGREGATOR_H

#include "bar_aggregator.h"

class TickBarAggregator : public BarAggregator {
   private:
    long long bar_length;
    long long last_timestamp;
    Bar cur_bar;

   public:
    explicit TickBarAggregator(long long bar_length);

    void receive(const Trade &trade) override;

    bool ready() override;

    Bar publish() override;
};

#endif  // TRADE_LAB_TICK_AGGREGATOR_H
