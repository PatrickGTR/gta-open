#include <YSI\y_hooks>


// VERY IMPORTANT!
// Do not change the priority of how the tables are being created
hook OnMySQLConnected() {

    // --------------------------------------------------------------------------------------------
    // PLAYERS
    // --------------------------------------------------------------------------------------------

    // players table.
    mysql_tquery(MySQL_GetHandle(), "players.sql");
    log("setting up 'players' table...");

    // player stats table.
    mysql_tquery(MySQL_GetHandle(), "stats.sql");
    log("setting up 'stats' table...");

    // vips table.
    mysql_tquery(MySQL_GetHandle(), "vips.sql");
    log("setting up 'vips' table...");

    // jailed players table.
    mysql_tquery_file(MySQL_GetHandle(), "jail.sql");
    log("setting up 'jailed' table...");

    // --------------------------------------------------------------------------------------------
    // ADMIN
    // --------------------------------------------------------------------------------------------

    // Admin accounts table.
    mysql_tquery_file(MySQL_GetHandle(), "admins.sql");
    log("setting up 'admins' table...");

    // Banned accounts table.
    mysql_tquery_file(MySQL_GetHandle(), "bans.sql");
    log("setting up 'bans' table...");

    // --------------------------------------------------------------------------------------------
    // HOUSES 
    // --------------------------------------------------------------------------------------------
    mysql_tquery_file(MySQL_GetHandle(), "houses.sql");
    log("setting up 'player_houses' table...");

    mysql_tquery_file(MySQL_GetHandle(), "furnitures.sql");
    log("setting up 'player_houses' table...");
    return 1;
}