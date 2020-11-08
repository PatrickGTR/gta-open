// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_progress2
	#undef _inc_progress2
#endif
// custom include-guard to ensure we don't duplicate
#if defined _progress2_included
	#endinput
#endif
#define _progress2_included

#include <a_samp>
#include <logger>
#include <YSI_Data\y_iterate>

#include <YSI_Coding\y_hooks>


#define MAX_PLAYER_BARS (_:MAX_PLAYER_TEXT_DRAWS / 3)
#define INVALID_PLAYER_BAR_VALUE (Float:0xFFFFFFFF)
#define INVALID_PLAYER_BAR_ID (PlayerBar:-1)

enum {
	BAR_DIRECTION_RIGHT,
	BAR_DIRECTION_LEFT,
	BAR_DIRECTION_UP,
	BAR_DIRECTION_DOWN
}

enum E_BAR_DATA {
	bool:pbar_show,
	Float:pbar_posX,
	Float:pbar_posY,
	Float:pbar_width,
	Float:pbar_height,
	pbar_colour,
	Float:pbar_maxValue,
	Float:pbar_progressValue,
	pbar_direction
}

enum E_BAR_TEXT_DRAW {
	PlayerText:pbar_back,
	PlayerText:pbar_fill,
	PlayerText:pbar_main
}

static pbar_TextDraw[MAX_PLAYERS][MAX_PLAYER_BARS][E_BAR_TEXT_DRAW];

new Iterator:pbar_Index[MAX_PLAYERS]<MAX_PLAYER_BARS>,
    pbar_Data[MAX_PLAYERS][MAX_PLAYER_BARS][E_BAR_DATA];

forward PlayerBar:CreatePlayerProgressBar(
	playerid, Float:x, Float:y, Float:width=55.5, Float:height=3.2,
	colour = 0xFF1C1CFF, Float:max=100.0, direction=BAR_DIRECTION_RIGHT);
forward Float:GetPlayerProgressBarValue(playerid, PlayerBar:barid);
forward Float:_bar_percent(Float:x, Float:widthorheight, Float:max, Float:value, direction);

stock PlayerBar:CreatePlayerProgressBar(
	playerid, Float:x, Float:y, Float:width = 55.5, Float:height = 3.2,
	colour = 0xFF1C1CFF, Float:max = 100.0, direction = BAR_DIRECTION_RIGHT
) {
	if(!IsPlayerConnected(playerid)) {
		Logger_Err("attempt to create player progress bar for invalid player",
			Logger_I("playerid", playerid));
		return INVALID_PLAYER_BAR_ID;
	}

	new barid = Iter_Free(pbar_Index[playerid]);

	if(barid == ITER_NONE) {
		Logger_Err("MAX_PLAYER_BARS limit reached.");
		return INVALID_PLAYER_BAR_ID;
	}

	pbar_TextDraw[playerid][barid][pbar_back] = PlayerText:INVALID_TEXT_DRAW;
	pbar_TextDraw[playerid][barid][pbar_fill] = PlayerText:INVALID_TEXT_DRAW;
	pbar_TextDraw[playerid][barid][pbar_main] = PlayerText:INVALID_TEXT_DRAW;
	pbar_Data[playerid][barid][pbar_show] = false;
	pbar_Data[playerid][barid][pbar_posX] = x;
	pbar_Data[playerid][barid][pbar_posY] = y;
	pbar_Data[playerid][barid][pbar_width] = width;
	pbar_Data[playerid][barid][pbar_height] = height;
	pbar_Data[playerid][barid][pbar_colour] = colour;
	pbar_Data[playerid][barid][pbar_maxValue] = max;
	pbar_Data[playerid][barid][pbar_progressValue] = 0.0;
	pbar_Data[playerid][barid][pbar_direction] = direction;

	Iter_Add(pbar_Index[playerid], barid);

	_progress2_renderBar(playerid, barid);

	return PlayerBar:barid;
}

