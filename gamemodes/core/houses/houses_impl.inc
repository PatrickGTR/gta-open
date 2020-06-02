#include <streamer>
#include <YSI_Data\y_iterate>

#define MAX_HOUSES              (100)
#define MAX_HOUSES_PER_PLAYER   (3)
#define MAX_HOUSE_DESCRIPTION   (24)
#define INVALID_HOUSE_ID        (-1)

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
stock House_Create(Float:x, Float:y, Float:z, Float:a, vworld, price, interior)
{
    new
        arr[2],
        string[128 + MAX_PLAYER_NAME + MAX_HOUSE_DESCRIPTION];

    new houseid = Iter_Free(HouseIndex);

    if(houseid == ITER_NONE) {
        return -1;
    }

    format(string, sizeof(string),
        "HouseID: "C_WHITE"%i\n\
        "C_ORANGE"Description: "C_WHITE"%s\n\
        "C_ORANGE"Owner: "C_WHITE"%s\n\
        "C_ORANGE"Price: "C_WHITE"%i",
        houseid,
        "For Sale!",
        "None",
        price);

    HouseEntranceLabel[houseid] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, x, y, z, 25.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 25.0);
    HouseEntranceCP[houseid] = CreateDynamicCP(x, y, z, 1.0, -1, -1, -1, 25.0);
    
    new
        Float:ex,
        Float:ey,
        Float:ez,
        intid,
        bool:unused;

    House_GetInteriorData(interior, ex, ey, ez, intid, unused, unused);
    HouseExitLabel[houseid] = CreateDynamic3DTextLabel("Exit", COLOR_ORANGE, ex, ey, ez, 25.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vworld, intid, -1, 25.0);
    HouseExitCP[houseid] = CreateDynamicCP(ex, ey, ez, 1.0, vworld, intid, -1, 25.0);


    arr[0] = HOUSES_STREAMER_IDENTIFIER;
    arr[1] = houseid;

    Streamer_SetArrayData(STREAMER_TYPE_CP, HouseEntranceCP[houseid], E_STREAMER_EXTRA_ID, arr);
    Streamer_SetArrayData(STREAMER_TYPE_CP, HouseExitCP[houseid], E_STREAMER_EXTRA_ID, arr);

    HouseID[houseid]            = houseid;
    HouseOwnerID[houseid]       = INVALID_HOUSE_ID;
    HouseDescription[houseid]   = "For Sale";
    HousePrice[houseid]         = price;
    HouseInterior[houseid]      = interior;

    HouseEntranceX[houseid]     = x;
    HouseEntranceY[houseid]     = y;
    HouseEntranceZ[houseid]     = z;
    HouseEntranceA[houseid]     = a;
    HouseVWorld[houseid]        = vworld;
    HouseInteriorID[houseid]    = intid;
    Iter_Add(HouseIndex, houseid);

    return houseid;
}

House_Buy(playerid, houseid) {


    HouseOwnerID[houseid] = Player_GetAccountID(playerid);

    new 
        string[128 + MAX_PLAYER_NAME + MAX_HOUSE_DESCRIPTION],
        name[MAX_PLAYER_NAME];

    GetPlayerName(playerid, name, sizeof(name));

    // set new description
    // SOLD TO PatrickGTR!
    HouseDescription[houseid][0] = EOS;
    strcat(HouseDescription[houseid], "SOLD TO");
    strcat(HouseDescription[houseid], " ");
    strcat(HouseDescription[houseid], name);

    // set new ownerid.
    HouseOwnerID[houseid] = Player_GetAccountID(playerid);


    format(string, sizeof(string),
        "HouseID: "C_WHITE"%i\n\
        "C_ORANGE"Description: "C_WHITE"%s!\n\
        "C_ORANGE"Owner: "C_WHITE"%s\n\
        "C_ORANGE"Price: "C_GREEN"$%i",
        HouseID[houseid], 
        HouseDescription[houseid],
        name,
        HousePrice[houseid]
    );

    UpdateDynamic3DTextLabelText(HouseEntranceLabel[houseid], COLOR_ORANGE, string);
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

stock House_HasOwner(houseid) {
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

stock House_PlayerIsOwner(playerid, houseid) {
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