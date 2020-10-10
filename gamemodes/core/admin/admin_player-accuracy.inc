#include <YSI_Coding\y_hooks>

static 
    gPlayerHits[MAX_PLAYERS],
    gPlayerMissed[MAX_PLAYERS],
    gPlayerTotalShots[MAX_PLAYERS]
;

ACMD:[1]bulletstats(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/bulletstats (name/id)");
    if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
    SendServerMsgF(playerid, "%p (%d)'s bullet stats", target, target);
    SendServerMsgF(playerid, "%d hits %d Missed %d total shots", Player_GetHits(target), Player_GetMissed(target), Player_GetTotalShots(target));
    SendServerMsgF(playerid, "%d accuracy", Player_GetAccuracy(target));
    return 1;
}

stock Player_GetTotalShots(playerid)
{
    return gPlayerTotalShots[playerid];
}

stock Player_GetHits(playerid)
{
    return gPlayerHits[playerid];
}

stock Player_GetMissed(playerid)
{
    return gPlayerMissed[playerid];
}

stock Player_GetAccuracy(playerid)
{
    return (gPlayerHits[playerid] / gPlayerTotalShots[playerid]);
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(hittype == BULLET_HIT_TYPE_NONE) 
    {
        gPlayerMissed[playerid]++;
    }
    else if(hittype == BULLET_HIT_TYPE_PLAYER && hitid != INVALID_PLAYER_ID)
    {
        gPlayerHits[playerid]++;   
    }
    gPlayerTotalShots[playerid]++;
    return 1;
}