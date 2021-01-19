#include <YSI_Coding\y_hooks>

static
    PlayerBreakCuffTick[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerBreakCuffTick[playerid] = 0;
    return 1;
}

CMD:breakcuff(playerid, params[]) {

    if (Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only civilians can break cuff.");
    }
    if (!Player_IsCuffed(playerid)) {
        return SendErrorMsg(playerid, "You are not cuffed, how is that possible?");
    }
    if (gettime() - PlayerBreakCuffTick[playerid] < 60) {
        return SendErrorMsg(playerid, "You just used this command recently, try again later.");
    }
    if (Player_GetPicklock(playerid) < 1) {
        return SendErrorMsg(playerid, "You need a picklock to escape from cuffs.");
    }

    new
        bool:success_rate = RandomChance(65);
    if (!success_rate) {
        SendServerMsg(playerid, "You failed to escape from cuffs");
        PlayerBreakCuffTick[playerid] = gettime();
        return 1;
    }

    // Notify player
    SendServerMsg(playerid, "You have managed to picklock the cuffs! Run away from the police!");

    // Set data
    Player_GivePicklock(playerid, -1);
    Player_Cuff(playerid, false);

    PlayerBreakCuffTick[playerid] = gettime();
    return 1;
}