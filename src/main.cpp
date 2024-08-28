#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

#include "aggregator_bar_builder.h"
#include "aggregator_rule.h"
#include "bar.h"
#include "statistic.h"
#include "stock_bar_aggregator.h"
#include "trade.h"
#include "trading_spec.h"

int main() {
    Statistic<double> total_volume(
        "Total Volume", [](const std::vector<Trade>& trades) {
            return std::accumulate(trades.begin(), trades.end(), 0.0,
                                   [](double sum, const Trade& trade) {
                                       return sum + trade.get_volume();
                                   });
        });

    Statistic<double> average_price(
        "Average Price", [](const std::vector<Trade>& trades) {
            if (trades.empty()) return 0.0;
            double total_price =
                std::accumulate(trades.begin(), trades.end(), 0.0,
                                [](double sum, const Trade& trade) {
                                    return sum + trade.get_price();
                                });
            return total_price / trades.size();
        });

    std::vector<std::shared_ptr<Statistic<double>>> stats = {
        std::make_shared<Statistic<double>>(total_volume),
        std::make_shared<Statistic<double>>(average_price)};

    AdditiveAggregatorRule rule(AdditiveAggregatorRule::OnTimeInterval, 0, 60);
    AggregatorBarBuilder builder(stats);
    SimpleTradingHrsSpec spec;

    StockBarAggregator<AdditiveAggregatorRule, SimpleTradingHrsSpec,
                       AggregatorBarBuilder>
        aggregator(rule, spec, builder);

    std::vector<Trade> trades = {Trade(1609459200, 100.0, 10.0, 1000.0, 1),
                                 Trade(1609459260, 101.0, 5.0, 500.0, -1),
                                 Trade(1609459320, 102.0, 20.0, 2000.0, 1),
                                 Trade(1609459380, 99.0, 15.0, 1500.0, -1),
                                 Trade(1609459440, 103.0, 8.0, 800.0, 1)};

    for (const auto& trade : trades) {
        aggregator.receive(trade);
    }

    while (aggregator.ready()) {
        Bar bar = aggregator.publish();
        std::cout << bar << std::endl;
    }
    // force publish (last unfinished bar)
    std::cout << aggregator.publish() << std::endl;

    return 0;
}
