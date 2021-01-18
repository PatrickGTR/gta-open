CREATE TABLE IF NOT EXISTS gangs (
    id INT(11) NOT NULL AUTO_INCREMENT,
    leader_uid INT(11) NOT NULL,
    name VARCHAR(30) NOT NULL,
    colour BIGINT(11) NOT NULL DEFAULT -1,
    kills INT(11) NOT NULL DEFAULT 0,
    deaths INT(11) NOT NULL DEFAULT 0,
    PRIMARY KEY
        (id),
    FOREIGN KEY
        (leader_uid)
    REFERENCES
        players(u_id)
    ON DELETE
        CASCADE
    ON UPDATE
        NO ACTION
);
CREATE TABLE IF NOT EXISTS gang_members (
    gang_id INT(11) NOT NULL AUTO_INCREMENT,
    user_id INT(11) NOT NULL,
    gang_rank INT(11) NOT NULL DEFAULT 1,
    PRIMARY KEY
        (user_id),
    FOREIGN KEY
        (user_id) REFERENCES players(u_id),
    FOREIGN KEY
        (gang_id) REFERENCES gangs(id)
    ON DELETE
        CASCADE
    ON UPDATE
        NO ACTION
);