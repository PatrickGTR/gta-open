#include <YSI_Coding\y_hooks>

static
    gPlayerCuffEscapeDelay[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    gPlayerCuffEscapeDelay[playerid] = 0;
    return 1;
}

CMD:breakcuff(playerid, params[])
{
    if (Player_IsCuffed(playerid))
        return SendErrorMsg(playerid, "You are not cuffed, how is that possible?");

    if (gettime() - gPlayerCuffEscapeDelay[playerid] < 60)
        return SendErrorMsg(playerid, "You just used this command recently, try again later.");

    if (Player_GetPicklock(playerid) < 1)
        return SendErrorMsg(playerid, "You need a picklock to escape from cuffs.");


    new bool:success_rate = RandomChance(65);
    if (!success_rate) {
        gPlayerCuffEscapeDelay[playerid] = gettime();
        SendServerMsg(playerid, "You failed to escape from cuffs");
        return 1;
    }

    gPlayerCuffEscapeDelay[playerid] = gettime();
    SendServerMsg(playerid, "You have managed to picklock the cuffs! Run away from the police!");

    Player_Cuff(playerid, false);
    return true;
}