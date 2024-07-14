#include <fstream>
#include <iomanip>

#include "bar-aggregators/time_aggregator.h"

int main() {
    std::string input_file = "trades.csv";
    std::ifstream trades(input_file);

    // receiving
    Trade trade;
    long long duration = 120000;  // change this
    TimeBarAggregator tba(duration);
    while (trades >> trade) {
        tba.receive(trade);
    }
    trades.close();

    // tba contains bars in queue

    std::string output_file = "bars.csv";
    std::ofstream bars(output_file);
    bars << std::fixed;            // fixed-point notation
    bars << std::setprecision(6);  // float precision (change this)
    while (tba.ready()) {
        bars << tba.publish() << '\n';
    }
    bars << tba.publish() << '\n';  // last unfinished bar (maybe don't use)
    bars.close();

    return 0;
}
