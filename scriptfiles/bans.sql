CREATE TABLE IF NOT EXISTS bans (
    username VARCHAR(24),
    ip VARCHAR(17),
    gcpi VARCHAR(60),
    reason VARCHAR(32),
    admin VARCHAR(24),
    ban_date datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
    unban_date datetime,
    UNIQUE KEY username (username)
);