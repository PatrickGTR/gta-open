#include <YSI_Coding\y_hooks>

static
    Statement: stmt_updateWantedLevel;

hook OnMySQLConnected(playerid) {
    stmt_updateWantedLevel = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE player_stats SET wanted_level = ? WHERE u_id = ?");
    return 1;
}

stock Player_SaveWantedLevel(playerid, plevel) {

    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    MySQL_BindInt(stmt_updateWantedLevel, 0, plevel);
    MySQL_BindInt(stmt_updateWantedLevel, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_updateWantedLevel);
    return 1;
}
