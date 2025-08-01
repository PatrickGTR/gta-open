#include <YSI_Coding\y_hooks>

static
    Text:ErrorSign,
    bool:ErrorAlreadyShown[MAX_PLAYERS],
    Timer:ErrorTimer[MAX_PLAYERS],
    PlayerText:ErrorContent[MAX_PLAYERS];

timer UI_HideError[3500](playerid) {
    if(!IsPlayerConnected(playerid)) {
        return;
    }

    if(!ErrorAlreadyShown[playerid]) {
        return;
    }

    ErrorAlreadyShown[playerid] = false;
    TextDrawHideForPlayer(playerid, ErrorSign);
    PlayerTextDrawHide(playerid, ErrorContent[playerid]);
}

hook OnGameModeInit() {
    ErrorSign = TextDrawCreate(340.000000, 285.000000, "ld_chat:badchat");
    TextDrawFont(ErrorSign, TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawLetterSize(ErrorSign, 0.600000, 2.000000);
    TextDrawTextSize(ErrorSign, 20.000000, 20.000000);
    TextDrawSetOutline(ErrorSign, 1);
    TextDrawSetShadow(ErrorSign, 0);
    TextDrawAlignment(ErrorSign, TEXT_DRAW_ALIGN_CENTRE);
    TextDrawColor(ErrorSign, -1);
    TextDrawBackgroundColor(ErrorSign, 255);
    TextDrawBoxColor(ErrorSign, 50);
    TextDrawUseBox(ErrorSign, true);
    TextDrawSetProportional(ErrorSign, true);
    TextDrawSetSelectable(ErrorSign, false);
    return 1;
}

hook OnPlayerConnect(playerid) {
    // just to be safe
    // as this textdraw is not deleted on player disconnect.
    TextDrawHideForPlayer(playerid, ErrorSign);

    ErrorContent[playerid] = INVALID_PLAYER_TEXT_DRAW;
    ErrorTimer[playerid] = Timer:0;
    ErrorAlreadyShown[playerid] = false;

    ErrorContent[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 300.000000, "~r~ERROR~n~~w~Oops something went wrong, try again!");
    PlayerTextDrawFont(playerid, ErrorContent[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, ErrorContent[playerid], 0.400000, 1.600000);
    PlayerTextDrawTextSize(playerid, ErrorContent[playerid], 420.000000, 300.000000);
    PlayerTextDrawSetOutline(playerid, ErrorContent[playerid], 1);
    PlayerTextDrawSetShadow(playerid, ErrorContent[playerid], 0);
    PlayerTextDrawAlignment(playerid, ErrorContent[playerid], TEXT_DRAW_ALIGN_CENTRE);
    PlayerTextDrawColor(playerid, ErrorContent[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ErrorContent[playerid], 200);
    PlayerTextDrawBoxColour(playerid, ErrorContent[playerid], 127);
    PlayerTextDrawUseBox(playerid, ErrorContent[playerid], false);
    PlayerTextDrawSetProportional(playerid, ErrorContent[playerid], true);
    PlayerTextDrawSetSelectable(playerid, ErrorContent[playerid], false);
    return 1;
}

stock void:UI_ShowError(playerid, const message[]) {
    if(!IsPlayerConnected(playerid)) {
        return;
    }

    if(strlen(message) > 128) {
        return;
    }

    new
        string[128];
    strcat(string, "~r~");
    strcat(string, "ERROR");
    strcat(string, "~n~");
    strcat(string, "~w~");
    strcat(string, message);

    PlayerTextDrawSetString(playerid, ErrorContent[playerid], string);
    TextDrawShowForPlayer(playerid, ErrorSign);
    PlayerTextDrawShow(playerid, ErrorContent[playerid]);

    // if error is already showing
    // restart the timer from 0.
    if(ErrorAlreadyShown[playerid]) {
        stop ErrorTimer[playerid];
    }

    ErrorTimer[playerid] = defer UI_HideError(playerid);
    ErrorAlreadyShown[playerid] = true;
}