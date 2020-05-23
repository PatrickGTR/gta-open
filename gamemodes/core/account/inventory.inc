#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

static
    PlayerInstaFix[MAX_PLAYERS],
    Statement: stmt_retrieveIfix
;

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
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerInvLoad()
    {
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

stock Player_SetInstaFix(playerid, stocks) 
{
    PlayerInstaFix[playerid] = stocks;

    new string[256];

    static const query[] = "\
    INSERT INTO \
        inv(u_id, instant_fix) \
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
