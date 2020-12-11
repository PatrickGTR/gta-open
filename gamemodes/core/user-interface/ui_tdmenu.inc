// Manual
// Text Menu and Text Info is different.
// TextMenu_Create(playerid, callback, name) -> Create a text menu "Selectable".
// TextMenu_Add(playerid, Item) -> Add an item to an text menu.
// TextMenu_Show(playerid) -> Must be at the bottom used to show the menu created with Create and Add
// TextMenu_Hide(playerid) -> Used for menus also work for info but doesn't reset the data of it. somehow in the script when you pressed n it will reset the data ALL of it.
// TextMenu_HideSpecific(playerid, callback) -> You can hide specific textdraws. You will find this usefull.
// TextInfo_Create(playerid, intname, title) -> same as the Menu_Create but this is not selectable don't use when you have TextMenu_Add in it. you will just use this if its pure Text Info.
// TextInfo_Add(playerid, text[]) -> You will just add a text to it you can't select it. You can add this at the TextMenu_Create also
// TextInfo_Show(playerid) -> Used for infos however when you have both TextMenu_Add use TextMenu_Add instead.
// TextInfo_Hide(playerid) -> same as Menu_Hide but used for info.
// TextInfo_HideSpecific(playerid, intname) -> Hide the intname. the intname means "Internal Name" which means this is the name that the script reads..

#include <YSI_Coding\y_hooks>

#define TDMenu:%1(%2) forward %1(%2); public %1(%2)

