#include <YSI_Coding\y_hooks>

static
    Text:TimeTD,
    Text:DayTD;

hook OnGameModeInit() {
   	TimeTD = TextDrawCreate(577.000000, 20.000000, "00:00");
	TextDrawFont(TimeTD, 3);
	TextDrawLetterSize(TimeTD, 0.5, 2.5);
	TextDrawTextSize(TimeTD, 400.000000, 17.000000);
	TextDrawSetOutline(TimeTD, 1);
	TextDrawSetShadow(TimeTD, 0);
	TextDrawAlignment(TimeTD, 2);
	TextDrawColor(TimeTD, -1);
	TextDrawBackgroundColor(TimeTD, 255);
	TextDrawBoxColor(TimeTD, 50);
	TextDrawUseBox(TimeTD, 0);
	TextDrawSetProportional(TimeTD, 1);
	TextDrawSetSelectable(TimeTD, 0);

	DayTD = TextDrawCreate(577.000000, 12.000000, "Monday");
	TextDrawFont(DayTD, 3);
	TextDrawLetterSize(DayTD, 0.25, 1.3);
	TextDrawTextSize(DayTD, 400.000000, 17.000000);
	TextDrawSetOutline(DayTD, 1);
	TextDrawSetShadow(DayTD, 0);
	TextDrawAlignment(DayTD, 2);
	TextDrawColor(DayTD, -1);
	TextDrawBackgroundColor(DayTD, 255);
	TextDrawBoxColor(DayTD, 50);
	TextDrawUseBox(DayTD, 0);
	TextDrawSetProportional(DayTD, 1);
	TextDrawSetSelectable(DayTD, 0);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    TextDrawShowForPlayer(playerid, TimeTD);
    TextDrawShowForPlayer(playerid, DayTD);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    TextDrawHideForPlayer(playerid, TimeTD);
    TextDrawHideForPlayer(playerid, DayTD);
    return 1;
}

void:UI_SetDayTime(const time[], const day[]) {
    TextDrawSetString(TimeTD, time);
    TextDrawSetString(DayTD, day);
}