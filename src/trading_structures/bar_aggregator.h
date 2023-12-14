//
// Created by letit6E on 14.12.2023.
//

#ifndef TRADE_LAB_BAR_AGGREGATOR_H
#define TRADE_LAB_BAR_AGGREGATOR_H

#include "bar.h"
#include <queue>

class BarAggregator {
private:
    std::queue<Bar> closedBars;
    Bar currentBar;
    unsigned long barStep;

public:

    explicit BarAggregator(long long step) : closedBars(), currentBar(), barStep(step) {}

    void receive(const Trade& t) {
        // TODO
    }

    bool ready() {
        return !closedBars.empty();
    }

    Bar publish() {
        if (ready()) {
            Bar publishedBar = closedBars.front();
            closedBars.pop();
            return publishedBar;
        } else {
            throw std::runtime_error("There are no ready bars to publish.");
        }
    }
};

#endif //TRADE_LAB_BAR_AGGREGATOR_H
