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
hook OnPlayerDeathEx(playerid, killerid, reason, Float: damage, bodypart) {
    if(killerid != INVALID_PLAYER_ID) {
        Player_GiveWantedLevel(killerid, 6);

        SendMsgF(killerid, COLOR_RED, "You commited murder, you've gained an extra 6 stars.");
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

    return 1;
}

// Player Roberry
hook OnPlayerRobPlayer(playerid, targetid, moneyTaken) {
    SendMsgF(playerid, COLOR_ORANGE, "(player robbery) "C_WHITE"You managed to rob "C_GREY"%p (%i) "C_WHITE"and found "C_GREEN"%m "C_WHITE"in his wallet.", targetid, targetid, moneyTaken);
    SendMsgF(targetid, COLOR_ORANGE, "(player robbery) "C_WHITE"You have been robbed by "C_GREY"%p (%i) "C_WHITE"and found "C_GREEN"%m "C_WHITE"in your wallet.", playerid, playerid, moneyTaken);

    GivePlayerMoney(targetid, -moneyTaken);
    GivePlayerMoney(playerid, moneyTaken);
    Player_GiveWantedLevel(playerid, 4);

    return 1;
}

// Shooting near a cop
hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
    // shooter is not civilian.
    if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return 1;
    }

    // disallow spam, only increase wanted level after 3 minutes.
    if((gettime() - gShotNearPoliceTick[playerid]) < (60 * 3)) {
        return 1;
    }

    new
        Float:distance = 20.0,
        closestID = Player_GetClosestLeo(playerid, distance);

    // no closest law enforce officers
    if(closestID == INVALID_PLAYER_ID) {
        return 1;
    }

    SendMsgF(playerid, COLOR_RED, "You shot near a on-duty police officer, you've gained an extra 4 stars.");
    Player_GiveWantedLevel(playerid, 4);
    gShotNearPoliceTick[playerid] = gettime();
    return 1;
}

// Shooting a cop detection.
hook OnPlayerTakePlayerDmg(playerid, issuerid, &Float: amount, weaponid, bodypart ) {
    // shooter is not civilian.
    if(Player_GetClass(issuerid) != TEAM_CIVILIAN) {
        return 1;
    }

    // disallow spam, only issue this crime every 3 minutes.
    if((gettime() - gShotPoliceTick[issuerid]) < (60 * 3)) {
        return 1;
    }

    // victim is not police.
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        return 1;
    }

    SendMsgF(issuerid, COLOR_RED, "You shot an on-duty police officer, you've gained an extra 4 stars.");
    Player_GiveWantedLevel(issuerid, 4);
    gShotPoliceTick[issuerid] = gettime();
    return 1;
}