stock DestroyPlayerProgressBar(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	PlayerTextDrawDestroy(playerid, pbar_TextDraw[playerid][_:barid][pbar_back]);
	PlayerTextDrawDestroy(playerid, pbar_TextDraw[playerid][_:barid][pbar_fill]);
	PlayerTextDrawDestroy(playerid, pbar_TextDraw[playerid][_:barid][pbar_main]);

	Iter_Remove(pbar_Index[playerid], _:barid);

	return 1;
}

stock bool:IsPlayerProgressBarVisible(playerid, PlayerBar:barid)
{
   return (IsValidPlayerProgressBar(playerid, barid) && pbar_Data[playerid][_:barid][pbar_show]);
}
stock ShowPlayerProgressBar(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	pbar_Data[playerid][_:barid][pbar_show] = true;

	PlayerTextDrawShow(playerid, pbar_TextDraw[playerid][_:barid][pbar_back]);
	PlayerTextDrawShow(playerid, pbar_TextDraw[playerid][_:barid][pbar_fill]);
	PlayerTextDrawShow(playerid, pbar_TextDraw[playerid][_:barid][pbar_main]);

	return 1;
}

stock HidePlayerProgressBar(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	pbar_Data[playerid][_:barid][pbar_show] = false;

	PlayerTextDrawHide(playerid, pbar_TextDraw[playerid][_:barid][pbar_back]);
	PlayerTextDrawHide(playerid, pbar_TextDraw[playerid][_:barid][pbar_fill]);
	PlayerTextDrawHide(playerid, pbar_TextDraw[playerid][_:barid][pbar_main]);

	return 1;
}

stock IsValidPlayerProgressBar(playerid, PlayerBar:barid) {
	return Iter_Contains(pbar_Index[playerid], _:barid);
}

// pbar_posX
// pbar_posY
stock GetPlayerProgressBarPos(playerid, PlayerBar:barid, &Float:x, &Float:y) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	x = pbar_Data[playerid][_:barid][pbar_posX];
	y = pbar_Data[playerid][_:barid][pbar_posY];

	return 1;
}

stock SetPlayerProgressBarPos(playerid, PlayerBar:barid, Float:x, Float:y) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return false;
	}

	pbar_Data[playerid][_:barid][pbar_posX] = x;
	pbar_Data[playerid][_:barid][pbar_posY] = y;

	_progress2_renderBar(playerid, _:barid);

	return true;
}

// pbar_width
stock Float:GetPlayerProgressBarWidth(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return INVALID_PLAYER_BAR_VALUE;
	}

	return pbar_Data[playerid][_:barid][pbar_width];
}

stock SetPlayerProgressBarWidth(playerid, PlayerBar:barid, Float:width) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	pbar_Data[playerid][_:barid][pbar_width] = width;

	_progress2_renderBar(playerid, _:barid);

	return 1;
}

// pbar_height
stock Float:GetPlayerProgressBarHeight(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return INVALID_PLAYER_BAR_VALUE;
	}

	return pbar_Data[playerid][_:barid][pbar_height];
}

stock SetPlayerProgressBarHeight(playerid, PlayerBar:barid, Float:height) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	pbar_Data[playerid][_:barid][pbar_height] = height;

	_progress2_renderBar(playerid, _:barid);

	return 1;
}

// pbar_colour
stock GetPlayerProgressBarColour(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	return pbar_Data[playerid][_:barid][pbar_colour];
}

stock SetPlayerProgressBarColour(playerid, PlayerBar:barid, colour) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	pbar_Data[playerid][_:barid][pbar_colour] = colour;

	PlayerTextDrawBoxColor(playerid, pbar_TextDraw[playerid][_:barid][pbar_back], 0x00000000 | (colour & 0x000000FF));
	PlayerTextDrawBoxColor(playerid, pbar_TextDraw[playerid][_:barid][pbar_fill], (colour & 0xFFFFFF00) | (0x66 & ((colour & 0x000000FF) / 2)));
	PlayerTextDrawBoxColor(playerid, pbar_TextDraw[playerid][_:barid][pbar_main], colour);

	return 1;
}

