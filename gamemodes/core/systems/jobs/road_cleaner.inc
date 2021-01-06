#include <YSI_Coding\y_hooks>

const
	ROAD_TRASH = 2672,
	SWEEPER_REWARD = 230;

// TODO:
// - Make it 3D Array
// - Add different routes! and randomise At the moment..
// there's only 1 route and could get boring after a while/
static
	 const Float:sweep_trash[13][3] = {
	{1659.9645, -1546.2712, 12.8828},
	{1700.1971, -1521.2524, 12.8828},
	{1676.4901, -1480.0886, 12.8828},
	{1629.0006, -1440.8375, 12.8828},
	{1537.6647, -1440.2332, 12.8828},
	{1448.3813, -1493.9938, 12.8734},
	{1429.2347, -1593.0725, 12.8906},
	{1428.9891, -1648.4590, 12.8828},
	{1475.9382, -1732.1252, 12.8828},
	{1638.1144, -1733.0811, 12.8828},
	{1689.3230, -1675.0255, 12.8828},
	{1659.0182, -1566.2804, 12.8906},
	{1656.9946, -1546.1586, 12.8828}
};

new
	SweeperObject[MAX_PLAYERS],
	PlayerSweepCount[MAX_PLAYERS],
	SweeperCheckpoint[MAX_PLAYERS],
	bool:PlayerStartedSweeping[MAX_PLAYERS],
	SweeperCommandTick[MAX_PLAYERS];

bool:IsSweepVeh(vehicleid) {
	new
		modelid = GetVehicleModel(vehicleid);
	return (modelid == 574);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(PRESSED(KEY_SUBMISSION)) {
		if(IsPlayerInAnyVehicle(playerid) && Player_GetClass(playerid) == TEAM_CIVILIAN) {
			new
				vehicleid = GetPlayerVehicleID(playerid);
			if(IsSweepVeh(vehicleid)) {
				if(!PlayerStartedSweeping[playerid]) {
					if(gettime() - SweeperCommandTick[playerid] < 180) {
						SendErrorMsgF(
							playerid,
							"Please wait %d seconds before starting sweeper side job again!",
							gettime() - SweeperCommandTick[playerid]
						);
					}

					SendClientMessage(
						playerid,
						COLOR_ORANGE,
						"(sweeper job) "C_WHITE"You have started sweeper job. Move to the checkpoint to clear the road!"
					);

					PlayerSweepCount[playerid] = 0;
					SweeperCommandTick[playerid] = gettime();
					PlayerStartedSweeping[playerid] = true;

					SweeperObject[playerid] = CreateDynamicObject(
						ROAD_TRASH,
						sweep_trash[PlayerSweepCount[playerid]][0],
						sweep_trash[PlayerSweepCount[playerid]][1],
						sweep_trash[PlayerSweepCount[playerid]][2],
						0, 0, 0, .playerid = playerid
					);

					SweeperCheckpoint[playerid] = CreateDynamicRaceCP(
						0,
						sweep_trash[PlayerSweepCount[playerid]][0],
						sweep_trash[PlayerSweepCount[playerid]][1],
						sweep_trash[PlayerSweepCount[playerid]][2],
						sweep_trash[PlayerSweepCount[playerid] +1][0],
						sweep_trash[PlayerSweepCount[playerid] +1][1],
						sweep_trash[PlayerSweepCount[playerid] +1][2],
						6.0, .playerid = playerid, .streamdistance = 400.0
					);

				}
				else {
					PlayerStartedSweeping[playerid] = false;
					PlayerSweepCount[playerid] = 0;
					DestroyDynamicRaceCP(SweeperCheckpoint[playerid]);
					DestroyDynamicObject(SweeperObject[playerid]);
					SendServerMsg(playerid, "You have cancelled the sweeper job!");
				}
			}
		}
	}
	return true;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
	if(newstate == PLAYER_STATE_DRIVER) {
		new
			vehicleid = GetPlayerVehicleID(playerid);
		if(IsSweepVeh(vehicleid) && Player_GetClass(playerid) == TEAM_CIVILIAN) {
			if(!PlayerStartedSweeping[playerid]) {
				GameTextForPlayer(playerid, "~w~Press ~y~~k~~TOGGLE_SUBMISSIONS~~w~ to start Sweeper job", 3000, 3);
			}
			else {
				GameTextForPlayer(playerid, "~w~Press ~y~~k~~TOGGLE_SUBMISSIONS~~w~ to stop Sweeper job", 3000, 3);
			}
		}
	}
	else {
		if(PlayerStartedSweeping[playerid]) {
			DestroyDynamicObject(SweeperObject[playerid]);
			DestroyDynamicRaceCP(SweeperCheckpoint[playerid]);
			PlayerStartedSweeping[playerid] = false;
			SweeperObject[playerid] = -1;
			SendServerMsg(playerid, "Your sweeper side job has been automatically been cancelled!");
		}
	}

	return true;

}
hook OnPlayerDeathEx(playerid, killerid, reason, Float: damage, bodypart) {
	if(PlayerStartedSweeping[playerid]) {
		PlayerStartedSweeping[playerid] = false;
		PlayerSweepCount[playerid] = 0;
		DestroyDynamicRaceCP(SweeperCheckpoint[playerid]);
		DestroyDynamicObject(SweeperObject[playerid]);
	}
	return true;
}


