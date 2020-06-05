
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
#include <YSI_Coding\y_inline>
#include <mysql_prepared>



static
    Player_UID[MAX_PLAYERS],
    Player_Kills[MAX_PLAYERS],
    Player_Deaths[MAX_PLAYERS],
    Statement: stmt_checkPlayer;

hook OnMySQLConnected() {
    stmt_checkPlayer = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT u_id, password FROM players WHERE username=?");
}

hook OnPlayerLogin(playerid) {
    Player_SetLoginStatus(playerid, true);
}

hook OnPlayerPassedBanCheck(playerid) {
    inline OnDataLoad() {
        new
            playerUID,
            playerHash[250];

        // retrieve u_id and password data and store them to local variable.
        MySQL_BindResultInt(stmt_checkPlayer, 0, playerUID);
        MySQL_BindResult(stmt_checkPlayer, 1, playerHash, sizeof(playerHash));

        if(MySQL_Statement_FetchRow(stmt_checkPlayer)) {
            Player_SetAccountID(playerid, playerUID);

            Account_PromptLogin(playerid, playerHash);
        } else {
            Account_PromptRegister(playerid);
        }
    }

    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

    MySQL_Bind(stmt_checkPlayer, 0, playerName);
    MySQL_ExecuteParallel_Inline(stmt_checkPlayer, using inline OnDataLoad);
}

stock Player_SetKills(playerid, value) {
    return Player_Kills[playerid] = value;
}

stock Player_GetKills(playerid) {
    return Player_Kills[playerid];
}

stock Player_SetDeaths(playerid, value) {
    return Player_Deaths[playerid] = value;
}

stock Player_GetDeaths(playerid) {
    return Player_Deaths[playerid];
}

stock Player_SetAccountID(playerid, value) {
    return Player_UID[playerid] = value;
}

stock Player_GetAccountID(playerid) {
    return Player_UID[playerid];
}
