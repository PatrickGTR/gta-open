#include <YSI_Coding\y_hooks>

#define MAX_GANGS   (30)

// Accessed Globaly
new
    Iterator:gang_Iter<MAX_GANGS>
;

static 
    Statement: stmt_insertGang,
    Statement: stmt_insertGangRank,
    Statement: stmt_deleteGang,
    Statement: stmt_checkGang,
    Statement: stmt_loadGang,
    Statement: stmt_updateKills,
    Statement: stmt_updateDeaths;

static
    GangID[MAX_GANGS],
    GangName[MAX_GANGS][30],
    GangLeader[MAX_GANGS][24],
    GangKills[MAX_GANGS],
    GangDeaths[MAX_GANGS];

hook OnMySQLConnected()
{
    static const insertQuery[] = "\
    INSERT INTO \
        gangs(g_id, u_id, gName, gLeader) \
    VALUES \
        (?,?,?,?) \
    ";
    stmt_insertGang = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const RankinsertQuery[] = "\
    INSERT INTO \
        gang_ranks(g_id) \
    VALUES \
        (?) \
    ";
    stmt_insertGangRank = MySQL_PrepareStatement(MySQL_GetHandle(), RankinsertQuery);

    static const deleteQuery[] = "\
    DELETE FROM \
        gangs \
    WHERE \
        gName = ? \
    ";
    stmt_deleteGang = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);

    static const checkQuery[] = "\
    SELECT \
        gName, \
        g_id \
    FROM \
        gangs \
    WHERE \
        gName = ? \
    ";
    stmt_checkGang = MySQL_PrepareStatement(MySQL_GetHandle(), checkQuery);

    static const loadQuery[] = "\
    SELECT \
        g_id, \
        gName, \
        gLeader, \
        g_kills, \
        g_deaths \
    FROM \
        gangs \
    ";
    stmt_loadGang = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const updateKillsQuery[] = "\
    UPDATE \
        gangs \
    SET \
        g_kills = ? \
    WHERE \
        g_id = ? \
    ";
    stmt_updateKills = MySQL_PrepareStatement(MySQL_GetHandle(), updateKillsQuery);

    static const updateDeathsQuery[] = "\
    UPDATE \
        gangs \
    SET \
        g_deaths = ? \
    WHERE \
        g_id = ? \
    ";
    stmt_updateDeaths = MySQL_PrepareStatement(MySQL_GetHandle(), updateDeathsQuery);
    
    LoadGang();
    return 1;
}

GangLoad(g_id, const gName[], const gLeader[], gkills, gdeaths) {
    SetGangID(g_id, g_id);
    strcpy(GangName[g_id], gName, 30);
    strcpy(GangLeader[g_id], gLeader, 24);
    AddGangKills(g_id, gkills);
    AddGangDeaths(g_id, gdeaths);
    LoadGangRanks(g_id);
    Iter_Add(gang_Iter, g_id);
    printf("The Gang %s gang id %d has been loaded", GangName[g_id], g_id);
}

LoadGang()
{
    inline const OnGANGLoad() {
        new
            g_id,
            gName[30],
            gLeader[24],
            g_kills,
            g_deaths;
        MySQL_BindResultInt(stmt_loadGang, 0, g_id);
        MySQL_BindResult(stmt_loadGang, 1, gName);
        MySQL_BindResult(stmt_loadGang, 2, gLeader);
        MySQL_BindResultInt(stmt_loadGang, 3, g_kills);
        MySQL_BindResultInt(stmt_loadGang, 4, g_deaths);

        while(MySQL_Statement_FetchRow(stmt_loadGang)) {
            GangLoad(g_id, gName, gLeader, g_kills, g_deaths);
        }
    }
    MySQL_ExecuteThreaded_Inline(stmt_loadGang, using inline OnGANGLoad);
}

CMD:gangs(playerid)
{
    new string[256];
    TextInfo_Create(playerid, "Gangs", "Gang List");
    inline const OnGANGLoad() {
        new
            g_id,
            gName[30],
            gLeader[24],
            g_kills,
            g_deaths;
        MySQL_BindResultInt(stmt_loadGang, 0, g_id);
        MySQL_BindResult(stmt_loadGang, 1, gName);
        MySQL_BindResult(stmt_loadGang, 2, gLeader);
        MySQL_BindResultInt(stmt_loadGang, 3, g_kills);
        MySQL_BindResultInt(stmt_loadGang, 4, g_deaths);

        while(MySQL_Statement_FetchRow(stmt_loadGang)) {
            format(string, sizeof(string), "~r~Gang Name:~w~ %s ~r~Gang Leader:~w~ %s", gName, gLeader);
            TextInfo_Add(playerid, string);
        }
        TextInfo_Show(playerid);
    }
    MySQL_ExecuteThreaded_Inline(stmt_loadGang, using inline OnGANGLoad);
    return 1;
}

