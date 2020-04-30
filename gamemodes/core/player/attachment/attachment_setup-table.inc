#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
	mysql_tquery(MySQL_GetHandle(),
		"CREATE TABLE IF NOT EXISTS attachments \
        (\
            u_id INTEGER, \
            slot TINYINT(2) NOT NULL, \
            model SMALLINT(6) NOT NULL, \
            bone TINYINT(2) NOT NULL, \
            offset_x FLOAT NOT NULL, \
            offset_y FLOAT NOT NULL, \
            offset_z FLOAT NOT NULL, \
            rotation_x FLOAT NOT NULL, \
            rotation_y FLOAT NOT NULL, \
            rotation_z FLOAT NOT NULL,  \
            scale_x FLOAT NOT NULL, \
            scale_y FLOAT NOT NULL, \
            scale_z FLOAT NOT NULL, \
		FOREIGN KEY(u_id) REFERENCES players(u_id) ON DELETE CASCADE ON UPDATE RESTRICT)");
    log("setting up 'attachments' table...");
    return 1;
}