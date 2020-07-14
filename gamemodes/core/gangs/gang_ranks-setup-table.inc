#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS gang_ranks \
    ( \
        g_id INT(11) NOT NULL, \
    	rank1 VARCHAR(30) NOT NULL DEFAULT 'Rank 1', \
        rank2 VARCHAR(30) NOT NULL DEFAULT 'Rank 2', \
        rank3 VARCHAR(30) NOT NULL DEFAULT 'Rank 3', \
        rank4 VARCHAR(30) NOT NULL DEFAULT 'Rank 4', \
        rank5 VARCHAR(30) NOT NULL DEFAULT 'Rank 5', \
        rank6 VARCHAR(30) NOT NULL DEFAULT 'Rank 6', \
        rank7 VARCHAR(30) NOT NULL DEFAULT 'Rank 7', \
        rank8 VARCHAR(30) NOT NULL DEFAULT 'Rank 8', \
        rank9 VARCHAR(30) NOT NULL DEFAULT 'Rank 9', \
        rank10 VARCHAR(30) NOT NULL DEFAULT 'Rank 10', \
    	PRIMARY KEY (g_id), \
    	FOREIGN KEY (g_id) REFERENCES gangs(g_id) \
        ON DELETE CASCADE \
        ON UPDATE CASCADE \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("setting up 'gang_ranks' table...");
    return 1;
}