// pbar_maxValue
stock Float:GetPlayerProgressBarMaxValue(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return INVALID_PLAYER_BAR_VALUE;
	}

	return pbar_Data[playerid][_:barid][pbar_maxValue];
}

stock SetPlayerProgressBarMaxValue(playerid, PlayerBar:barid, Float:max) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	pbar_Data[playerid][_:barid][pbar_maxValue] = max;
	SetPlayerProgressBarValue(playerid, barid, pbar_Data[playerid][_:barid][pbar_progressValue]);

	return 1;
}

// pbar_progressValue
stock SetPlayerProgressBarValue(playerid, PlayerBar:barid, Float:value) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	if(value < 0.0) {
		value = 0.0;
	} else {
		if(value > pbar_Data[playerid][_:barid][pbar_maxValue]) {
			value = pbar_Data[playerid][_:barid][pbar_maxValue];
		}
	}

	PlayerTextDrawUseBox(playerid, pbar_TextDraw[playerid][_:barid][pbar_main], value > 0.0);

	pbar_Data[playerid][_:barid][pbar_progressValue] = value;

	switch(pbar_Data[playerid][_:barid][pbar_direction]) {
		case BAR_DIRECTION_RIGHT, BAR_DIRECTION_LEFT: {
			PlayerTextDrawTextSize(playerid, pbar_TextDraw[playerid][_:barid][pbar_main],
				_bar_percent(
					pbar_Data[playerid][_:barid][pbar_posX],
					pbar_Data[playerid][_:barid][pbar_width],
					pbar_Data[playerid][_:barid][pbar_maxValue],
					value,
					pbar_Data[playerid][_:barid][pbar_direction]), 0.0);
		}
		case BAR_DIRECTION_UP, BAR_DIRECTION_DOWN: {
			PlayerTextDrawLetterSize(playerid, pbar_TextDraw[playerid][_:barid][pbar_main], 1.0,
				_bar_percent(
					pbar_Data[playerid][_:barid][pbar_posX],
					pbar_Data[playerid][_:barid][pbar_height],
					pbar_Data[playerid][_:barid][pbar_maxValue],
					value,
					pbar_Data[playerid][_:barid][pbar_direction]));
		}
	}

	if(pbar_Data[playerid][_:barid][pbar_show]) {
		ShowPlayerProgressBar(playerid, barid);
	}

	return 1;
}

stock Float:GetPlayerProgressBarValue(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return INVALID_PLAYER_BAR_VALUE;
	}

	return pbar_Data[playerid][_:barid][pbar_progressValue];
}

// pbar_direction
stock GetPlayerProgressBarDirection(playerid, PlayerBar:barid) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	return pbar_Data[playerid][_:barid][pbar_direction];
}

stock SetPlayerProgressBarDirection(playerid, PlayerBar:barid, direction) {
	if(!IsValidPlayerProgressBar(playerid, barid)) {
		return 0;
	}

	pbar_Data[playerid][_:barid][pbar_direction] = direction;
	_progress2_renderBar(playerid, _:barid);

	return 1;
}

/*
	Internal
*/

