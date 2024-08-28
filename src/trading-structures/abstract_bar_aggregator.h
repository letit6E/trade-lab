//
// Created by letit6E on 28.08.2024.
//

#ifndef ABSTRACT_BAR_AGGREGATOR_H
#define ABSTRACT_BAR_AGGREGATOR_H

#include <vector>

#include "bar.h"
#include "trade.h"

class AbstractBarAggregator {
   public:
    virtual void receive(const Trade& trade) = 0;
    virtual bool ready() const = 0;
    virtual Bar publish() = 0;
    virtual Bar collect(const std::vector<Trade>& trades) = 0;
    virtual std::vector<Bar> aggregate(const std::vector<Trade>& trades) = 0;
    virtual ~AbstractBarAggregator() = default;
};

#endif  // ABSTRACT_BAR_AGGREGATOR_H
