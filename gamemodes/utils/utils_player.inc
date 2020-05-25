
static 
    lastDrunkLevel[MAX_PLAYERS],
    currFPS[MAX_PLAYERS];

GetPlayerFPS(playerid) {
    new playerDrunkLevel = GetPlayerDrunkLevel(playerid);

    if(playerDrunkLevel < 100)
    {
        SetPlayerDrunkLevel(playerid, 2000);
    }
    else
    {
        if(lastDrunkLevel[playerid] != playerDrunkLevel)
        {
            currFPS[playerid] = (lastDrunkLevel[playerid] - playerDrunkLevel);

            lastDrunkLevel[playerid] = playerDrunkLevel;
            if((currFPS[playerid] > 0) && (currFPS[playerid] < 256))
            {
                return currFPS[playerid] - 1;
            }
        }
    }
    return 0;
}

Player_IsInAmmu(playerid) 
{
    if(GetPlayerVirtualWorld(playerid) == 7 || GetPlayerVirtualWorld(playerid) == 8) {
        new const ammunationInteriors[] = {
            1, 4, 6, 7
        };
        for(new i = 0; i < sizeof(ammunationInteriors); i ++) {
            if(GetPlayerInterior(playerid) == ammunationInteriors[i]) {
                return 1;
            }
        }
    }
    return 0;
}
