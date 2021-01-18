#include <YSI_Coding\y_hooks>

static
    BitArray:PlayerIsArmy<MAX_PLAYERS>;

hook OnPlayerConnect(playerid) {
    Bit_Set(PlayerIsArmy, playerid, false);
    return 1;
}

hook OnPlayerLogin(playerid) {
    static
        Statement:stmt_isArmy;

    inline const OnArmyLoad() {
        if(MySQL_Statement_FetchRow(stmt_isArmy)) {
            Bit_Set(PlayerIsArmy, playerid, true);
        }
    }

    stmt_isArmy = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT 1 FROM armys WHERE u_id = ?");
    MySQL_BindInt(stmt_isArmy, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_isArmy, using inline OnArmyLoad);
    return 1;
}

hook OnPlayerRequestSpawn(playerid) {
    if(Player_GetClass(playerid) == TEAM_ARMY) {
        if(!Player_IsArmy(playerid)) {
            SendErrorMsg(playerid, "No permission to play as army");
            return ~0;
        }
    }
    return 1;
}

stock Player_AddToArmyDB(playerid) {
    Player_SetArmy(playerid, true);

    new stmt_insertArmy = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO armys (u_id) VALUES (?)");
    MySQL_BindInt(stmt_insertArmy, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_insertArmy);
    MySQL_StatementClose(stmt_insertArmy);
}

Player_IsArmy(playerid) {
    return Bit_Get(PlayerIsArmy, playerid);
}

stock Player_SetArmy(playerid, bool:toggle) {
    Bit_Set(PlayerIsArmy, playerid, toggle);
}