#include <YSI_Coding\y_hooks>

#define INVALID_ATM_ID (-1)

#define ATM_LABEL_INFO "%s's ATM\n"C_YELLOW"Press "C_GREEN"'~k~~CONVERSATION_YES~' "C_YELLOW"to interact"

// Prepared Statements
static
    Statement: stmt_InsertATM,
    Statement: stmt_RemoveATM,
    Statement: stmt_LoadATM,
    Statement: stmt_UpdateATM;

// ATM
static
    Iterator:ATMIndex<MAX_ATMS>,
    ATM_ObjectID[MAX_ATMS],
    Text3D:ATM_Label[MAX_ATMS],
    ATM_ID[MAX_ATMS],
    Float: ATM_X[MAX_ATMS],
    Float: ATM_Y[MAX_ATMS],
    Float: ATM_Z[MAX_ATMS],
    Float: ATM_RX[MAX_ATMS],
    Float: ATM_RY[MAX_ATMS],
    Float: ATM_RZ[MAX_ATMS],
    ATM_World[MAX_ATMS],
    ATM_Interior[MAX_ATMS],
    bool:ATM_Disabled[MAX_ATMS] = {false, ...};
// ATM Editing State
static
    PlayerEditingATM[MAX_PLAYERS] = INVALID_ATM_ID,
    bool:PlayerIsEditingATM[MAX_PLAYERS] = false;

hook OnPlayerConnect(playerid) {
    PlayerEditingATM[playerid] = INVALID_ATM_ID;
    PlayerIsEditingATM[playerid] = false;
    return 1;
}

hook OnMySQLConnected() {
	static const insertQuery[] = "\
	INSERT INTO \
		atms (atm_x, atm_y, atm_z, wid, interior) \
	VALUES \
		(?, ?, ?, ?, ?) \
	";
	stmt_InsertATM = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const
        deleteQuery[] = "DELETE FROM atms WHERE atm_id = ?";
    stmt_RemoveATM = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);

    static const loadQuery[] = "\
        SELECT \
            atm_id, \
            atm_x, \
            atm_y, \
            atm_z, \
            rx, \
            ry, \
            rz, \
            wid, \
            interior \
        FROM \
            atms \
    ";
	stmt_LoadATM = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const updateQuery[] = "\
    UPDATE \
        atms \
    SET \
        atm_x = ?, \
        atm_y = ?, \
        atm_z = ?, \
        rx = ?, \
        ry = ?, \
        rz = ?, \
        wid = ?, \
        interior = ? \
    WHERE \
        atm_id = ?";

    stmt_UpdateATM = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);

    ATM_Load();
    return 1;
}

hook OnPlayerEditDynObj(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    new
        Float:oldX,
        Float:oldY,
        Float:oldZ,
        Float:oldRotX,
        Float:oldRotY,
        Float:oldRotZ;

	GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

    if(response == EDIT_RESPONSE_FINAL && PlayerIsEditingATM[playerid]) {
        ATM_Update(PlayerEditingATM[playerid], x, y, z, rx, ry, rz, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        PlayerIsEditingATM[playerid] = false;
    }

    if(response == EDIT_RESPONSE_CANCEL) {
        if(PlayerIsEditingATM[playerid]) {
            PlayerIsEditingATM[playerid] = false;
        }

        SetObjectPos(objectid, oldX, oldY, oldZ);
		SetObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
    }
    return 1;
}


// getters


// returns
// INVALID_ATM_ID if player is close to none.
// returns the ATM ID on success.
stock ATM_GetObjectID(atmID) {
    new
        idx = ATM_FindIndexIDBySQLID(atmID);

    if(idx == INVALID_ATM_ID) {
        return INVALID_ATM_ID;
    }

    return ATM_ObjectID[idx];
}

// returns
// INVALID_ATM_ID if player is close to none.
// returns the ATM ID on success.
stock ATM_GetClosest(playerid, Float:lowestdistance = 5000.0) {
    new
        Float:x,
        Float:y,
        Float:z,
        Float:plyX,
        Float:plyY,
        Float:plyZ,
        Float:distance = 5.0,
        closestATM = -1;

    foreach(new i : ATMIndex) {
        x = ATM_X[i],
        y = ATM_Y[i],
        z = ATM_Z[i];

        GetPlayerPos(playerid, plyX, plyY, plyZ);

        distance = Distance(plyX, plyY, plyZ, x, y, z);

        if (distance < lowestdistance) {
            lowestdistance = distance;
            closestATM = ATM_ID[i];
        }
    }
    return closestATM;
}

// returns
// true -> player is within range of ATM.
// false -> player not close to any ATM.
stock bool:Player_IsNearATM(playerid) {
    foreach(new i : ATMIndex) {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, ATM_X[i], ATM_Y[i], ATM_Z[i])) {
            return true;
        }
    }
    return false;
}

