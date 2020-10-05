#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS players_health \
        (\
            u_id int(11) NOT NULL AUTO_INCREMENT,\
            health float NOT NULL,\
            armour float NOT NULL,\
            PRIMARY KEY (u_id), \
            FOREIGN KEY (u_id) REFERENCES players(u_id) \
            ON DELETE CASCADE \
            ON UPDATE RESTRICT \
        )";
    mysql_tquery(MySQL_GetHandle(), query);

    log("setting up 'players_health' table...");
    return 1;
}
