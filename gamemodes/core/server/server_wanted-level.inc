// Server sided wanted level.
// Author: PatrickGTR (28/04/2020)

#include <YSI_Coding\y_hooks>

const
    MAX_WANTED_LEVEL = 1024;

static
    PlayerWantedLevel[MAX_PLAYERS];

// Purpose:
// to return the server-sided wanted level instead of the client side.
stock PLAYER_GetPlayerWantedLevel(playerid) {
	return PlayerWantedLevel[playerid];
}

#if defined _ALS_GetPlayerWantedLevel
    #undef GetPlayerWantedLevel
#else
    #define _ALS_GetPlayerWantedLevel
#endif

#define GetPlayerWantedLevel PLAYER_GetPlayerWantedLevel

stock PLAYER_SetPlayerWantedLevel(playerid, plevel) {

    // we do not allow negative value.
    if(plevel < 0) {
       plevel = 0;
    }

    // if player goes above the limit then
    // we put his wanted level back to the limit.
    if(plevel > MAX_WANTED_LEVEL) {
        plevel = MAX_WANTED_LEVEL;
    }

    PlayerWantedLevel[playerid] = plevel;
    UI_UpdatePlayerWanted(playerid, plevel);
    Player_UpdateColour(playerid);
    Player_SaveWantedLevel(playerid, plevel);
	return SetPlayerWantedLevel(playerid, plevel);
}

#if defined _ALS_SetPlayerWantedLevel
    #undef SetPlayerWantedLevel
#else
    #define _ALS_SetPlayerWantedLevel
#endif

#define SetPlayerWantedLevel PLAYER_SetPlayerWantedLevel

// wrapper - change function name for consistency.
stock Player_GetWantedLevel(playerid) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    return GetPlayerWantedLevel(playerid);
}

stock Player_GiveWantedLevel(playerid, plevel)  {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }
    new
        currentLevel = Player_GetWantedLevel(playerid),
        newLevel = currentLevel + plevel;

    SetPlayerWantedLevel(playerid, newLevel);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason) {
    SetPlayerWantedLevel(playerid, 0);
    return 1;
}
