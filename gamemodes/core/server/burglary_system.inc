#include <YSI_Coding\y_hooks>


new bankcp;

new robbing[MAX_PLAYERS];
new BurglaryInfo[MAX_PLAYERS];
new bankrecent, bankreset;

enum RHIDEOUTS {
    Float:rhX,
    Float:rhY,
    Float:rhZ,
    Float:rhSize
}

stock const RandomHideouts[][RHIDEOUTS] =
{
    { -68.8063, -1576.7695, 2.6172, 3.0}
};

stock SetRandomHideout(playerid) {
    new rand = random(sizeof(RandomHideouts));
    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, RandomHideouts[rand][rhX], RandomHideouts[rand][rhY], RandomHideouts[rand][rhZ], RandomHideouts[rand][rhX], RandomHideouts[rand][rhY], RandomHideouts[rand][rhZ], RandomHideouts[rand][rhSize]);
    return 1;
}

hook OnGameModeInit()
{
    //bank
    CreateDynamicObject(2332, 2305.8000488281, -5.0999999046326, 26.200000762939, 0.0, 0.0, 90, 30);
    bankcp = CreateDynamicCP(2306.5659, -5.1260, 26.7422, 1.5, 30, 0, 100);
    //casino
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid) 
{
    if(checkpointid == bankcp) {
        SendServerMsg(playerid, "Use /robbery to rob the bank!");
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(robbing[playerid] == 1)
    {
        if(BurglaryInfo[playerid] == 1) //bank
        {
            new bmrand = random(50000);
            GivePlayerMoney(playerid, bmrand);
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                SendServerMsgF(i, "%p (%d) has robbed %d from the bank!", playerid, playerid, bmrand);
            }
            DisablePlayerRaceCheckpoint(playerid);
            robbing[playerid] = 0;
            bankrecent = 1;
            bankreset = SetTimer("BankCooldown", 300000, false);
        }
    }
    else return 0;
    return 1;
}

CMD:robbery(playerid) {
    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2306.5659, -5.1260, 26.7422)) {
        if(bankrecent == 1) return SendServerMsg(playerid, "The bank is recently robbed!");
        robbing[playerid] = 1;
        BurglaryInfo[playerid] = 1;
        bankrecent = 1;
        SendServerMsg(playerid, "Robbing the bank stay in the red marker!");
        SetTimerEx("SetHideoutTimer", 20000, false, "i", playerid);
    }
    return 1;
}

forward SetHideoutTimer(playerid);
public SetHideoutTimer(playerid)
{
    robbing[playerid] = 1;
    SetRandomHideout(playerid);
    SendServerMsg(playerid, "Go to the hideout and evede the cops!");
    return 1;
}

forward BankCooldown();
public BankCooldown()
{
    bankrecent = 0;
    KillTimer(bankreset);
    return 1;
}