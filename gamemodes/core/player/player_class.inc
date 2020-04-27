#include <YSI_Coding\y_hooks>

static 
    PlayerClass[MAX_PLAYERS];

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
}

hook OnPlayerConnect(playerid) {
    PlayerClass[playerid] = -1;
	return 1;
}

stock Player_SetClass(playerid, classid) {
    PlayerClass[playerid] = classid;
	return 1;
}

stock Player_GetClass(playerid) {
    return PlayerClass[playerid];
}