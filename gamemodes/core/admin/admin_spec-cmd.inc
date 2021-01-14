#include <YSI_Coding\y_hooks>

static
    bool:gPlayerIsSpectating[MAX_PLAYERS],
    gSpectatingPlayer[MAX_PLAYERS],
    gPlayerLastInterior[MAX_PLAYERS],
    gPlayerLastWorld[MAX_PLAYERS],
    bool:gIsPlayerBeingSpectated[MAX_PLAYERS],
    Float:gPlayerLastPos[MAX_PLAYERS][3],
    Float:gPlayerArmour[MAX_PLAYERS],
    Float:gPlayerHealth[MAX_PLAYERS]
;

hook OnPlayerConnect(playerid)
{
    gPlayerIsSpectating[playerid] = false;
    gSpectatingPlayer[playerid] = INVALID_PLAYER_ID;
    gIsPlayerBeingSpectated[playerid] = false;
    gPlayerArmour[playerid] = 0.0;
    gPlayerHealth[playerid] = 0.0;
    return 1;
}

hook OnPlayerEnterEntrance(playerid) {
    if(gIsPlayerBeingSpectated[playerid])
    {
        foreach(new i : Player)
        {
            if(gPlayerIsSpectating[i] && gSpectatingPlayer[i] == playerid)
            {
                PlayerSpectatePlayer(i, playerid);
            }
        }
    }
    return 1;
}

ACMD:[1]specoff(playerid, params[])
{
    new spectators;
    if(!gPlayerIsSpectating[playerid]) return SendErrorMsg(playerid, "You're not spectating");
    foreach(new i : Player)
    {
        if(i == playerid) continue;
        if(gPlayerIsSpectating[i] && gSpectatingPlayer[i] == gSpectatingPlayer[playerid])
        {
            spectators++;
        }
    }
    if(spectators == 0)
    {
        gIsPlayerBeingSpectated[gSpectatingPlayer[playerid]] = false;
    }
    TogglePlayerSpectating(playerid, false);
    SpawnPlayer(playerid);

    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(gPlayerIsSpectating[playerid])
    {
        Weapon_Load(playerid);
        SetPlayerHealth(playerid, gPlayerHealth[playerid]);
        SetPlayerArmour(playerid, gPlayerArmour[playerid]);
        gPlayerIsSpectating[playerid] = false;
        SetPlayerPos(playerid, gPlayerLastPos[playerid][0], gPlayerLastPos[playerid][1], gPlayerLastPos[playerid][2]);
        SetPlayerInterior(playerid, gPlayerLastInterior[playerid]);
        SetPlayerVirtualWorld(playerid, gPlayerLastWorld[playerid]);
    }
    return 1;
}

ACMD:[1]spec(playerid, params[])
{
    new target;
    new Float:pos[3];
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/spec (name/id)");
    if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected!");
    GetPlayerHealth(playerid, gPlayerHealth[playerid]);
    GetPlayerArmour(playerid, gPlayerArmour[playerid]);
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    gPlayerLastPos[playerid][0] = pos[0];
    gPlayerLastPos[playerid][1] = pos[1];
    gPlayerLastPos[playerid][2] = pos[2];
    gPlayerLastInterior[playerid] = GetPlayerInterior(playerid);
    gPlayerLastWorld[playerid] = GetPlayerVirtualWorld(playerid);
    TogglePlayerSpectating(playerid, true);
    gPlayerIsSpectating[playerid] = true;
    gIsPlayerBeingSpectated[target] = true;
    gSpectatingPlayer[playerid] = target;
    if(IsPlayerInAnyVehicle(target))
    {
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(target));
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(target));
        SetPlayerInterior(playerid, GetPlayerInterior(target));
    }
    else
    {
        PlayerSpectatePlayer(playerid, target);
    }
    Weapon_Save(playerid);
    ResetPlayerWeapons(playerid);

    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(gIsPlayerBeingSpectated[playerid])
    {
        if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
        {
            foreach(new i : Player)
            {
                if(gPlayerIsSpectating[i] && gSpectatingPlayer[i] == playerid)
                {
                    PlayerSpectateVehicle(i, GetPlayerVehicleID(playerid));
                }
            }
        }
        else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
        {
            foreach(new i : Player)
            {
                if(gPlayerIsSpectating[i] && gSpectatingPlayer[i] == playerid)
                {
                    PlayerSpectatePlayer(i, playerid);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(gIsPlayerBeingSpectated[playerid])
    {
        foreach(new i : Player)
        {
            if(gPlayerIsSpectating[i] && gSpectatingPlayer[i] == playerid)
            {
                TogglePlayerSpectating(i, false);
                SpawnPlayer(i);
            }
        }
    }
    return 1;
}