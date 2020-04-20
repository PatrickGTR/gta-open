#include <YSI_Coding\y_hooks>
#include <formatex>

static 
    Text: LeaveJoinTD,
    joinString[5][32]
;

hook OnGameModeInit() {
    LeaveJoinTD = TextDrawCreate    (536.000000, 210.000000, "JOIN: PDS2K12");
    TextDrawLetterSize              (LeaveJoinTD, 0.1999, 0.8999);
    TextDrawAlignment               (LeaveJoinTD, 1);
    TextDrawBackgroundColor         (LeaveJoinTD, TD_OUTLINE_COLOUR);
    TextDrawColor                   (LeaveJoinTD, -1);
    TextDrawSetOutline              (LeaveJoinTD, 1);
    TextDrawSetProportional         (LeaveJoinTD, 1);
    TextDrawFont                    (LeaveJoinTD, 1);
    TextDrawSetSelectable           (LeaveJoinTD, 0);
}

hook OnGameModeExit()
{
    TextDrawDestroy(LeaveJoinTD);
}

hook OnPlayerConnect(playerid) {
    strcpy(joinString[4], joinString[3]);
    strcpy(joinString[3], joinString[2]);
    strcpy(joinString[2], joinString[1]);
    strcpy(joinString[1], joinString[0]);

    new 
        string[sizeof(joinString[]) * 5];

    format(joinString[0], sizeof(joinString[]), "~g~JOIN: ~w~%p (%i)~n~", playerid, playerid);

    strcat(string, joinString[4], sizeof(string));
    strcat(string, joinString[3], sizeof(string));
    strcat(string, joinString[2], sizeof(string));
    strcat(string, joinString[1], sizeof(string));
    strcat(string, joinString[0], sizeof(string));

    TextDrawSetString(LeaveJoinTD, string);
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
        string[128];

    format(joinString[0], sizeof(joinString[]), "%s: ~w~%p (%i)~n~", leave_reason, playerid, playerid);
    
    strcat(string, joinString[4], sizeof(string));
    strcat(string, joinString[3], sizeof(string));
    strcat(string, joinString[2], sizeof(string));
    strcat(string, joinString[1], sizeof(string));
    strcat(string, joinString[0], sizeof(string));
    
    TextDrawSetString(LeaveJoinTD, string);
}


hook OnPlayerSpawn(playerid) {
    TextDrawShowForPlayer(playerid, LeaveJoinTD);
}

hook OnPlayerDeath(playerid, killerid) {
    TextDrawHideForPlayer(playerid, LeaveJoinTD);
}