_progress2_renderBar(playerid, barid)
{
	if(!IsPlayerConnected(playerid)) {
		return false;
	}

	if(!IsValidPlayerProgressBar(playerid, PlayerBar:barid)) {
		return false;
	}

	PlayerTextDrawDestroy(playerid, pbar_TextDraw[playerid][barid][pbar_back]);
	PlayerTextDrawDestroy(playerid, pbar_TextDraw[playerid][barid][pbar_fill]);
	PlayerTextDrawDestroy(playerid, pbar_TextDraw[playerid][barid][pbar_main]);

	switch(pbar_Data[playerid][barid][pbar_direction]) {
		case BAR_DIRECTION_RIGHT: {
			pbar_TextDraw[playerid][barid][pbar_back] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX], pbar_Data[playerid][barid][pbar_posY], "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_back], pbar_Data[playerid][barid][pbar_posX] + pbar_Data[playerid][barid][pbar_width] - 4.0, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1.0, pbar_Data[playerid][barid][pbar_height] / 10);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 0x00000000 | (pbar_Data[playerid][barid][pbar_colour] & 0x000000FF));

			pbar_TextDraw[playerid][barid][pbar_fill] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] + 1.2, pbar_Data[playerid][barid][pbar_posY] + 2.15, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], pbar_Data[playerid][barid][pbar_posX] + pbar_Data[playerid][barid][pbar_width] - 5.5, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1.0, pbar_Data[playerid][barid][pbar_height] / 10 - 0.35);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], (pbar_Data[playerid][barid][pbar_colour] & 0xFFFFFF00) | (0x66 & ((pbar_Data[playerid][barid][pbar_colour] & 0x000000FF) / 2)));

			pbar_TextDraw[playerid][barid][pbar_main] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] + 1.2, pbar_Data[playerid][barid][pbar_posY] + 2.15, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_main], _bar_percent(pbar_Data[playerid][barid][pbar_posX], pbar_Data[playerid][barid][pbar_width], pbar_Data[playerid][barid][pbar_maxValue], pbar_Data[playerid][barid][pbar_progressValue], pbar_Data[playerid][barid][pbar_direction]), 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_main], 1.0, pbar_Data[playerid][barid][pbar_height] / 10 - 0.35);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_main], pbar_Data[playerid][barid][pbar_colour]);
		}
		case BAR_DIRECTION_LEFT: {
			pbar_TextDraw[playerid][barid][pbar_back] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX], pbar_Data[playerid][barid][pbar_posY], "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_back], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 4.0, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1.0, pbar_Data[playerid][barid][pbar_height] / 10);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 0x00000000 | (pbar_Data[playerid][barid][pbar_colour] & 0x000000FF));

			pbar_TextDraw[playerid][barid][pbar_fill] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] - 1.2, pbar_Data[playerid][barid][pbar_posY] + 2.15, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 2.5, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1.0, pbar_Data[playerid][barid][pbar_height] / 10 - 0.35);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], (pbar_Data[playerid][barid][pbar_colour] & 0xFFFFFF00) | (0x66 & ((pbar_Data[playerid][barid][pbar_colour] & 0x000000FF) / 2)));

			pbar_TextDraw[playerid][barid][pbar_main] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] - 1.2, pbar_Data[playerid][barid][pbar_posY] + 2.15, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_main], _bar_percent(pbar_Data[playerid][barid][pbar_posX], pbar_Data[playerid][barid][pbar_width], pbar_Data[playerid][barid][pbar_maxValue], pbar_Data[playerid][barid][pbar_progressValue], pbar_Data[playerid][barid][pbar_direction]), 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_main], 1.0, pbar_Data[playerid][barid][pbar_height] / 10 - 0.35);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_main], pbar_Data[playerid][barid][pbar_colour]);
		}
		case BAR_DIRECTION_UP: {
			pbar_TextDraw[playerid][barid][pbar_back] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX], pbar_Data[playerid][barid][pbar_posY], "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_back], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 4.0, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1.0, -((pbar_Data[playerid][barid][pbar_height] / 10) * 1.02) -0.35);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 0x00000000 | (pbar_Data[playerid][barid][pbar_colour] & 0x000000FF));

			pbar_TextDraw[playerid][barid][pbar_fill] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] - 1.2, pbar_Data[playerid][barid][pbar_posY] - 1.0, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 2.5, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1.0, -(pbar_Data[playerid][barid][pbar_height] / 10.0) * 1.02);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], (pbar_Data[playerid][barid][pbar_colour] & 0xFFFFFF00) | (0x66 & ((pbar_Data[playerid][barid][pbar_colour] & 0x000000FF) / 2)));

			pbar_TextDraw[playerid][barid][pbar_main] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] - 1.2, pbar_Data[playerid][barid][pbar_posY] - 1.0, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_main], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_main], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 2.5, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_main], 1.0, _bar_percent(pbar_Data[playerid][_:barid][pbar_posX], pbar_Data[playerid][_:barid][pbar_height], pbar_Data[playerid][_:barid][pbar_maxValue], pbar_Data[playerid][barid][pbar_progressValue], pbar_Data[playerid][barid][pbar_direction]));
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_main], pbar_Data[playerid][barid][pbar_colour]);
		}
		case BAR_DIRECTION_DOWN: {
			pbar_TextDraw[playerid][barid][pbar_back] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX], pbar_Data[playerid][barid][pbar_posY], "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_back], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 4.0, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_back], 1.0, ((pbar_Data[playerid][barid][pbar_height] / 10)) -0.35);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_back], 0x00000000 | (pbar_Data[playerid][barid][pbar_colour] & 0x000000FF));

			pbar_TextDraw[playerid][barid][pbar_fill] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] - 1.2, pbar_Data[playerid][barid][pbar_posY] + 1.0, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 2.5, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_fill], 1.0, (pbar_Data[playerid][barid][pbar_height] / 10.0) - 0.55);
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_fill], (pbar_Data[playerid][barid][pbar_colour] & 0xFFFFFF00) | (0x66 & ((pbar_Data[playerid][barid][pbar_colour] & 0x000000FF) / 2)));

			pbar_TextDraw[playerid][barid][pbar_main] = CreatePlayerTextDraw(playerid, pbar_Data[playerid][barid][pbar_posX] - 1.2, pbar_Data[playerid][barid][pbar_posY] + 1.0, "_");
			PlayerTextDrawUseBox		(playerid, pbar_TextDraw[playerid][barid][pbar_main], 1);
			PlayerTextDrawTextSize		(playerid, pbar_TextDraw[playerid][barid][pbar_main], pbar_Data[playerid][barid][pbar_posX] - pbar_Data[playerid][barid][pbar_width] - 2.5, 0.0);
			PlayerTextDrawLetterSize	(playerid, pbar_TextDraw[playerid][barid][pbar_main], 1.0, _bar_percent(pbar_Data[playerid][_:barid][pbar_posX], pbar_Data[playerid][_:barid][pbar_height], pbar_Data[playerid][_:barid][pbar_maxValue], pbar_Data[playerid][barid][pbar_progressValue], pbar_Data[playerid][barid][pbar_direction]));
			PlayerTextDrawBoxColor		(playerid, pbar_TextDraw[playerid][barid][pbar_main], pbar_Data[playerid][barid][pbar_colour]);
		}
	}

	if(pbar_Data[playerid][barid][pbar_show]) {
		ShowPlayerProgressBar(playerid, PlayerBar:barid);
	}

	return true;
}

