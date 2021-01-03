// Definitions
#define MAX_ENTRANCES               (128 * 2)
#define MAX_STORE_NAME              (30)

#define ENTRANCE_UP                 (true)
#define ENTRANCE_DOWN               (false)

// Declarations
static
    // Animation
    bool:EnExObjectState[MAX_ENTRANCES],
    EnExObject[MAX_ENTRANCES],
    // Area
    EnExArea[MAX_ENTRANCES],
    // Entrance
    entranceStoreName[MAX_ENTRANCES][MAX_STORE_NAME],
    Float: entranceX[MAX_ENTRANCES],
    Float: entranceY[MAX_ENTRANCES],
    Float: entranceZ[MAX_ENTRANCES],
    Float: entranceAng[MAX_ENTRANCES],
    // Exit
    Float: exitX[MAX_ENTRANCES],
    Float: exitY[MAX_ENTRANCES],
    Float: exitZ[MAX_ENTRANCES],
    Float: exitAng[MAX_ENTRANCES],
    exitVirtualID[MAX_ENTRANCES],
    exitInteriorID[MAX_ENTRANCES],
    // Other
    Iterator: entranceID<MAX_ENTRANCES>,
    playerEnExCoolDown[MAX_PLAYERS],
    getShopName[MAX_PLAYERS][MAX_STORE_NAME],
    entranceFreezePlayer[MAX_ENTRANCES];

// Attach a map icon to assigned entranceid.
stock Entrance_SetIcon(id, iconid) {

    if(!Iter_Contains(entranceID, id)) {
        return 0;
    }

    CreateDynamicMapIcon(entranceX[id], entranceY[id], entranceZ[id], iconid, -1, .streamdistance = 200.0, .style = MAPICON_GLOBAL);
    return 1;
}

// Attach entrance name to assigned entranceid.
stock Entrance_SetName(id, const name[]) {

    if(!Iter_Contains(entranceID, id)){
        return 0;
    }

    if(isnull(name)) {
        printf("ERROR: Entrance Name is null.");
        return 0;
    }

    strcpy(entranceStoreName[id], name, MAX_STORE_NAME);
    return 1;
}

// Returns the entrance name that player is inside.
stock Entrance_PlayerIn(playerid) {
    return (!isnull(getShopName[playerid])) ? (getShopName[playerid]) : ("None");
}

stock Entrance_EnableFreeze(id, bool:status) {
    if(!Iter_Contains(entranceID, id)) {
        return 0;
    }

    entranceFreezePlayer[id] = status;
    return 1;
}
stock Entrance_FreeWorld() {
    return Iter_Free(entranceID);
}

//Create an entrance with exit on specificied coordinates.
stock Entrance_Create(
    Float:x,
    Float:y,
    Float:z,
    Float:ang,
    world,
    interior,
    Float:eX,
    Float:eY,
    Float:eZ,
    Float:eAng,
    eWorld = 0,
    eInterior = 0,
    Float:streamdistance = 200.0,
    Float:drawdistance = 200.0) {
    new
        idx = Iter_Alloc(entranceID),
        arr[2];

    arr[0] = ENEX_STREAMER_IDENTIFIER;
    arr[1] = idx;

    // Object
    EnExObject[idx] = CreateDynamicObject(19198, x, y, z, 0.0, 0.0, 0.0, world, interior, -1,streamdistance, drawdistance);

    Streamer_SetArrayData(STREAMER_TYPE_OBJECT, EnExObject[idx], E_STREAMER_EXTRA_ID, arr, sizeof(arr));

    MoveDynamicObject(EnExObject[idx], x, y, (z + 1.0), 1.0);

    // Area
    EnExArea[idx] = CreateDynamicCircle(x, y, 2.0, world, interior);

    Streamer_SetArrayData(STREAMER_TYPE_AREA, EnExArea[idx], E_STREAMER_EXTRA_ID, arr, sizeof(arr));

    // Setting data
    EnExObjectState[idx]            = ENTRANCE_UP;

    entranceX[idx]                  = x;
    entranceY[idx]                  = y;
    entranceZ[idx]                  = z;
    entranceAng[idx]                = ang;

    exitX[idx]                      = eX;
    exitY[idx]                      = eY;
    exitZ[idx]                      = eZ;
    exitAng[idx]                    = eAng;
    exitVirtualID[idx]              = eWorld;
    exitInteriorID[idx]             = eInterior;
    return idx;
}

// Returns unix timestamp of player last entered CP
stock Entrance_GetPlayerCD(playerid) {
    return (gettime() - playerEnExCoolDown[playerid]);
}

// Assign unix timestamp of player last entered CP
stock Entrance_UpdatePlayerCooldown(playerid, seconds = 2) {
    return playerEnExCoolDown[playerid] = (gettime() + seconds);
}

timer void:EntranceUnfreezePlayer[seconds](playerid, seconds) {
    #pragma unused seconds
    TogglePlayerControllable(playerid, true);
}

// Object Visual (Animation)
hook OnDynamicObjectMoved(objectid) {
    new
        arr[2];

    Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, arr, sizeof(arr));

    if(arr[0] == ENEX_STREAMER_IDENTIFIER) {
        new
            idx = arr[1];
        if(EnExObject[idx] == objectid) {
            new
                Float:x,
                Float:y,
                Float:z;
            if(EnExObjectState[idx] == ENTRANCE_UP) {
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, x);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, y);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, z);

                EnExObjectState[idx] = ENTRANCE_DOWN;
                MoveDynamicObject(objectid, x, y, (z - 1), 1.0);
            }
            else {
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, x);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, y);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, z);

                EnExObjectState[idx] = ENTRANCE_UP;
                MoveDynamicObject(objectid, x, y, (z + 1), 1.0);
            }
        }
    }
    return 1;
}

// Handler
hook OnPlayerEnterDynArea(playerid, areaid) {
    if (Entrance_GetPlayerCD(playerid) <= 2) {
        return 1;
    }

    if(IsPlayerInAnyVehicle(playerid)) {
        return 1;
    }

    new
        arr[2];

    Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, arr);

    if (arr[0] == ENEX_STREAMER_IDENTIFIER) {
        new
            idx = arr[1];

        if (areaid == EnExArea[idx]) {

            if(entranceFreezePlayer[idx]) {
                TogglePlayerControllable(playerid, false);
                defer EntranceUnfreezePlayer(playerid, 2000 + GetPlayerPing(playerid));
            }

            SetPlayerInterior(playerid, exitInteriorID[idx]);
            SetPlayerVirtualWorld(playerid, exitVirtualID[idx]);

            SetPlayerPos(playerid, exitX[idx], exitY[idx], exitZ[idx]);
            SetPlayerFacingAngle(playerid, exitAng[idx]);

            strcpy(getShopName[playerid], entranceStoreName[idx], MAX_STORE_NAME);

            Entrance_UpdatePlayerCooldown(playerid);
        }
    }
    return 1;
}
