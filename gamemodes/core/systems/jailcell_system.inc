#include <YSI_Coding\y_hooks>

new
    JailCell1,
    JailCell2,
    bool:JailCellBreached = false;

hook OnGameModeInit() {
    CreateDynamicObject (19302, 266.36240, 85.68930, 1001.29077, 0.00000, 0.00000, 90.00000, 16); //cell 1 left
    JailCell1 = CreateDynamicObject (19302, 266.36240, 87.45930, 1001.29077, 0.00000, 0.00000, 270.00000, 16); //cell 1 right the cell that you might want to move
    CreateDynamicObject (19302, 266.36240, 81.21280, 1001.29077, 0.00000, 0.00000, 90.00000, 16); //cell 2 left
    JailCell2 = CreateDynamicObject (19302, 266.36240, 82.94550, 1001.29077, 0.00000, 0.00000, 270.00000, 16); //cell 2 right the cell that you might want to move
    CreateDynamicObject (19302, 266.36240, 78.46120, 1001.29077, 0.00000, 0.00000, 270.00000, 16);//cell 3 left
    CreateDynamicObject (19302, 266.36240, 76.72040, 1001.29077, 0.00000, 0.00000, 90.00000, 16);//cell  3 right#

	return 1;
}

hook OnPlayerConnect(playerid) {
    RemoveBuildingForPlayer(playerid, 14843, 266.3516, 81.1953, 1001.2813, 0.25);
    return 1;
}

hook OnExplosiveDetonate(playerid, Float: x, Float: y, Float:z) {
	new
		Float:distCompare = Distance(x, y, z, 266.36240, 82.94550, 1001.29077);

	if(distCompare <= 15) {
		if(!LS_OpenCells(playerid)) {
		    defer LSCellClose();
        }
	}
	return 1;
}

timer LSCellClose[1000 * 8]() {
	MoveDynamicObject(JailCell1, 266.36240, 87.45930, 1001.29077, 0.5);
	MoveDynamicObject(JailCell2, 266.36240, 82.94550, 1001.29077, 0.5);
	JailCellBreached = false;
}

 static LS_OpenCells(playerid) {
	if(JailCellBreached)
		return 1;

	foreach(new i : Player) {
		if(Player_IsInJail(i)) {
			Player_ReleaseFromJail(i, false);
			SendMsgF(i, COLOR_RED, "(terrorism) The cell doors have been breached, the doors are open for you to escape! RUN!");
		}
	}
	SendMsgAllF(COLOR_RED, "(terrorism) %p (%i) "C_WHITE"managed to free all the prisoners by planting c4 and detonated it.", playerid, playerid);

	MoveDynamicObject(JailCell1, 266.36240, 86.68930, 1001.29077, 0.5);
    MoveDynamicObject(JailCell2, 266.36240, 82.21280, 1001.29077, 0.5);

	JailCellBreached = true;
	return 0;
}
