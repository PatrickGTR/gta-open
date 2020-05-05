#include <YSI_Coding\y_hooks>

new hideout1;

new bankcp;

new robbing[MAX_PLAYERS];
new BurglaryInfo[MAX_PLAYERS];
new bankrecent, bankreset;

hook OnGameModeInit()
{
    //hideouts
    hideout1 = CreatePickup(1274, 2, 70.7297, -1577.4290, 2.6172);
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

hook OnPlayerPickUpPickup(playerid, pickupid)
{
    if(pickupid == hideout1)
    {
        if(BurglaryInfo[playerid] == 1)
        {
            new randmoney = random(100000);
            GivePlayerMoney(playerid, randmoney);
            bankreset = SetTimer("BankCooldown", 600000, false);
            SendServerMsgF(playerid, "You have robbed %d from the bank!", randmoney);
        }
        else return SendServerMsg(playerid, "You don't have any burglarys!");
    }
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