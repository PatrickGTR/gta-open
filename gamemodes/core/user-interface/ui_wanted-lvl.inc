#include <YSI_Coding\y_hooks>

static
    PlayerText: PlayerWantedLevel[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerWantedLevel[playerid] = CreatePlayerTextDraw   (playerid,600.000000, 109.000000, "7");
    PlayerTextDrawAlignment                 (playerid, PlayerWantedLevel[playerid], 2);
    PlayerTextDrawBackgroundColor           (playerid, PlayerWantedLevel[playerid], TD_OUTLINE_COLOUR);
    PlayerTextDrawFont                      (playerid, PlayerWantedLevel[playerid], 1);
    PlayerTextDrawLetterSize                (playerid, PlayerWantedLevel[playerid], 0.230000, 0.899999);
    PlayerTextDrawColor                     (playerid, PlayerWantedLevel[playerid], -1872621313);
    PlayerTextDrawSetOutline                (playerid, PlayerWantedLevel[playerid], 1);
    PlayerTextDrawSetProportional           (playerid, PlayerWantedLevel[playerid], 1);
    PlayerTextDrawSetSelectable             (playerid, PlayerWantedLevel[playerid], 0);
}

hook OnPlayerDisconnect(playerid, reason) {
    PlayerTextDrawHide(playerid, PlayerWantedLevel[playerid]);
}

hook OnPlayerDeath(playerid, killerid, reason) {
    SetPlayerWantedLevel(playerid, 0);
}

static stock UpdatedPlayerWantedLevelTD(playerid, level)
{
    if(level == 0)
    {
        PlayerTextDrawHide(playerid, PlayerWantedLevel[playerid]);
    }
    else
    {
        PlayerTextDrawHide(playerid, PlayerWantedLevel[playerid]);
        PlayerTextDrawShow(playerid, PlayerWantedLevel[playerid]);
    }

    new 
        string[5];
    format(string, sizeof(string), "%d", level);
    PlayerTextDrawSetString(playerid, PlayerWantedLevel[playerid], string);
}

stock ALS_SetPlayerWantedLevel(playerid, level)
{
    UpdatedPlayerWantedLevelTD(playerid, level);
    // TOODO: save wanted level when function is called
    //UpdatePlayerWantedLevelMySQL(playerid, level);
    return SetPlayerWantedLevel(playerid, level);
}
#if defined _ALS_SetPlayerWantedLevel
    #undef SetPlayerWantedLevel
#else
    #define _ALS_SetPlayerWantedLevel
#endif

#define SetPlayerWantedLevel ALS_SetPlayerWantedLevel