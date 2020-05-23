#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

#define RobberyCD 300000

new
    Timer:burglarytimer[MAX_PLAYERS];

new 
    bankcp, 
    casinocp, 
    manscp;

new 
    robbing[MAX_PLAYERS],
    robbingdone[MAX_PLAYERS],
    BurglaryInfo[MAX_PLAYERS];

new 
    bankrecent,
    casinorecent,
    mansrecent;

enum RHIDEOUTS {
    Float:rhX,
    Float:rhY,
    Float:rhZ
}

stock const RandomHideouts[][RHIDEOUTS] =
{
    {-68.8063, -1576.7695, 2.6172},
    {-1644.6675, -2253.2825, 31.7160},
    {-52.6506, -1147.7380, 1.0781},
    {-42.4774, -222.8400, 5.4297}
};

stock SetRandomHideout(playerid) {
    new rand = random(sizeof(RandomHideouts));
    robbingdone[playerid] = 1;
    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, RandomHideouts[rand][rhX], RandomHideouts[rand][rhY], RandomHideouts[rand][rhZ], RandomHideouts[rand][rhX], RandomHideouts[rand][rhY], RandomHideouts[rand][rhZ], 3.0);
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
            stop burglarytimer[playerid];
            defer BankCooldown();
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
            stop burglarytimer[playerid];
            defer CasinoCooldown();
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
            stop burglarytimer[playerid];
            defer MansCooldown();
        }
    }
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
        if(robbing[playerid] == 1) return 0;
        SendServerMsg(playerid, "Use /robbery to rob the bank!");
    }
    if(checkpointid == casinocp) {
        if(robbing[playerid] == 1) return 0;
        SendServerMsg(playerid, "Use /robbery to rob the casino!");
    }
    if(checkpointid == manscp) {
        if(robbing[playerid] == 1) return 0;
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
            defer BankCooldown();
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
            defer CasinoCooldown();
        }
        if(BurglaryInfo[playerid] == 3) //mansion
        {
            new bmrand = random(200000);
            GivePlayerMoney(playerid, bmrand);
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                SendServerMsgF(i, "%p (%d) has robbed %d from XomoX's mansion!", playerid, playerid, bmrand);
            }
            DisablePlayerRaceCheckpoint(playerid);
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            defer MansCooldown();
        }
        if(BurglaryInfo[playerid] == 4)
        {
            new bmrand = random(100000);
            GivePlayerMoney(playerid, bmrand);
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                SendServerMsgF(i, "%p (%d) has robbed %d from the tower!", playerid, playerid, bmrand);
            }
            DisablePlayerRaceCheckpoint(playerid);
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            defer TowerCooldown();
        }
    }
    return 1;
}

CMD:robbery(playerid) {
    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2306.5659, -5.1260, 26.7422)) {
        if(bankrecent == 1) {
            return SendServerMsg(playerid, "The bank is recently robbed!");
        }
        if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
            return SendServerMsg(playerid, "Only Civilians can rob the Bank!");
        }
        if(BurglaryInfo[playerid] != 0) {
            return SendServerMsg(playerid, "You already robbed, Please go to the hideout!");
        }
        robbing[playerid] = 1;
        BurglaryInfo[playerid] = 1;
        bankrecent = 1;
        SendServerMsg(playerid, "Robbing the bank stay in the red marker!");
        ApplyAnimation(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 5000, 0);
        burglarytimer[playerid] = defer SetHideoutTimer(playerid);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 7.0, 1141.6899, 11.1338, 1000.6797)) {
        if(casinorecent == 1) {
            return SendServerMsg(playerid, "The Casino is recently robbed!");
        }
        if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
            return SendServerMsg(playerid, "Only Civilians can rob the Casino!");
        }
        if(BurglaryInfo[playerid] != 0) {
            return SendServerMsg(playerid, "You already robbed, Please go to the hideout!");
        }
        robbing[playerid] = 1;
        BurglaryInfo[playerid] = 2;
        casinorecent = 1;
        SendServerMsg(playerid, "Robbing the casino stay in the red marker!");
        burglarytimer[playerid] = defer SetHideoutTimer(playerid);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 7.0, 1230.8403, -807.2298, 1084.0078)) {
        if(mansrecent == 1) {
            return SendServerMsg(playerid, "The Mansion is recently robbed!");
        }
        if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
            return SendServerMsg(playerid, "Only Civilians can rob the Mansion!");
        }
        if(BurglaryInfo[playerid] != 0) {
            return SendServerMsg(playerid, "You already robbed, Please go to the hideout!");
        }
        robbing[playerid] = 1;
        BurglaryInfo[playerid] = 3;
        mansrecent = 1;
        SendServerMsg(playerid, "Robbing the mansion stay in the red marker!");
        burglarytimer[playerid] = defer SetHideoutTimer(playerid);
    }
    else {
        return SendServerMsg(playerid, "You're not near a robbery checkpoint!");
    }
    return 1;
}

timer SetHideoutTimer[20000](playerid)
{
    Player_GiveWantedLevel(playerid, 6);
    ClearAnimations(playerid, 1);
    robbingdone[playerid] = 1;
    SetRandomHideout(playerid);
    SendServerMsg(playerid, "Go to the hideout and evede the cops!");
    return 1;
}

timer BankCooldown[RobberyCD]()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        SendServerMsg(i, "Bank CooledDown!");
    }
    bankrecent = 0;
    return 1;
}

timer CasinoCooldown[RobberyCD]()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        SendServerMsg(i, "Casino CooledDown!");
    }
    casinorecent = 0;
    return 1;
}

timer MansCooldown[RobberyCD]()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        SendServerMsg(i, "Mansion CooledDown!");
    }
    mansrecent = 0;
    return 1;
}