#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS gangs \
    ( \
    	g_id INT(11) NOT NULL, \
        u_id INT(11) NOT NULL, \
        gName VARCHAR(30) NOT NULL, \
    	gLeader VARCHAR(24) NOT NULL, \
        g_kills INT(11) NOT NULL DEFAULT 0, \
        g_deaths INT(11) NOT NULL DEFAULT 0, \
    	PRIMARY KEY (g_id), \
    	FOREIGN KEY (u_id) REFERENCES players(u_id) \
        ON DELETE CASCADE \
        ON UPDATE CASCADE \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("setting up 'gangs' table...");
    return 1;
}