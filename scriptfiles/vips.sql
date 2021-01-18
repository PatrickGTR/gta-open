CREATE TABLE IF NOT EXISTS vips (
    u_id INT(11) AUTO_INCREMENT,
    vip_level TINYINT(2) NOT NULL DEFAULT 0,
    vip_expire_date datetime NULL,
    PRIMARY KEY
        (u_id),
    FOREIGN KEY
        (u_id)
    REFERENCES
        players(u_id)
    ON DELETE
        CASCADE
    ON UPDATE
        RESTRICT
);