#include <YSI_Coding\y_hooks>

#define MAX_WEED_PLANT_PER_PLAYER	(5)

static
	weedObject[MAX_PLAYERS][MAX_WEED_PLANT_PER_PLAYER],
	weedPercent[MAX_PLAYERS][MAX_WEED_PLANT_PER_PLAYER],
	Text3D:weedLabel[MAX_PLAYERS][MAX_WEED_PLANT_PER_PLAYER],
	Float:weedObjectPosX[MAX_PLAYERS][MAX_WEED_PLANT_PER_PLAYER],
	Float:weedObjectPosY[MAX_PLAYERS][MAX_WEED_PLANT_PER_PLAYER],
	Float:weedObjectPosZ[MAX_PLAYERS][MAX_WEED_PLANT_PER_PLAYER],
	Iterator:weedIndex[MAX_PLAYERS]<MAX_WEED_PLANT_PER_PLAYER>,
	Timer:weedTimer[MAX_PLAYERS][MAX_WEED_PLANT_PER_PLAYER];

hook OnPlayerDisconnect(playerid, reason) {
	for(new i = 0; i < MAX_WEED_PLANT_PER_PLAYER; i++) {
		Weed_ResetData(playerid, i);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

// FUNCTIONS //

Weed_Create(playerid, Float:x, Float:y, Float:z)
{
	new
		slot;

	slot = Iter_Free(weedIndex[playerid]);

	if (Iter_Count(weedIndex[playerid]) == MAX_WEED_PLANT_PER_PLAYER)
		return SendErrorMsg(playerid, "You have reached the maximum weed you could plant!");

	weedPercent[playerid][slot] 	= 0;
	weedObjectPosX[playerid][slot] 	= x;
	weedObjectPosY[playerid][slot] 	= y;
	weedObjectPosZ[playerid][slot] 	= z;

	weedObject[playerid][slot] 		= CreateDynamicObject(19473, x, y, z - 2.2, 0, 0, 0);
	weedLabel[playerid][slot] 		= CreateDynamic3DTextLabelEx("[CANNABIS PLANT]\n"C_GREY"0% "C_WHITE"out of "C_GREY"100%", COLOR_YELLOW, x, y, z, 100.0, .testlos = 0);

	weedTimer[playerid][slot] 		= repeat OnWeedGrow(playerid, slot);

	Iter_Add(weedIndex[playerid], slot);
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0 , 0, 0, 0, 0, 1);

	SendMsgF(playerid, COLOR_GREEN, "** WEED PLANT ** "C_WHITE"You have planted your weed - You could plant "C_GREY"%i "C_WHITE"more cannabis plant.", MAX_WEED_PLANT_PER_PLAYER - Iter_Count(weedIndex[playerid]));
	return slot;
}


Weed_ResetData(playerid, slot)
{
	DestroyDynamic3DTextLabel(weedLabel[playerid][slot]);
	DestroyDynamicObject(weedObject[playerid][slot]);

	weedObjectPosX[playerid][slot]		= 0.0;
	weedObjectPosY[playerid][slot]		= 0.0;
	weedObjectPosZ[playerid][slot]		= 0.0;

	weedObject[playerid][slot] 			= INVALID_OBJECT_ID;
	weedLabel[playerid][slot] 			= Text3D:INVALID_3DTEXT_ID;
	weedPercent[playerid][slot] 		= -1;

	Iter_Remove(weedIndex[playerid], slot);
}

Weed_GetClosest(playerid) {
	foreach(new i : weedIndex[playerid]) {
		if(IsPlayerInRangeOfPoint(playerid, 2, weedObjectPosX[playerid][i], weedObjectPosY[playerid][i], weedObjectPosZ[playerid][i])) {
			return i;
		}
	}
	return -1;
}

timer OnWeedGrow[1000 * 30](playerid, slot) { // 5 minutes to fully grow.

	if(weedPercent[playerid][slot] >= 100){
		UpdateDynamic3DTextLabelText(weedLabel[playerid][slot], COLOR_YELLOW, "[CANNABIS PLANT]\n"C_WHITE"Ready to be harvested!");
		stop weedTimer[playerid][slot];
		return 1;
	}

	new
		Float:null,
		Float:z;

	GetDynamicObjectPos(weedObject[playerid][slot], null, null, z);

	weedObjectPosZ[playerid][slot] = z + 0.0666;

	SetDynamicObjectPos(weedObject[playerid][slot],
		weedObjectPosX[playerid][slot],
		weedObjectPosY[playerid][slot],
		weedObjectPosZ[playerid][slot]);

    new
        string[64];

    format(string, sizeof(string), "[CANNABIS PLANT]\n"C_GREY"%i%% "C_WHITE"out of "C_GREY"100%", weedPercent[playerid][slot]);
	UpdateDynamic3DTextLabelText(weedLabel[playerid][slot], COLOR_YELLOW, string);
	weedPercent[playerid][slot] += 10;
	return 1;
}

Weed_GetPercent(playerid, slot) {
	return weedPercent[playerid][slot];
}
