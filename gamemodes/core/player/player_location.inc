#include <map-zones>
#include <YSI_Coding\y_hooks>

static
    MapZone:PlayerLastZoneID[MAX_PLAYERS] = INVALID_MAP_ZONE_ID,
    MapZone:PlayerInteriorZoneID[MAX_PLAYERS] = INVALID_MAP_ZONE_ID;


stock Player_GetLocation(playerid, string[], len = sizeof(string)) {

    new
        MapZone: zoneid = GetPlayerMapZone(playerid),
        location[MAX_MAP_ZONE_NAME + 12];

    if(GetPlayerInterior(playerid) > 0) {
        zoneid = PlayerInteriorZoneID[playerid];
    }

    GetMapZoneName(zoneid, location);

    strcpy(string, location, len);
    return 1;
}

hook OnPlayerSecondUpdate(playerid) {
    new
        MapZone:zoneID = GetPlayerMapZone(playerid);

    // only update if last zone id is not the same as current ID.
    if(PlayerLastZoneID[playerid] != zoneID) {
        new
            zoneName[MAX_MAP_ZONE_NAME];
        Player_GetLocation(playerid, zoneName);
        UI_SetLocation(playerid, zoneName);
        PlayerLastZoneID[playerid] = zoneID;
    }
    return 1;
}

hook OnPlayerConnect(playerid) {

    PlayerInteriorZoneID[playerid] = INVALID_MAP_ZONE_ID;
    PlayerInteriorZoneID[playerid] = INVALID_MAP_ZONE_ID;
    return 1;
}

hook OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
    if(oldinteriorid != newinteriorid) {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        PlayerInteriorZoneID[playerid] = GetMapZoneAtPoint2D(x, y);
    }
    return 1;
}
