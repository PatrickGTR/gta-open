CMD:instafix(playerid) {
    if(!IsPlayerInAnyVehicle(playerid)) {
        return SendServerMsg(playerid, "You're not in any vehicle!");
    }
    if(GetPlayerState(playerid) != 2) {
        return SendServerMsg(playerid, "You're not in the driver seat!");
    }
    if(Player_GetInstaFix(playerid) != 1) {
        return SendServerMsg(playerid, "You don't have any instafixes");
    }
    RepairVehicle(GetPlayerVehicleID(playerid));
    SendMsgAllF(-1, "%p (%d) used insta fix to fix his vehicle", playerid, playerid);
    Player_SetInstaFix(playerid, 0);
    return 1;
}

CMD:ifix(playerid) {
 
    return cmd_instafix(playerid);
}