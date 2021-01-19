#include <YSI_Coding\y_hooks>

static
    PlayerBreakOutTick[MAX_PLAYERS];


hook OnPlayerConnect(playerid) {
    PlayerBreakOutTick[playerid] = 0;
    return 1;
}

CMD:breakout(playerid, params[]) {

    if(!Player_IsInJail(playerid)) {
        return SendErrorMsg(playerid, "You are not in prison.");
    }

    if(gettime() - PlayerBreakOutTick[playerid] < 60) {
        return SendErrorMsg(playerid, "You just used this command recently, please wait... ");
    }

    if (Player_GetPicklock(playerid) < 1) {
        return SendErrorMsg(playerid, "You need a picklock to escape from jail.");
    }

    new
        bool:success_rate = RandomChance(65);
    if (!success_rate) {
        SendServerMsg(playerid, "You failed to escape from jail.");
        PlayerBreakOutTick[playerid] = gettime();
        return 1;
    }


    Player_GivePicklock(playerid, -1);
    Player_ReleaseFromJail(playerid);

    PlayerBreakOutTick[playerid] = gettime();
    return 1;
}