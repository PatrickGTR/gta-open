#include <YSI_Coding\y_hooks>

#define MAX_HOUSES              (100)
#define MAX_HOUSES_PER_PLAYER   (1)
#define MAX_HOUSE_DESCRIPTION   (24)
#define INVALID_HOUSE_ID        (-1)

static
    Statement: stmt_InsertHouse,
    Statement: stmt_LoadHouse,
    Statement: stmt_updateDescription,
    Statement: stmt_houseExists,
    Statement: stmt_removeHouse,
    Statement: stmt_updateOwner;

hook OnMySQLConnected() {

    static const insertQuery[] = "\
    INSERT INTO \
        player_houses (house_id, u_id, interior, description, price, \
        money_stored, entrance_x, entrance_y, entrance_z, entrance_a, \
        virtual_world, interior_id) \
    VALUES \
        (?,NULL,?,?,?,?,?,?,?,?,?,?) \
    ";
    stmt_InsertHouse = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = "\
    SELECT \
        h.house_id, \
        IFNULL(h.u_id, -1) AS u_id, \
        h.description, \
        h.price, \
        h.money_stored, \
        h.interior, \
        h.entrance_x, \
        h.entrance_y, \
        h.entrance_z, \
        h.entrance_a, \
        h.interior_id, \
        IFNULL(p.username, 'None') as username \
    FROM \
        player_houses as h \
    LEFT JOIN \
        players as p \
    ON \
        h.u_id = p.u_id \
    ";
    stmt_LoadHouse = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const updateDescriptionQuery[] = "\
    UPDATE \
        player_houses \
    SET \
        description = ? \
    WHERE \
        house_id = ? AND u_id = ? \
    ";

    stmt_updateDescription = MySQL_PrepareStatement(MySQL_GetHandle(), updateDescriptionQuery);

    static const checkQuery[] = "\
    SELECT \
        house_id \
    FROM \
        player_houses \
    WHERE \
        house_id = ? \
    ";
    stmt_houseExists = MySQL_PrepareStatement(MySQL_GetHandle(), checkQuery);

    static const deleteQuery[] = "\
    DELETE FROM \
        player_houses \
    WHERE \
        house_id = ? \
    ";
    stmt_removeHouse = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);

    static const updateOwnerQuery[] = "\
    UPDATE \
        player_houses \
    SET \
        u_id = ? \
    WHERE \
        house_id = ? \
    ";
    stmt_updateOwner = MySQL_PrepareStatement(MySQL_GetHandle(), updateOwnerQuery);
    return 1;
}

static
    Iterator:HouseIndex<MAX_HOUSES>,
    Text3D:HouseEntranceLabel[MAX_HOUSES],
    Text3D:HouseExitLabel[MAX_HOUSES],
    HouseEntranceCP[MAX_HOUSES],
    HouseExitCP[MAX_HOUSES],
    HouseID[MAX_HOUSES],
    HouseOwnerID[MAX_HOUSES],
    HousePrice[MAX_HOUSES],
    HouseInterior[MAX_HOUSES],
    HouseDescription[MAX_HOUSES][MAX_HOUSE_DESCRIPTION],
    Float:HouseEntranceX[MAX_HOUSES],
    Float:HouseEntranceY[MAX_HOUSES],
    Float:HouseEntranceZ[MAX_HOUSES],
    Float:HouseEntranceA[MAX_HOUSES],
    HouseVWorld[MAX_HOUSES],
    HouseInteriorID[MAX_HOUSES];


