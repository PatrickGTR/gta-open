
#include <account_create>
#include <account_login>
#include <account_vip>
#include <account_wanted-level>
#include <inventory>
#include <account_stats>

#if SETUP_TABLE
    #include <account_setup-players-table>
    #include <account_setup-vip-table>
    #include <account_setup-inventory>
    #include <account_setup-jailed>
    #include <account_setup-stats>
#endif

#include <YSI_Coding\y_hooks>

static
    Player_UID[MAX_PLAYERS],
    bool:PlayerArmyLvl[MAX_PLAYERS],
    bool:Blacklist[MAX_PLAYERS],
    Statement: stmt_checkPlayer,
    Statement: stmt_loadPlayerArmy,
    Statement: stmt_insertPlayerArmy,
    Statement: stmt_savePlayerMoney;

hook OnMySQLConnected() {
    stmt_checkPlayer = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT u_id, password FROM players WHERE username=?");
    stmt_savePlayerMoney = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE player_stats SET money=? WHERE u_id=?");
    stmt_loadPlayerArmy = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT IsArmy, Blacklisted FROM armys WHERE u_id = ?");
    stmt_insertPlayerArmy = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO armys (u_id) VALUES (?)");
    return 1;
}

hook OnPlayerConnect(playerid) {
    Player_UID[playerid] = 0;
    PlayerArmyLvl[playerid] = false;
    Blacklist[playerid] = false;
    return 1;
}

hook OnPlayerLogin(playerid) {
    MySQL_BindInt(stmt_insertPlayerArmy, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_insertPlayerArmy);
    Player_SetLoginStatus(playerid, true);
    return 1;
}

public OnPlayerMoneyChange(playerid, previous, current) {
    MySQL_BindInt(stmt_savePlayerMoney, 0, current);
    MySQL_BindInt(stmt_savePlayerMoney, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_savePlayerMoney);
    return 1;
}

timer MoveCamera[500](playerid) {
    InterpolateCameraPos(playerid, 3.1435,-1955.6364,88.1194, 2106.8354,-1270.0221,100.7057, 1000 * 25, CAMERA_MOVE);
    InterpolateCameraLookAt(playerid, 2325.7061,-1063.7642,55.4202, 2325.7061,-1063.7642,45.4202, 1000 * 25, CAMERA_MOVE);
}

hook OnPlayerPassedBanCheck(playerid) {

    defer MoveCamera(playerid);
    inline const OnDataLoad() {
        new
            playerUID,
            playerHash[250];

        MySQL_BindResultInt(stmt_checkPlayer, 0, playerUID);
        MySQL_BindResult(stmt_checkPlayer, 1, playerHash, sizeof(playerHash));

        if(MySQL_Statement_FetchRow(stmt_checkPlayer)) {
            Player_SetAccountID(playerid, playerUID);

            inline const OnArmyLoad() {
                new
                    IsArmy,
                    blacklist;
                MySQL_BindResultInt(stmt_loadPlayerArmy, 0, IsArmy);

                if(MySQL_Statement_FetchRow(stmt_loadPlayerArmy)) {
			        Player_SetArmy(playerid, bool:IsArmy);
                    Player_SetBlacklist(playerid, bool:blacklist);
		        }
            }
            MySQL_BindInt(stmt_loadPlayerArmy, 0, Player_GetAccountID(playerid));
	        MySQL_ExecuteParallel_Inline(stmt_loadPlayerArmy, using inline OnArmyLoad);
            Account_PromptLogin(playerid, playerHash);
        }
        else {
            Account_PromptRegister(playerid);
        }
    }

    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

    MySQL_Bind(stmt_checkPlayer, 0, playerName);
    MySQL_ExecuteParallel_Inline(stmt_checkPlayer, using inline OnDataLoad);
}

stock Player_SetAccountID(playerid, value) {
    return Player_UID[playerid] = value;
}

stock Player_GetAccountID(playerid) {
    return Player_UID[playerid];
}

stock Player_SetArmy(playerid, bool:value) {
    return PlayerArmyLvl[playerid] = value;
}

stock bool:Player_GetArmy(playerid) {
    return PlayerArmyLvl[playerid];
}

stock Player_SetBlacklist(playerid, bool:value) {
    return Blacklist[playerid] = value;
}

stock bool:IsPlayerBlacklisted(playerid) {
    return Blacklist[playerid];
}