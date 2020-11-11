#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS gang_members \
    ( \
    	gang_id INT(11) NOT NULL, \
        user_id INT(11) NOT NULL, \
        gang_rank INT(11) NOT NULL DEFAULT 1, \
    	PRIMARY KEY (user_id), \
    	FOREIGN KEY (user_id) REFERENCES players(user_id),\
		FOREIGN KEY (gang_id) REFERENCES gangs(gang_id)\
        ON DELETE CASCADE \
        ON UPDATE CASCADE \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("setting up 'gang_members' table...");
    return 1;
}