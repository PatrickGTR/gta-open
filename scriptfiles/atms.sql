CREATE TABLE atms (
    atm_id int(11) NOT NULL AUTO_INCREMENT,
    atm_x float NOT NULL,
    atm_y float NOT NULL,
    atm_z float NOT NULL,
    rx float NOT NULL DEFAULT 0,
    ry float NOT NULL DEFAULT 0,
    rz float NOT NULL DEFAULT 0,
    wid tinyint(6) NOT NULL,
    interior tinyint(6) NOT NULL,
    PRIMARY KEY (atm_id)
);