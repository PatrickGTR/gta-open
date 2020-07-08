#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS player_bank \
    ( \
    	u_id INT(11) NOT NULL, \
    	bank_money INT(11) NOT NULL DEFAULT 0, \
        player_tax INT(11) NOT NULL DEFAULT 0, \
        player_dept INT(11) NOT NULL DEFAULT 0, \
    	PRIMARY KEY (u_id), \
    	FOREIGN KEY (u_id) REFERENCES players(u_id) \
        ON DELETE CASCADE \
        ON UPDATE CASCADE \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("setting up 'player_bank' table...");
    return 1;
}