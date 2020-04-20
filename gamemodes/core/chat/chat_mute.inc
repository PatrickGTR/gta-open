#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_hooks>

static 
BitArray: ply_mute<MAX_PLAYERS>,
   Timer: ply_mutetimer[MAX_PLAYERS],
          ply_muteDuration[MAX_PLAYERS]
;

hook OnPlayerDisconnect(playerid, reason)
{
    Mute_ToggleForPlayer(playerid, false);
    return 1;
} 

// Toggles on/off the mute for player
// return n/a
Mute_ToggleForPlayer(playerid, bool:toggle, seconds = -1)
{
    if (toggle)
    {
        Bit_Let(ply_mute, playerid);
        if (seconds > 0)
        {
            stop ply_mutetimer[playerid];

            ply_muteDuration[playerid] = seconds;
        	ply_mutetimer[playerid] = defer UnmuteTimer(playerid, 1000 * seconds);
        }
    }
    else 
    {  
        Bit_Vet(ply_mute, playerid);
        ply_muteDuration[playerid] = 0;
        stop ply_mutetimer[playerid];
    }
}

// check if player is muted
// return true if player is muted otherwise false.
Mute_PlayerHas(playerid) 
    return (Bit_Get(ply_mute, playerid));

// returns how long the player is muted for in seconds.
Mute_GetPlayerDuration(playerid) 
    return (ply_muteDuration[playerid]);

timer UnmuteTimer[seconds](playerid, seconds)
{   
    #pragma unused seconds
    Bit_Vet(ply_mute, playerid);
    ply_muteDuration[playerid] = 0;
}
