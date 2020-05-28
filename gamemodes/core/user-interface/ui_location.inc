#include <YSI_Coding\y_hooks>

new 
    PlayerText: PlayerLocationTD[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerLocationTD[playerid] = CreatePlayerTextDraw(playerid, 5.000000, 437.000000, "_");
    PlayerTextDrawFont(playerid, PlayerLocationTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, PlayerLocationTD[playerid], 0.200000, 0.2 * 4);
    PlayerTextDrawSetOutline(playerid, PlayerLocationTD[playerid], 1);
    PlayerTextDrawAlignment(playerid, PlayerLocationTD[playerid], 1);
    PlayerTextDrawColor(playerid, PlayerLocationTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerLocationTD[playerid], TD_OUTLINE_COLOUR);
    PlayerTextDrawSetProportional(playerid, PlayerLocationTD[playerid], 1);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason, Float: damage, bodypart) {
    PlayerTextDrawHide(playerid, PlayerLocationTD[playerid]);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    PlayerTextDrawShow(playerid, PlayerLocationTD[playerid]);
    return 1;
}

// returns
// 1 -> success
// 0 -> player not connected or empty string passed..
stock UI_SetLocation(playerid, const location[]) {

    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    if(isnull(location)) {
        return 0;
    }

    PlayerTextDrawSetString(playerid, PlayerLocationTD[playerid], location);    
    return 1;
}