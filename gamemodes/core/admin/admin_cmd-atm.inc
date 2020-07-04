#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_iterate>

#define MAX_ATMS 		(100)

// Statements
static
	Statement: stmt_InsertATM,
	Statement: stmt_LoadATM,
	Statement: stmt_ATMExists,
	Statement: stmt_RemoveATM;

// Variables
static
	Iterator: atm_Iter<MAX_ATMS>,
	Text3D: atm_Label[MAX_ATMS],

	AtmID[MAX_ATMS],
	atm_Object[MAX_ATMS],

	Float: AtmPosX[MAX_ATMS],
	Float: AtmPosY[MAX_ATMS],
	Float: AtmPosZ[MAX_ATMS],
	Float: AtmPosA[MAX_ATMS],
    AtmWid[MAX_ATMS],
    AtmInt[MAX_ATMS],
    
    PlayerEditingATMID[MAX_PLAYERS];

// Hooks

hook OnMySQLConnected()
{
	static const insertQuery[] = "\
	INSERT INTO \
		atms (atm_id, atm_x, atm_y, atm_z, atm_a, wid, interior) \
	VALUES \
		(?,?,?,?,?,?,?) \
	";
	stmt_InsertATM = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

	static const loadQuery[] = "\
	SELECT \
		atm_id, \
		atm_x, \
		atm_y, \
		atm_z, \
		atm_a, \
        wid, \
        interior \
	FROM \
		atms \
	";
	stmt_LoadATM = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

	static const checkQuery[] = "\
	SELECT \
		atm_id \
	FROM \
		atms \
	WHERE \
		atm_id = ? \
	";
	stmt_ATMExists = MySQL_PrepareStatement(MySQL_GetHandle(), checkQuery);

	static const deleteQuery[] = "\
    DELETE FROM \
        atms \
    WHERE \
        atm_id = ? \
    ";
    stmt_RemoveATM = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);

	Atm_Load();

	return 1;
}


// Functions

stock Atm_Create(Float: x, Float: y, Float: z, Float: a, wid, int, bool:save = false)
{
	new
		atmID = Iter_Alloc(atm_Iter);

	if (atmID == ITER_NONE) {
		return -1;
	}

	new
		string[50];

	format(string, sizeof string, "(ATM - "C_WHITE"%d"C_ORANGE")", atmID);
	atm_Label[atmID] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, x, y, z, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 30.0, -1, 0);

	atm_Object[atmID] = CreateDynamicObject(19324, x, y, z, 0.0, 0.0, a, wid, int, -1, 300.0);

	AtmID[atmID] = atmID;
	AtmPosX[atmID] = x;
	AtmPosY[atmID] = y;
	AtmPosZ[atmID] = z;
	AtmPosA[atmID] = a;
    AtmWid[atmID] = wid;
    AtmInt[atmID] = int;

	Iter_Add(atm_Iter, atmID);

	if (save) {
		Atm_InsertToDatabase(atmID);
	}

	return atmID;
}

stock Atm_Update(atmID, Float:x, Float:y, Float:z, Float:a, wid, int)
{
    new
		string[50];

	format(string, sizeof string, "(ATM - "C_WHITE"%d"C_ORANGE")", atmID);
    DestroyDynamic3DTextLabel(atm_Label[atmID]);
	atm_Label[atmID] = CreateDynamic3DTextLabel(string, COLOR_ORANGE, x, y, z, 30.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 30.0, -1, 0);

    DestroyDynamicObject(atm_Object[atmID]);
	atm_Object[atmID] = CreateDynamicObject(19324, x, y, z, 0.0, 0.0, a, wid, int, -1, 300.0);

	AtmID[atmID] = atmID;
	AtmPosX[atmID] = x;
	AtmPosY[atmID] = y;
	AtmPosZ[atmID] = z;
	AtmPosA[atmID] = a;
    AtmWid[atmID] = wid;
    AtmInt[atmID] = int;
    new
        string2[256];
    static const query[] = " \
    INSERT INTO \
        atms (atm_id, atm_x, atm_y, atm_z, atm_a, wid, interior) \
    VALUES \
        (%i, %f, %f, %f, %f, %i, %i) \
    ON DUPLICATE KEY UPDATE \
        atm_x = %f, \
        atm_y = %f, \
        atm_z = %f, \
        atm_a = %f, \
        wid = %i, \
        interior = %i \
    ";
    mysql_format(MySQL_GetHandle(), string2, sizeof(string2), query, atmID, x, y, z, a, wid, int, x, y, z, a, wid, int);
    mysql_tquery(MySQL_GetHandle(), string2);
}

stock Atm_InsertToDatabase(atmID)
{
	MySQL_BindInt(stmt_InsertATM, 0, atmID);
    MySQL_BindFloat(stmt_InsertATM, 1, AtmPosX[atmID]);
    MySQL_BindFloat(stmt_InsertATM, 2, AtmPosY[atmID]);
    MySQL_BindFloat(stmt_InsertATM, 3, AtmPosZ[atmID]);
    MySQL_BindFloat(stmt_InsertATM, 4, AtmPosA[atmID]);
    MySQL_BindInt(stmt_InsertATM, 5, AtmWid[atmID]);
    MySQL_BindInt(stmt_InsertATM, 6, AtmInt[atmID]);
    MySQL_ExecuteThreaded(stmt_InsertATM);
}

