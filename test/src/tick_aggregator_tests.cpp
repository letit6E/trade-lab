//
// Created by letit6E on 20.12.2023.
//

#include <gtest/gtest.h>
#include "bar-aggregators/tick_aggregator.h"

// Тестирование функции receive()
TEST(TickBarAggregatorTest, ReceiveTrade) {
    TickBarAggregator aggregator(5); // Создаем агрегатор с длиной бара 5
    Trade trade1(1, 10.0, 1.0, 1.0, 1);
    Trade trade2(2, 11.0, 2.0, 2.0, 1);
    Trade trade3(3, 12.0, 3.0, 3.0, 1);
    Trade trade4(4, 13.0, 4.0, 4.0, 1);
    Trade trade5(5, 14.0, 5.0, 5.0, 1);
    Trade trade6(6, 15.0, 6.0, 6.0, 1);

    aggregator.receive(trade1);
    aggregator.receive(trade2);
    aggregator.receive(trade3);
    aggregator.receive(trade4);
    aggregator.receive(trade5);

    // Проверяем, что бар не готов к публикации
    EXPECT_TRUE(aggregator.ready());

    aggregator.receive(trade6);

    // Проверяем, что бар готов к публикации
    EXPECT_TRUE(aggregator.ready());

    // Проверяем, что публикуемый бар соответствует ожидаемым значениям
    Bar published_bar = aggregator.publish();
    EXPECT_EQ(published_bar.get_length(), 5);
    EXPECT_EQ(published_bar.get_open(), 10.0);
    EXPECT_EQ(published_bar.get_close(), 14.0);
    EXPECT_EQ(published_bar.get_high(), 14.0);
    EXPECT_EQ(published_bar.get_low(), 10.0);
    EXPECT_EQ(published_bar.get_volume(), 15.0);
    EXPECT_EQ(published_bar.get_size(), 15.0);
}

// Тестирование функции ready()
TEST(TickBarAggregatorTest, Ready) {
    TickBarAggregator aggregator(3); // Создаем агрегатор с длиной бара 3
    Trade trade1(1, 10.0, 1.0, 1.0, 1);
    Trade trade2(2, 11.0, 2.0, 2.0, 1);
    Trade trade3(3, 12.0, 3.0, 3.0, 1);
    Trade trade4(4, 13.0, 4.0, 4.0, 1);

    // Проверяем, что агрегатор не готов к публикации
    EXPECT_FALSE(aggregator.ready());

    aggregator.receive(trade1);
    aggregator.receive(trade2);

    // Проверяем, что агрегатор не готов к публикации
    EXPECT_FALSE(aggregator.ready());

    aggregator.receive(trade3);

    // Проверяем, что агрегатор готов к публикации
    EXPECT_TRUE(aggregator.ready());

    aggregator.publish();

    aggregator.receive(trade4);

    // Проверяем, что агрегатор снова не готов к публикации
    EXPECT_FALSE(aggregator.ready());
}

TEST(TickBarAggregatorTest, Publish) {
    // Create a TickBarAggregator with bar length of 2
    TickBarAggregator aggregator(2);

    // Create some sample trades
    Trade trade1(1, 10.0, 1.0, 1.0, 1);
    Trade trade2(2, 11.0, 2.0, 2.0, 1);
    Trade trade3(3, 12.0, 3.0, 3.0, 1);

    // Receive the first trade
    aggregator.receive(trade1);

    // Check that the aggregator is not ready to publish yet
    EXPECT_FALSE(aggregator.ready());

    // Receive the second trade
    aggregator.receive(trade2);

    // Check that the aggregator is ready to publish
    EXPECT_TRUE(aggregator.ready());

    // Publish the bar
    Bar published_bar = aggregator.publish();

    // Check that the published bar matches the expected values
    EXPECT_EQ(published_bar.get_open(), 10.0);
    EXPECT_EQ(published_bar.get_close(), 11.0);
    EXPECT_EQ(published_bar.get_high(), 11.0);
    EXPECT_EQ(published_bar.get_low(), 10.0);
    EXPECT_EQ(published_bar.get_volume(), 3.0);
    EXPECT_EQ(published_bar.get_size(), 3.0);
    EXPECT_EQ(published_bar.get_signed_volume(), 2.0);
    EXPECT_EQ(published_bar.get_signed_size(), 2.0);
    EXPECT_EQ(published_bar.get_directed_volume(), 3.0);
    EXPECT_EQ(published_bar.get_directed_size(), 3.0);
    EXPECT_EQ(published_bar.get_vwap(), 16.0);
    EXPECT_EQ(published_bar.get_startstamp(), 1);
    EXPECT_EQ(published_bar.get_stopstamp(), 2);
    EXPECT_EQ(published_bar.get_duration(), 1);
    EXPECT_EQ(published_bar.get_length(), 2);

    // Check that the aggregator is not ready to publish again
    EXPECT_FALSE(aggregator.ready());

    // Receive the third trade
    aggregator.receive(trade3);

    // Check that the aggregator is ready to publish again
    EXPECT_FALSE(aggregator.ready());
}

// Тестирование исключения при попытке публикации, когда нет готовых баров
TEST(TickBarAggregatorTest, PublishException) {
    TickBarAggregator aggregator(2); // Создаем агрегатор с длиной бара 2

    // Проверяем, что выбрасывается исключение при попытке публикации
    EXPECT_THROW(aggregator.publish(), std::runtime_error);
}
