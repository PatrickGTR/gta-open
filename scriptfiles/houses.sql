CREATE TABLE IF NOT EXISTS player_houses (
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
    PRIMARY KEY
        (house_id),
    FOREIGN KEY
        (u_id)
    REFERENCES
        players(u_id)
    ON DELETE
        SET NULL
    ON UPDATE
        NO ACTION
);

CREATE TABLE IF NOT EXISTS house_settings (
    house_id smallint(6) NOT NULL,
    locked tinyint(1) NOT NULL DEFAULT 0,
    PRIMARY KEY
        (house_id),
    FOREIGN KEY
        (house_id)
    REFERENCES
        player_houses (house_id)
    ON DELETE
        CASCADE
    ON UPDATE
        CASCADE
);

CREATE TABLE IF NOT EXISTS house_furniture (
    furniture_id INT(11) AUTO_INCREMENT,
    house_id SMALLINT(6) NOT NULL,
    object_id INT(11) NOT NULL,
    x FLOAT(6) NOT NULL,
    y FLOAT(6) NOT NULL,
    z FLOAT(6) NOT NULL,
    rx FLOAT(6) NOT NULL,
    ry FLOAT(6) NOT NULL,
    rz FLOAT(6) NOT NULL,
    intid INT(11) NOT NULL,
    vworld INT(11) NOT NULL,
    INDEX
        (house_id),
    PRIMARY KEY
        (furniture_id),
    FOREIGN KEY
        (house_id)
    REFERENCES
        player_houses(house_id)
    ON DELETE
        CASCADE
    ON UPDATE
        NO ACTION
);