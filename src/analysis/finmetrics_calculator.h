//
// Created by letit6E on 10.04.2024.
//

#ifndef TRADE_LAB_FINMETRICS_CALCULATOR_H
#define TRADE_LAB_FINMETRICS_CALCULATOR_H

#include <queue>

#include "bar.h"

class FinancialMetricsCalculator {
   public:
    std::deque<Bar>& bars;
    FinancialMetricsCalculator(std::deque<Bar>& bars);

    double calculateMean();

    double calculateVariance();

    double calculateVolume();

    double calculateRSI(int period);

    std::pair<double, double> calculateMACD(int short_period, int long_period,
                                            int signal_period);
};

#endif  // TRADE_LAB_FINMETRICS_CALCULATOR_H
