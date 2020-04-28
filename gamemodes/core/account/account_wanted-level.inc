#include <YSI_Coding\y_hooks>

static 
    Statement: stmt_updateWantedLevel;

hook OnMySQLConnected(playerid) {
    stmt_updateWantedLevel = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE players SET wanted_level = ? WHERE u_id = ?");
    return 1;
}

stock Player_SaveWantedLevel(playerid, level) {

    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    MySQL_BindInt(stmt_updateWantedLevel, 0, level);
    MySQL_BindInt(stmt_updateWantedLevel, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_updateWantedLevel);
    return 1;
}
