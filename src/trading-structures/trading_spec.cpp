//
// Created by letit6E on 19.08.2024.
//

#include "trading_spec.h"

bool SimpleTradingHrsSpec::is_trading_time(const Trade& trade) const {
    return trade.get_timestamp() % 15000 <= 10000;
}