// !! PLEASE NOTE !!
// Interior -> The actual mapping interior of the house.
// InteriorID -> Used to set the player's interior depending on ID.
// this function returns
// -1 if there are no slots left.
// new house id on success
stock House_Create(Float:x, Float:y, Float:z, Float:a, price, interior, description[MAX_HOUSE_DESCRIPTION] = "", ownerName[MAX_PLAYER_NAME] = "", ownerID = -1, bool:save = false)
{
    new
        houseid = Iter_Alloc(HouseIndex);

    if(houseid == ITER_NONE) {
        return -1;
    }

    new
        string[128 + MAX_PLAYER_NAME + MAX_HOUSE_DESCRIPTION + MAX_MAP_ZONE_NAME];

    description = (isnull(description) ? ("For Sale!") : (description));
    ownerName = (isnull(ownerName) ? ("None") : (ownerName));

    new
        MapZone:zoneID = GetMapZoneAtPoint(x, y, z),
        zoneName[MAX_MAP_ZONE_NAME];

    GetMapZoneName(zoneID, zoneName);

    format(string, sizeof(string),
        "%i "C_WHITE"%s\n\
        "C_ORANGE"Description: "C_WHITE"%s\n\
        "C_ORANGE"Owner: "C_WHITE"%s\n\
        "C_ORANGE"Price: "C_GREEN"$%i",
        houseid,
        zoneName,
        description,
        ownerName,
        price);


    HouseEntranceLabel[houseid] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, x, y, z, 25.0, .worldid = -1, .streamdistance = 25.0);
    HouseEntranceCP[houseid] = CreateDynamicCP(x, y, z, 1.0, -1, -1, -1, 25.0);

    new
        Float:ex,
        Float:ey,
        Float:ez,
        intid,
        bool:unused;


    // use houseid as a unique virtual world for
    new
        world = houseid;

    House_GetInteriorData(interior, ex, ey, ez, intid, unused, unused);
    HouseExitLabel[houseid] = CreateDynamic3DTextLabel("Exit", COLOR_ORANGE, ex, ey, ez, 25.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, world, intid, -1, 25.0);
    HouseExitCP[houseid] = CreateDynamicCP(ex, ey, ez, 1.0, world, intid, -1, 25.0);

    new
        arr[2];

    arr[0] = HOUSES_STREAMER_IDENTIFIER;
    arr[1] = houseid;

    Streamer_SetArrayData(STREAMER_TYPE_CP, HouseEntranceCP[houseid], E_STREAMER_EXTRA_ID, arr);
    Streamer_SetArrayData(STREAMER_TYPE_CP, HouseExitCP[houseid], E_STREAMER_EXTRA_ID, arr);

    HouseID[houseid]            = houseid;
    HouseOwnerID[houseid]       = ownerID;
    HouseDescription[houseid]   = description;
    HousePrice[houseid]         = price;
    HouseInterior[houseid]      = interior;

    HouseEntranceX[houseid]     = x;
    HouseEntranceY[houseid]     = y;
    HouseEntranceZ[houseid]     = z;
    HouseEntranceA[houseid]     = a;
    HouseVWorld[houseid]        = world;
    HouseInteriorID[houseid]    = intid;
    Iter_Add(HouseIndex, houseid);

    if(save) {
        House_InsertToDatabase(houseid);
    }
    return houseid;
}

House_Delete(playerid, houseid) {
    inline OnHouseRemove()
    {
        if (MySQL_Statement_FetchRow(stmt_houseExists))
        {
            MySQL_BindInt(stmt_removeHouse, 0, houseid);
            MySQL_ExecuteThreaded(stmt_removeHouse);

            if (playerid != INVALID_PLAYER_ID)
            {
                SendServerMsgF(playerid, "You successfully deleted house id "C_GREY"%i", houseid);
            }

            Streamer_RemoveArrayData(STREAMER_TYPE_CP, HouseEntranceCP[houseid], E_STREAMER_EXTRA_ID, houseid);
            Streamer_RemoveArrayData(STREAMER_TYPE_CP, HouseExitCP[houseid], E_STREAMER_EXTRA_ID, houseid);

            DestroyDynamicCP(HouseEntranceCP[houseid]);
            DestroyDynamicCP(HouseExitCP[houseid]);
            DestroyDynamic3DTextLabel(HouseEntranceLabel[houseid]);
            DestroyDynamic3DTextLabel(HouseExitLabel[houseid]);
            HouseOwnerID[houseid] = -1;

            Iter_Remove(HouseIndex, houseid);
        }
        else
        {
            if (playerid != INVALID_PLAYER_ID)
            {
                SendErrorMsgF(playerid, "The house "C_GREY"(ID:%i) "C_WHITE"you are trying to delete was not found in the database.", houseid);
            }
        }
    }
    MySQL_BindInt(stmt_houseExists, 0, houseid);
    MySQL_ExecuteThreaded_Inline(stmt_houseExists, using inline OnHouseRemove);
}

