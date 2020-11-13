CREATE TABLE IF NOT EXISTS player_houses
(
    house_id SMALLINT NOT NULL DEFAULT 0, 
    u_id INT(11) NULL DEFAULT NULL, 
    description VARCHAR(32) DEFAULT 'No description', 
    price MEDIUMINT NOT NULL, 
    money_stored MEDIUMINT NOT NULL, 
    interior TINYINT NOT NULL DEFAULT 0, 
    entrance_x FLOAT NOT NULL, 
    entrance_y FLOAT NOT NULL, 
    entrance_z FLOAT NOT NULL, 
    entrance_a FLOAT NOT NULL, 
    interior_id TINYINT(4) NOT NULL, 
    virtual_world MEDIUMINT NOT NULL, 
    PRIMARY KEY (house_id), 
    FOREIGN KEY(u_id) REFERENCES players(u_id) ON DELETE SET NULL ON UPDATE CASCADE
);