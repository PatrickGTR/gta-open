#include <YSI_Coding\y_hooks>

static
    gShotNearPoliceTick[MAX_PLAYERS],
    gShotPoliceTick[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    gShotNearPoliceTick[playerid] = 0;
    gShotPoliceTick[playerid] = 0;
    return 1;
}

// Murder
hook OnPlayerDeath(playerid, killerid, reason) {
    if(killerid != INVALID_PLAYER_ID) {
        Player_GiveWantedLevel(killerid, 4);
    }
    return 1;
}

// Store Robbery
hook OnPlayerRobStore(playerid, moneyTaken) {
    new
        location[MAX_MAP_ZONE_NAME];
    Player_GetLocation(playerid, location, sizeof(location));
    SendMsgAllF(COLOR_ORANGE, "(store robbery) "C_GREY"%p(%i) "C_WHITE"took "C_GREEN"%m "C_WHITE"from "C_YELLOW"%s "C_WHITE"in "C_GREY"%s.", playerid, playerid, moneyTaken, Entrance_PlayerIn(playerid), location);

    GivePlayerMoney(playerid, moneyTaken);
    Player_GiveWantedLevel(playerid, 4);
}

// Player Roberry
hook OnPlayerRobPlayer(playerid, targetid, moneyTaken) {
    SendMsgF(playerid, COLOR_ORANGE, "(player robbery) "C_WHITE"You managed to rob "C_GREY"%p (%i) "C_WHITE"and found "C_GREEN"%m "C_WHITE"in his wallet.", targetid, targetid, moneyTaken);
    SendMsgF(targetid, COLOR_ORANGE, "(player robbery) "C_WHITE"You have been robbed by "C_GREY"%p (%i) "C_WHITE"and found "C_GREEN"%m "C_WHITE"in your wallet.", playerid, playerid, moneyTaken);

    GivePlayerMoney(targetid, -moneyTaken);
    GivePlayerMoney(playerid, moneyTaken);
    Player_GiveWantedLevel(playerid, 4);
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
                return 1;
            }

            SendMsgF(playerid, COLOR_RED, "You shot near a on-duty police officer, you've gained an extra 4 stars.");

            Player_GiveWantedLevel(playerid, 4);
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
            return 1;
        }
        SendMsgF(issuerid, COLOR_RED, "You shot an on-duty police officer, you've gained an extra 4 stars.");

        Player_GiveWantedLevel(playerid, 4);
        gShotPoliceTick[issuerid] = gettime();
    }
    return 1;
}