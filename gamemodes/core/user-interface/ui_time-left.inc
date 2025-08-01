#include <YSI_Coding\y_hooks>

static
    PlayerText:timeLeft[MAX_PLAYERS],
    bool:timeLeftShown[MAX_PLAYERS],
    timeLeftCounter[MAX_PLAYERS],
    Timer:timeLeftTimer[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    timeLeft[playerid] = CreatePlayerTextDraw(playerid, 130.000000, 400.000000, "Time left:~n~~g~05:55");
    PlayerTextDrawFont(playerid, timeLeft[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, timeLeft[playerid], 0.270000,  0.270000 * 4);
    PlayerTextDrawTextSize(playerid, timeLeft[playerid], 200.000000, 46.500000);
    PlayerTextDrawSetOutline(playerid, timeLeft[playerid], 1);
    PlayerTextDrawSetShadow(playerid, timeLeft[playerid], 0);
    PlayerTextDrawAlignment(playerid, timeLeft[playerid], TEXT_DRAW_ALIGN_CENTRE);
    PlayerTextDrawColor(playerid, timeLeft[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, timeLeft[playerid], 255);
    PlayerTextDrawBoxColour(playerid, timeLeft[playerid], 50);
    PlayerTextDrawUseBox(playerid, timeLeft[playerid], false);
    PlayerTextDrawSetProportional(playerid, timeLeft[playerid], true);
    PlayerTextDrawSetSelectable(playerid, timeLeft[playerid], false);

    timeLeftShown[playerid] = false;
    timeLeftCounter[playerid] = 0;
    return 1;
}

// returns
// 0 - if playerid is invalid
// 1 - success
stock UI_TimeLeft(playerid, seconds) {

    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    new
        string[30],
        mins,
        secs;

    mins = seconds / 60;
    secs = seconds % 60;
    format(string, sizeof(string), "Time Left~n~~g~%02d:%02d", mins, secs);
    PlayerTextDrawSetString(playerid, timeLeft[playerid], string);

    if(!timeLeftShown[playerid]) {
        timeLeftShown[playerid] = true;
        timeLeftTimer[playerid] = repeat decrementTimeLeft(playerid);
        PlayerTextDrawShow(playerid, timeLeft[playerid]);
    }
    if(seconds <= 0) {
        timeLeftShown[playerid] = false;
        PlayerTextDrawHide(playerid, timeLeft[playerid]);
        stop timeLeftTimer[playerid];
    }

    timeLeftCounter[playerid] = seconds;
    return 1;
}

timer decrementTimeLeft[1000](playerid) {
    if(timeLeftCounter[playerid] -- <= 0) {
        stop timeLeftTimer[playerid];
    }
    UI_TimeLeft(playerid, timeLeftCounter[playerid]);
}

stock UI_HideTimeLeft(playerid) {
    return UI_TimeLeft(playerid, 0);
}

stock UI_GetTimeLeft(playerid) {
    return timeLeftCounter[playerid];
}