stock House_InsertToDatabase(houseid) {
    MySQL_BindInt(stmt_InsertHouse, 0, houseid);
    MySQL_BindInt(stmt_InsertHouse, 1, HouseInterior[houseid]);
    MySQL_Bind(stmt_InsertHouse, 2, HouseDescription[houseid]);
    MySQL_BindInt(stmt_InsertHouse, 3, HousePrice[houseid]);
    MySQL_BindInt(stmt_InsertHouse, 4, 0);
    MySQL_BindFloat(stmt_InsertHouse, 5, HouseEntranceX[houseid]);
    MySQL_BindFloat(stmt_InsertHouse, 6, HouseEntranceY[houseid]);
    MySQL_BindFloat(stmt_InsertHouse, 7, HouseEntranceZ[houseid]);
    MySQL_BindFloat(stmt_InsertHouse, 8, HouseEntranceA[houseid]);
    MySQL_BindInt(stmt_InsertHouse, 9, HouseVWorld[houseid]);
    MySQL_BindInt(stmt_InsertHouse, 10, HouseInteriorID[houseid]);
    MySQL_ExecuteThreaded(stmt_InsertHouse);
}

// Change the owner ID to the buyer
// Change the description to 'SOLD TO BuyerName!'
// returns N/A
stock House_Buy(playerid, houseid) {
    new
        description[MAX_PLAYER_NAME + MAX_HOUSE_DESCRIPTION],
        name[MAX_PLAYER_NAME];

    GetPlayerName(playerid, name, sizeof(name));

    // set new description
    // e.g SOLD TO PatrickGTR!
    strcat(description, "SOLD TO");
    strcat(description, " ");
    strcat(description, name);
    strcat(description, "!");

    // set new ownerid.
    HouseOwnerID[houseid] = Player_GetAccountID(playerid);

    // Update Description
    House_UpdateDescription(playerid, houseid, description);

    MySQL_BindInt(stmt_updateOwner, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_updateOwner, 1, houseid);
    MySQL_ExecuteThreaded(stmt_updateOwner);
}

// Updates the house description specified by the owner.
// returns
// 1 on success
// 0 if description is more than MAX_HOUSE_DESCRIPTION
// -1 if invalid houseid.

House_UpdateDescription(playerid, houseid, const description[]) {

    if(strlen(description) > MAX_HOUSE_DESCRIPTION) {
        return 0;
    }

    if(!(0 <= houseid < MAX_HOUSES)) {
        return -1;
    }

    new
        string[128 + MAX_PLAYER_NAME + MAX_HOUSE_DESCRIPTION];

    strcpy(HouseDescription[houseid], description);

    new
        MapZone:zoneID = GetMapZoneAtPoint(HouseEntranceX[houseid], HouseEntranceY[houseid], HouseEntranceZ[houseid]),
        zoneName[MAX_MAP_ZONE_NAME];

    GetMapZoneName(zoneID, zoneName);

    format(string, sizeof(string),
        "%i "C_WHITE"%s\n\
        "C_ORANGE"Description: "C_WHITE"%s\n\
        "C_ORANGE"Owner: "C_WHITE"%s\n\
        "C_ORANGE"Price: "C_GREEN"$%i",
        HouseID[houseid],
        zoneName,
        HouseDescription[houseid],
        ReturnPlayerName(playerid),
        HousePrice[houseid]
    );
    UpdateDynamic3DTextLabelText(HouseEntranceLabel[houseid], COLOR_ORANGE, string);

    MySQL_Bind(stmt_updateDescription, 0, HouseDescription[houseid]);
    MySQL_BindInt(stmt_updateDescription, 1, houseid);
    MySQL_BindInt(stmt_updateDescription, 2, HouseOwnerID[houseid]);
    MySQL_ExecuteThreaded(stmt_updateDescription);
    return 1;
}

