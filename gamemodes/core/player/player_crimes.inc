#include <YSI_Coding\y_hooks>

static 
    gShotNearPoliceTick[MAX_PLAYERS],
    gShotPoliceTick[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    gShotNearPoliceTick[playerid] = 0;
    gShotPoliceTick[playerid] = 0;
    return 1;
}

// Shooting near a cop
hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
    // disallow spam, only increase wanted every after 2 minutes.
    if(Player_GetClass(playerid) == TEAM_CIVILIAN) {
        new 
            closestID = Player_GetClosestLeo(playerid),
            Float:x, 
            Float:y, 
            Float:z;
        GetPlayerPos(closestID, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid, 20.0, x, y, z)) {
            if((gettime() - gShotNearPoliceTick[playerid]) < (60 * 2)) {
                SendMsgF(playerid, COLOR_RED, "You shot near a on-duty police officer, you've gained an extra 4 stars.");

                Player_GiveWantedLevel(playerid, 4);
            }
            gShotNearPoliceTick[playerid] = gettime();
        }
        
    }
    return 1;    
}

// Shooting a cop detection.
hook OnPlayerTakePlayerDmg(playerid, issuerid, &Float: amount, weaponid, bodypart )
{
    if(Player_GetClass(issuerid) == TEAM_CIVILIAN && Player_GetClass(playerid) == TEAM_POLICE) {
        // disallow spam, only increase wanted every after 2 minutes.
        if((gettime() - gShotPoliceTick[playerid]) < (60 * 2)) {
            SendMsgF(issuerid, COLOR_RED, "You shot an on-duty police officer, you've gained an extra 4 stars.");

            Player_GiveWantedLevel(playerid, 4);
            gShotPoliceTick[issuerid] = gettime();
        }
    }
    return 1;
}