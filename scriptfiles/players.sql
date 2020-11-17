CREATE TABLE IF NOT EXISTS players
(
    u_id int(11) NOT NULL AUTO_INCREMENT,
    username varchar(24) NOT NULL,
    password char(250) NOT NULL,
    register_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    last_login DATETIME DEFAULT NULL,
    armour FLOAT NOT NULL DEFAULT '100.0',
    health FLOAT NOT NULL DEFAULT '100.0',
    PRIMARY KEY (u_id),
    UNIQUE KEY username (username)
);