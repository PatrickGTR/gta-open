#include <YSI_Coding\y_hooks>

new 
    BailBalance[MAX_PLAYERS],
    Jailtime[MAX_PLAYERS]
;

static
    Statement: stmt_retrieveBal,
    Statement: stmt_retrieveTime
;

hook OnGameModeInit()
{
    static const query_retrieveBal[] = "\
        SELECT \
            bail_balance \
        FROM \
            jailed \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveBal = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveBal);
    static const query_retrieveTime[] = "\
        SELECT \
            jailed_time \
        FROM   \
            jailed \
        WHERE  \
            u_id = ? \
        "
    ;
    stmt_retrieveTime = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveTime);
}

hook OnPlayerLogin(playerid){
    inline OnPlayerJailedTimeLoad()
    {
        new
            jailedtime,
            bailbal;
        MySQL_BindResultInt(stmt_retrieveTime, 0, jailedtime);
        MySQL_BindResultInt(stmt_retrieveBal, 0, bailbal);

        if(MySQL_Statement_FetchRow(stmt_retrieveTime)) {
            Jailtime[playerid] = jailedtime;
        }
        if(MySQL_Statement_FetchRow(stmt_retrieveBal)) {
            BailBalance[playerid] = bailbal;
        }
    }
    MySQL_BindInt(stmt_retrieveTime, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveTime, using inline OnPlayerJailedTimeLoad);
}
