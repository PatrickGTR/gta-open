#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>

new 
    TowerCP,
    TowerRobbedRecently,
    BriefCase,
    TowerEnt,
    Timer:FindingTimer[MAX_PLAYERS];

enum E_BRIEFCASE_DATA {
    Float:E_BRIEFCASE_X,
    Float:E_BRIEFCASE_Y,
    Float:E_BRIEFCASE_Z
}

static const RandomBriefCase[][E_BRIEFCASE_DATA] =
{
    {1831.9935, -1274.5226, 125.7266},
    {1788.1812, -1309.2687, 125.7266},
    {1816.2598, -1299.8323, 125.7266},
    {1774.2363,-1301.4355,125.7209}
};

Briefcase_SetRandomLoc(playerid) {
    new rand = random(sizeof(RandomBriefCase));
    robbingdone[playerid] = 1;
    DestroyPickup(BriefCase);
    BriefCase = CreatePickup(1210, 2, RandomBriefCase[rand][E_BRIEFCASE_X], RandomBriefCase[rand][E_BRIEFCASE_Y], RandomBriefCase[rand][E_BRIEFCASE_Z], 0);
}

hook OnGameModeInit()
{
    CreateObject(1652, 1788.966796, -1297.323242, 12.930883, 0, 0, 177.300064, 0.0); //fence
    CreateObject(2332, 1817.233276, -1306.228027, 97.952163, 0, 0, 0, 0.0); //safe
    TowerCP = CreateDynamicCP(1817.1315, -1307.1591, 98.5000, 1.0, 0, 0, .streamdistance = CHECKPOINT_STREAMDISTANCE);
    TowerEnt = Entrance_Create(1807.0723, -1290.1117, 131.7344, 90.0, 1815.9473, -1317.6854, 125.7266, 90.0, 0, 0);
    Entrance_SetIcon(TowerEnt, 42);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(checkpointid == TowerCP) 
    {
        if(robbing[playerid] == 1) return 0;
        SendServerMsg(playerid, "Use /towerrobbery to rob the tower!");
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
    if(checkpointid == TowerCP) {
        if(robbing[playerid] == 1 && BurglaryInfo[playerid] == 4) {
            if(robbingdone[playerid] == 1) return 0;
            SendServerMsg(playerid, "You've left the checkpoint robbery cancelled!");
            robbing[playerid] = 0;
            BurglaryInfo[playerid] = 0;
            robbingdone[playerid] = 0;
            stop burglarytimer[playerid];
            defer TowerCooldown();
        }
    }
    return 1;
}

hook OnPlayerPickUpPickup(playerid, pickupid) {
    if(pickupid == BriefCase) {
        SetHideout(playerid); 
        
        DestroyPickup(BriefCase);

        stop FindingTimer[playerid];
    }
    return 1;
}

CMD:towerrobbery(playerid) {
    if(!IsPlayerInRangeOfPoint(playerid, 7.0, 1817.1315, -1307.1591, 98.5000)) {
        return SendServerMsg(playerid, "You're not near the safe!");
    }
    if(TowerRobbedRecently == 1) {
        return SendServerMsg(playerid, "The Tower is recently robbed!");
    }
    if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendServerMsg(playerid, "Only Civilians can rob the Bank!");
    }
    if(BurglaryInfo[playerid] != 0) {
        return SendServerMsg(playerid, "You already robbed, Please go to the hideout!");
    }
    robbing[playerid] = 1;
    BurglaryInfo[playerid] = 4;
    TowerRobbedRecently = 1;
    SendServerMsg(playerid, "Robbing the Office stay in the red marker!");
    ApplyAnimation(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 5000, 0);
    burglarytimer[playerid] = defer SetBriefCaseLoc(playerid);
    return 1;
}

timer SetBriefCaseLoc[20000](playerid)
{
    Player_GiveWantedLevel(playerid, 6);
    ClearAnimations(playerid, 1);
    robbingdone[playerid] = 1;
    Briefcase_SetRandomLoc(playerid);
    FindingTimer[playerid] = defer TowerFailedToGetBC(playerid);
    SendServerMsg(playerid, "You have 25 seconds to get the Brief Case on the PentHouse");
    return 1;
}

timer TowerFailedToGetBC[25000](playerid)
{
    Player_GiveWantedLevel(playerid, 6);
    DestroyPickup(BriefCase);
    robbing[playerid] = 0;
    BurglaryInfo[playerid] = 0;
    robbingdone[playerid] = 0;
    return 1;
}

timer TowerCooldown[RobberyCD]()
{
    foreach(new i : Player) {
        SendServerMsg(i, "Tower CooledDown!");
    }
    TowerRobbedRecently = 0;
}

CMD:forcetowercd(playerid)
{
    TowerCooldown();
    return 1;
}

stock SetHideout(playerid)
{
    robbingdone[playerid] = 1;
    ClearAnimations(playerid, 1);
    SetRandomHideout(playerid);

    SendServerMsg(playerid, "Go to the hideout and evede the cops!");
    Player_GiveWantedLevel(playerid, 6);
    return 1;
}

CMD:tower(playerid)
{
    SetPlayerPos(playerid, 1817.1315, -1307.1591, 98.5000);
    return 1;
}