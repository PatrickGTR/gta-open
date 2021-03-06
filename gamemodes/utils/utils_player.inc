
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

stock bool:RandomChance(percentage) {
	return (percentage >= random(100) + 1);
}

Player_IsLEO(playerid) {
    return (Player_GetClass(playerid) == TEAM_POLICE || Player_GetClass(playerid) == TEAM_ARMY);
}

// Player_IsInAmmu(playerid)
// {
//     if(GetPlayerVirtualWorld(playerid) == 6 || GetPlayerVirtualWorld(playerid) == 7) {
//         new const ammunationInteriors[] = {
//             1, 4, 6, 7
//         };
//         for(new i = 0; i < sizeof(ammunationInteriors); i ++) {
//             if(GetPlayerInterior(playerid) == ammunationInteriors[i]) {
//                 return 1;
//             }
//         }
//     }
//     return 0;
// }

Float:Player_GetArmour(playerid) {
    new
        Float:playerArmour;

    GetPlayerArmour(playerid, playerArmour);
    return playerArmour;
}

stock Player_FacePlayer(playerid, giveplayerid) {
    // function made by Nero_3D.
    new
        Float: pX,
        Float: pY,
        Float: pZ,
        Float: gX,
        Float: gY,
        Float: gZ
    ;
    if(GetPlayerPos(playerid, pX, pY, pZ) && GetPlayerPos(giveplayerid, gX, gY, gZ)) {
        SetPlayerFacingAngle(playerid, (pX = -atan2((gX - pX), (gY - pY))));
        return SetPlayerFacingAngle(giveplayerid, (pX + 180.0));
    }
    return false;
}

stock Player_GetClosestWanted(playerid, Float:dist = 30.0) {
    new
        closestID = INVALID_PLAYER_ID;

    foreach(new i : Player) {

        if(playerid == i) {
            continue;
        }

        if(Player_GetClosestPlayer(playerid, dist) && Player_GetWantedLevel(i) >= 3) {
            closestID = i;
            break;
        }
    }
    return closestID;
}

Player_GetClosestLeo(playerid, Float:dist = 30.0) {
    new
        closestID = INVALID_PLAYER_ID;

    foreach(new i : Player) {

        if(playerid == i) {
            continue;
        }

        if(Player_GetClosestPlayer(playerid, dist) && Player_IsLEO(i)) {
            closestID = i;
            break;
        }
    }
    return closestID;
}

Player_IsNearPlayer(playerid, targetid, Float:radius)
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

Player_GetClosestPlayer(playerid, Float:range = 10000.0)
{
    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(playerid, x, y, z);

    return GetClosestPlayerFromPoint(x, y, z, range, playerid);
}

GetClosestPlayerFromPoint(Float:x, Float:y, Float:z, &Float:lowestdistance = 10000.0, exceptionid = INVALID_PLAYER_ID)
{
    new
        Float:px,
        Float:py,
        Float:pz,
        Float:distance,
        closestplayer = -1;

    foreach(new i : Player)
    {
        if (i == exceptionid)
            continue;

        GetPlayerPos(i, px, py, pz);

        distance = Distance(px, py, pz, x, y, z);

        if (distance < lowestdistance)
        {
            lowestdistance = distance;
            closestplayer = i;
        }
    }
    return closestplayer;
}