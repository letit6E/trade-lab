#include <iostream>
#include "trading_structures/trade.h"

using namespace std;

static const char *const HEADER = "\nTrade-lab © 2023 Rustam Shangareev.\n\n";
static const char *const USAGE = "Usage:\n\ttrade-lab <data>\n\nDescription:\n\tCreates the trade class,\n\tand reports its inside\n";

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("%s%s", HEADER, USAGE);
        return 0;
    }

    Trade trade;

    std::istringstream iss(argv[1]);
    iss >> trade;

    std::cout << trade << std::endl;

    return 0;
}