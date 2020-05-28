#include <YSI_Coding\y_hooks>

static
    Jailtime[MAX_PLAYERS],
    BailBalance[MAX_PLAYERS],
    Statement: stmt_retrieveBal,
    Statement: stmt_retrieveTime;

hook OnGameModeInit()
{
    static const query_retrieveBal[] = "\
        SELECT \
            jailed_time, \
            bail_balance \
        FROM \
            jailed \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveBal = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveBal);
    return 1;
}

hook OnPlayerLogin(playerid){
    inline OnPlayerJailedTimeLoad()
    {
        new
            jailTime,
            bailBalance;
            
        MySQL_BindResultInt(stmt_retrieveTime, 0, jailTime);
        MySQL_BindResultInt(stmt_retrieveBal, 1, bailBalance);

        if(MySQL_Statement_FetchRow(stmt_retrieveTime)) {
            Jailtime[playerid] = jailTime;
            BailBalance[playerid] = bailBalance;
        }
    }
    MySQL_BindInt(stmt_retrieveTime, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveTime, using inline OnPlayerJailedTimeLoad);
    return 1;
}

stock Player_SetBailAmount(playerid, amount) {
    BailBalance[playerid] = amount;
    return 1;
}

stock Player_GetBailAmount(playerid) {
    return BailBalance[playerid];
}