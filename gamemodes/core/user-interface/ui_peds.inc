#include <YSI_Coding\y_hooks>

new ammuactor, recentrobbed[MAX_ACTORS];
new robbing[MAX_PLAYERS], myrecentrobbedstore[MAX_PLAYERS];
new robbingammu;

hook OnGameModeInit()
{
    ammuactor = CreateActor(30, 313.2123, -167.7643, 999.5938, 1.8504);
    SetActorVirtualWorld(ammuactor, 7);
    return 1;
}

hook OnPlayerUpdate(playerid) {
    if(!IsPlayerInRangeOfPoint(playerid, 7.0, 313.2123, -167.7643, 999.5938) && robbing[playerid] == 1) {
        SendServerMsg(playerid, "You must be near the clerk. Robbery failed!");
        robbing[playerid] = 0;
        recentrobbed[ammuactor] = 1;
        myrecentrobbedstore[playerid] = ammuactor;
        ApplyActorAnimation(ammuactor, "PED", "DUCK_cower", 4.1, 0, 1, 1, 1, 0);
        SetTimerEx("AmmuHoldupCD", 30000, false, "i", playerid);
        KillTimer(robbingammu);    
    }
    return 1;
}

CMD:holdup(playerid) {
    if(IsPlayerInRangeOfPoint(playerid, 7.0, 313.2123, -167.7643, 999.5938))
    {
        if(recentrobbed[ammuactor] == 1) return SendServerMsg(playerid, "This store is recently robbed!");
        if(myrecentrobbedstore[playerid] == ammuactor) return SendServerMsg(playerid, "You can't rob the same store 2 times in a row!");
        ClearActorAnimations(ammuactor);
        ApplyActorAnimation(ammuactor, "SHOP", "SHP_Rob_GiveCash", 4.1, 1, 1, 1, 1, 0);
        SendServerMsg(playerid, "You're robbing the store!");
        robbing[playerid] = 1;
        robbingammu = SetTimerEx("AmmuHoldupDone", 10000, false, "i", playerid);
    }
    else return SendServerMsg(playerid, "You're not near a store clerk!");
    return 1;
}

forward AmmuHoldupDone(playerid);
public AmmuHoldupDone(playerid) {
    new randholdup = random(3000);
    ClearActorAnimations(ammuactor);
    ApplyActorAnimation(ammuactor, "PED", "DUCK_cower", 4.1, 0, 1, 1, 1, 0);
    GivePlayerMoney(playerid, randholdup);
    recentrobbed[ammuactor] = 1;
    myrecentrobbedstore[playerid] = ammuactor;
    SendServerMsgF(playerid, "Robbed %d", randholdup);
    SendServerMsg(playerid, "You've robbed this store successfuly!");
    robbing[playerid] = 0;
    SetTimerEx("AmmuHoldupCD", 30000, false, "i", playerid);
    return 1;
}

forward AmmuHoldupCD(playerid);
public AmmuHoldupCD(playerid) {
    ClearActorAnimations(ammuactor);
    recentrobbed[ammuactor] = 0;
    return 1;
}