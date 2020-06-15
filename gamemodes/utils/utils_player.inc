
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
    if(GetPlayerVirtualWorld(playerid) == 6 || GetPlayerVirtualWorld(playerid) == 7) {
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

Float:Player_GetArmour(playerid) {
    new
        Float:playerArmour;

    GetPlayerArmour(playerid, playerArmour);
    return playerArmour;
}

stock Player_GetClosestWanted(playerid) {
    new
        closestID = INVALID_PLAYER_ID;

    foreach(new i : Player) {

        if(playerid == i) {
            continue;
        }

        if(Player_IsNearPlayer(playerid, i, 4.0) && Player_GetWantedLevel(i) >= 3) {
            closestID = i;
            break;
        }
    }
    return closestID;
}

stock Player_IsNearPlayer(playerid, targetid, Float:radius)
{
	new
        Float:x,
        Float:y,
        Float:z;

	GetPlayerPos(playerid, x, y, z);

    new
        matchingVW = GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid),
        matchingInt = GetPlayerInterior(playerid) == GetPlayerInterior(targetid),
        inRange = IsPlayerInRangeOfPoint(targetid, radius, x, y, z);

	return matchingVW && matchingInt && inRange;
}