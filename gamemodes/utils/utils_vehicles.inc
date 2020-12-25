#include <YSI_Coding\y_hooks>

static gPlayerLastVehicle[MAX_PLAYERS];

forward OnPlayerEnteredVehicle(playerid, vehicleid, ispassenger);

stock LoadStaticVehiclesFromFile(const filename[])
{
    new
        line[55],
        File:file_ptr,
        vehicletype,
        Float:SpawnX,
        Float:SpawnY,
        Float:SpawnZ,
        Float:SpawnRot,
        col1,
        col2,
        vehicles_loaded;

    file_ptr = fopen(filename, filemode:io_read);

    if (!file_ptr) return 0;

    vehicles_loaded = 0;

    while(fread(file_ptr, line, sizeof(line)) > 0)
    {
        sscanf(line, "p<,>iffffii", vehicletype, SpawnX, SpawnY, SpawnZ, SpawnRot, col1, col2);

        if (vehicletype < 400 || vehicletype > 611) {
            continue;
        }
        
        AddStaticVehicleEx(vehicletype, SpawnX, SpawnY, SpawnZ, SpawnRot, col1, col2, (60*60)); // respawn 60 minutes
        vehicles_loaded ++;
    }
    fclose(file_ptr);
    printf("Loaded %d vehicles from: %s", vehicles_loaded, filename);
    return vehicles_loaded;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
    {
        new vehid = GetPlayerVehicleID(playerid);
        CallLocalFunction("OnPlayerEnteredVehicle", "ddd", playerid, vehid, 0);
    } else if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_PASSENGER) {
        new vehid = GetPlayerVehicleID(playerid);
        CallLocalFunction("OnPlayerEnteredVehicle", "ddd", playerid, vehid, 1);
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    gPlayerLastVehicle[playerid] = INVALID_PLAYER_ID;
    return 1;
}

public OnPlayerEnteredVehicle(playerid, vehicleid, ispassenger)
{
    gPlayerLastVehicle[playerid] = vehicleid;
    return 1;
}

stock Player_GetLastVehicle(playerid) return gPlayerLastVehicle[playerid];