hook OnPlayerDisconnect(playerid, reason) {
	if(PlayerStartedSweeping[playerid]) {
		PlayerStartedSweeping[playerid] = false;
		PlayerSweepCount[playerid] = 0;
		DestroyDynamicRaceCP(SweeperCheckpoint[playerid]);
		DestroyDynamicObject(SweeperObject[playerid]);
	}
	return true;
}

hook OnPlayerEnterDynRaceCP(playerid, checkpointid) {
	if(checkpointid == SweeperCheckpoint[playerid] && PlayerStartedSweeping[playerid]) {
		new
			string[64];
		format(string, sizeof(string), "~n~~n~~n~~n~~w~Great work! Reward: %m.", SWEEPER_REWARD);
		GameTextForPlayer(playerid, string , 3000, 3);

		GivePlayerMoney(playerid, SWEEPER_REWARD);
		if(PlayerSweepCount[playerid] >= 11) {
			PlayerSweepCount[playerid] = 0;
			DestroyDynamicRaceCP(SweeperCheckpoint[playerid]);
			DestroyDynamicObject(SweeperObject[playerid]);
			SweeperObject[playerid] = CreateDynamicObject(ROAD_TRASH, sweep_trash[PlayerSweepCount[playerid]][0],sweep_trash[PlayerSweepCount[playerid]][1], sweep_trash[PlayerSweepCount[playerid]][2], 0, 0, 0, .playerid = playerid);
			SweeperCheckpoint[playerid] = CreateDynamicRaceCP(0, sweep_trash[PlayerSweepCount[playerid]][0],sweep_trash[PlayerSweepCount[playerid]][1], sweep_trash[PlayerSweepCount[playerid]][2], sweep_trash[PlayerSweepCount[playerid]+1][0],sweep_trash[PlayerSweepCount[playerid]+1][1], sweep_trash[PlayerSweepCount[playerid]+1][2],  6.0, .playerid = playerid, .streamdistance = 400.0);
		}
		else {
			PlayerSweepCount[playerid] ++;
			DestroyDynamicRaceCP(SweeperCheckpoint[playerid]);
			DestroyDynamicObject(SweeperObject[playerid]);
			SweeperObject[playerid] = CreateDynamicObject(ROAD_TRASH, sweep_trash[PlayerSweepCount[playerid]][0],sweep_trash[PlayerSweepCount[playerid]][1], sweep_trash[PlayerSweepCount[playerid]][2], 0, 0, 0, .playerid = playerid);
			SweeperCheckpoint[playerid] = CreateDynamicRaceCP(0, sweep_trash[PlayerSweepCount[playerid]][0],sweep_trash[PlayerSweepCount[playerid]][1], sweep_trash[PlayerSweepCount[playerid]][2], sweep_trash[PlayerSweepCount[playerid]+1][0],sweep_trash[PlayerSweepCount[playerid]+1][1], sweep_trash[PlayerSweepCount[playerid]+1][2],  6.0, .playerid = playerid, .streamdistance = 400.0);

		}
	}
	return true;
}