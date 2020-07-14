#include <gang_create>
#include <gang_control-panel>

#if SETUP_TABLE
    #include <gang_setup-table>
    #include <gang_ranks-setup-table>
    #include <playergang_setup-table>
#endif
#include <YSI_Coding\y_hooks>

static
    Statement: stmt_loadPGang;

static 
    PlayerGang[MAX_PLAYERS],
    PlayerRank[MAX_PLAYERS]
;

hook OnMySQLConnected()
{
    static const loadQuery[] = "\
    SELECT \
        g_id, \
        gRank \
    FROM \
        player_gang \
    WHERE \
        u_id = ? \
    ";
    stmt_loadPGang = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    PlayerGang[playerid] = 0;
    PlayerRank[playerid] = 0;
    return 1;
}

hook OnPlayerLogin(playerid)
{
    Account_LoadGang(playerid);
    return 1;
}

static Account_LoadGang(playerid)
{
    inline OnGangLoad() {
        new 
            gangid,
            pgangrank;
        MySQL_BindResultInt(stmt_loadPGang, 0, gangid);
        MySQL_BindResultInt(stmt_loadPGang, 1, pgangrank);

        if(MySQL_Statement_FetchRow(stmt_loadPGang)) {
            PlayerGang[playerid] = gangid;
            PlayerRank[playerid] = pgangrank;
            foreach(new i : Player)
            {
                if(IsPlayerConnected(i))
                {
                    if(Player_GetGangID(i) == Player_GetGangID(playerid))
                    {
                        SendMsgF(i, COLOR_BLUE, "[GANG CONNECT]: %p (%d) Rank %i has connected to the server", playerid, playerid, pgangrank);
                    }
                }
            }
        }
    }
    MySQL_BindInt(stmt_loadPGang, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPGang, using inline OnGangLoad);
}

stock Player_SetGangID(playerid, gangid) {
    return PlayerGang[playerid] = gangid;
}

stock Player_GetGangID(playerid) {
    return PlayerGang[playerid];
}

stock Player_SetGangRank(playerid, rank) {
    return PlayerRank[playerid] = rank;
}

stock Player_GetGangRank(playerid) {
    return PlayerRank[playerid];
}