// getters end

// no returns
stock void:ATM_Load() {

    inline const OnATMLoad() {
        new
            atmID,
            Float:x,
            Float:y,
            Float:z,
            Float:rx,
            Float:ry,
            Float:rz,
            world,
            interior;

        MySQL_BindResultInt(stmt_LoadATM, 0, atmID);
        MySQL_BindResultFloat(stmt_LoadATM, 1, x);
        MySQL_BindResultFloat(stmt_LoadATM, 2, y);
        MySQL_BindResultFloat(stmt_LoadATM, 3, z);

        MySQL_BindResultFloat(stmt_LoadATM, 4, rx);
        MySQL_BindResultFloat(stmt_LoadATM, 5, ry);
        MySQL_BindResultFloat(stmt_LoadATM, 6, rz);

        MySQL_BindResultInt(stmt_LoadATM, 7, world);
        MySQL_BindResultInt(stmt_LoadATM, 8, interior);

        new
            idx;

        // Thanks to Lorenc for this ATM position.
        idx = Internal_ATM_Create(2234.733398, 51.345561000, 26.134365, 0.0, 0.0, 0.000000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(1381.069213, 259.56204200, 19.156929, 0.0, 0.0, 157.0000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(661.3598020, -555.1714470, 15.965932, 0.0, 0.0, -90.0000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(-2177.50292, -2435.006591, 30.214990, 0.0, 0.0, 52.00000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(1367.251464, -1284.611938, 13.156874, 0.0, 0.0, -90.6000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(1928.592651, -1771.088012, 13.172806, 0.0, 0.0, 90.00000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(2323.767333, -1644.993896, 14.442724, 0.0, 0.0, 0.000000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(2043.748779, -1416.704711, 16.810766, 0.0, 0.0, -90.0000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(2387.751464, -1981.961669, 13.156866, 0.0, 0.0, -180.000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(1494.450195, -1768.979492, 18.365745, 0.0, 0.0, -90.0000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(1051.627075, -1026.406616, 31.661567, 0.0, 0.0, 0.000000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(816.8725580, -1356.521240, 13.156099, 0.0, 0.0, -180.000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(1808.732177, -1567.267822, 13.063967, 0.0, 0.0, 37.00000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(2412.541259, -1492.666992, 23.628126, 0.0, 0.0, -180.000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(2431.131347, -1219.477539, 25.022165, 0.0, 0.0, 0.000000);
        ATM_UpdateLabel(idx);
        idx = Internal_ATM_Create(255.4551690, -197.5846250, 1.2381240, 0.0, 0.0, -90.0000);
        ATM_UpdateLabel(idx);

        while(MySQL_Statement_FetchRow(stmt_LoadATM)) {
            idx = Internal_ATM_Create(x, y, z, rx, ry, rz, world, interior);
            ATM_ID[idx] = atmID;
            ATM_UpdateLabel(idx);

            Logger_Dbg("server-atm", "[OnMySQLConnected / server_atm.inc] atm loaded",
                Logger_I("atm id", atmID),
                Logger_F("x", x),
                Logger_F("y", y),
                Logger_F("z", z),
                Logger_F("rx", rx),
                Logger_F("ry", ry),
                Logger_F("rz", rz),
                Logger_I("world", world),
                Logger_I("interior", interior)
            );
        }
    }
    MySQL_ExecuteThreaded_Inline(stmt_LoadATM, using inline OnATMLoad);
}

void:ATM_UpdateLabel(atmIndex, colour = COLOR_YELLOW, const label[] = ATM_LABEL_INFO) {
    // Delete the current atm if one already exists in this index.
    if(ATM_Label[atmIndex] != INVALID_3DTEXT_ID) {
        DestroyDynamic3DTextLabel(ATM_Label[atmIndex]);
    }

    new
        string[64 + MAX_MAP_ZONE_NAME + 11];

    new
        MapZone:zoneID = GetMapZoneAtPoint(ATM_X[atmIndex], ATM_Y[atmIndex], ATM_Z[atmIndex]),
        zoneName[MAX_MAP_ZONE_NAME];
    GetMapZoneName(zoneID, zoneName, sizeof(zoneName));

    formatex(string, sizeof(string), label, zoneName);
    ATM_Label[atmIndex] = CreateDynamic3DTextLabel(string,
        colour,
        ATM_X[atmIndex],
        ATM_Y[atmIndex],
        ATM_Z[atmIndex] + 1.5,
        100.0,
        .worldid = ATM_World[atmIndex],
        .interiorid = ATM_Interior[atmIndex],
        .testlos = 1);
}

// returns
// 0 -> if atmID provided is invalid.
// 1 -> if atmID is valid, proceed deletion.
stock ATM_Delete(atmID) {

    new
        idx = INVALID_ATM_ID,
        bool:found = false;
    // finding the index based on ATM MYSQL ID.
    foreach(new i : ATMIndex) {
        if(ATM_ID[i] == atmID) {
            idx = i;
            found = true;
            break;
        }
    }

    if(!found) {
        return 0;
    }

    // remove from database.
    MySQL_BindInt(stmt_RemoveATM, 0, atmID);
    MySQL_ExecuteThreaded(stmt_RemoveATM);

    // reset data.
    DestroyDynamicObject(ATM_ObjectID[idx]);
    DestroyDynamic3DTextLabel(ATM_Label[idx]);


    ATM_ID[idx] = INVALID_ATM_ID;
    ATM_X[idx] =
    ATM_Y[idx] =
    ATM_Z[idx] =
    ATM_RX[idx] =
    ATM_RY[idx] =
    ATM_RZ[idx] = 0.0;
    ATM_World[idx] =
    ATM_Interior[idx] = 0;
    ATM_Disabled[idx] = false;
    Iter_Remove(ATMIndex, idx);

    Logger_Dbg(
        "server-atm",
        "[ATM_Delete / server_atm.inc] atm deleted",
        Logger_I("atm id", atmID)
    );
    return 1;
}

// returns
// INVALID_ATM_ID = no sqlID found.
// returns index of sqlID if found.
stock ATM_FindIndexIDBySQLID(sqlID) {
    new
        idx = INVALID_ATM_ID;
    foreach(idx : ATMIndex) {
        if(ATM_ID[idx] == sqlID) {
            return idx;
        }
    }
    return INVALID_ATM_ID;
}

// returns
// 0 -> atmIndex == invalid
// -1 -> atmID == invalid
// 1 -> success
stock ATM_Edit(playerid, atmIndex) {
    if(atmIndex == INVALID_ATM_ID) {
        return 0;
    }

    EditDynamicObject(playerid, ATM_ObjectID[atmIndex]);
    PlayerEditingATM[playerid] = ATM_ID[atmIndex];
    PlayerIsEditingATM[playerid] =  true;
    return 1;
}

// no returns
stock void:ATM_Update(atmID,
    Float: x,
    Float: y,
    Float: z,
    Float: rx,
    Float: ry,
    Float: rz,
    world,
    interior
) {

    new
        idx = ATM_FindIndexIDBySQLID(atmID);

    // update data
    DestroyDynamicObject(ATM_ObjectID[idx]);
    // ATM_ObjectID[idx] = CreateDynamicObject(19324, x, y, z, rx, ry, rz, world, interior, -1, 300.0);

    ATM_X[idx] = x;
    ATM_Y[idx] = y;
    ATM_Z[idx] = z;
    ATM_RX[idx] = rx;
    ATM_RY[idx] = ry;
    ATM_RZ[idx] = rz;
    ATM_World[idx] = world;
    ATM_Interior[idx] = interior;

    ATM_UpdateLabel(idx);

   // update database
    MySQL_BindFloat(stmt_UpdateATM, 0, x);
    MySQL_BindFloat(stmt_UpdateATM, 1, y);
    MySQL_BindFloat(stmt_UpdateATM, 2, z);
    MySQL_BindFloat(stmt_UpdateATM, 3, rx);
    MySQL_BindFloat(stmt_UpdateATM, 4, ry);
    MySQL_BindFloat(stmt_UpdateATM, 5, rz);
    MySQL_BindInt(stmt_UpdateATM, 6, world);
    MySQL_BindInt(stmt_UpdateATM, 7, interior);
    MySQL_BindInt(stmt_UpdateATM, 8, atmID);
    MySQL_ExecuteThreaded(stmt_UpdateATM);

    Logger_Dbg("server-atm", "[ATM_Update / server_atm.inc] atm edited",
        Logger_I("atm id", atmID),
        Logger_F("x", x),
        Logger_F("y", y),
        Logger_F("z", z),
        Logger_F("rx", rx),
        Logger_F("ry", ry),
        Logger_F("rz", rz),
        Logger_I("world", world),
        Logger_I("interior", interior)
    );
}

static Internal_ATM_Create(Float: x, Float: y, Float: z, Float:rx, Float:ry, Float:rz, world = 0, interior = 0) {

    new
        idx = Iter_Alloc(ATMIndex);

    if(idx == ITER_NONE) {
        Logger_Dbg("server-atm", "[ATM_Create / server_atm.inc] MAX_ATM limit reached.");
        return -1;
    }

    //ATM_ID[idx]         = id;
    ATM_X[idx]          = x;
    ATM_Y[idx]          = y;
    ATM_Z[idx]          = z;
    ATM_RX[idx]         = rx;
    ATM_RY[idx]         = ry;
    ATM_RZ[idx]         = rz;
    ATM_World[idx]      = world;
    ATM_Interior[idx]   = interior;
    ATM_Disabled[idx]   = false;

    ATM_ObjectID[idx]   = CreateDynamicObject(19324, x, y, z, 0.0, 0.0, rz, world, interior, -1, 300.0);
    ATM_Label[idx]      = CreateDynamic3DTextLabel("Creation in progress...", COLOR_YELLOW, x, y, z + 1.5, 300.0, .worldid = world, .interiorid = interior);

    Iter_Add(ATMIndex, idx);

    Logger_Dbg(
        "server-atm",
        "[ATM_Create / server_atm.inc] atm created",
        // Logger_I("atm id", id),
        Logger_F("x", x),
        Logger_F("y", y),
        Logger_F("z", z),
        Logger_I("world", world),
        Logger_I("interior", interior)
    );
    return idx;
}

// returns
// -1 -> all slots used
// if success, function returns the new id found.
stock ATM_Create(Float: x, Float: y, Float: z, Float:ang, world, interior) {

    new
        idx = Internal_ATM_Create(Float: x, Float: y, Float: z, 0.0, 0.0, Float:ang, world, interior);

    // finding new id.
    inline const OnATMCreated() {
        // assign data.
        new
            id = cache_insert_id();

        ATM_ID[idx] = id;
    }

    // Insert data to database.
    MySQL_BindFloat(stmt_InsertATM, 0, x);
    MySQL_BindFloat(stmt_InsertATM, 1, y);
    MySQL_BindFloat(stmt_InsertATM, 2, z);
    MySQL_BindInt(stmt_InsertATM, 3, world);
    MySQL_BindInt(stmt_InsertATM, 4, interior);
    MySQL_ExecuteParallel_Inline(stmt_InsertATM, using inline OnATMCreated);
    return idx;
}

ATM_State(idx, bool: disable) {
    ATM_Disabled[idx] = disable;
}

ATM_GetState(idx) {
    return ATM_Disabled[idx];
}
