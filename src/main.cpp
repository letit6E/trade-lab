#include <iostream>
#include "trading_structures/trade.h"

using namespace std;

static const char *const HEADER = "\nDivider © 2018 Monkey Claps Inc.\n\n";
static const char *const USAGE = "Usage:\n\tdivider <numerator> <denominator>\n\nDescription:\n\tComputes the result of a fractional division,\n\tand reports both the result and the remainder.\n";

int main(int argc, const char* argv[]) {
    Trade trade;

    std::istringstream iss("1618920000,100.5,10,1005,1\n");
    iss >> trade;

    std::cout << trade << std::endl;

    return 0;
}