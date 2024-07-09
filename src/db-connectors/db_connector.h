//
// Created by letit6E on 10.05.2024.
//

#ifndef TRADE_LAB_DB_CONNECTOR_H
#define TRADE_LAB_DB_CONNECTOR_H

#include <trade.h>

class DataBaseConnector {
   public:
    virtual void connect() {
        throw std::logic_error("This is abstract method and not implemented");
    }

    virtual void insert_trades(const std::string& table_name,
                               const std::vector<Trade>& trades) {
        throw std::logic_error("This is abstract method and not implemented");
    }
};

#endif  // TRADE_LAB_DB_CONNECTOR_H
