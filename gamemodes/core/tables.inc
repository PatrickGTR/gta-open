#include <YSI_Coding\y_hooks>


// VERY IMPORTANT!
// Do not change the priority of how the tables are being created
hook OnMySQLConnected() {

    // --------------------------------------------------------------------------------------------
    // PLAYERS
    // --------------------------------------------------------------------------------------------

    // players table.
    mysql_tquery(MySQL_GetHandle(), "players.sql");
    Logger_Log("setting up 'players' table...");

    // player stats table.
    mysql_tquery(MySQL_GetHandle(), "stats.sql");
    Logger_Log("setting up 'stats' table...");

    // vips table.
    mysql_tquery(MySQL_GetHandle(), "vips.sql");
    Logger_Log("setting up 'vips' table...");

    // jailed players table.
    mysql_tquery_file(MySQL_GetHandle(), "jail.sql");
    Logger_Log("setting up 'jailed' table...");

    // --------------------------------------------------------------------------------------------
    // ADMIN
    // --------------------------------------------------------------------------------------------

    // Admin accounts table.
    mysql_tquery_file(MySQL_GetHandle(), "admins.sql");
    Logger_Log("setting up 'admins' table...");

    // Banned accounts table.
    mysql_tquery_file(MySQL_GetHandle(), "bans.sql");
    Logger_Log("setting up 'bans' table...");

    // --------------------------------------------------------------------------------------------
    // HOUSES 
    // --------------------------------------------------------------------------------------------

    mysql_tquery_file(MySQL_GetHandle(), "houses.sql");
    Logger_Log("setting up 'player_houses' table...");
    Logger_Log("setting up 'house_furniture' table...");

    // --------------------------------------------------------------------------------------------
    // Gangs
    // --------------------------------------------------------------------------------------------
    mysql_tquery_file(MySQL_GetHandle(), "gangs.sql");
    Logger_Log("setting up 'gangs' table...");
    Logger_Log("setting up 'gang_members' table...");
    return 1;
}

