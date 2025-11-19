CREATE TABLE users
(
    -- 使用 UUIDv7
    id            UUID PRIMARY KEY,

    phone_number  VARCHAR(20)                           NOT NULL UNIQUE,
    username      VARCHAR(64) UNIQUE,
    email         VARCHAR(128) UNIQUE,

    -- 密码安全
    password_hash VARCHAR(256)                          NOT NULL,
    salt          VARCHAR(64)                           NOT NULL,

    -- 资料
    avatar_url    VARCHAR(512),
    status        SMALLINT    DEFAULT 0                 NOT NULL, -- 0:正常, 1:冻结

    -- 时间
    created_at    TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP NOT NULL,
    deleted_at    TIMESTAMPTZ                                     -- 软删除，不删物理行
);