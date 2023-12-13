//
// Created by Konstantin Gredeskoul on 5/16/17.
//
#include <trading_structures/trade.h>
#include "gtest/gtest.h"

using namespace std;

TEST(TradeTests, TestOne) {
    Trade trade;

    std::istringstream iss("1618920000,100.5,10,1005,1\n");
    iss >> trade;

    ASSERT_EQ(trade.direction, 1);
}
