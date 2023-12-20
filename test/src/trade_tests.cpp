//
// Created by letit6E on 03.12.2023.
//
#include <trading-structures/trade.h>
#include <fstream>
#include "gtest/gtest.h"

std::vector<Trade> read_from_file(const std::string& filename) {
    std::vector<Trade> trades;
    std::ifstream file(filename);
    Trade trade;

    while (file >> trade) {
        trades.push_back(trade);
    }

    return trades;
}

std::string get_path(const std::string& file_name) {
    return std::string(RESOURCE_DIR) + file_name;
}

TEST(TradeTest, ReadFromFileCorrectData) {
    std::vector<Trade> trades = read_from_file(get_path("test_data.csv"));

    ASSERT_EQ(trades.size(), 2);

    EXPECT_EQ(trades[0].timestamp, 1618920000);
    EXPECT_DOUBLE_EQ(trades[0].price, 100.5);
    EXPECT_DOUBLE_EQ(trades[0].size, 10);
    EXPECT_DOUBLE_EQ(trades[0].volume, 1005);
    EXPECT_EQ(trades[0].direction, 1);

    EXPECT_EQ(trades[1].timestamp, 1628920000);
    EXPECT_DOUBLE_EQ(trades[1].price, 200.0);
    EXPECT_DOUBLE_EQ(trades[1].size, 5);
    EXPECT_DOUBLE_EQ(trades[1].volume, 1000);
    EXPECT_EQ(trades[1].direction, -1);
}

TEST(TradeTest, ReadFromFileIncorrectData) {
    std::vector<Trade> trades = read_from_file(get_path("bad_data.csv"));

    EXPECT_TRUE(trades.empty());
}

TEST(TradeTest, DefaultConstructor) {
    Trade trade;
    EXPECT_EQ(trade.timestamp, 0);
    EXPECT_DOUBLE_EQ(trade.price, 0.0);
    EXPECT_DOUBLE_EQ(trade.size, 0.0);
    EXPECT_DOUBLE_EQ(trade.volume, 0.0);
    EXPECT_EQ(trade.direction, 0);
}

TEST(TradeTest, ParameterizedConstructor) {
    Trade trade(1618920000, 100.5, 10, 1005, 1);
    EXPECT_EQ(trade.timestamp, 1618920000);
    EXPECT_DOUBLE_EQ(trade.price, 100.5);
    EXPECT_DOUBLE_EQ(trade.size, 10);
    EXPECT_DOUBLE_EQ(trade.volume, 1005);
    EXPECT_EQ(trade.direction, 1);
}

TEST(TradeTest, InputOperator) {
    std::istringstream is("1618920000,100.5,10,1005,1");
    Trade trade;
    is >> trade;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(trade.timestamp, 1618920000);
    EXPECT_DOUBLE_EQ(trade.price, 100.5);
    EXPECT_DOUBLE_EQ(trade.size, 10);
    EXPECT_DOUBLE_EQ(trade.volume, 1005);
    EXPECT_EQ(trade.direction, 1);
}

TEST(TradeTest, InputOperatorWithBadData) {
    std::istringstream is("1618920000;100.5;10;1005");
    Trade trade;
    is >> trade;
    EXPECT_TRUE(is.fail());
}

TEST(TradeTest, OutputOperator) {
    std::ostringstream os;
    Trade trade(1618920000, 100.5, 10, 1005, -1);
    os << trade;
    EXPECT_EQ(os.str(), "1618920000,100.5,10,1005,-1");
}
