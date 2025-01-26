//
// Created by letit6E on 19.12.2023.
//

#include <gtest/gtest.h>

#include "bar-aggregators/time_aggregator.h"


TEST(TimeBarAggregatorTest, ReceiveTradeWithEarlierTimestamp) {
    TimeBarAggregator aggregator(1000);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);
    Trade trade2(500, 11.0, 2.0, 2.0, -1);

    aggregator.receive(trade1);
    EXPECT_THROW(aggregator.receive(trade2), std::invalid_argument);
}

TEST(TimeBarAggregatorTest, ReadyToPublish) {
    TimeBarAggregator aggregator(1000);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);
    Trade trade2(1500, 11.0, 2.0, 2.0, -1);
    Trade trade3(3000, 117.0, 4.0, 3.0, -1);

    aggregator.receive(trade1);
    aggregator.receive(trade2);
    aggregator.receive(trade3);

    EXPECT_TRUE(aggregator.ready());
}

TEST(TimeBarAggregatorTest, ReceiveTradeWithLaterTimestamp) {
    TimeBarAggregator aggregator(1000);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);
    Trade trade2(1500, 11.0, 2.0, 2.0, -1);
    Trade trade3(3000, 117.0, 4.0, 3.0, -1);

    aggregator.receive(trade1);
    aggregator.receive(trade2);
    aggregator.receive(trade3);
    Bar published_bar = aggregator.publish();

    EXPECT_EQ(published_bar.get_startstamp(), 1000);
    EXPECT_EQ(published_bar.get_stopstamp(), 1500);
    EXPECT_EQ(published_bar.get_length(), 2);
    EXPECT_EQ(published_bar.get_open(), 10.0);
    EXPECT_EQ(published_bar.get_close(), 11.0);
    EXPECT_EQ(published_bar.get_high(), 11.0);
    EXPECT_EQ(published_bar.get_low(), 10.0);
    EXPECT_EQ(published_bar.get_volume(), 3.0);
}

TEST(TimeBarAggregatorTest, ReadyWithoutAvailableBar) {
    TimeBarAggregator aggregator(1000);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);

    aggregator.receive(trade1);

    EXPECT_FALSE(aggregator.ready());
}

TEST(TimeBarAggregatorTest, PublishWithoutAvailableBar) {
    TimeBarAggregator aggregator(
        1000);  // Создаем агрегатор с временным интервалом 1000 миллисекунд
    Trade trade1(1000, 10.0, 1.0, 1.0,
                 1);  // Первая сделка с меткой времени 1000

    aggregator.receive(trade1);

    EXPECT_FALSE(aggregator.ready());
    EXPECT_NO_THROW(aggregator.publish());
}