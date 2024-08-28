//
// Created by letit6E on 28.08.2024.
//

#ifndef TRADE_LAB_STOCK_BAR_AGGREGATOR_H
#define TRADE_LAB_STOCK_BAR_AGGREGATOR_H

#include <vector>

#include "abstract_bar_aggregator.h"
#include "aggregator_bar_builder.h"
#include "aggregator_rule.h"
#include "trading_spec.h"

template <typename Rule, typename Spec, typename Builder>
class StockBarAggregator : public AbstractBarAggregator {
   private:
    Rule rule;
    Builder builder;
    Spec spec;
    std::vector<Bar> bars;

   public:
    StockBarAggregator(const Rule& r, const Spec& s, const Builder& b)
        : rule(r), spec(s), builder(b) {}

    void receive(const Trade& trade) override {
        if (spec.is_trading_time(trade) && rule.is_addable(trade)) {
            builder.add(trade);
            rule.update_on_bar_feed(trade);
            if (rule.prepare_to_addition(trade)) {
                Bar bar = builder.build();
                rule.update_on_bar_close(bar);
                bars.push_back(bar);
                builder.reset();
            }
        }
    }

    bool ready() const override { return !bars.empty(); }

    Bar publish() override {
        if (ready()) {
            Bar bar = bars.front();
            bars.erase(bars.begin());
            return bar;
        }
        // user don't check ready, force build
        return builder.build();
    }

    Bar collect(const std::vector<Trade>& trades) override {
        for (const Trade& trade : trades) {
            receive(trade);
        }
        return publish();
    }

    std::vector<Bar> aggregate(const std::vector<Trade>& trades) override {
        for (const Trade& trade : trades) {
            receive(trade);
        }
        std::vector<Bar> result = bars;
        bars.clear();
        return result;
    }
};

#endif  // TRADE_LAB_STOCK_BAR_AGGREGATOR_H
