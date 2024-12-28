#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <vector>

#include "trade.h"

class Bar {
   public:
    double open, close, high, low, volume;
    long long start_timestamp, end_timestamp;
    std::map<std::string, double> statistics;

    Bar()
        : open(0),
          close(0),
          high(0),
          low(0),
          volume(0),
          start_timestamp(0),
          end_timestamp(0) {}

    void add_trade(const Trade &trade) {
        if (start_timestamp == 0) start_timestamp = trade.get_timestamp();
        end_timestamp = trade.get_timestamp();
        if (volume == 0) open = trade.get_price();
        close = trade.get_price();
        high = std::max(high, trade.get_price());
        low = (low == 0) ? trade.get_price() : std::min(low, trade.get_price());
        volume += trade.get_volume();
    }

    void add_statistics(const std::map<std::string, double> &stats) {
        statistics = stats;
    }

    friend std::ostream &operator<<(std::ostream &os, const Bar &bar) {
        os << "Bar(Open: " << bar.open << ", Close: " << bar.close
           << ", High: " << bar.high << ", Low: " << bar.low
           << ", Volume: " << bar.volume << ")\n";
        for (const auto &[key, value] : bar.statistics) {
            os << key << ": " << value << "\n";
        }
        return os;
    }
};

class Statistic {
   public:
    using ComputeFunc = std::function<double(const std::vector<Trade> &)>;

   private:
    std::string name;
    ComputeFunc compute;

   public:
    Statistic(const std::string &n, ComputeFunc c) : name(n), compute(c) {}

    double compute_stat(const std::vector<Trade> &trades) const {
        return compute(trades);
    }

    std::string get_name() const { return name; }
};

class AggregatorConfig {
   public:
    virtual void feed(const Trade &trade) = 0;
    virtual std::pair<Trade, Trade> split(const Trade &trade) = 0;
    virtual std::map<std::string, double> compute_statistics(
        const std::vector<Trade> &trades) const = 0;
    virtual ~AggregatorConfig() = default;
};

class TimeIntervalConfig : public AggregatorConfig {
   private:
    long long interval_duration;
    long long current_start;
    std::vector<Trade> trades;
    std::vector<Statistic> statistics;

   public:
    TimeIntervalConfig(long long duration, const std::vector<Statistic> &stats)
        : interval_duration(duration), current_start(0), statistics(stats) {}

    void feed(const Trade &trade) override { trades.push_back(trade); }

    std::pair<Trade, Trade> split(const Trade &trade) override {
        if (current_start == 0) current_start = trade.get_timestamp();

        if (trade.get_timestamp() - current_start >= interval_duration) {
            current_start = trade.get_timestamp();
            return {trade, Trade()};  // All to current, none to next
        }

        return {Trade(), trade};  // None to current, all to next
    }

    std::map<std::string, double> compute_statistics(
        const std::vector<Trade> &trades) const override {
        std::map<std::string, double> stats_results;
        for (const auto &stat : statistics) {
            stats_results[stat.get_name()] = stat.compute_stat(trades);
        }
        return stats_results;
    }
};

class NewBarAggregator {
   private:
    std::shared_ptr<AggregatorConfig> config;
    Bar current_bar;
    std::queue<Bar> bar_queue;
    std::vector<Trade> current_trades;

   public:
    explicit NewBarAggregator(std::shared_ptr<AggregatorConfig> cfg)
        : config(std::move(cfg)) {}

    void receive(const Trade &trade) {
        config->feed(trade);
        auto [to_current, to_next] = config->split(trade);

        if (to_current.get_timestamp() != 0) {
            current_bar.add_trade(to_current);
            current_trades.push_back(to_current);
        }

        if (to_next.get_timestamp() != 0) {
            close_current_bar();
            current_bar.add_trade(to_next);
            current_trades.push_back(to_next);
        }
    }

    void close_current_bar() {
        if (current_bar.volume > 0) {
            current_bar.add_statistics(
                config->compute_statistics(current_trades));
            bar_queue.push(current_bar);
            current_bar = Bar();
            current_trades.clear();
        }
    }

    bool ready() { return !bar_queue.empty(); }

    Bar publish() {
        if (ready()) {
            Bar published_bar = bar_queue.front();
            bar_queue.pop();
            return published_bar;
        } else {
            throw std::runtime_error("There are no ready bars to publish.");
        }
    }
};

int main() {
    auto stats = std::vector<Statistic>{
        Statistic("Total Volume",
                  [](const std::vector<Trade> &trades) {
                      return std::accumulate(
                          trades.begin(), trades.end(), 0.0,
                          [](double sum, const Trade &trade) {
                              return sum + trade.get_volume();
                          });
                  }),
        Statistic("Average Price", [](const std::vector<Trade> &trades) {
            if (trades.empty()) return 0.0;
            double total_price =
                std::accumulate(trades.begin(), trades.end(), 0.0,
                                [](double sum, const Trade &trade) {
                                    return sum + trade.get_price();
                                });
            return total_price / trades.size();
        })};

    auto config =
        std::make_shared<TimeIntervalConfig>(60, stats);  // 60-second interval
    NewBarAggregator aggregator(config);

    std::vector<Trade> trades = {Trade(1609459200, 100.0, 10.0, 1000.0, 1),
                                 Trade(1609459260, 101.0, 5.0, 500.0, -1),
                                 Trade(1609459320, 102.0, 20.0, 2000.0, 1),
                                 Trade(1609459380, 99.0, 15.0, 1500.0, -1),
                                 Trade(1609459440, 103.0, 8.0, 800.0, 1)};

    for (const auto &trade : trades) {
        aggregator.receive(trade);
    }

    while (aggregator.ready()) {
        std::cout << aggregator.publish() << std::endl;
    }

    return 0;
}