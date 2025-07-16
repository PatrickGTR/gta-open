#include <YSI_Coding\y_hooks>

new
    PlayerText: PlayerLocationTD[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerLocationTD[playerid] = CreatePlayerTextDraw(playerid, 5.000000, 437.000000, "_");
    PlayerTextDrawFont(playerid, PlayerLocationTD[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, PlayerLocationTD[playerid], 0.200000, 0.2 * 4);
    PlayerTextDrawSetOutline(playerid, PlayerLocationTD[playerid], 1);
    PlayerTextDrawAlignment(playerid, PlayerLocationTD[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColor(playerid, PlayerLocationTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerLocationTD[playerid], TD_OUTLINE_COLOUR);
    PlayerTextDrawSetProportional(playerid, PlayerLocationTD[playerid], true);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason) {
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
stock UI_SetLocation(playerid, const plocation[]) {

    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    if(isnull(plocation)) {
        return 0;
    }

    PlayerTextDrawSetString(playerid, PlayerLocationTD[playerid], plocation);
    return 1;
}