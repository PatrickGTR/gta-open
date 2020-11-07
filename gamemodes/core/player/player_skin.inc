#include <YSI_Coding\y_hooks>

static
    PlayerSkin[MAX_PLAYERS] = -1,
    bool:PlayerNew[MAX_PLAYERS] = false,
    Statement: stmt_updatePlayerSkin,
    Statement: stmt_loadPlayerSkin;

hook OnMySQLConnected() {
    stmt_updatePlayerSkin = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE player_stats SET skin = ? WHERE u_id = ?");
    stmt_loadPlayerSkin = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT skin FROM player_stats WHERE u_id = ?");
    return 1;
}

hook OnPlayerRegister(playerid) {
    PlayerNew[playerid] = true;
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerSkin[playerid] = -1;
    PlayerNew[playerid] = false;
    return 1;   
}

hook OnPlayerLogin(playerid) {
    inline const OnSkinLoad() {
        new
            playerSkin;

        MySQL_BindResultInt(stmt_loadPlayerSkin, 0, playerSkin);

        if(MySQL_Statement_FetchRow(stmt_loadPlayerSkin)) {
            Player_SetSkin(playerid, playerSkin);
        }
    }
    MySQL_BindInt(stmt_loadPlayerSkin, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerSkin, using inline OnSkinLoad);
    return 1;
}

hook OnPlayerFirstSpawn(playerid) {
    SetPlayerSkin(playerid, Player_GetSkin(playerid));

    if(PlayerNew[playerid]) {
        MySQL_BindInt(stmt_updatePlayerSkin, 0, Player_GetSkin(playerid));
        MySQL_BindInt(stmt_updatePlayerSkin, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteParallel(stmt_updatePlayerSkin);
    }
    return 1;
}

stock Player_SetSkin(playerid, skinid) {
	PlayerSkin[playerid] = skinid;
}

stock Player_GetSkin(playerid) {
	return PlayerSkin[playerid];
}