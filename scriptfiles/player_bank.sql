CREATE TABLE player_bank (
    u_id int(11) NOT NULL,
    money int(11) NOT NULL DEFAULT 0,
    PRIMARY KEY
        (u_id),
    FOREIGN KEY
        (u_id)
    REFERENCES
    players (u_id)
    ON DELETE
        CASCADE
    ON UPDATE
        NO ACTION
);