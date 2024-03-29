//
// Created by letit6E on 29.03.2024.
//

#include <gtest/gtest.h>

#include "bar-aggregators/volume_aggregator.h"

TEST(VolumeBarAggregatorTest, ReceiveTradeWithEarlierTimestamp) {
    VolumeBarAggregator aggregator(1000);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);
    Trade trade2(500, 11.0, 2.0, 2.0, -1);

    aggregator.receive(trade1);
    EXPECT_THROW(aggregator.receive(trade2), std::invalid_argument);
}

TEST(VolumeBarAggregatorTest, ReadyToPublish) {
    VolumeBarAggregator aggregator(5.0);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);
    Trade trade2(1500, 11.0, 2.0, 2.0, -1);
    Trade trade3(3000, 117.0, 4.0, 3.0, -1);

    aggregator.receive(trade1);
    aggregator.receive(trade2);
    aggregator.receive(trade3);

    EXPECT_TRUE(aggregator.ready());
}

TEST(VolumeBarAggregatorTest, ReceiveTradeWithLaterTimestamp) {
    VolumeBarAggregator aggregator(3.0);
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

TEST(VolumeBarAggregatorTest, ReadyWithoutAvailableBar) {
    VolumeBarAggregator aggregator(1000);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);

    aggregator.receive(trade1);

    EXPECT_FALSE(aggregator.ready());
}

TEST(VolumeBarAggregatorTest, PublishWithoutAvailableBar) {
    VolumeBarAggregator aggregator(1000);
    Trade trade1(1000, 10.0, 1.0, 1.0, 1);

    aggregator.receive(trade1);

    EXPECT_FALSE(aggregator.ready());
    EXPECT_NO_THROW(aggregator.publish());
}