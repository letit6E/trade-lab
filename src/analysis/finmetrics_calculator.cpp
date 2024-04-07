//
// Created by letit6E on 10.04.2024.
//

#include "finmetrics_calculator.h"

FinancialMetricsCalculator::FinancialMetricsCalculator(std::deque<Bar>& bars)
    : bars(bars) {}

double FinancialMetricsCalculator::calculateRSI(int period) {
    if (bars.size() < period)
        throw std::invalid_argument("Not enough bars to calculate RSI");

    double avg_gain = 0;
    double avg_loss = 0;

    for (int i = 1; i <= period; ++i) {
        double change = bars[i].get_close() - bars[i - 1].get_close();

        if (change >= 0) {
            avg_gain += change;
        } else {
            avg_loss -= change;
        }
    }

    avg_gain /= period;
    avg_loss /= period;

    if (avg_loss == 0) {
        return 100;
    }

    double rs = avg_gain / avg_loss;

    return 100 - (100 / (1 + rs));
}

double FinancialMetricsCalculator::calculateMean() {
    double sum = 0.0;
    for (const auto& bar : bars) {
        sum += bar.get_close();
    }
    return sum / bars.size();
}

double FinancialMetricsCalculator::calculateVariance() {
    double mean = calculateMean();
    double temp = 0;
    for (const auto& bar : bars)
        temp += (bar.get_close() - mean) * (bar.get_close() - mean);
    return temp / (bars.size() - 1);
}

double FinancialMetricsCalculator::calculateVolume() {
    double total_volume = 0.0;
    for (const auto& bar : bars) {
        total_volume += bar.get_volume();
    }
    return total_volume;
}

std::pair<double, double> FinancialMetricsCalculator::calculateMACD(
    int short_period, int long_period, int signal_period) {
    if (bars.size() < long_period)
        throw std::invalid_argument("Not enough bars to calculate MACD");

    double short_ema = 0.0;
    double long_ema = 0.0;

    double short_multiplier = 2.0 / (short_period + 1);
    double long_multiplier = 2.0 / (long_period + 1);

    for (int i = 0; i < bars.size(); ++i) {
        if (i == 0) {
            short_ema = bars[i].get_close();
            long_ema = bars[i].get_close();
        } else {
            short_ema = ((bars[i].get_close() - short_ema) * short_multiplier) +
                        short_ema;
            long_ema =
                ((bars[i].get_close() - long_ema) * long_multiplier) + long_ema;
        }
    }

    double macd_line = short_ema - long_ema;

    double signal_multiplier = 2.0 / (signal_period + 1);
    double signal_line = macd_line;

    for (int i = 1; i < bars.size(); ++i) {
        signal_line =
            ((macd_line - signal_line) * signal_multiplier) + signal_line;
    }

    return {macd_line, signal_line};
}

#include "finmetrics_calculator.h"
