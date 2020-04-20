#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static admin_banQuery[] = "\
        CREATE TABLE IF NOT EXISTS bans (\
            username VARCHAR(24), \
            ip VARCHAR(17), \
            gcpi VARCHAR(60), \
            reason VARCHAR(32), \
            admin VARCHAR(24), \
            ban_date datetime NOT NULL DEFAULT CURRENT_TIMESTAMP, \
            unban_date datetime, \
            UNIQUE KEY username (username) \
            )";
    mysql_tquery(MySQL_GetHandle(), admin_banQuery);
    log("setting up 'bans' table...");

    static const admin_accountQuery[] = "\
        CREATE TABLE IF NOT EXISTS admins ( \
    	u_id INT(11) NOT NULL, \
    	admin_level TINYINT(2) NOT NULL DEFAULT 0, \
    	PRIMARY KEY (u_id), \
    	FOREIGN KEY (u_id) REFERENCES players(u_id) ON DELETE CASCADE ON UPDATE CASCADE)\
    ";
    mysql_tquery(MySQL_GetHandle(), admin_accountQuery);
    log("setting up 'admins' table...");
}
