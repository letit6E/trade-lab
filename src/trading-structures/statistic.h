//
// Created by letit6E on 20.08.2024.
//

#ifndef TRADE_LAB_STATISTIC_H
#define TRADE_LAB_STATISTIC_H

#include <trade.h>

#include <functional>
#include <string>

template <typename StatType>
class Statistic {
   private:
    std::string name;
    std::function<StatType(const std::vector<Trade>&)> method;

   public:
    Statistic(const std::string& n,
              std::function<StatType(const std::vector<Trade>&)> m)
        : name(n), method(m) {}

    StatType compute(const std::vector<Trade>& trades) const {
        return method(trades);
    }

    std::string get_name() const { return name; }
};

#endif  // TRADE_LAB_STATISTIC_H
