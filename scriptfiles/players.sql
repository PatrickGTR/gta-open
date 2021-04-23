CREATE TABLE IF NOT EXISTS players
(
    u_id int(11) NOT NULL AUTO_INCREMENT,
    username varchar(24) NOT NULL,
    password char(60) NOT NULL,
    register_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    last_login DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    PRIMARY KEY
        (u_id),
    UNIQUE KEY
        username (username)
);
