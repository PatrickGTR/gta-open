#include <YSI_Coding\y_hooks>

static
    Text:TimeTD,
    Text:DayTD;

hook OnGameModeInit() {
   	TimeTD = TextDrawCreate(577.000000, 20.000000, "00:00");
	TextDrawFont(TimeTD, TEXT_DRAW_FONT_3);
	TextDrawLetterSize(TimeTD, 0.5, 2.5);
	TextDrawTextSize(TimeTD, 400.000000, 17.000000);
	TextDrawSetOutline(TimeTD, 1);
	TextDrawSetShadow(TimeTD, 0);
	TextDrawAlignment(TimeTD, TEXT_DRAW_ALIGN_CENTRE);
	TextDrawColor(TimeTD, -1);
	TextDrawBackgroundColor(TimeTD, 255);
	TextDrawBoxColor(TimeTD, 50);
	TextDrawUseBox(TimeTD, false);
	TextDrawSetProportional(TimeTD, true);
	TextDrawSetSelectable(TimeTD, false);

	DayTD = TextDrawCreate(577.000000, 12.000000, "Monday");
	TextDrawFont(DayTD, TEXT_DRAW_FONT_3);
	TextDrawLetterSize(DayTD, 0.25, 1.3);
	TextDrawTextSize(DayTD, 400.000000, 17.000000);
	TextDrawSetOutline(DayTD, 1);
	TextDrawSetShadow(DayTD, 0);
	TextDrawAlignment(DayTD, TEXT_DRAW_ALIGN_CENTRE);
	TextDrawColor(DayTD, -1);
	TextDrawBackgroundColor(DayTD, 255);
	TextDrawBoxColor(DayTD, 50);
	TextDrawUseBox(DayTD, false);
	TextDrawSetProportional(DayTD, true);
	TextDrawSetSelectable(DayTD, false);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    TextDrawShowForPlayer(playerid, TimeTD);
    TextDrawShowForPlayer(playerid, DayTD);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason) {
    TextDrawHideForPlayer(playerid, TimeTD);
    TextDrawHideForPlayer(playerid, DayTD);
    return 1;
}

void:UI_SetDay(const day[]) {
	TextDrawSetString(DayTD, day);
}

void:UI_SetTime(const time[]) {
    TextDrawSetString(TimeTD, time);
}