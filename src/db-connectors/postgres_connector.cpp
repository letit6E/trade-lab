//
// Created by letit6E on 14.03.2024.
//

#include "postgres_connector.h"

PostgresConnector::PostgresConnector(const std::string &db_name,
                                     const std::string &user_name,
                                     const std::string &password) {
    connection = std::make_unique<pqxx::connection>(
        "dbname=" + db_name + " user=" + user_name + " password=" + password);
    if (!connection->is_open()) {
        throw std::runtime_error("Can't open database!");
    }
}

void PostgresConnector::insert_trades(const std::string &table_name,
                                      const std::vector<Trade> &trades) {
    if (!connection->is_open()) {
        throw std::runtime_error("Database is not opened!");
    }
    pqxx::nontransaction N(*connection);

    std::string sql =
        "SELECT EXISTS ("
        "SELECT FROM information_schema.tables "
        "WHERE  table_schema = 'public'"
        "AND    table_name   = '" +
        table_name + "');";

    pqxx::result R(N.exec(sql));
    N.abort();

    pqxx::work W(*connection);
    if (R.empty() || !R[0][0].as<bool>()) {
        sql =
            "CREATE TABLE trades("
            "timestamp BIGINT     NOT NULL,"
            "price     DOUBLE PRECISION,"
            "size      DOUBLE PRECISION,"
            "volume    DOUBLE PRECISION,"
            "direction INTEGER);";

        W.exec(sql);
    }

    for (const auto &trade : trades) {
        sql =
            "INSERT INTO trades (timestamp, price, size, volume, direction) "
            "VALUES (" +
            std::to_string(trade.get_timestamp()) + ", " +
            std::to_string(trade.get_price()) + ", " +
            std::to_string(trade.get_size()) + ", " +
            std::to_string(trade.get_volume()) + ", " +
            std::to_string(trade.get_direction()) + ");";

        W.exec(sql);
    }
    W.commit();
}