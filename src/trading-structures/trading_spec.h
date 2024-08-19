//
// Created by letit6E on 19.08.2024.
//

#ifndef TRADING_HRS_SPEC_H
#define TRADING_HRS_SPEC_H

#include "trade.h"

class TradingSpec {
   public:
    virtual bool is_trading_time(const Trade& trade) const = 0;
    virtual ~TradingSpec() = default;
};

class SimpleTradingHrsSpec : public TradingSpec {
   public:
    bool is_trading_time(const Trade& trade) const override;
};

#endif  // TRADING_HRS_SPEC_H
