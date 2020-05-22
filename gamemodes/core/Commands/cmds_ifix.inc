CMD:instafix(playerid) {
    if(!IsPlayerInAnyVehicle(playerid)) {
        return SendServerMsg(playerid, "You're not in any vehicle!");
    }
    if(GetPlayerState(playerid) != 2) {
        return SendServerMsg(playerid, "You're not in the driver seat!");
    }
    if(GetInstaFix(playerid) != 1) {
        return SendServerMsg(playerid, "You don't have any instafixes");
    }
    RepairVehicle(GetPlayerVehicleID(playerid));
    SendMsgAllF(-1, "%p (%d) used insta fix to fix his vehicle", playerid, playerid);
    SetInstaFix(playerid, 0);
    return 1;
}