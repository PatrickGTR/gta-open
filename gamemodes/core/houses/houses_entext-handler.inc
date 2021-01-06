#include <YSI_Coding\y_hooks>

stock Player_GetInHouseID(playerid) {
    return GetPVarInt(playerid, "House_Id");
}

stock Player_InHouseEntrance(playerid, houseid) {
    return IsPlayerInDynamicCP(playerid, House_GetEntranceCPHandler(houseid));
}

stock Player_InHouseExit(playerid, houseid) {
    return IsPlayerInDynamicCP(playerid, House_GetExitCPHandler(houseid));
}

stock Player_InHouseWorld(playerid) {
    new
        arr[2];

    Streamer_GetArrayData(STREAMER_TYPE_CP, GetPVarInt(playerid, "House_CheckpointId"), E_STREAMER_EXTRA_ID, arr);
    return House_GetWorld(arr[1]);
}

stock Player_InHouseInterior(playerid) {
    new
        arr[2];

    Streamer_GetArrayData(STREAMER_TYPE_CP, GetPVarInt(playerid, "House_CheckpointId"), E_STREAMER_EXTRA_ID, arr);
    return House_GetInterior(arr[1]);
}


hook OnPlayerEnterDynamicCP(playerid, checkpointid) {
    new
        arr[2];
    Streamer_GetArrayData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID, arr);

    if (arr[0] == HOUSES_STREAMER_IDENTIFIER) {
        new
            index = arr[1];
        if (checkpointid == House_GetEntranceCPHandler(index)) {
            SetPVarInt(playerid, "House_Id", index);
            SetPVarInt(playerid, "House_CheckpointId", checkpointid);
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, checkpointid) {
    new
        arr[2];
    Streamer_GetArrayData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID, arr);

    if (arr[0] == HOUSES_STREAMER_IDENTIFIER) {
        new
            index = arr[1];

        if (checkpointid == House_GetEntranceCPHandler(index)) {
            // Do not delete data just yet if player is inside the house
            // or entered the house.
            if(Player_IsInsideHouse(playerid)) {
                return 1;
            }

            DeletePVar(playerid, "House_Id");
            DeletePVar(playerid, "House_CheckpointId");
        }
    }
    return 1;
}