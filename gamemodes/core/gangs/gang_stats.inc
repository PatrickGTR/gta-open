#include <YSI_Coding\y_hooks>

static 
    GangKills[MAX_GANGS],
    GangDeaths[MAX_GANGS];

static  
    Statement: stmt_UpdateKills,
    Statement: stmt_UpdateDeaths;

hook OnMySQLConnected() {
    stmt_UpdateKills = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE gangs SET kills = kills + ? WHERE id = ?");
    stmt_UpdateDeaths = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE gangs SET deaths = deaths + ? WHERE id = ?");
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    if(killerid != INVALID_PLAYER_ID) {
        if(Player_GetGangID(playerid) != INVALID_GANG_ID && Player_GetGangID(killerid) != INVALID_GANG_ID) {

            new 
                killerGangName[MAX_GANG_NAME],
                playerGangName[MAX_GANG_NAME];
            
            Gang_GetName(Player_GetGangID(playerid), playerGangName, sizeof(playerGangName));
            Gang_GetName(Player_GetGangID(killerid), killerGangName, sizeof(killerGangName));

            foreach(new i : Player) {
                if(Player_GetGangID(i) == Player_GetGangID(playerid)) {
                    SendMsgF(i, COLOR_RED, "[GANG DEATH]: %p (%d) got killed by %p (%d) Gang %s", playerid, playerid, killerid, killerid, killerGangName);
                }
                if(Player_GetGangID(i) == Player_GetGangID(killerid)) {
                    SendMsgF(i, COLOR_RED, "[GANG KILL]: %p (%d) has killed %p (%d) Gang %s", killerid, killerid, playerid, playerid, playerGangName);
                }
            }
            Gang_AddKills(Player_GetGangID(playerid), 1, true);
            Gang_AddDeaths(Player_GetGangID(killerid), 1, true);
        }
    }
    return 1;
}

stock Gang_GetKills(gangid) {
    return GangKills[gangid];
}

stock Gang_GetDeaths(gangid) {
    return GangDeaths[gangid];
}

Gang_AddKills(gangid, kills, bool:save = false) {
    GangKills[gangid] += kills;

    if(save) {
        MySQL_BindInt(stmt_UpdateKills, 0, kills);
        MySQL_BindInt(stmt_UpdateKills, 1, gangid);
        MySQL_ExecuteThreaded(stmt_UpdateKills);
    }
}

Gang_AddDeaths(gangid, deaths, bool:save = false) {        
    GangDeaths[gangid] += deaths;

    if(save) {
        MySQL_BindInt(stmt_UpdateDeaths, 0, deaths);
        MySQL_BindInt(stmt_UpdateDeaths, 1, gangid);
        MySQL_ExecuteThreaded(stmt_UpdateDeaths);
    }
}