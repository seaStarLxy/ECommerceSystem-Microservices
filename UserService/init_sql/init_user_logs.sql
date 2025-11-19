-- 登录日志表 (只写)
CREATE TABLE user_login_logs
(
    id       BIGSERIAL PRIMARY KEY,
    user_id  UUID NOT NULL,
    login_ip VARCHAR(45),
    login_at TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_user FOREIGN KEY (user_id) REFERENCES users (id)
);

-- 加索引
CREATE INDEX idx_login_logs_user ON user_login_logs (user_id);
CREATE INDEX idx_login_logs_time ON user_login_logs (login_at);