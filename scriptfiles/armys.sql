CREATE TABLE armys (
    u_id int(11) NOT NULL,
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