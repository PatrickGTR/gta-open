#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

new
    bool:PlayerCuffed[MAX_PLAYERS],
    bool:PlayerJailed[MAX_PLAYERS]
;

static
    Statement: stmt_retrieveJailed
;

static
    Float:jailX,
    Float:jailY,
    Float:jailZ,
    Float:jailA
;

enum E_JAILPOS_DATA
{
    Float:E_JAILPOS_X,
    Float:E_JAILPOS_Y,
    Float:E_JAILPOS_Z,
    Float:E_JAILPOS_A,
}

static
    const DATA[][E_JAILPOS_DATA] =
{
    {264.2428, 86.4775, 1001.0391, 271.6097},
    {263.9785, 82.0106, 1001.0391, 269.8944}
};

hook OnGameModeInit()
{
    static const query_retrieveJailed[] = "\
        SELECT \
            player_jailed \
        FROM \
            players \
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

stock Player_Jail(playerid) {
    for(new i = 0; i < sizeof(DATA); i++) {
        jailX = DATA[i][E_JAILPOS_X];
        jailY = DATA[i][E_JAILPOS_Y];
        jailZ = DATA[i][E_JAILPOS_Z];
        jailA = DATA[i][E_JAILPOS_A];

        SetPlayerPos(playerid, jailX, jailY, jailZ);
        SetPlayerFacingAngle(playerid, jailA);
        SetPlayerVirtualWorld(playerid, 16);
        SetPlayerInterior(playerid, 6);
        ClearAnimations(playerid, 1);
        Player_SetJail(playerid, true);
        PlayerCuffed[playerid] = false;
        ResetPlayerWeapons(playerid);
        RemovePlayerAttachedObject(playerid, 0);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        PLAYER_SetPlayerWantedLevel(playerid, 0);
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

hook OnPlayerSpawn(playerid)
{
    if(Player_IsJailed(playerid)) {
        Player_Jail(playerid);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerCuffed[playerid] == true) {
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
        players(u_id, player_jailed) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        player_jailed = %i \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), jailed, jailed);
    mysql_tquery(MySQL_GetHandle(), string);
}

stock Player_IsJailed(playerid) {
    if(PlayerJailed[playerid] == true) {
        return 1;
    }
    return 0;
}