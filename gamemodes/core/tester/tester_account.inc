#include <YSI_Coding\y_hooks>

static
    bool:PlayerTester[MAX_PLAYERS],
    Statement: stmt_retrieveTester
;

hook OnGameModeInit() {
    static const query_retrieveTester[] = "\
        SELECT \
            tester \
        FROM  \
            player_stats \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveTester = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveTester);
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerTester[playerid] = false;
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerTesterLoad() {
        new
            testerLevel;

        MySQL_BindResultInt(stmt_retrieveTester, 0, testerLevel);

        if(MySQL_Statement_FetchRow(stmt_retrieveTester)) {
            SetPlayerTester(playerid, bool:testerLevel);
        }

    }
    MySQL_BindInt(stmt_retrieveTester, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveTester, using inline OnPlayerTesterLoad);
}

stock SetPlayerTester(playerid, bool:level)
{
    PlayerTester[playerid] = level;

    new string[256];

    static const query[] = "\
    INSERT INTO \
        player_stats(u_id, tester) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        tester = %i \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), level, level);
    mysql_tquery(MySQL_GetHandle(), string);
}

stock GetPlayerTester(playerid)
    return PlayerTester[playerid];
