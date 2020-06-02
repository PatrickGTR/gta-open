#include <YSI_Coding\y_hooks>

new 
    PlayerInHouseID[MAX_PLAYERS];

stock Player_GetInHouseID(playerid) {
    return PlayerInHouseID[playerid];
}

stock Player_InHouseEntrance(playerid, houseid) {
    return IsPlayerInDynamicCP(playerid, House_GetEntranceCPHandler(houseid));
}

stock Player_InHouseExit(playerid, houseid) {
    return IsPlayerInDynamicCP(playerid, House_GetExitCPHandler(houseid));
}


hook OnPlayerEnterDynamicCP(playerid, checkpointid) {
    new
        arr[2];

    Streamer_GetArrayData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID, arr);

    if (arr[0] == HOUSES_STREAMER_IDENTIFIER) {
        new index = arr[1];
        if (checkpointid == House_GetEntranceCPHandler(index)) {
            PlayerInHouseID[playerid] = index;
            //ply_houseCheckpointID[playerid] = checkpointid;
        }
    }
    return 1;
}