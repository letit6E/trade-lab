//
// Created by letit6E on 05.12.2023.
//

#include <gtest/gtest.h>

#include <sstream>

#include "trading-structures/bar.h"

TEST(BarTest, ConstructorTest) {
    Bar bar(1.0, 2.0, 3.0, 0.5, 100, 10, 50, 5, -50, -5, 2.5, 1617282000,
            1617282600, 600, 40);

    EXPECT_DOUBLE_EQ(1.0, bar.get_open());
    EXPECT_DOUBLE_EQ(2.0, bar.get_close());
    EXPECT_DOUBLE_EQ(3.0, bar.get_high());
    EXPECT_DOUBLE_EQ(0.5, bar.get_low());
    EXPECT_DOUBLE_EQ(100, bar.get_volume());
    EXPECT_DOUBLE_EQ(10, bar.get_size());
    EXPECT_DOUBLE_EQ(50, bar.get_signed_volume());
    EXPECT_DOUBLE_EQ(5, bar.get_signed_size());
    EXPECT_DOUBLE_EQ(-50, bar.get_directed_volume());
    EXPECT_DOUBLE_EQ(-5, bar.get_directed_size());
    EXPECT_DOUBLE_EQ(2.5, bar.get_vwap());
    EXPECT_EQ(1617282000, bar.get_startstamp());
    EXPECT_EQ(1617282600, bar.get_stopstamp());
    EXPECT_EQ(600, bar.get_duration());
    EXPECT_EQ(40, bar.get_length());
}

TEST(BarTest, InputOperatorTest) {
    std::istringstream iss(
        "1.0,2.0,3.0,0.5,100,10,50,5,-50,-5,2.5,1617282000,1617282600,600,40");
    Bar bar;

    iss >> bar;

    EXPECT_DOUBLE_EQ(1.0, bar.get_open());
    EXPECT_DOUBLE_EQ(2.0, bar.get_close());
    EXPECT_DOUBLE_EQ(3.0, bar.get_high());
    EXPECT_DOUBLE_EQ(0.5, bar.get_low());
    EXPECT_DOUBLE_EQ(100, bar.get_volume());
    EXPECT_DOUBLE_EQ(10, bar.get_size());
    EXPECT_DOUBLE_EQ(50, bar.get_signed_volume());
    EXPECT_DOUBLE_EQ(5, bar.get_signed_size());
    EXPECT_DOUBLE_EQ(-50, bar.get_directed_volume());
    EXPECT_DOUBLE_EQ(-5, bar.get_directed_size());
    EXPECT_DOUBLE_EQ(2.5, bar.get_vwap());
    EXPECT_EQ(1617282000, bar.get_startstamp());
    EXPECT_EQ(1617282600, bar.get_stopstamp());
    EXPECT_EQ(600, bar.get_duration());
    EXPECT_EQ(40, bar.get_length());
}

TEST(BarTest, OutputOperatorTest) {
    std::ostringstream oss;
    Bar bar(1.0, 2.0, 3.0, 0.5, 100, 10, 50, 5, -50, -5, 2.5, 1617282000,
            1617282600, 600, 40);

    oss << bar;
    std::string expectedResult =
        "1,2,3,0.5,100,10,50,5,-50,-5,2.5,1617282000,1617282600,600,40";

    EXPECT_EQ(expectedResult, oss.str());
}

TEST(BarTest, AggregatesTradeDataCorrectly) {
    std::vector<Trade> trades = {{1617283500, 10.0, 5, 500, 1},
                                 {1617283600, 11.0, 3, 330, 1},
                                 {1617283700, 12.0, 4, 480, -1},
                                 {1617283800, 9.0, 2, 180, 1},
                                 {1617283900, 10.5, 1, 105, -1}};
    Bar bar(trades);

    EXPECT_DOUBLE_EQ(
        (10.0 * 500 + 11.0 * 330 + 12.0 * 480 + 9.0 * 180 + 10.5 * 105) / 5,
        bar.get_vwap());
    EXPECT_EQ(5, bar.get_length());
    EXPECT_EQ(10.0, bar.get_open());
    EXPECT_EQ(10.5, bar.get_close());
    EXPECT_EQ(12.0, bar.get_high());
    EXPECT_EQ(9.0, bar.get_low());
    EXPECT_EQ(500 + 330 + 480 + 180 + 105, bar.get_volume());
    EXPECT_EQ(1617283500, bar.get_startstamp());
    EXPECT_EQ(1617283900, bar.get_stopstamp());
    EXPECT_EQ(5 + 3 - 4 + 2 - 1, bar.get_directed_size());
    EXPECT_EQ(500 + 330 - 480 + 180 - 105, bar.get_directed_volume());
    EXPECT_EQ(3 + 4 - 2 + 1, bar.get_signed_size());
    EXPECT_EQ(330 + 480 - 180 + 105, bar.get_signed_volume());
}

TEST(BarTest, BarBuilderTest) {
    Bar bar = BarBuilder()
                  .set_open(123.45)
                  .set_close(130.67)
                  .set_high(135.00)
                  .set_low(120.00)
                  .set_volume(1000.0)
                  .set_size(100.0)
                  .set_signed_volume(500.0)
                  .set_signed_size(50.0)
                  .set_directed_volume(250.0)
                  .set_directed_size(25.0)
                  .set_vwap(125.33)
                  .set_startstamp(1628168400)
                  .set_stopstamp(1628204800)
                  .set_duration(3600)
                  .set_length(10)
                  .build();
    EXPECT_EQ(123.45, bar.get_open());
    EXPECT_EQ(130.67, bar.get_close());
    EXPECT_EQ(135, bar.get_high());
    EXPECT_EQ(120, bar.get_low());
    EXPECT_EQ(1000, bar.get_volume());
    EXPECT_EQ(1628168400, bar.get_startstamp());
    EXPECT_EQ(1628204800, bar.get_stopstamp());
    EXPECT_EQ(25, bar.get_directed_size());
    EXPECT_EQ(250, bar.get_directed_volume());
    EXPECT_EQ(50, bar.get_signed_size());
    EXPECT_EQ(500, bar.get_signed_volume());
}