#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

static
    PlayerInstaFix[MAX_PLAYERS],
    PlayerCrack[MAX_PLAYERS],
    PlayerPickLock[MAX_PLAYERS],
    PlayerWallet[MAX_PLAYERS],
    Statement: stmt_retrieveIfix;

#pragma unused stmt_retrieveIfix

hook OnGameModeInit()
{
    static const query_retrieveIfix[] = "\
        SELECT \
            instant_fix \
        FROM   \
            inv \
        WHERE  \
            u_id = ? \
        "
    ;
    stmt_retrieveIfix = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveIfix);
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerInstaFix[playerid] =
    PlayerPickLock[playerid] =
    PlayerWallet[playerid] =
    PlayerCrack[playerid] = 0;
    return 1;
}

hook OnPlayerLogin(playerid) {
    inline OnPlayerInvLoad() {
        new
            instafix;
        MySQL_BindResultInt(stmt_retrieveIfix, 0, instafix);

        if(MySQL_Statement_FetchRow(stmt_retrieveIfix)) {
            Player_SetInstaFix(playerid, instafix);
        }
    }
    MySQL_BindInt(stmt_retrieveIfix, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveIfix, using inline OnPlayerInvLoad);
}

stock Player_SetInstaFix(playerid, stocks) {
    PlayerInstaFix[playerid] = stocks;

    new string[256];

    static const query[] = "\
    INSERT INTO \
        inventory(u_id, instant_fix) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        instant_fix = %i \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), stocks, stocks);
    mysql_tquery(MySQL_GetHandle(), string);
}

stock Player_GetInstaFix(playerid)
    return PlayerInstaFix[playerid];


stock void:Player_GiveCrack(playerid, amount) {
    PlayerCrack[playerid] += amount;
}

stock Player_GetCrack(playerid) {
    return PlayerCrack[playerid];
}

stock void:Player_GivePicklock(playerid, amount) {
    PlayerPickLock[playerid] += amount;
}

stock Player_GetPicklock(playerid) {
    return PlayerPickLock[playerid];
}

stock void:Player_GiveWallet(playerid, amount) {
    PlayerWallet[playerid] += amount;
}

stock Player_GetWallet(playerid) {
    return PlayerWallet[playerid];
}