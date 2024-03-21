//
// Created by letit6E on 10.05.2024.
//

#ifndef TRADE_LAB_VOLUME_AGGREGATOR_H
#define TRADE_LAB_VOLUME_AGGREGATOR_H

#include "bar_aggregator.h"

class VolumeBarAggregator : public BarAggregator {
   private:
    double volume_duration;
    long long bar_length;
    long long last_timestamp;
    Bar cur_bar;

   public:
    explicit VolumeBarAggregator(double volume_duration);

    void receive(const Trade &trade) override;

    bool ready() override;

    Bar publish() override;
};

#endif  // TRADE_LAB_VOLUME_AGGREGATOR_H
