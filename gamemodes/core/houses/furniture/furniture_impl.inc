#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
	// Reset
	Furniture_DeleteTemporary(playerid);
	return 1;
}

enum E_EDITING_STATE
{
	INVALID_EDITING_TYPE = -1,
	TYPE_EDITING_FURNITURE,
	TYPE_BUYING_FURNITURE,
    TYPE_DELETING_FURNITURE
}

static
	E_EDITING_STATE:g_playerEditingType[MAX_PLAYERS] = {INVALID_EDITING_TYPE, ...},
	g_tmpPlayerObjID[MAX_PLAYERS] = {INVALID_OBJECT_ID, ...},
BitArray: PlayerFurnitureMode<MAX_PLAYERS>;

new
          g_tmpPlayerIndexID[MAX_PLAYERS] = {-1, ...};

Furniture_SetEditingState(playerid, E_EDITING_STATE:status) {
	g_playerEditingType[playerid] = status;
}

E_EDITING_STATE:Furniture_GetEditingState(playerid) {
	return E_EDITING_STATE:g_playerEditingType[playerid];
}

Player_SetFurnitureMode(playerid, bool:status) {
    Bit_Set(PlayerFurnitureMode, playerid, status);
}

Player_IsOnFurnitureMode(playerid) {
    return (Bit_Get(PlayerFurnitureMode, playerid));
}

static _FurnitureTypeDialog(playerid, page) {
	new
		tmp_string[128],
		big_string[2048];


	for(new i = 0; i < Furniture_GetArraySize(); i++) {
		if(Furniture_GetType(i)  != page) {
			continue;
		}

		format(tmp_string, sizeof(tmp_string), "%i(0.0, 0.0, 0.0, 1.5, 0, 6)\t~w~%s:%s%m\n",
			Furniture_GetObjectID(i),
			Furniture_GetName(i),
			((GetPlayerMoney(playerid) < Furniture_GetPrice(i)) ? ("~r~") : ("~g~")),
			Furniture_GetPrice(i)
		);
		strcat(big_string, tmp_string);

	}

	inline const _response(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, inputtext, dialogid, listitem
		if(!response) {
			return Furniture_ShowDialog(playerid);
        }

		new
			objectid = strval(inputtext),
			index = 0;

		for(new i = 0; i < Furniture_GetArraySize(); i++) {
			if (Furniture_GetObjectID(i) == objectid) {
				index = i;
				break;
			}
		}

		Furniture_Buy(playerid, index);
	}

	Dialog_ShowCallback(
		playerid,
		using inline _response,
		DIALOG_STYLE_PREVIEW_MODEL,
		"Furniture Shop - Choose Furniture",
		big_string,
		"Select",
		"Go back"
	);
	return 1;
}


Furniture_ShowDialog(playerid) {
    inline DialogFurnitureType(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext

        if (!response) {
        	return SendServerMsg(playerid, "Furniture Type Dialog, closed.");
        }

        _FurnitureTypeDialog(playerid, listitem);
    }

    Dialog_ShowCallback(playerid, using inline DialogFurnitureType,
        DIALOG_STYLE_LIST,
        "Furniture Type", // Title
        "Appliances\n\
        Bathroom\n\
        Bedroom\n\
        Carpet\n\
        Kitchen\n\
        Tables\n\
        Chairs\n\
        Poster/Frames\n\
        Storage\n\
        Plants\n\
        Trash\n\
        Door/Gates\n\
        Walls\n\
        Decors",
        "Select",   // BTN 1
        "Close"     // BTN 2
    );
    return 1;
}

Furniture_Create(furnitureID, houseID, modelId, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw, int) {
  	new
  		tmp_objectid = CreateDynamicObject(modelId, x, y, z, rx, ry, rz, vw, int),
  		arr[2];

    arr[0] = houseID;
    arr[1] = furnitureID;

	return Streamer_SetArrayData(STREAMER_TYPE_OBJECT, tmp_objectid, E_STREAMER_EXTRA_ID, arr);
}

Furniture_Delete(houseID, furnitureID) {
	new
		Statement: stmt_deleteFurniture;

	static const deleteQuery[] = "\
		DELETE FROM \
			house_furniture \
		WHERE \
			furniture_id = ? \
		AND \
			house_id = ? \
	";
	stmt_deleteFurniture = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);

	MySQL_BindInt(stmt_deleteFurniture, 0, furnitureID);
	MySQL_BindInt(stmt_deleteFurniture, 1, houseID);
	MySQL_ExecuteThreaded(stmt_deleteFurniture);
	MySQL_StatementClose(stmt_deleteFurniture);

}

Furniture_DeleteTemporary(playerid) {
	if(g_tmpPlayerObjID[playerid] != INVALID_OBJECT_ID) {
		DestroyDynamicObject(g_tmpPlayerObjID[playerid]);
	}

	g_tmpPlayerObjID[playerid] = INVALID_OBJECT_ID;
	g_tmpPlayerIndexID[playerid] = -1;
	Furniture_SetEditingState(playerid, INVALID_EDITING_TYPE);
	Player_SetFurnitureMode(playerid, false);
}

// --
// Internal
// --

static Furniture_Buy(playerid, index) {
	new
        Float: x,
        Float: y,
        Float: z,
	    Float: a;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	g_tmpPlayerObjID[playerid] = CreateDynamicObject(Furniture_GetObjectID(index), x + 2.0 * floatsin(-a, degrees), y + 2.0 * floatcos(-a, degrees), z + 1.0, 0.0, 0.0, a, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    g_tmpPlayerIndexID[playerid] = index;
	Furniture_SetEditingState(playerid, TYPE_BUYING_FURNITURE);
    Player_SetFurnitureMode(playerid, true);

	SendMsgF(playerid, COLOR_YELLOW, "** FURNITURE ** "C_WHITE"You are now looking at furniture "C_GREY"%s"C_WHITE". This item costs "C_GREEN"$%i", Furniture_GetName(index), Furniture_GetPrice(index));
	SendMsgF(playerid, COLOR_YELLOW, "** FURNITURE ** "C_WHITE"Use your cursor to control the editor interface. Click the floppy disk to save changes.");
    EditDynamicObject(playerid, g_tmpPlayerObjID[playerid]);
}