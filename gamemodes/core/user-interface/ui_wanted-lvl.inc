#include <YSI_Coding\y_hooks>

static
    PlayerText: ui_WantedLevel[MAX_PLAYERS],
    bool: ui_WantedLevelShown[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    ui_WantedLevel[playerid] = CreatePlayerTextDraw(playerid,600.000000, 109.000000, "7");
    PlayerTextDrawAlignment(playerid, ui_WantedLevel[playerid], TEXT_DRAW_ALIGN_CENTRE);
    PlayerTextDrawBackgroundColor           (playerid, ui_WantedLevel[playerid], TD_OUTLINE_COLOUR);
    PlayerTextDrawFont(playerid, ui_WantedLevel[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize                (playerid, ui_WantedLevel[playerid], 0.23, 0.23 * 4);
    PlayerTextDrawColor                     (playerid, ui_WantedLevel[playerid], -1872621313);
    PlayerTextDrawSetOutline                (playerid, ui_WantedLevel[playerid], 1);
    PlayerTextDrawSetProportional           (playerid, ui_WantedLevel[playerid], true);
    PlayerTextDrawSetSelectable             (playerid, ui_WantedLevel[playerid], false);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    PlayerTextDrawHide(playerid, ui_WantedLevel[playerid]);
    ui_WantedLevelShown[playerid] = false;
    return 1;
}

stock UI_UpdatePlayerWanted(playerid, plevel)
{
    new
        string[5];
    format(string, sizeof(string), "%d", plevel);
    PlayerTextDrawSetString(playerid, ui_WantedLevel[playerid], string);

    if(plevel == 0) {
        PlayerTextDrawHide(playerid, ui_WantedLevel[playerid]);
        ui_WantedLevelShown[playerid] = false;
        return 0;
    }

    if(!ui_WantedLevelShown[playerid]) {
        PlayerTextDrawShow(playerid, ui_WantedLevel[playerid]);
        ui_WantedLevelShown[playerid] = true;
    }
    return 1;
}