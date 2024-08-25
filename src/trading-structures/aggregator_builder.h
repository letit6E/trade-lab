//
// Created by letit6E on 25.08.2024.
//

#ifndef TRADE_LAB_AGGREGATOR_BUILDER_H
#define TRADE_LAB_AGGREGATOR_BUILDER_H

#include "bar.h"
#include "trade.h"

class AggregatorBuilder {
   public:
    virtual void add(const Trade& trade) = 0;
    virtual Bar build() = 0;
    virtual void reset() = 0;
    virtual ~AggregatorBuilder() = default;
};

#endif  // TRADE_LAB_AGGREGATOR_BUILDER_H
