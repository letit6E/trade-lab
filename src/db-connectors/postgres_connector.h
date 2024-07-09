//
// Created by letit6E on 14.03.2024.
//

#ifndef TRADE_LAB_POSTGRES_CONNECTOR_H
#define TRADE_LAB_POSTGRES_CONNECTOR_H

#include <trade.h>

#include <pqxx/pqxx>
#include <string>
#include <vector>

#include "db_connector.h"

class PostgresConnector : DataBaseConnector {
   public:
    PostgresConnector(std::string db_name, std::string user_name,
                      std::string password);

    void connect() override;

    void insert_trades(const std::string& table_name,
                       const std::vector<Trade>& trades) override;

   private:
    std::unique_ptr<pqxx::connection> connection;
    std::string db_name, user_name, password;
};

#endif  // TRADE_LAB_POSTGRES_CONNECTOR_H
