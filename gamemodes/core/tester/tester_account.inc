#include <YSI_Coding\y_hooks>

static
    bool:PlayerTester[MAX_PLAYERS],
    Statement: stmt_retrieveTester,
    Statement: stmt_retriveUID,
    Statement: stmt_insertTester
;

hook OnGameModeInit() {
    static const query_retrieveTester[] = "\
        SELECT \
            tester_level \
        FROM  \
            testers \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveTester = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveTester);

    static const query_retrieveUID[] = "\
        SELECT \
            u_id, \
            username \
        FROM \
            players \
        WHERE \
            username = ? \
        "
    ;
    stmt_retriveUID = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveUID);

    static const insertTester[] = "\
        INSERT INTO \
            testers(u_id, tester_level) \
        VALUES \
            (?,?) \
        "
    ;
    stmt_insertTester = MySQL_PrepareStatement(MySQL_GetHandle(), insertTester);
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

    if(level == true) {
        static const query[] = "\
        INSERT INTO \
            testers(u_id, tester_level) \
        VALUES \
            (%i, %i) \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), level);
        mysql_tquery(MySQL_GetHandle(), string);
    }
    if(level == false) {
        static const deletequery[] = "\
        DELETE FROM \
            testers \
        WHERE \
            u_id = %i \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof(string), deletequery, Player_GetAccountID(playerid));
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock OffSetTester(playerid, const username[], bool:level)
{
    new 
        playername[MAX_PLAYER_NAME],
        string[512];
    strcpy(playername, username, sizeof(playername));
    inline OnSetTester() {
        new
            useruid,
            name[MAX_PLAYER_NAME];

        MySQL_BindResultInt(stmt_retriveUID, 0, useruid);
        MySQL_BindResult(stmt_retriveUID, 1, name);

        if(MySQL_Statement_FetchRow(stmt_retriveUID))
        {
            if(level)
            {
                MySQL_BindInt(stmt_insertTester, 0, useruid);
                MySQL_BindInt(stmt_insertTester, 1, 1);
                MySQL_ExecuteThreaded(stmt_insertTester);
                SendMsgF(playerid, COLOR_MODERATION, "The Account (%s) is now a Beta Tester", name);
            }
            if(!level)
            {
                mysql_format(MySQL_GetHandle(), string, sizeof(string), "DELETE FROM testers WHERE u_id = %i", useruid);
                mysql_tquery(MySQL_GetHandle(), string);
                SendMsgF(playerid, COLOR_MODERATION, "The Account (%s) is now Removed from the Beta Tester", name);
            }
        }
        else {
            return SendErrorMsgF(playerid, "The Account (%s) is not on the database", name);
        }
    }
    MySQL_Bind(stmt_retriveUID, 0, playername);
    MySQL_ExecuteParallel_Inline(stmt_retriveUID, using inline OnSetTester);
    return 1;
}

stock GetPlayerTester(playerid)
    return PlayerTester[playerid];
