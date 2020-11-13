CREATE TABLE IF NOT EXISTS jailed
(
    u_id int(11) NOT NULL AUTO_INCREMENT,
    bail_required tinyint(4) NOT NULL DEFAULT '0',
    jailed_time mediumint(8) NOT NULL DEFAULT '0',
    bail_balance mediumint(8) NOT NULL DEFAULT '0',
    PRIMARY KEY (u_id),
    FOREIGN KEY (u_id) REFERENCES players(u_id)
    ON DELETE CASCADE
    ON UPDATE RESTRICT
);