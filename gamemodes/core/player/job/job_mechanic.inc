static 
    PlayerFixCooldown[MAX_PLAYERS];

/*
    This command can be used by mechanics only,
    it has 3 minute cooldown everytime the command
    is used to avoid repair abuse during chase.
*/
CMD:mechfix(playerid, params[]) {
    if(Player_GetJob(playerid) != TYPE_MECHANIC) {
        return SendErrorMsg(playerid, "Only mechanics can use this command.");
    }

    if(gettime() < PlayerFixCooldown[playerid]) {
        return SendErrorMsgF(playerid, "Please wait "C_GREY"%i seconds "C_WHITE"before using this command again.", (gettime() - PlayerFixCooldown[playerid]));
    }

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
        return SendErrorMsg(playerid, "You need to be the driver in order to fix the vehicle.");
    }
    
    RepairVehicle(GetPlayerVehicleID(playerid));
    PlayerFixCooldown[playerid] = gettime() + (60 * 3); 

    SendClientMessage(playerid, COLOR_PURPLE, "[MECH FIX] "C_WHITE"Your vehicle has been repaired, 3 minutes cooldown.");
    return 1;
}