hook OnScriptInit() {
	Iter_Init(pbar_Index);
}

hook OnPlayerDisconnect(playerid, reason) {
	Iter_Clear(pbar_Index[playerid]);
}

hook OnScriptExit() {
	for(new i = 0; i < MAX_PLAYERS; i++) {
		if(IsPlayerConnected(i))
			DestroyAllPlayerProgressBars(i);
	}
}

stock DestroyAllPlayerProgressBars(playerid) {
	for(new i = 0; i < MAX_PLAYER_BARS; i++) {
		DestroyPlayerProgressBar(playerid, PlayerBar:i);
	}

	return 1;
}

stock Float:_bar_percent(Float:x, Float:widthorheight, Float:max, Float:value, direction) {
	new Float:result;

	switch(direction) {
		case BAR_DIRECTION_RIGHT: {
			result = ((x - 3.0) + (((((x - 2.0) + widthorheight) - x) / max) * value));
		}
		case BAR_DIRECTION_LEFT: {
			result = ((x - 1.0) - (((((x + 2.0) - widthorheight) - x) / max) * -value)) - 4.0;
		}
		case BAR_DIRECTION_UP: {
			result = -((((((widthorheight / 10.0) - 0.45) * 1.02) / max) * value) + 0.55);
		}
		case BAR_DIRECTION_DOWN: {
			result = ((((((widthorheight / 10.0) - 0.45) * 1.02) / max) * value) - 0.55);
		}
	}

	return result;
}