House_Load() {

    inline const OnHouseLoad() {
        new
            houseid,
            ownerID,
            description[MAX_HOUSE_DESCRIPTION],
            price,
            money_stored,
            interior,
            Float:x,
            Float:y,
            Float:z,
            Float:a,
            intid,
            ownerName[MAX_PLAYER_NAME];

        MySQL_BindResultInt(stmt_LoadHouse, 0, houseid);
        MySQL_BindResultInt(stmt_LoadHouse, 1, ownerID);
        MySQL_BindResult(stmt_LoadHouse, 2, description);
        MySQL_BindResultInt(stmt_LoadHouse, 3, price);
        MySQL_BindResultInt(stmt_LoadHouse, 4, money_stored);
        MySQL_BindResultInt(stmt_LoadHouse, 5, interior);
        MySQL_BindResultFloat(stmt_LoadHouse, 6, x);
        MySQL_BindResultFloat(stmt_LoadHouse, 7, y);
        MySQL_BindResultFloat(stmt_LoadHouse, 8, z);
        MySQL_BindResultFloat(stmt_LoadHouse, 9, a);
        MySQL_BindResultInt(stmt_LoadHouse, 10, intid);
        MySQL_BindResult(stmt_LoadHouse, 11, ownerName);

        new
            benchHouse = GetTickCount(),
            count = 0;
        while(MySQL_Statement_FetchRow(stmt_LoadHouse)) {
            House_Create(x, y, z, a, price, interior, description, ownerName, ownerID);
            count ++;
        }
        Logger_Log(
            "House Loaded",
            Logger_I("total", count),
            Logger_I("took (ms)", GetTickCount() - benchHouse)
        );
    }

    MySQL_ExecuteThreaded_Inline(stmt_LoadHouse, using inline OnHouseLoad);
}

stock House_GetEntranceData(houseid, &Float:x, &Float:y, &Float:z, &Float:a) {
    x = HouseEntranceX[houseid];
    y = HouseEntranceY[houseid];
    z = HouseEntranceZ[houseid];
    a = HouseEntranceA[houseid];
    return 1;
}

stock House_GetEntranceCPHandler(houseid) {
    return HouseEntranceCP[houseid];
}

stock House_GetExitCPHandler(houseid) {
    return HouseExitCP[houseid];
}

stock bool:House_HasOwner(houseid) {
    return (HouseOwnerID[houseid] != INVALID_HOUSE_ID);
}

stock House_GetInterior(houseid) {
    return HouseInterior[houseid];
}

stock House_GetWorld(houseid) {
    return HouseVWorld[houseid];
}

stock House_GetPrice(houseid) {
    return HousePrice[houseid];
}

stock bool:House_PlayerIsOwner(playerid, houseid) {
    return (HouseOwnerID[houseid] == Player_GetAccountID(playerid));
}


// this function returns the value of how many
// houses are created in-game.
stock House_GetTotal() {
    return Iter_Count(HouseIndex);
}


stock Player_GetTotalHouses(playerid) {
    new
        count = 0;

    foreach(new i : HouseIndex) {
        if(HouseOwnerID[i] == Player_GetAccountID(playerid)) {
            count ++;
        }
        if(count == MAX_HOUSES_PER_PLAYER) {
            // stop the searching if player has reached
            // per player house limit.
            break;
        }
    }
    return count;
}
