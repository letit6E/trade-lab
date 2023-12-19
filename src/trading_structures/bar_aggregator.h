//
// Created by letit6E on 14.12.2023.
//

#ifndef TRADE_LAB_BAR_AGGREGATOR_H
#define TRADE_LAB_BAR_AGGREGATOR_H

#include "bar.h"
#include <queue>

class BarAggregator {
protected:
    std::queue<Bar> bar_queue;

public:

    virtual void receive(const Trade &trade);

    virtual bool ready() {
        return !bar_queue.empty();
    }

    virtual Bar publish() {
        if (ready()) {
            Bar published_bar = bar_queue.front();
            bar_queue.pop();
            return published_bar;
        } else {
            throw std::runtime_error("There are no ready bars to publish.");
        }
    }
};

#endif //TRADE_LAB_BAR_AGGREGATOR_H
