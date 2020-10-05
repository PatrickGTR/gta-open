#include <YSI_Coding\y_hooks>

static
    Statement:stmt_saveArmour
;

hook OnMySQLConnected()
{
    static const updateQuery[] = "\
    UPDATE \
        players_health \
    SET \
        armour = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_saveArmour = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);
    return 1;
}

hook function SetPlayerArmour(playerid, Float:armour)
{
    MySQL_BindFloat(stmt_saveArmour, 0, armour);
    MySQL_BindInt(stmt_saveArmour, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveArmour);
    continue(playerid, armour);
}

hook OnPlayerDisconnect(playerid, reason)
{
    new Float:armour;
    GetPlayerArmour(playerid, armour);
    MySQL_BindFloat(stmt_saveArmour, 0, armour);
    MySQL_BindInt(stmt_saveArmour, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveArmour);
    return 1;
}