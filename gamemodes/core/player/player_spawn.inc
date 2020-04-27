#include <YSI_Coding\y_hooks>

static const Float:LS_SpawnPoints[][] = {
	{810.63520, -1340.0682, 13.5386, 37.33070},
	{1124.6071, -1427.5155, 15.7969, 350.9336},
	{585.81520, -1247.9160, 17.9521, 335.6035},
	{2025.2626, -1423.2682, 16.9922, 135.4516},
	{2509.2468, -1679.2029, 13.5469, 50.24740},
	{1457.1467, -1011.7307, 26.8438, 51.79910},
	{2017.8206, -1279.4851, 23.9820, 47.38920},
	{1935.7644, -1794.6068, 13.5469, 295.5515},
	{1371.4569, -1090.6387, 24.5459, 92.84640},
	{2298.4055, -1500.3264, 25.3047, 199.6940},
	{1178.0417, -1323.6000, 14.1005, 285.5701},
	{1757.44350, -1456.7, 13.5469, 282.4133}
};

static 
    PlayerLastSpawn[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerLastSpawn[playerid] = -1;
	return 1;
}

Player_RandomSpawn(playerid) {
	new id = random(sizeof(LS_SpawnPoints));

    if(id == PlayerLastSpawn[playerid]) {
        // regen new id
        id = random(sizeof(LS_SpawnPoints));
		dbg("player", "regenerating new spawnid for player.", 
			_p("username", playerid), 
			_i("id", playerid)
		);
    }

	new 
		Float:x = LS_SpawnPoints[id][0], 
		Float:y = LS_SpawnPoints[id][1], 
		Float:z = LS_SpawnPoints[id][2]; 

	SetPlayerPos(playerid, x, y, z);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);

    PlayerLastSpawn[playerid] = id;

	dbg("player", "player random spawned", 
		_p("username", playerid), 
		_i("id", playerid), 
		_f("x", x),
		_f("y", y), 
		_f("z", z)
	);
    return 1;
}