Atm_Load() {

    inline const OnATMLoad() {
        new
            atmID,
            Float:x,
            Float:y,
            Float:z,
            Float:a,
            wid,
            interior;

        MySQL_BindResultInt(stmt_LoadATM, 0, atmID);
        MySQL_BindResultFloat(stmt_LoadATM, 1, x);
        MySQL_BindResultFloat(stmt_LoadATM, 2, y);
        MySQL_BindResultFloat(stmt_LoadATM, 3, z);
        MySQL_BindResultFloat(stmt_LoadATM, 4, a);
        MySQL_BindResultInt(stmt_LoadATM, 5, wid);
        MySQL_BindResultInt(stmt_LoadATM, 6, interior);


        while(MySQL_Statement_FetchRow(stmt_LoadATM)) {
            Atm_Create(x, y, z, a, wid, interior);
        }
    }

    MySQL_ExecuteThreaded_Inline(stmt_LoadATM, using inline OnATMLoad);
}

Atm_Delete(playerid, atmID) {
    inline OnATMRemove()
    {
        if (MySQL_Statement_FetchRow(stmt_ATMExists)) {
            MySQL_BindInt(stmt_RemoveATM, 0, atmID);
            MySQL_ExecuteThreaded(stmt_RemoveATM);

            if (playerid != INVALID_PLAYER_ID) {
                SendServerMsgF(playerid, "You successfully deleted atm id "C_GREY"%i", atmID);
            }

            DestroyDynamicObject(atm_Object[atmID]);
            DestroyDynamic3DTextLabel(atm_Label[atmID]);

            Iter_Remove(atm_Iter, atmID);
        }
        else {
            if (playerid != INVALID_PLAYER_ID) {
                SendErrorMsgF(playerid, "The atm "C_GREY"(ID:%i) "C_WHITE"you are trying to delete was not found in the database.", atmID);
            }
        }
    }

    MySQL_BindInt(stmt_ATMExists, 0, atmID);
    MySQL_ExecuteThreaded_Inline(stmt_ATMExists, using inline OnATMRemove);
}

//IsPlayerNearATM(playerid)
//{
//    for(new i = 0; i < MAX_ATMS; i++) {
//        if(IsPlayerInRangeOfPoint(playerid, 3.0, AtmPosX[i], AtmPosY[i], AtmPosZ[i])) {
//            return 1;
//        }
//    }
//    return 0;
//}

hook OnPlayerEditDynObj(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;
	GetObjectPos(objectid, oldX, oldY, oldZ);
	GetObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
    if(response == EDIT_RESPONSE_FINAL)
    {
        Atm_Update(PlayerEditingATMID[playerid], x, y, z, rz, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    }
    if(response == EDIT_RESPONSE_CANCEL)
    {
        SetObjectPos(objectid, oldX, oldY, oldZ);
		SetObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
    }
    return 1;
}

// Commands
TCMD:createatm(playerid, params[])
{
	new 
        Float:x,
        Float:y,
        Float:z,
        Float:a;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new 
        ret = Atm_Create(
        x, 
        y, 
        z,
        a,
        GetPlayerVirtualWorld(playerid),
        GetPlayerInterior(playerid),
        true
    );

    if(ret == -1) {
        return SendErrorMsg(playerid, "Can't create more atms, please increase the size of MAX_ATMS");
    }

	return 1;
}

TCMD:deleteatm(playerid, params[])
{

    if(isnull(params)) {
        return SendErrorMsg(playerid, "/deleteatm <atm id>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Invalid input.");
    }

    new 
        atmID = strval(params);
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, AtmPosX[atmID], AtmPosY[atmID], AtmPosZ[atmID])) {
        return SendErrorMsg(playerid, "You're not near the atm");
    } 
    Atm_Delete(playerid, atmID);

    return 1;
}

TCMD:editatm(playerid, params[])
{
    new targetatm;
    if(sscanf(params, "i", targetatm)) return SendSyntaxMsg(playerid, "/editatm (atmid)");
    if(atm_Object[targetatm] == INVALID_OBJECT_ID) {
        return SendErrorMsg(playerid, "Invalid ATM id");
    }
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, AtmPosX[targetatm], AtmPosY[targetatm], AtmPosZ[targetatm])) {
        return SendErrorMsg(playerid, "You're not near the atm");
    } 
    EditDynamicObject(playerid, atm_Object[targetatm]);
    PlayerEditingATMID[playerid] = targetatm;
    return 1;
}

TCMD:nearatm(playerid, params[])
{
    new atms = 0;
    for (new i = 0; i < MAX_ATMS; i++) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, AtmPosX[i], AtmPosY[i], AtmPosZ[i])) {
			SendServerMsgF(playerid, "You're near atm id %d.", i);
            atms++;
        }
	}
    if(atms == 0) 
    {
        SendServerMsg(playerid, "You're not near any atms");
    }
    return 1;
}