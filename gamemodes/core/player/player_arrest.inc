#include <logger>
#include <YSI_Coding\y_hooks>
new
    bool:gPlayerGettingArrested[MAX_PLAYERS]
;

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(killerid != INVALID_PLAYER_ID) {
        if(Player_IsLEO(killerid) && Player_GetWantedLevel(playerid) >= 3) {
            if(Player_GetWantedLevel(playerid) >= 10) {
                foreach(new i : Player) {
                    if(Player_IsLEO(i)) {
                        SendMsgF(playerid, COLOR_BLUE, "[POLICE TAKEDOWN]: %p (%d) has taken %p (%d) with brutal force", killerid, killerid, playerid, playerid);
                        GivePlayerMoney(playerid, 5000);
                    }
                }
            }
            Player_GiveScore(killerid, 5, true);
            Player_RemoveScore(playerid, 2);
            DelaySendToJail(playerid);
        }
    }
    return 1;
}

// returns
// 0 fail
// - (player is not a cop)
// - (target is not connected)
// - (target is below arrestable)
// 1 success
// - (target is in car, pull over demand.)
Player_Arrest(playerid, targetid, errorMessage[], len = sizeof(errorMessage)) {
    if(!Player_IsLEO(playerid)) {
        strcat(errorMessage, "Only cops can use this command!", len);
        return 0;
    }

    if(!IsPlayerConnected(targetid)) {
        strcat(errorMessage, "Player is not connected!", len);
        return 0;
    }

    // do nothing, automatically return 1
    // can't arrest player with wanted level lower than 3.
    if(Player_GetWantedLevel(targetid) <= 3) {
        return 1;
    }

    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        Player_NotifyPullover(playerid, targetid);
        return 1;
    }

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
        strcat(errorMessage, "You must be on foot to arrest the criminal", len);
        return 0;
    }

    if(!Player_IsCuffed(targetid)) {
        strcat(errorMessage, "You need to cuff the player first!", len);
        return 0;
    }

    if(gPlayerGettingArrested[targetid]) {
        strcat(errorMessage, "The player is now getting arrested", len);
        return 0;
    }

    if(targetid == playerid) {
        strcat(errorMessage, "You can't arrest yourself, dummy!", len);
        return 0;
    }

    // UI
    GameTextForPlayer(targetid, "~r~Busted!", 4000, 0);
    ApplyAnimation(targetid, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 3000, 1);
    ApplyAnimation(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 3000, 1);
    SendServerMsgF(playerid, "You have arrested %p (%d)", targetid, targetid);
    SendServerMsgF(targetid, "You have been arrested by %p (%d)", playerid, playerid);
    // make of them face each other.
    Player_FacePlayer(playerid, targetid);
    Player_FacePlayer(targetid, playerid);
    // let animation play out for both end before sending player to jail x, y, z
    defer DelaySendToJail(targetid);

    Player_AwardArrest(playerid, targetid);

    // if player is getting arrested, disallow actions from other police officers while UI is playing.
    gPlayerGettingArrested[targetid] = true;
    return 1;
}

timer void:DelaySendToJail[1500 + GetPlayerPing(targetid)](targetid) {
    new
        level = GetPlayerWantedLevel(targetid),
        seconds = (level * 2);
    Player_SetBailAmount(targetid, 5000);
    Player_SendToJail(targetid, seconds, true);
    gPlayerGettingArrested[targetid] = false;
}

stock void:Player_AwardArrest(playerid, targetid, bool:notify = true) {

    new
        level =  GetPlayerWantedLevel(targetid),
        money = level * 200;
    GivePlayerMoney(playerid, money);
    Player_GiveScore(playerid, 1, true);
    Player_RemoveScore(playerid, 1);

    if(notify) {
        SendMsgF(playerid, COLOR_YELLOW, "REWARD! "C_WHITE"You have been rewarded "C_GREEN"%m "C_WHITE"for arresting "C_GREY"%p[%i] "C_WHITE"with "C_GREY"%i "C_WHITE"wanted level.", money, targetid, targetid, level);
    }

    if(money > 40000) {
        Logger_Dbg(PLAYER_DEBUG_HANDLER, "player arrest reward",
            Logger_P(playerid),
            Logger_P(targetid),
            Logger_I("amount", money)
        );
    }
}

stock void:Player_NotifyPullover(playerid, targetid) {
    SendMsgF(playerid, COLOR_BLUE, "[PULLOVER] "C_WHITE"You have asked "C_GREY"%p (%d) "C_WHITE"to pull over!", targetid, targetid);
    SendMsgF(targetid, COLOR_BLUE, "[PULLOVER] "C_WHITE"Officer "C_GREY"%p (%d) "C_WHITE"has asked you to pull over!", playerid, playerid);
}