static
	PlayerText:TextMenuHeader[MAX_PLAYERS],
	PlayerText:TextMenuBody[MAX_PLAYERS],
	TextMenuCallbackHandler[MAX_PLAYERS][32],
	TextInfoNameHandler[MAX_PLAYERS][32],
	TextMenuItems[MAX_PLAYERS][512],
	TextMenuState[MAX_PLAYERS],
	TextMenuItemCount[MAX_PLAYERS],
	TextInfoState[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
	// reset data
	TextMenuState[playerid] = false;
	TextInfoState[playerid] = false;
	TextMenuItemCount[playerid] = 0;
	TextMenuCallbackHandler[playerid][0] = EOS;
	TextMenuItems[playerid][0] = EOS;
	TextInfoNameHandler[playerid][0] = EOS;

	TextMenuHeader[playerid] = CreatePlayerTextDraw(playerid, 85.000000, 170.000000, "Title");
	PlayerTextDrawFont(playerid, TextMenuHeader[playerid], 0);
	PlayerTextDrawLetterSize(playerid, TextMenuHeader[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TextMenuHeader[playerid], 274.000000, 153.000000);
	PlayerTextDrawSetOutline(playerid, TextMenuHeader[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TextMenuHeader[playerid], 0);
	PlayerTextDrawAlignment(playerid, TextMenuHeader[playerid], 2);
	PlayerTextDrawColor(playerid, TextMenuHeader[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, TextMenuHeader[playerid], 255);
	PlayerTextDrawBoxColor(playerid, TextMenuHeader[playerid], 50);
	PlayerTextDrawUseBox(playerid, TextMenuHeader[playerid], 0);
	PlayerTextDrawSetProportional(playerid, TextMenuHeader[playerid], 1);

	TextMenuBody[playerid] = CreatePlayerTextDraw(playerid, 15.000000, 185.000000, "Content");
	PlayerTextDrawFont(playerid, TextMenuBody[playerid], 1);
	PlayerTextDrawLetterSize(playerid, TextMenuBody[playerid], 0.200000, 0.800000);
	PlayerTextDrawTextSize(playerid, TextMenuBody[playerid], 168.000000, 18.000000);
	PlayerTextDrawSetOutline(playerid, TextMenuBody[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TextMenuBody[playerid], 0);
	PlayerTextDrawAlignment(playerid, TextMenuBody[playerid], 1);
	PlayerTextDrawColor(playerid, TextMenuBody[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, TextMenuBody[playerid], 255);
	PlayerTextDrawBoxColor(playerid, TextMenuBody[playerid], 50);
	PlayerTextDrawUseBox(playerid, TextMenuBody[playerid], 1);
	PlayerTextDrawSetProportional(playerid, TextMenuBody[playerid], 1);
	return 1;
}

hook OnPlayerText(playerid, text[]) {
    if(TextMenuState[playerid]) {
        if(TextMenuItemCount[playerid] != 0) {
            if(isnumeric(text)) {
				new value = strval(text);
			    if(value > 0 && value <= TextMenuItemCount[playerid]) {

					if(!isnull(TextMenuCallbackHandler[playerid])) {

						TextMenuState[playerid] = false;
						TextMenuItemCount[playerid] = 0;
						TextMenuItems[playerid][0] = EOS;
						PlayerTextDrawHide(playerid, TextMenuHeader[playerid]);
						PlayerTextDrawHide(playerid, TextMenuBody[playerid]);

						CallLocalFunction(TextMenuCallbackHandler[playerid], "ii", playerid, value);
						return ~0; // stop the hook from caryying on and don't show the input to players.
					} else {
						Logger_Log("ui_tdmenu.inc - SEVERE! - empty string passed to CallLocalFunction.");
					}
			    }
			}
        }
    }
    return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
 	    if(TextMenuState[playerid]) {
	  		if(newkeys == KEY_NO) {
				TextMenu_Hide(playerid);
			}
		}
		if(TextInfoState[playerid]) {
			if(newkeys == KEY_NO) {
				TextInfo_Hide(playerid);
			}
		}
	}
	return 1;
}

// returns
// - 0 if playerid is invalid.
// - total items.
stock TextMenu_Add(playerid, const item[]) {

	if(!IsPlayerConnected(playerid)) {
		return 0;
	}

	new tempString[128];
	// layout e.g (1. Deagle)
	TextMenuItemCount[playerid] ++;
	format(tempString, sizeof(tempString), "_~r~%i. ~w~%s~n~", TextMenuItemCount[playerid], item);
	strcat(TextMenuItems[playerid], tempString, sizeof(TextMenuItems[]));
	return TextMenuItemCount[playerid];
}

// returns
// - 0 if player is invalid.
// - 1 success
stock TextMenu_Create(playerid, const callback[], const title[]) {
	if(!IsPlayerConnected(playerid)) {
		return 0;
	}

	// Just to make sure everything is fresh everytime we create
	// a new  Text Menu.
	TextMenu_Hide(playerid);
	TextInfo_Hide(playerid);

	strcpy(TextMenuCallbackHandler[playerid], callback, 32);

	new tempString[35];
	format(tempString, sizeof(tempString), "~y~%s", title);
    PlayerTextDrawSetString(playerid, TextMenuHeader[playerid], tempString);
	return 1;
}

// returns
// - 0 if player is invalid.
// - 1 success
stock TextMenu_Show(playerid)
{
	if(!IsPlayerConnected(playerid)) {
		return 0;
	}

	//~n~_1. Option~n~
	//~n~~n~
	//_____~w~Press ~y~T~w~ or ~y~F6~w~ and choose option~n~
	//_________Press ~y~N~w~ to close this box~n~

	new
		string[1024];
    format(string, sizeof(string), "\
		~n~\
		%s \
		~n~ \
		_____~w~Press ~y~T~w~ or ~y~F6~w~ and choose option~n~ \
		_________Press ~y~N~w~ to close this box \
		~n~~n~ \
		", TextMenuItems[playerid]
	);
	PlayerTextDrawSetString(playerid, TextMenuBody[playerid], string);

	PlayerTextDrawShow(playerid,TextMenuHeader[playerid]);
	PlayerTextDrawShow(playerid,TextMenuBody[playerid]);

	TextMenuState[playerid] = true;
	return 1;
}

// returns
// - 0 if player is invalid or trying to hide a menu when hithere isn't shown.
// - 1 success
stock TextMenu_Hide(playerid)
{
	if(!IsPlayerConnected(playerid)) {
		return 0;
	}

	if(!TextMenuState[playerid]) {
		return 0;
	}

	TextMenuCallbackHandler[playerid][0] = EOS;
	TextMenuState[playerid] = false;
	TextMenuItemCount[playerid] = 0;
	TextMenuItems[playerid][0] = EOS;
	PlayerTextDrawHide(playerid,TextMenuHeader[playerid]);
	PlayerTextDrawHide(playerid,TextMenuBody[playerid]);
	return 1;
}


// returns
// - 0 if player is invalid.
// - 1 success
stock TextMenu_HideSpecific(playerid, const callback[]) {

	if(!strcmp(TextMenuCallbackHandler[playerid], callback)) {
		if(TextMenu_Hide(playerid)) {
			return 1;
		}
	}
	return 0;
}

stock TextInfo_Add(playerid, const text[]) {
	if(!IsPlayerConnected(playerid)) {
		return 0;
	}
	new tempString[128];
	format(tempString, sizeof(tempString), "_%s~n~", text);
	strcat(TextMenuItems[playerid], tempString, sizeof(TextMenuItems[]));
	return 1;
}

stock TextInfo_Create(playerid, const intname[], const title[]) {
	if(!IsPlayerConnected(playerid)) {
		return 0;
	}

	TextMenu_Hide(playerid);
    TextInfo_Hide(playerid);

	strcpy(TextInfoNameHandler[playerid], intname, 32);

	new tempString[35];
	format(tempString, sizeof(tempString), "~y~%s", title);
	PlayerTextDrawSetString(playerid, TextMenuHeader[playerid], tempString);
	return 1;
}

stock TextInfo_Show(playerid)
{
	if(!IsPlayerConnected(playerid)) {
		return 0;
	}

	new
		string[1024];
	format(string, sizeof(string), "~n~\
		%s \
		~n~ \
		_________Press ~y~N~w~ to close this box \
		~n~~n~ \
		",
		TextMenuItems[playerid]
	);
	PlayerTextDrawSetString(playerid, TextMenuBody[playerid], string);

	PlayerTextDrawShow(playerid,TextMenuHeader[playerid]);
	PlayerTextDrawShow(playerid,TextMenuBody[playerid]);

	TextInfoState[playerid] = true;
	return 1;
}

stock TextInfo_Hide(playerid)
{
	if(!IsPlayerConnected(playerid)) {
		return 0;
	}

	if(!TextInfoState[playerid]) {
		return 0;
	}

	TextInfoNameHandler[playerid][0] = EOS;
	TextInfoState[playerid] = false;
	TextMenuItems[playerid][0] = EOS;
	PlayerTextDrawHide(playerid,TextMenuHeader[playerid]);
	PlayerTextDrawHide(playerid,TextMenuBody[playerid]);
	return 1;
}

stock TextInfo_HideSpecific(playerid, const intname[]) {

	if(!strcmp(TextInfoNameHandler[playerid], intname)) {
		if(TextInfo_Hide(playerid)) {
			return 1;
		}
	}
	return 0;
}