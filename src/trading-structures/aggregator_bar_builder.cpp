//
// Created by letit6E on 25.08.2024.
//

#include "aggregator_bar_builder.h"

#include <iostream>

AggregatorBarBuilder::AggregatorBarBuilder(
    const std::vector<std::shared_ptr<Statistic<double>>>& stats)
    : statistics(stats) {}

void AggregatorBarBuilder::add(const Trade& trade) { trades.push_back(trade); }

Bar AggregatorBarBuilder::build() {
    Bar bar(trades);

    std::cout << "Bar built: \n";
    for (const auto& stat : statistics) {
        double value = stat->compute(trades);
        std::cout << stat->get_name() << ": " << value << std::endl;
    }

    return bar;
}

void AggregatorBarBuilder::reset() { trades.clear(); }
