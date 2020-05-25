#include <YSI_Data\y_iterate>

new
    PlayerCuffed[MAX_PLAYERS],
    PlayerJailed[MAX_PLAYERS]
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
        PlayerJailed[playerid] = 1;
        PlayerCuffed[playerid] = 0;
        ResetPlayerWeapons(playerid);
        RemovePlayerAttachedObject(playerid, 0);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        PLAYER_SetPlayerWantedLevel(playerid, 0);
    }
    return 1;
}