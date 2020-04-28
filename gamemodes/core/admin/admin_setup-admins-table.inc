#include <YSI_Coding\y_hooks>

hook OnMYSQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS admins \
    ( \
    	u_id INT(11) NOT NULL, \
    	admin_level TINYINT(2) NOT NULL DEFAULT 0, \
    	PRIMARY KEY (u_id), \
    	FOREIGN KEY (u_id) REFERENCES players(u_id) \
        ON DELETE CASCADE \
        ON UPDATE CASCADE \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("setting up 'admins' table...");
    return 1;
}