// Copyright (c) 2025 seaStarLxy.
// All Rights Reserved.

#pragma once
#include <libpq-fe.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <memory>

namespace common::db {
    using PGResultPtr = std::unique_ptr<PGresult, decltype(&PQclear)>;

    class PQConnection : public std::enable_shared_from_this<PQConnection> {
    public:
        explicit PQConnection(boost::asio::io_context &ioc);

        boost::asio::awaitable<void> async_connect(const std::string &conn_str);

        boost::asio::awaitable<PGResultPtr> async_exec_params(const std::string &query,
                                                              const std::vector<std::string> &params);

    private:
        // 维护数据库连接，
        std::unique_ptr<PGconn, decltype(&PQfinish)> conn_;
        // 协程上下文
        boost::asio::posix::stream_descriptor socket_;
    };
}
