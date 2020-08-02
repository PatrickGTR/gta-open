#include <logger>
#include <YSI_Coding\y_hooks>
new 
    bool:PlayerIsGettingAr[MAX_PLAYERS]
;

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(killerid != INVALID_PLAYER_ID && Player_IsLEO(killerid) && Player_GetWantedLevel(playerid) >= 3)
    {
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
    new closestleo = Player_GetClosestLeo(playerid);
    new Float:x, Float:y, Float:z;
    GetPlayerPos(closestleo, x, y, z);
    if(IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
    {
        SendMsgF(closestleo, COLOR_BLUE, "[POLICE]: You have took down %p (%d)", playerid, playerid);
        Player_GiveScore(closestleo, 5, true);
        Player_RemoveScore(playerid, 2);
        DelaySendToJail(playerid);
    }
    return 1;
}

// returns
// -1 (player is not a cop)
// -2 (target is not connected)
// -3 (target is below arrestable)
// -4 (target is in car, pull over demand.)
stock Player_Arrest(playerid, targetid) {

    if(!Player_IsLEO(playerid)) {
        return -1;
    }

    if(!IsPlayerConnected(targetid)) {
        return INVALID_PLAYER_ID;
    }

    if(Player_GetWantedLevel(targetid) <= 3) {
        return -3;
    }

    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        Player_NotifyPullover(playerid, targetid);
        return -4;
    }

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
        SendServerMsg(playerid, "You must be on foot to arrest the criminal");
        return -5;
    }

    if(!Player_IsCuffed(targetid)) {
        SendErrorMsg(playerid, "You need to cuff the player first!");
        return -6;
    }

    if(PlayerIsGettingAr[targetid]) {
        SendErrorMsg(playerid, "The player is now getting arrested");
        return -7;
    }

    ApplyAnimation(targetid, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 3000, 1);
    ApplyAnimation(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 3000, 1);

    // make of them face each other.
    Player_FacePlayer(playerid, targetid);
    Player_FacePlayer(targetid, playerid);

    // let animation play out for both  end.
    defer DelaySendToJail(targetid);

    Player_AwardArrest(playerid, targetid);

    PlayerIsGettingAr[targetid] = true;
    
    SendServerMsgF(playerid, "You have arrested %p (%d)", targetid, targetid);
    SendServerMsgF(targetid, "You have been arrested by %p (%d)", playerid, playerid);

    GameTextForPlayer(targetid, "~r~Busted!", 4000, 0);
    return 1;
}

timer void:DelaySendToJail[3000 + GetPlayerPing(targetid)](targetid) {
    new
        level = GetPlayerWantedLevel(targetid),
        seconds = (level * 2);
    Player_SetBailAmount(targetid, 5000);
    Player_SendToJail(targetid, seconds, true);
    PlayerIsGettingAr[targetid] = false;
}

stock void:Player_AwardArrest(playerid, targetid, bool:notify = true) {

    new
        level =  GetPlayerWantedLevel(targetid),
        money = level * 100;
    GivePlayerMoney(playerid, money);
    Player_GiveScore(playerid, 1, true);
    Player_RemoveScore(playerid, 1);

    if(notify) {
        SendMsgF(playerid, COLOR_YELLOW, "REWARD! "C_WHITE"You have been rewarded "C_GREEN"%m "C_WHITE"for arresting "C_GREY"%p[%i] "C_WHITE"with "C_GREY"%i "C_WHITE"wanted level.", money, targetid, targetid, level);
    }

    if(money > 40000) {
        dbg(PLAYER_DEBUG_HANDLER, "player arrest reward",
            _p("playerid", playerid),
            _p("targetid", targetid),
            _i("amount", money)
        );
    }
}

stock void:Player_NotifyPullover(playerid, targetid) {
    SendMsgF(playerid, COLOR_BLUE, "[PULLOVER] "C_WHITE"You have asked "C_GREY"%p (%d) "C_WHITE"to pull over!", targetid, targetid);
    SendMsgF(targetid, COLOR_BLUE, "[PULLOVER] "C_WHITE"Officer "C_GREY"%p (%d) "C_WHITE"has asked you to pull over!", playerid, playerid);
}