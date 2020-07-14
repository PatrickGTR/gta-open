#include <YSI_Coding\y_hooks>

static 
    Statement: stmt_loadRanks;

static 
    GangRank1[MAX_GANGS][15],
    GangRank2[MAX_GANGS][15],
    GangRank3[MAX_GANGS][15],
    GangRank4[MAX_GANGS][15],
    GangRank5[MAX_GANGS][15],
    GangRank6[MAX_GANGS][15],
    GangRank7[MAX_GANGS][15],
    GangRank8[MAX_GANGS][15],
    GangRank9[MAX_GANGS][15],
    GangRank10[MAX_GANGS][15],
;

hook OnMySQLConnected()
{
    static const loadQuery[] = "\
    SELECT \
        rank1, \
        rank2, \
        rank3, \
        rank4, \
        rank5, \
        rank6, \
        rank7, \
        rank8, \
        rank9, \
        rank10, \
    FROM \
        gang_ranks \
    WHERE \
        g_id = ?\
    ";
    stmt_loadRanks = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

//TODO: Load the gang ranks and everytime the Player Logged in Send Server Message 
//("Player" has logged in "Gang Rank")

