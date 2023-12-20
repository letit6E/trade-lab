//
// Created by letit6E on 14.12.2023.
//

#ifndef TRADE_LAB_BAR_AGGREGATOR_H
#define TRADE_LAB_BAR_AGGREGATOR_H

#include <queue>
#include <fstream>
#include "bar.h"

class BarAggregator {
protected:
    std::queue<Bar> bar_queue;

public:

    virtual void receive(const Trade &trade) {
        throw std::logic_error("This is abstract method and not implemented");
    }

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

    template<typename T>
    static std::queue<Bar> process(const std::string &filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open trade history file");
        }

        std::queue<Bar> closed_bars;
        T aggregator;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Trade trade;
            if (!(iss >> trade)) {
                throw std::runtime_error("Failed to parse trade data");
            }

            aggregator.receive(trade);
            if (aggregator.ready()) {
                closed_bars.push(aggregator.publish());
            }
        }

        file.close();

        try {
            closed_bars.push(aggregator.publish()); // force push
        } catch (...) {}

        return closed_bars;
    }

};

#endif //TRADE_LAB_BAR_AGGREGATOR_H
