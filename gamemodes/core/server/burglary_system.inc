#include <YSI_Coding\y_hooks>


new bankcp, casinocp, manscp;

new robbing[MAX_PLAYERS];
new robbingdone[MAX_PLAYERS];
new BurglaryInfo[MAX_PLAYERS];

new bankrecent, bankreset;
new casinorecent, casinoreset;
new mansrecent, mansreset;

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
    robbingdone[playerid] = 1;
    SetPlayerRaceCheckpoint(playerid, 1, RandomHideouts[rand][rhX], RandomHideouts[rand][rhY], RandomHideouts[rand][rhZ], RandomHideouts[rand][rhX], RandomHideouts[rand][rhY], RandomHideouts[rand][rhZ], RandomHideouts[rand][rhSize]);
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(robbing[playerid] == 1 && BurglaryInfo[playerid] == 1)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 7.0, 2306.5659, -5.1260, 26.7422))
        {
            if(robbingdone[playerid] == 1) return 0;
            SendServerMsg(playerid, "You've left the checkpoint robbery cancelled!");
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0; 
            bankreset = SetTimer("BankCooldown", 300000, false);
        }
    }
    if(robbing[playerid] == 1 && BurglaryInfo[playerid] == 2)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 7.0, 1141.6899, 11.1338, 1000.6797))
        {
            if(robbingdone[playerid] == 1) return 0;
            SendServerMsg(playerid, "You've left the checkpoint robbery cancelled!");
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            casinoreset = SetTimer("CasinoCooldown", 300000, false);
        }
    }
    if(robbing[playerid] == 1 && BurglaryInfo[playerid] == 3)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 7.0, 1230.8403, -807.2298, 1084.0078))
        {
            if(robbingdone[playerid] == 1) return 0;
            SendServerMsg(playerid, "You've left the checkpoint robbery cancelled!");
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            mansreset = SetTimer("MansCooldown", 300000, false);
        }
    }
    else return 0;
    return 1;
}

hook OnGameModeInit()
{
    //bank
    CreateDynamicObject(2332, 2305.8000488281, -5.0999999046326, 26.200000762939, 0.0, 0.0, 90, 30);
    bankcp = CreateDynamicCP(2306.5659, -5.1260, 26.7422, 1.0, 30, 0, .streamdistance = CHECKPOINT_STREAMDISTANCE);
    //casino
    CreateDynamicObject(2332, 1141.6999511719, 12.10000038147, 1000.0999755859, 0.0, 0.0, 0.0, 31);
    casinocp = CreateDynamicCP(1141.6899, 11.1338, 1000.6797, 1.0, 31, 12, .streamdistance = CHECKPOINT_STREAMDISTANCE);
    //mansion
    manscp = CreateDynamicCP(1230.8403, -807.2298, 1084.0078, 1.0, 32, 5, .streamdistance = CHECKPOINT_STREAMDISTANCE);
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid) 
{
    if(checkpointid == bankcp) {
        SendServerMsg(playerid, "Use /robbery to rob the bank!");
    }
    if(checkpointid == casinocp) {
        SendServerMsg(playerid, "Use /robbery to rob the casino!");
    }
    if(checkpointid == manscp) {
        SendServerMsg(playerid, "Use /robbery to rob the mansion!");
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(robbing[playerid] == 1)
    {
        if(BurglaryInfo[playerid] == 1) //bank
        {
            new bmrand = random(100000);
            GivePlayerMoney(playerid, bmrand);
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                SendServerMsgF(i, "%p (%d) has robbed %d from the bank!", playerid, playerid, bmrand);
            }
            DisablePlayerRaceCheckpoint(playerid);
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            bankreset = SetTimer("BankCooldown", 300000, false);
        }
        if(BurglaryInfo[playerid] == 2) //casino
        {
            new bmrand = random(50000);
            GivePlayerMoney(playerid, bmrand);
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                SendServerMsgF(i, "%p (%d) has robbed %d from the casino!", playerid, playerid, bmrand);
            }
            DisablePlayerRaceCheckpoint(playerid);
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            casinoreset = SetTimer("CasinoCooldown", 300000, false);
        }
        if(BurglaryInfo[playerid] == 3) //mansion
        {
            new bmrand = random(200000);
            GivePlayerMoney(playerid, bmrand);
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                SendServerMsgF(i, "%p (%d) has robbed %d from XomoX's mansion!", playerid, playerid, bmrand);
            }
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            mansreset = SetTimer("MansCooldown", 300000, false);
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
    else if(IsPlayerInRangeOfPoint(playerid, 7.0, 1141.6899, 11.1338, 1000.6797)) {
        if(casinorecent == 1) return SendServerMsg(playerid, "The Casino is recently robbed!");
        robbing[playerid] = 1;
        BurglaryInfo[playerid] = 2;
        casinorecent = 1;
        SendServerMsg(playerid, "Robbing the casino stay in the red marker!");
        SetTimerEx("SetHideoutTimer", 20000, false, "i", playerid);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 7.0, 1230.8403, -807.2298, 1084.0078)) {
        if(mansrecent == 1) return SendServerMsg(playerid, "The Mansion is recently robbed!");
        robbing[playerid] = 1;
        BurglaryInfo[playerid] = 3;
        mansrecent = 1;
        SendServerMsg(playerid, "Robbing the mansion stay in the red marker!");
        SetTimerEx("SetHideoutTimer", 20000, false, "i", playerid);
    }
    else return SendServerMsg(playerid, "You're not near a robbery checkpoint!");
    return 1;
}

forward SetHideoutTimer(playerid);
public SetHideoutTimer(playerid)
{
    SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 6);
    Player_SaveWantedLevel(playerid, GetPlayerWantedLevel(playerid));
    robbingdone[playerid] = 1;
    SetRandomHideout(playerid);
    SendServerMsg(playerid, "Go to the hideout and evede the cops!");
    return 1;
}

forward BankCooldown();
public BankCooldown()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        SendServerMsg(i, "Bank CooledDown!");
    }
    bankrecent = 0;
    KillTimer(bankreset);
    return 1;
}

forward CasinoCooldown();
public CasinoCooldown() 
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        SendServerMsg(i, "Casino CooledDown!");
    }
    casinorecent = 0;
    KillTimer(casinoreset);
    return 1;
}

forward MansCooldown();
public MansCooldown()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        SendServerMsg(i, "Mansion CooledDown!");
    }
    mansrecent = 1;
    KillTimer(mansreset);
    return 1;
}