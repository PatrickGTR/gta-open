#include <YSI_Coding\y_hooks>

#define MAX_MISSION_NAME       (30)

static
    pmissioncp,
    bool:CanMission[MAX_PLAYERS],
    bool:PlayerMissionState[MAX_PLAYERS],
    LastCheckpoint[MAX_PLAYERS],
    PlayerCallsDone[MAX_PLAYERS] = 0;

enum F_MISSION_DATA
{
    F_NAME[MAX_MISSION_NAME],
    Float:F_MISSION_X,
    Float:F_MISSION_Y,
    Float:F_MISSION_Z
}

static
    const MissionData[][F_MISSION_DATA] =
{
    {"Ammu-Nation", 1360.0903, -1279.8955, 13.3828},
    {"All Saints Hospital", 1196.0430, -1323.8611, 13.3984},
    {"Bank", 587.2368, -1230.0907, 17.7013},
    {"Casino", 1023.2428, -1142.2000, 23.6563},
    {"XomoX's Mansion", 1242.0171, -747.2955, 94.7491},
    {"City Hall", 1479.6250, -1735.0322, 13.3828},
    {"Disco", 1823.6171, -1682.7771, 13.3828},
    {"SA-MP Tower", 1786.9865, -1280.0614, 13.4688}
};

hook OnGameModeInit()
{
    pmissioncp = CreateDynamicCP(1580.2233, -1634.8108, 13.5615, 1.0, 0, 0, .streamdistance = CHECKPOINT_STREAMDISTANCE);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(checkpointid == pmissioncp)
    {
        if(Player_IsLEO(playerid))
        {
            CanMission[playerid] = true;

            MessageBox_Show(
                playerid, TYPE_MSGBOX,
                "~p~Police Mission",
                "~w~Use ~p~/mission ~w~to start a mission."
            );
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
    if(CanMission[playerid]) {
        CanMission[playerid] = false;
    }
    return 1;
}

CMD:mission(playerid)
{
    if(!Player_IsLEO(playerid)) {
        return SendErrorMsg(playerid, "You're not a Cop!");
    }
    if(!CanMission[playerid]) {
        return SendErrorMsg(playerid, "You're not in a mission area!");
    }
    mission_begin(playerid);
    return 1;
}

mission_begin(playerid)
{
    PlayerMissionState[playerid] = true;
    new randloc = random(sizeof(MissionData));
    if(LastCheckpoint[playerid] == randloc) {
        mission_begin(playerid);
        return -1;
    }
    if(PlayerCallsDone[playerid] == 3) {
        GivePlayerMoney(playerid, 25000);
        SendServerMsgF(playerid, "Completed a Police Mission Recieved 25k");
        Player_GiveScore(playerid, 1, true);
        mission_cancel(playerid);
        return -2;
    }
    new
        Float:x,
        Float:y,
        Float:z,
        mname[MAX_MISSION_NAME];
    x = MissionData[randloc][F_MISSION_X];
    y = MissionData[randloc][F_MISSION_Y];
    z = MissionData[randloc][F_MISSION_Z];
    strcpy(mname, MissionData[randloc][F_NAME], sizeof(mname));

    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, x, y, z, x, y, z, 3.0);

    new
        currentTime = UI_GetTimeLeft(playerid),
        newtime = currentTime + 60;

    UI_TimeLeft(playerid, newtime);

    SendServerMsgF(playerid, "Respond to the Call at %s", mname);
    LastCheckpoint[playerid] = randloc;
    return 1;
}

mission_cancel(playerid) {
    PlayerMissionState[playerid] = false;
    DisablePlayerRaceCheckpoint(playerid);
    PlayerCallsDone[playerid] = 0;
    CanMission[playerid] = false;
    LastCheckpoint[playerid] = -1;
    UI_HideTimeLeft(playerid);
    return 1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(PlayerMissionState[playerid])
    {
        if(PlayerCallsDone[playerid] < 3) {
            GivePlayerMoney(playerid, 5000);
            Player_GiveScore(playerid, 1, true);
            PlayerCallsDone[playerid]++;
            mission_begin(playerid);
        }
    }
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(UI_GetTimeLeft(playerid) == 0 && PlayerMissionState[playerid])
    {
        SendServerMsgF(playerid, "Failed to respond to the Checkpoint.");
        mission_cancel(playerid);
    }
    return 1;
}