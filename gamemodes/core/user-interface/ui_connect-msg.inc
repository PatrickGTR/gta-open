#include <YSI_Coding\y_hooks>
#include <formatex>

static
    Text: LeaveJoinTD,
    joinString[5][MAX_PLAYER_NAME + 9 /* Colours */ +  6 /* brackets + ID */ ];

hook OnGameModeInit() {
    LeaveJoinTD = TextDrawCreate    (536.000000, 210.000000, "JOIN: PDS2K12");
    TextDrawLetterSize              (LeaveJoinTD, 0.2, 0.2 * 4);
    TextDrawAlignment(LeaveJoinTD, TEXT_DRAW_ALIGN_LEFT);
    TextDrawBackgroundColor         (LeaveJoinTD, TD_OUTLINE_COLOUR);
    TextDrawColor                   (LeaveJoinTD, -1);
    TextDrawSetOutline              (LeaveJoinTD, 1);
    TextDrawSetProportional         (LeaveJoinTD, true);
    TextDrawFont(LeaveJoinTD, TEXT_DRAW_FONT_1);
    TextDrawSetSelectable           (LeaveJoinTD, false);
    return 1;
}

hook OnGameModeExit()
{
    TextDrawDestroy(LeaveJoinTD);
    return 1;
}

hook OnPlayerConnect(playerid) {
    strcpy(joinString[4], joinString[3]);
    strcpy(joinString[3], joinString[2]);
    strcpy(joinString[2], joinString[1]);
    strcpy(joinString[1], joinString[0]);

    new
        string[sizeof(joinString[]) * 5];

    format(joinString[0], sizeof(joinString[]), "~n~~g~JOIN: ~w~%p (%i)", playerid, playerid);

    strcat(string, joinString[4], sizeof(string));
    strcat(string, joinString[3], sizeof(string));
    strcat(string, joinString[2], sizeof(string));
    strcat(string, joinString[1], sizeof(string));
    strcat(string, joinString[0], sizeof(string));

    TextDrawSetString(LeaveJoinTD, string);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    strcpy(joinString[4], joinString[3]);
    strcpy(joinString[3], joinString[2]);
    strcpy(joinString[2], joinString[1]);
    strcpy(joinString[1], joinString[0]);

    new
        leave_reason[16];

    switch(reason) {
        case 0: leave_reason = "~y~LOST" ;
        case 1: leave_reason = "~r~QUIT";
        case 2: leave_reason = "~p~KICK" ;
    }

    new
        string[7 + ((sizeof(joinString[]) * 5))];

    format(joinString[0], sizeof(joinString[]), "~n~%s: ~w~%p (%i)", leave_reason, playerid, playerid);

    strcat(string, joinString[4], sizeof(string));
    strcat(string, joinString[3], sizeof(string));
    strcat(string, joinString[2], sizeof(string));
    strcat(string, joinString[1], sizeof(string));
    strcat(string, joinString[0], sizeof(string));

    TextDrawSetString(LeaveJoinTD, string);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    TextDrawShowForPlayer(playerid, LeaveJoinTD);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason) {
    TextDrawHideForPlayer(playerid, LeaveJoinTD);
    return 1;
}
