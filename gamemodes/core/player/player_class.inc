#include <YSI_Coding\y_hooks>

static
	bool:PlayerFromSelection[MAX_PLAYERS];

hook OnGameModeInit() {
    // Civilian Skin
    AddPlayerClass(56,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(119, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(55,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(60,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(11,  0, 0, 0, 0, 0, 0, 0, 0, 0 , 0);
	AddPlayerClass(2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(299, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(296, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(297, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(294, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(293, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(289, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(272, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(264, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(268, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(259, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(221, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(29,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(22,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(19,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	// Police Officer Skins
	AddPlayerClass(280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(281, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(282, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(283, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(284, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(285, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	// Army Skins
	AddPlayerClass(121, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(287, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Medic Skins
	AddPlayerClass( 274, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass( 275, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass( 276, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 1;
}


static
	Statement: stmt_loadPlayerSkin,
	PlayerSkin[MAX_PLAYERS],
	bool:PlayerClassState[MAX_PLAYERS] = true,
	PlayerClass[MAX_PLAYERS];

hook OnMySQLConnected() {
	stmt_loadPlayerSkin = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT skin FROM player_stats WHERE u_id = ?");
	return 1;
}

hook OnPlayerLogin(playerid) {

	inline const OnSkinLoad() {

		new
			playerSkin;

		MySQL_BindResultInt(stmt_loadPlayerSkin, 0, playerSkin);

		if(MySQL_Statement_FetchRow(stmt_loadPlayerSkin)) {
			PlayerSkin[playerid] = playerSkin;
		}
	}
	MySQL_BindInt(stmt_loadPlayerSkin, 0, Player_GetAccountID(playerid));
	MySQL_ExecuteParallel_Inline(stmt_loadPlayerSkin, using inline OnSkinLoad);

	PlayerClassState[playerid] = false;
	return 1;
}

hook OnPlayerRequestClass(playerid, classid) {

	// F4 Detection.
	// bypass this action if PlayerClassState is set to false.
	// it's true by default.
	if(!Class_SelectionStatus(playerid)) {
		TogglePlayerSpectating(playerid, true);
		defer ForceSpawnPlayer(playerid);

		dbg(PLAYER_DEBUG_HANDLER, "skipping class selection",
			_p("username", playerid)
    	);
	} else {
		SetPlayerPos(playerid, 180.892608, 1830.717895, 23.242187);
		SetPlayerFacingAngle(playerid, 255.810241);
		SetPlayerCameraLookAt(playerid, 180.892608, 1830.717895, 23.242187);
		SetPlayerCameraPos(playerid, 180.892608 + (5 * floatsin(-255.810241, degrees)), 1830.717895 + (5 * floatcos(-255.810241, degrees)), 23.242187);
		UI_ClassSelectionTDShow(playerid);
		if(classid <= 22) {
			SetPlayerColor(playerid, COLOR_WHITE);
			Player_SetClass(playerid, TEAM_CIVILIAN);
			UI_ClassSelectionTDUpdate(playerid, COLOR_WHITE, "Civilian", "- Rob stores and kill players to earn XP.~n~- Show them you run the streets.");
		}
		if(classid >= 23 && classid <= 28) {
			SetPlayerColor(playerid, COLOR_BLUE);
			Player_SetClass(playerid, TEAM_POLICE);
			UI_ClassSelectionTDUpdate(playerid, COLOR_BLUE, "Police", "- Hunt down and arrest criminals for cash and XP.~n~- Bring criminals to justice.");
		}
		if(classid >= 29 && classid <= 31) {
			SetPlayerColor(playerid, COLOR_PURPLE);
			Player_SetClass(playerid, TEAM_ARMY);
			UI_ClassSelectionTDUpdate(playerid, COLOR_PURPLE, "Army", "- Hunt down and arrest criminals for cash and XP.~n~- Access powerful weaponry and machinery to kill criminals.");
		}
		if(classid >= 32 && classid <= 34) {
			SetPlayerColor(playerid, COLOR_GREEN);
			Player_SetClass(playerid, TEAM_MEDIC);
			UI_ClassSelectionTDUpdate(playerid, COLOR_GREEN, "Medic", "- Heal people from diseases, keeping the city clean.");
		}
	}
	return 1;
}

timer void:ForceSpawnPlayer[GetPlayerPing(playerid)](playerid) {

	// using SetSpawnInfo fixes the kick bug when
	// TogglePlayerSpectating is used to force spawn player but without using
	// SetSpawnInfo the server does not know where to spawn the player.
	SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);

	TogglePlayerSpectating(playerid, false);
}

hook OnPlayerRequestSpawn(playerid)
{
	PlayerFromSelection[playerid] = true;
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(!PlayerFromSelection[playerid]) {
		SetPlayerSkin(playerid, PlayerSkin[playerid]);
	}
	if(PlayerFromSelection[playerid]) {
		PlayerSkin[playerid] = GetPlayerSkin(playerid);
		SetPlayerSkin(playerid, PlayerSkin[playerid]);
		PlayerFromSelection[playerid] = false;
	}
	if(GetPlayerSkin(playerid) == 0) {
		SetPlayerSkin(playerid, PlayerSkin[playerid]);
	}
	return 1;
}

hook OnPlayerConnect(playerid) {
	PlayerSkin[playerid] = 0;
    PlayerClass[playerid] = -1;
	PlayerClassState[playerid] = true;
	return 1;
}

stock Class_SelectionStatus(playerid) {
	return PlayerClassState[playerid];
}

stock void:Class_SelectionState(playerid, bool:status) {
	PlayerClassState[playerid] = status;
}

stock Player_GetClassName(playerid) 
{
	new class_ranknames[4][24] = 
	{
		"Civilian",
		"Police",
		"Army",
		"Medic"
	};

	return class_ranknames[Player_GetClass(playerid)];
}

stock void:Player_SetClass(playerid, classid) {
	if(PlayerClass[playerid] != classid) {
		new query[64];

		mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE player_stats SET class_id = %i WHERE u_id = %i", classid, Player_GetAccountID(playerid));
		mysql_tquery(MySQL_GetHandle(), query);
	}
    PlayerClass[playerid] = classid;
}

stock Player_GetClass(playerid) {
    return PlayerClass[playerid];
}

stock Player_SetSkin(playerid, skinid) {
	PlayerSkin[playerid] = skinid;
}

stock Player_GetSkin(playerid) {
	return PlayerSkin[playerid];
}