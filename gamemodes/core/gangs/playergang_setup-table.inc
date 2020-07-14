#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS player_gang \
    ( \
    	g_id INT(11) NOT NULL, \
        u_id INT(11) NOT NULL, \
        gRank INT(11) NOT NULL DEFAULT 1, \
    	PRIMARY KEY (u_id), \
    	FOREIGN KEY (u_id) REFERENCES players(u_id),\
		FOREIGN KEY (g_id) REFERENCES gangs(g_id)\
        ON DELETE CASCADE \
        ON UPDATE CASCADE \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("setting up 'player_gang' table...");
    return 1;
}