//
// Created by letit6E on 14.03.2024.
//

#ifndef TRADE_LAB_POSTGRES_CONNECTOR_H
#define TRADE_LAB_POSTGRES_CONNECTOR_H

#include <trade.h>

#include <pqxx/pqxx>
#include <string>
#include <vector>

class PostgresConnector {
   public:
    PostgresConnector(const std::string& db_name, const std::string& user_name,
                      const std::string& password);

    void insert_trades(const std::string& table_name,
                       const std::vector<Trade>& trades);

   private:
    std::unique_ptr<pqxx::connection> connection;
};

#endif  // TRADE_LAB_POSTGRES_CONNECTOR_H
