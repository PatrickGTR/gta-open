#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

new
    bool:PlayerCuffed[MAX_PLAYERS],
    bool:PlayerJailed[MAX_PLAYERS]
;

static
    Statement: stmt_retrieveJailed
;

enum E_JAILPOS_DATA
{
    Float:E_JAILPOS_X,
    Float:E_JAILPOS_Y,
    Float:E_JAILPOS_Z,
    Float:E_JAILPOS_A,
}

static
    const JailData[][E_JAILPOS_DATA] =
{
    {264.2428, 86.4775, 1001.0391, 271.6097},
    {263.9785, 82.0106, 1001.0391, 269.8944}
};

hook OnGameModeInit()
{
    static const query_retrieveJailed[] = "\
        SELECT \
            bail_required \
        FROM \
            jailed \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveJailed = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveJailed);
}

stock Player_GetClosestWanted(playerid) {
    new  
        closestID = -1, 
        Float: x,
        Float: y,
        Float: z;

    GetPlayerPos(playerid, x, y, z);
    foreach(new i : Player) 
    {
        if(IsPlayerInRangeOfPoint(i, 4.0, x, y, z) && Player_GetWantedLevel(i) >= 3) {
            closestID = i;
        }
    } 
    return closestID;
}

stock Player_SendToJail(playerid, seconds, bool:save = false) {
    if(!UI_TimeLeft(playerid, seconds)) { 
        return 0;
    }

    new
        Float:x,
        Float:y,
        Float:z,
        Float:ang,
        idx = random(sizeof(JailData));
    x = JailData[idx][E_JAILPOS_X];
    y = JailData[idx][E_JAILPOS_Y];
    z = JailData[idx][E_JAILPOS_Z];
    ang = JailData[idx][E_JAILPOS_A];

    SetPlayerPos(playerid, x, y, z);
    SetPlayerFacingAngle(playerid, ang);
    SetPlayerVirtualWorld(playerid, 16);
    SetPlayerInterior(playerid, 6);

    ClearAnimations(playerid, 1);

    Player_SetJail(playerid, true);
    Player_SetCuffed(playerid, false);

    ResetPlayerWeapons(playerid);
    RemovePlayerAttachedObject(playerid, 0);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    PLAYER_SetPlayerWantedLevel(playerid, 0);
    if(BurglaryInfo[playerid] != 0) {
        Player_StopRobbery(playerid);
    }

    if(save) {
        new 
            string[256];
        static const query[] = "\
            INSERT INTO \
                jailed(u_id, jailed_time) \
            VALUES \
                (%i, %i) \
            ON DUPLICATE KEY UPDATE \
                jailed_time = %i \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), seconds, seconds);
        mysql_tquery(MySQL_GetHandle(), string);
    }
    return 1;
}

stock Player_UnJail(playerid) {
    SetPlayerPos(playerid, 254.9862, 86.8028, 1002.4453);
    SetPlayerFacingAngle(playerid, 90.9168);
    SetPlayerVirtualWorld(playerid, 16);
    SetPlayerInterior(playerid, 6);
    Player_SetJail(playerid, false);
    return 1;
}

hook OnPlayerLogin(playerid) 
{
    inline OnPlayerJailLoad()
    {
        new
            player_jailed;
        MySQL_BindResultInt(stmt_retrieveJailed, 0, player_jailed);

        if(MySQL_Statement_FetchRow(stmt_retrieveJailed)) {
            Player_SetJail(playerid, bool:player_jailed);
        }
    }
    MySQL_BindInt(stmt_retrieveJailed, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveJailed, using inline OnPlayerJailLoad);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_SUBMISSION)) {
        if(Player_GetClass(playerid) != TEAM_POLICE) {
            return 0;
        }
        new id = Player_GetClosestWanted(playerid);

        if(id == -1) {
            return 1;
        }

        if(PlayerCuffed[id] == false) {
            return cmd_cuffcw(playerid);
        }
        else if(PlayerCuffed[id] == true) {
            return cmd_arrestcw(playerid);
        }
    }
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(Player_IsJailed(playerid)) {
        Player_SendToJail(playerid, 300, true);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerCuffed[playerid] == true) {
        Player_SendToJail(playerid, 300, true);
        Player_SetJail(playerid, true);
    }
    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if(PlayerCuffed[playerid] == true) {
        SendServerMsg(playerid, "You can't enter a vehicle while cuffed! EJECTED!");
        RemovePlayerFromVehicle(playerid);
    }
    return 1;
}

stock Player_SetJail(playerid, bool:jailed)
{
    PlayerJailed[playerid] = jailed;

    new string[256];

    static const query[] = "\
    INSERT INTO \
        jailed(u_id, bail_required) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        bail_required = %i \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), jailed, jailed);
    mysql_tquery(MySQL_GetHandle(), string);
}

stock Player_SetCuffed(playerid, bool:cuffed) {
    return PlayerCuffed[playerid] = cuffed;
}

stock Player_IsJailed(playerid) {
    if(PlayerJailed[playerid] == true) {
        return 1;
    }
    return 0;
}