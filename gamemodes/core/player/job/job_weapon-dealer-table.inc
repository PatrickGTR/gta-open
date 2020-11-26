#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS player_weaponInv \
    ( \
        u_id INT(11) NOT NULL AUTO_INCREMENT, \
        index mediumint(8) NOT NULL, \
        count mediumint(8) NOT NULL, \
        weaponid smallint(8) NOT NULL, \
        ammo mediumint(8) NOT NULL, \
        price bigint(20) NOT NULL, \
        armours mediumint(8) NOT NULL, \
        PRIMARY KEY (u_id), \
        FOREIGH KEY (u_id) REFERENCES players(u_id) \
        ON DELETE CASCADE \
        ON UPDATE RESTRICT \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    Logger_Log("Creating player_weaponInv...");
}