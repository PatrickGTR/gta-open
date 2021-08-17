CREATE TABLE IF NOT EXISTS player_items (
    u_id int(11) NOT NULL,
    c4 tinyint(4) NOT NULL DEFAULT 0,
    crack tinyint(4) NOT NULL DEFAULT 0,
    weed tinyint(4) NOT NULL DEFAULT 0,
    picklock tinyint(4) NOT NULL DEFAULT 0,
    wallet tinyint(4) NOT NULL DEFAULT 0,
    rope tinyint(4) NOT NULL DEFAULT 0,
    condom tinyint(4) NOT NULL DEFAULT 0,
    scissors tinyint(4) NOT NULL DEFAULT 0,
    UNIQUE KEY
        u_id (u_id),
    FOREIGN KEY
        (u_id)
    REFERENCES
        players (u_id)
    ON DELETE
        CASCADE
    ON UPDATE
        NO ACTION
);