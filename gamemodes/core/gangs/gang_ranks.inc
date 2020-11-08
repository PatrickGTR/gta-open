#include <YSI_Coding\y_hooks>

static 
    Statement: stmt_loadRanks;

static 
    GangRank[MAX_GANGS][11][15] // Due to lack of braincells i've decided to NOT use the index 0 thats why its 11 
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
        rank10 \
    FROM \
        gang_ranks \
    WHERE \
        g_id = ?\
    ";
    stmt_loadRanks = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

LoadGangRanks(gId) {
    inline OnGangRankLoad() {
        new
            GangRanks[10][15];
        MySQL_BindResult(stmt_loadRanks, 0, GangRanks[0]);
        MySQL_BindResult(stmt_loadRanks, 1, GangRanks[1]);
        MySQL_BindResult(stmt_loadRanks, 2, GangRanks[2]);
        MySQL_BindResult(stmt_loadRanks, 3, GangRanks[3]);
        MySQL_BindResult(stmt_loadRanks, 4, GangRanks[4]);
        MySQL_BindResult(stmt_loadRanks, 5, GangRanks[5]);
        MySQL_BindResult(stmt_loadRanks, 6, GangRanks[6]);
        MySQL_BindResult(stmt_loadRanks, 7, GangRanks[7]);
        MySQL_BindResult(stmt_loadRanks, 8, GangRanks[8]);
        MySQL_BindResult(stmt_loadRanks, 9, GangRanks[9]);
        if(MySQL_Statement_FetchRow(stmt_loadRanks)) {
            strcpy(GangRank[gId][1], GangRanks[0]);
            strcpy(GangRank[gId][2], GangRanks[1]);
            strcpy(GangRank[gId][3], GangRanks[2]);
            strcpy(GangRank[gId][4], GangRanks[3]);
            strcpy(GangRank[gId][5], GangRanks[4]);
            strcpy(GangRank[gId][6], GangRanks[5]);
            strcpy(GangRank[gId][7], GangRanks[6]);
            strcpy(GangRank[gId][8], GangRanks[7]);
            strcpy(GangRank[gId][9], GangRanks[8]);
            strcpy(GangRank[gId][10], GangRanks[9]);
        }
    }
    MySQL_BindInt(stmt_loadRanks, 0, gId);
    MySQL_ExecuteParallel_Inline(stmt_loadRanks, using inline OnGangRankLoad);
}

GetGangRankName(gId, lvl) {
    new tempStr[15];
    switch(lvl) {
        case 1: strcpy(tempStr, GangRank[gId][1]);
        case 2: strcpy(tempStr, GangRank[gId][2]);
        case 3: strcpy(tempStr, GangRank[gId][3]);
        case 4: strcpy(tempStr, GangRank[gId][4]);
        case 5: strcpy(tempStr, GangRank[gId][5]);
        case 6: strcpy(tempStr, GangRank[gId][6]);
        case 7: strcpy(tempStr, GangRank[gId][7]);
        case 8: strcpy(tempStr, GangRank[gId][8]);
        case 9: strcpy(tempStr, GangRank[gId][9]);
        case 10: strcpy(tempStr, GangRank[gId][10]);
    }
    return tempStr;
}

forward OnPlayerEditGangRank(playerid, listitem);
public OnPlayerEditGangRank(playerid, listitem)
{
    new string[126], tmpString[128];
    new gangid = Player_GetGangID(playerid);
    format(tmpString, sizeof(tmpString), "GangRank_%i", listitem);
    new rank = GetPVarInt(playerid, tmpString);
    inline OnPutGangRankName(pid, dialogid, response, llistitem, string:inputtext[]) {
        #pragma unused pid, dialogid, llistitem
        if(!response) return 1;
        format(string, sizeof(string), "UPDATE gang_ranks SET rank%d = '%s' WHERE g_id = %d", rank, inputtext, gangid);
        mysql_tquery(MySQL_GetHandle(), string);
        strcpy(GangRank[gangid][rank], inputtext);
    }
    format(tmpString, sizeof(tmpString), "Put the name for Gang Rank %i", rank);
    Dialog_ShowCallback(playerid, using inline OnPutGangRankName, DIALOG_STYLE_INPUT, "Put the Gangrank Name", tmpString, "Ok", "Cancle");
    return 1;
}

CMD:gangranks(playerid, params[])
{
    new count = 0, tmpStr[128];
    if(Player_GetGangID(playerid) == INVALID_GANG_ID) return SendErrorMsg(playerid, "You're not in a Gang!");
    if(Player_GetGangRank(playerid) < 9) return SendErrorMsg(playerid, "Only level 9+ can use this command");
    TextMenu_Create(playerid, "OnPlayerEditGangRank", "Gang Ranks");
    for(new i; i < 11; i++) {
        if(i == 0) continue;
        count++;
        format(tmpStr, sizeof(tmpStr), "~w~%s", GetGangRankName(Player_GetGangID(playerid), i));
        TextMenu_Add(playerid, tmpStr);
        format(tmpStr, sizeof(tmpStr), "GangRank_%i", count);
        SetPVarInt(playerid, tmpStr, i);
    }
    TextMenu_Show(playerid);
    return 1;
}