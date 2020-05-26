#include <YSI_Coding\y_hooks>

new 
    PlayerText:timeLeft[MAX_PLAYERS],
    bool:timeLeftShown[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    timeLeft[playerid] = CreatePlayerTextDraw(playerid, 130.000000, 400.000000, "Time left:~n~~g~05:55");
    PlayerTextDrawFont(playerid, timeLeft[playerid], 1);
    PlayerTextDrawLetterSize(playerid, timeLeft[playerid], 0.270000, 1.500000);
    PlayerTextDrawTextSize(playerid, timeLeft[playerid], 200.000000, 46.500000);
    PlayerTextDrawSetOutline(playerid, timeLeft[playerid], 1);
    PlayerTextDrawSetShadow(playerid, timeLeft[playerid], 0);
    PlayerTextDrawAlignment(playerid, timeLeft[playerid], 2);
    PlayerTextDrawColor(playerid, timeLeft[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, timeLeft[playerid], 255);
    PlayerTextDrawBoxColor(playerid, timeLeft[playerid], 50);
    PlayerTextDrawUseBox(playerid, timeLeft[playerid], 0);
    PlayerTextDrawSetProportional(playerid, timeLeft[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, timeLeft[playerid], 0);

    timeLeftShown[playerid] = false; 
    return 1;
}

// returns
// 0 - if playerid is invalid
// 1 - success
stock UI_TimeLeft(playerid, seconds) {

    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    if(seconds <= 0  && timeLeftShown[playerid]) {
        timeLeftShown[playerid] = false;
        PlayerTextDrawHide(playerid, timeLeft[playerid]);
        return 1;
    }

    new 
        string[30],
        mins,
        secs;

    mins = seconds / 60;
    secs = seconds % 60;
    format(string, sizeof(string), "Time Left~n~~g~%02d:%02d", mins ,secs);
    PlayerTextDrawSetString(playerid, timeLeft[playerid], string);


    if(!timeLeftShown[playerid]) {
        timeLeftShown[playerid] = true;
        PlayerTextDrawShow(playerid, timeLeft[playerid]);
    }

    return 1;
}

stock UI_HideTimeLeft(playerid) {
    return UI_TimeLeft(playerid, 0);
}



