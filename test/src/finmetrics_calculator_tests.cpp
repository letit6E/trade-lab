//
// Created by letit6E on 17.04.2024.
//

#include <gtest/gtest.h>

#include "analysis/finmetrics_calculator.h"

const std::vector<Trade> trades = {{1617283500, 10.0, 5, 500, 1},
                                   {1617283600, 11.0, 3, 330, 1},
                                   {1617283700, 12.0, 4, 480, -1},
                                   {1617283800, 9.0, 2, 180, 1},
                                   {1617283900, 10.5, 1, 105, -1}};

std::deque<Bar> get_test_data() {
    std::deque<Bar> d;

    for (const auto& trade : trades) {
        Bar bar;
        bar.add_trade(trade);
        d.push_back(bar);
    }

    return d;
}

TEST(FinmetricsCalculatorTest, ThrowRSITest) {
    auto test_data = get_test_data();
    auto calculator = FinancialMetricsCalculator(test_data);

    EXPECT_THROW(calculator.calculateRSI(10), std::invalid_argument);
}

TEST(FinmetricsCalculatorTest, RSITest) {
    auto test_data = get_test_data();
    auto calculator = FinancialMetricsCalculator(test_data);

    EXPECT_DOUBLE_EQ(calculator.calculateRSI(3), 40);
}

TEST(FinmetricsCalculatorTest, MeanTest) {
    auto test_data = get_test_data();
    auto calculator = FinancialMetricsCalculator(test_data);

    EXPECT_DOUBLE_EQ(calculator.calculateMean(), 10.5);
}

TEST(FinmetricsCalculatorTest, VarianceTest) {
    auto test_data = get_test_data();
    auto calculator = FinancialMetricsCalculator(test_data);

    EXPECT_DOUBLE_EQ(calculator.calculateVariance(), 1.25);
}

TEST(FinmetricsCalculatorTest, VolumeTest) {
    auto test_data = get_test_data();
    auto calculator = FinancialMetricsCalculator(test_data);

    EXPECT_DOUBLE_EQ(calculator.calculateVolume(), 1595);
}

TEST(FinmetricsCalculatorTest, MACDTest) {
    auto test_data = get_test_data();
    auto calculator = FinancialMetricsCalculator(test_data);

    auto result = calculator.calculateMACD(1, 5, 3);
    EXPECT_DOUBLE_EQ(result.first, 0.16049382716049365);
    EXPECT_DOUBLE_EQ(result.second, 0.16049382716049365);
}

TEST(FinmetricsCalculatorTest, MACDThrowTest) {
    auto test_data = get_test_data();
    auto calculator = FinancialMetricsCalculator(test_data);

    EXPECT_THROW(calculator.calculateMACD(1, 10, 3), std::invalid_argument);
}

// TEST(FinmetricsCalculatorTest, ReadyToPublish) {
//     TimeBarAggregator aggregator(1000);
//     Trade trade1(1000, 10.0, 1.0, 1.0, 1);
//     Trade trade2(1500, 11.0, 2.0, 2.0, -1);
//     Trade trade3(3000, 117.0, 4.0, 3.0, -1);
//
//     aggregator.receive(trade1);
//     aggregator.receive(trade2);
//     aggregator.receive(trade3);
//
//     EXPECT_TRUE(aggregator.ready());
// }
//
// TEST(FinmetricsCalculatorTest, ReceiveTradeWithLaterTimestamp) {
//     TimeBarAggregator aggregator(1000);
//     Trade trade1(1000, 10.0, 1.0, 1.0, 1);
//     Trade trade2(1500, 11.0, 2.0, 2.0, -1);
//     Trade trade3(3000, 117.0, 4.0, 3.0, -1);
//
//     aggregator.receive(trade1);
//     aggregator.receive(trade2);
//     aggregator.receive(trade3);
//     Bar published_bar = aggregator.publish();
//
//     EXPECT_EQ(published_bar.get_startstamp(), 1000);
//     EXPECT_EQ(published_bar.get_stopstamp(), 1500);
//     EXPECT_EQ(published_bar.get_length(), 2);
//     EXPECT_EQ(published_bar.get_open(), 10.0);
//     EXPECT_EQ(published_bar.get_close(), 11.0);
//     EXPECT_EQ(published_bar.get_high(), 11.0);
//     EXPECT_EQ(published_bar.get_low(), 10.0);
//     EXPECT_EQ(published_bar.get_volume(), 3.0);
// }
//
// TEST(FinmetricsCalculatorTest, ReadyWithoutAvailableBar) {
//     TimeBarAggregator aggregator(1000);
//     Trade trade1(1000, 10.0, 1.0, 1.0, 1);
//
//     aggregator.receive(trade1);
//
//     EXPECT_FALSE(aggregator.ready());
// }
//
// TEST(FinmetricsCalculatorTest, PublishWithoutAvailableBar) {
//     TimeBarAggregator aggregator(
//         1000);  // Создаем агрегатор с временным интервалом 1000 миллисекунд
//     Trade trade1(1000, 10.0, 1.0, 1.0,
//                  1);  // Первая сделка с меткой времени 1000
//
//     aggregator.receive(trade1);
//
//     EXPECT_FALSE(aggregator.ready());
//     EXPECT_NO_THROW(aggregator.publish());
// }