// Copyright (c) 2025 seaStarLxy.
// Licensed under the MIT License.

#pragma once
#include <string>
#include <expected>
#include <boost/redis/connection.hpp>
#include <boost/asio.hpp>

namespace user_service::infrastructure {

    enum class RedisErrorType {
        SystemError,
        CommandError,
        ProtocolError
    };

    struct RedisError {
        RedisErrorType type;
        std::string message;
    };

    struct RedisConfig {
        std::string host;
        std::string port;
    };

    class RedisClient {
    public:
        RedisClient(const std::shared_ptr<boost::asio::io_context>& ioc, const RedisConfig& config);
        ~RedisClient();
        boost::asio::awaitable<void> Init();
        boost::asio::awaitable<std::expected<void, RedisError>> Set(const std::string& key, const std::string& value) const;
        boost::asio::awaitable<std::expected<void, RedisError>> Set(const std::string& key, const std::string& value, const std::chrono::seconds& expiry) const;
        boost::asio::awaitable<std::expected<std::optional<std::string>, RedisError>> Get(const std::string& key) const;
    private:
        // 等待联通
        boost::asio::awaitable<std::expected<void, RedisError>> Ping() const;
        // 结果解析
        [[nodiscard]] std::expected<std::optional<std::string>, RedisError> ExtractResult(
            const boost::system::result<boost::redis::resp3::node, boost::redis::adapter::error>& result,
            const std::string& command_name, const std::string& key_context= "") const;

        const std::shared_ptr<boost::asio::io_context> ioc_;
        std::shared_ptr<boost::redis::connection> conn_;
        boost::redis::config cfg_;
    };
}