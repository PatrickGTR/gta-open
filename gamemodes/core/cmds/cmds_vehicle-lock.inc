static 
    PlayerLastVehicle[MAX_PLAYERS],
    VehiclePlayer[MAX_VEHICLES],
    bool:IsVehicleLocked[MAX_VEHICLES]
;

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        new playercar = GetPlayerVehicleID(playerid);
        if(!IsVehicleLocked[playercar])
        {
            PlayerLastVehicle[playerid] = playercar;
            VehiclePlayer[playercar] = playerid;
        }
        if(IsVehicleLocked[playercar] && PlayerLastVehicle[playerid] == playercar)
        {
            IsVehicleLocked[playercar] = false;
            SendServerMsg(playerid, "Vehicle Unlocked");
        }
        else if(IsVehicleLocked[playercar] && PlayerLastVehicle[playerid] != playercar)
        {
            SendServerMsg(playerid, "This vehicle is locked!");
            RemovePlayerFromVehicle(playerid);
        }
    }
    return 1;
}

hook OnVehicleDeath(vehicleid, killerid)
{
    new playercar = VehiclePlayer[vehicleid];
    if(IsVehicleLocked[vehicleid])
    {
        PlayerLastVehicle[playercar] = -1;
        SendServerMsg(playercar, "Your vehicle is destroyed");
    }
    return 1;
}

ALTCMD:lk(lock);
CMD:lock(playerid, params[])
{
    if(PlayerLastVehicle[playerid] == -1) {
        return SendErrorMsg(playerid, "You don't have any vehicles!");
    }
    if(VehiclePlayer[PlayerLastVehicle[playerid]] != playerid) {
        SendErrorMsg(playerid, "You don't have any vehicles!");
        PlayerLastVehicle[playerid] = -1;
        return 1;
    }
    if(VehicleHasDriver(PlayerLastVehicle[playerid])) {
        return SendErrorMsg(playerid, "There is a player in your vehicle!");
    }
    if(IsPlayerInAnyVehicle(playerid)) {
        return SendErrorMsg(playerid, "You can't lock the vehicle from inside!");
    }
    new playercar = PlayerLastVehicle[playerid];    
    IsVehicleLocked[playercar] = true;
    SendServerMsg(playerid, "Vehicle locked");
    return 1;
}

ALTCMD:ulk(unlock);
CMD:unlock(playerid, params[])
{
    new playercar = PlayerLastVehicle[playerid];
    if(PlayerLastVehicle[playerid] == -1) {
        return SendErrorMsg(playerid, "You don't have any vehicles!");
    }
    if(!IsVehicleLocked[playercar]) {
        return SendErrorMsg(playerid, "The vehicle is unlocked");
    }
    IsVehicleLocked[playercar] = false;
    SendServerMsg(playerid, "Vehicle Unlocked!");
    return 1;
}

CMD:givekeys(playerid, params[])
{
    if(PlayerLastVehicle[playerid] == -1) {
        return SendErrorMsg(playerid, "You don't have any vehicles!");
    }
    new target;
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/givekeys (player/id)");
    if(target == playerid) {
        return SendErrorMsg(playerid, "You can't give your vehicle keys to yourself");
    }
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "player is not connected");
    }
    PlayerLastVehicle[target] = PlayerLastVehicle[playerid];
    SendServerMsgF(playerid, "You have give your vehicle keys to %p (%d)", target, target);
    SendServerMsgF(target, "%p (%d) gave his vehicle keys to you", playerid, playerid);
    return 1;
}

stock VehicleHasDriver(vehicleid)
{
    for(new i; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerInAnyVehicle(i))
        {
            if(GetPlayerVehicleID(i) == vehicleid)
            {
                if(GetPlayerState(i) == PLAYER_STATE_PASSENGER)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}