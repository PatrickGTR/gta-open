CREATE TABLE IF NOT EXISTS player_stats
(
    u_id int(11) NOT NULL AUTO_INCREMENT,
    armour float NOT NULL DEFAULT '100.0',
    health float NOT NULL DEFAULT '100.0',
    kills mediumint(8) NOT NULL DEFAULT '0',
    deaths mediumint(8) NOT NULL DEFAULT '0',
    job_id tinyint(4) NOT NULL DEFAULT '0',
    class_id tinyint(4) NOT NULL DEFAULT '0',
    wanted_level mediumint(6) NOT NULL DEFAULT '0',
    player_bounty mediumint(8) NOT NULL DEFAULT '0',
    money bigint(20) NOT NULL DEFAULT '0',
    score int(11) NOT NULL DEFAULT '0',
    skin smallint(4) NOT NULL DEFAULT '0',
    PRIMARY KEY
        (u_id),
    FOREIGN KEY
        (u_id)
    REFERENCES
        players(u_id)
    ON DELETE
        CASCADE
    ON UPDATE
        NO ACTION
);