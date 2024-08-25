//
// Created by letit6E on 25.08.2024.
//

#ifndef TRADE_LAB_AGGREGATOR_BAR_BUILDER_H
#define TRADE_LAB_AGGREGATOR_BAR_BUILDER_H

#include <aggregator_builder.h>
#include <statistic.h>
#include <trade.h>

#include <memory>

class AggregatorBarBuilder : public AggregatorBuilder {
   private:
    std::vector<Trade> trades;
    std::vector<std::shared_ptr<Statistic<double>>> statistics;

   public:
    AggregatorBarBuilder(
        const std::vector<std::shared_ptr<Statistic<double>>>& stats);

    void add(const Trade& trade) override;
    Bar build() override;
    void reset() override;
};

#endif  // TRADE_LAB_AGGREGATOR_BAR_BUILDER_H