ACMD:[5]gangcreate(playerid, params[])
{
    new leader, gname[30], lName[MAX_PLAYER_NAME], gangID = Iter_Free(gang_Iter);
    new string[512];
    if(sscanf(params, "us[30]", leader, gname)) return SendSyntaxMsg(playerid, "/gangcreate (leadername) (gangname)");
    if(!IsPlayerConnected(leader)) return SendErrorMsg(playerid, "Player is not connected");
    if (gangID == ITER_NONE) {
		return -1;
	}
    GetPlayerName(leader, lName, sizeof(lName));
    MySQL_BindInt(stmt_insertGang, 0, gangID);
    MySQL_BindInt(stmt_insertGang, 1, Player_GetAccountID(leader));
    MySQL_Bind(stmt_insertGang, 2, gname);
    MySQL_Bind(stmt_insertGang, 3, lName);
    MySQL_ExecuteThreaded(stmt_insertGang);
    MySQL_BindInt(stmt_insertGangRank, 0, gangID);
    MySQL_ExecuteThreaded(stmt_insertGangRank);
    SetGangID(gangID, gangID);
    Iter_Add(gang_Iter, gangID);
    strcpy(GangName[gangID], gname, 30);
    static const query[] = "\
    INSERT INTO \
        gang_members(g_id, u_id, gRank) \
    VALUES \
        (%i,%i,%i)";
    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, gangID, Player_GetAccountID(leader), 10);
    mysql_tquery(MySQL_GetHandle(), string);
    Player_SetGangID(leader, gangID);
    Player_SetGangRank(leader, 10);
    SendMsgAllF(COLOR_MODERATION, "[GANG]: The Gang %s has been created", gname);
    SendMsgAllF(COLOR_MODERATION, "[GANG]: Gang Leader %p", leader);
    LoadGangRanks(gangID);
    Iter_Add(gang_Iter, gangID);
    return 1;
}

ACMD:[5]gangdelete(playerid, params[])
{
    new gname[30];
    if(sscanf(params, "s[30]", gname)) return SendSyntaxMsg(playerid, "/gangdelete (gangname)");
    inline OnGangDelete()
    {
        new
            gName[30],
            gId;

        MySQL_BindResult(stmt_checkGang, 0, gName);
        MySQL_BindResultInt(stmt_checkGang, 1, gId);

        if(MySQL_Statement_FetchRow(stmt_checkGang))
        {
            MySQL_Bind(stmt_deleteGang, 0, gName);
            MySQL_ExecuteThreaded(stmt_deleteGang);
            foreach(new i : Player)
            {
                if(Player_GetGangID(i) == gId)
                {
                    Player_SetGangRank(i, INVALID_GANG_RANK);
                    Player_SetGangID(i, INVALID_GANG_ID);
                }
            }
            Iter_Remove(gang_Iter, gId);
            SendMsgAllF(COLOR_MODERATION, "[GANG]: The Gang %s has been deleted", gName);
        }
        else {
            SendErrorMsgF(playerid, "The Gang (%s) is not in the database", gName);
        }
    }
    MySQL_Bind(stmt_checkGang, 0, gname);
    MySQL_ExecuteParallel_Inline(stmt_checkGang, using inline OnGangDelete);
    return 1;
}

stock GetGangKills(gangid) {
    return GangKills[gangid];
}

stock AddGangKills(gangid, kills, bool:save = false)
{
    new
        currentKills = GetGangKills(gangid),
        newKills = currentKills + kills;
    GangKills[gangid] = newKills;
    if(save) {
        MySQL_BindInt(stmt_updateKills, 0, newKills);
        MySQL_ExecuteThreaded(stmt_updateKills);
    }
}

stock GetGangDeaths(gangid) {
    return GangDeaths[gangid];
}

stock AddGangDeaths(gangid, deaths, bool:save = false)
{
    new 
        currentDeaths = GetGangDeaths(gangid),
        newDeaths = currentDeaths + deaths;
    GangDeaths[gangid] = newDeaths;
    if(save) {
        MySQL_BindInt(stmt_updateDeaths, 0, newDeaths);
        MySQL_ExecuteThreaded(stmt_updateDeaths);
    }
    return 1;
}

stock SetGangID(gangid, value) {
    return GangID[gangid] = value;
}

stock GetGangName(gangid) {
    return GangName[gangid];
}

stock GetGangID(gangid) {
    return GangID[gangid];
}