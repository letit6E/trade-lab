#include <pybind11/functional.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "bar.h"
#include "bar_aggregator.h"
#include "exchange.h"
#include "finmetrics_calculator.h"
#include "footprint.h"
#include "postgres_connector.h"
#include "tick_aggregator.h"
#include "time_aggregator.h"
#include "trade.h"
#include "volume_aggregator.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<Trade>);

PYBIND11_MODULE(trade_lab_python_bindings, m) {
    // Trade class binding
    py::class_<Trade>(m, "Trade")
        .def(py::init<>())
        .def(py::init<long long, double, double, double, int>())
        .def_property_readonly("timestamp", &Trade::get_timestamp)
        .def_property_readonly("price", &Trade::get_price)
        .def_property_readonly("size", &Trade::get_size)
        .def_property_readonly("volume", &Trade::get_volume)
        .def_property_readonly("direction", &Trade::get_direction)
        .def("__repr__", [](const Trade& t) {
            std::ostringstream ss;
            ss << t;
            return ss.str();
        });

    // Bar class binding
    py::class_<Bar>(m, "Bar")
        .def(py::init<>())
        .def(py::init<const std::vector<Trade>&>())
        .def("add_trade", &Bar::add_trade)
        .def_property_readonly("open", &Bar::get_open)
        .def_property_readonly("close", &Bar::get_close)
        .def_property_readonly("high", &Bar::get_high)
        .def_property_readonly("low", &Bar::get_low)
        .def_property_readonly("volume", &Bar::get_volume)
        .def_property_readonly("size", &Bar::get_size)
        .def_property_readonly("vwap", &Bar::get_vwap)
        .def_property_readonly("startstamp", &Bar::get_startstamp)
        .def_property_readonly("stopstamp", &Bar::get_stopstamp)
        .def("__repr__", [](const Bar& b) {
            std::ostringstream ss;
            ss << b;
            return ss.str();
        });

    // FinancialMetricsCalculator binding
    py::class_<FinancialMetricsCalculator>(m, "FinancialMetricsCalculator")
        .def(py::init<std::deque<Bar>&>())
        .def("calculate_rsi", &FinancialMetricsCalculator::calculateRSI)
        .def("calculate_mean", &FinancialMetricsCalculator::calculateMean)
        .def("calculate_variance",
             &FinancialMetricsCalculator::calculateVariance)
        .def("calculate_volume", &FinancialMetricsCalculator::calculateVolume)
        .def("calculate_macd", &FinancialMetricsCalculator::calculateMACD);

    // BarAggregator and derived classes
    py::class_<BarAggregator>(m, "BarAggregator")
        .def("receive", &BarAggregator::receive)
        .def("ready", &BarAggregator::ready)
        .def("publish", &BarAggregator::publish);

    py::class_<TimeBarAggregator, BarAggregator>(m, "TimeBarAggregator")
        .def(py::init<long long>());

    py::class_<TickBarAggregator, BarAggregator>(m, "TickBarAggregator")
        .def(py::init<long long>());

    py::class_<VolumeBarAggregator, BarAggregator>(m, "VolumeBarAggregator")
        .def(py::init<double>());

    py::bind_vector<std::vector<Trade>>(m, "TradeVector");

    // Exchange class binding
    py::class_<Exchange>(m, "Exchange")
        .def(py::init<std::string, const std::string&>())
        .def("init_web_socket", &Exchange::init_webSocket)
        .def("read_socket", &Exchange::read_Socket)
        .def("is_socket_open", &Exchange::is_socket_open)
        .def("write_socket", &Exchange::write_Socket)
        .def("get_buffer_data", &Exchange::get_buffer_data)
        .def("get_socket_data", &Exchange::get_socket_data)
        .def("get_socket_trades", &Exchange::get_socket_trades,
             py::return_value_policy::reference_internal)
        .def("buffer_clear", &Exchange::buffer_clear)
        .def("web_socket_close", &Exchange::webSocket_close);

    // Footprint class
    py::class_<Footprint>(m, "Footprint")
        .def(py::init<>())
        .def_property_readonly("id", &Footprint::get_id)
        .def_property_readonly("price_min", &Footprint::get_price_min)
        .def_property_readonly("price_max", &Footprint::get_price_max)
        .def_property_readonly("buy_volume", &Footprint::get_buy_volume)
        .def_property_readonly("sell_volume", &Footprint::get_sell_volume)
        .def("__repr__", [](const Footprint& fp) {
            std::ostringstream ss;
            ss << fp;
            return ss.str();
        });
}