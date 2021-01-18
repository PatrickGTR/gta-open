
CREATE TABLE IF NOT EXISTS player_shots_stats (
    uid int(11) NOT NULL,
    chest int(11) NOT NULL DEFAULT 0,
    torso int(11) NOT NULL DEFAULT 0,
    left_arm int(11) NOT NULL DEFAULT 0,
    right_arm int(11) NOT NULL DEFAULT 0,
    left_leg int(11) NOT NULL DEFAULT 0,
    right_leg int(11) NOT NULL DEFAULT 0,
    head int(11) NOT NULL DEFAULT 0,
    misses int(11) NOT NULL DEFAULT 0,
    PRIMARY KEY
        (uid),
    FOREIGN KEY
        (uid)
    REFERENCES
        players (u_id)
    ON DELETE
        CASCADE
    ON UPDATE
        CASCADE
);