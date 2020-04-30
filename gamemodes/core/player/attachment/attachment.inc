#define MAX_ATTACHMENTS             (5)
#define MAX_ATTACHMENT_NAME         (34)

enum E_ATTACHMENT_DATA
{
    E_ATTACHMENT_DATA_MODELID,
    E_ATTACHMENT_DATA_BONEID,
    Float:E_ATTACHMENT_DATA_OFFSETX,
    Float:E_ATTACHMENT_DATA_OFFSETY,
    Float:E_ATTACHMENT_DATA_OFFSETZ,
    Float:E_ATTACHMENT_DATA_ROTX,
    Float:E_ATTACHMENT_DATA_ROTY,
    Float:E_ATTACHMENT_DATA_ROTZ,
    Float:E_ATTACHMENT_DATA_SCALEX,
    Float:E_ATTACHMENT_DATA_SCALEY,
    Float:E_ATTACHMENT_DATA_SCALEZ
}
new
    gAttachmentData[MAX_PLAYERS][MAX_ATTACHMENTS][E_ATTACHMENT_DATA],
    gAttachmentPrice[MAX_PLAYERS],
    Iterator:gAttachmentIndex[MAX_PLAYERS]<MAX_ATTACHMENTS>;

static
    BitArray:gPlayerAttachmentState<MAX_PLAYERS>;

#include <attachment_data>
#if SETUP_TABLE
    #include <attachment_setup-table>
#endif
#include <attachment_impl>


#include <YSI_Coding\y_hooks>
#include <a_mysql>
#include <mysql_prepared>

static
    Statement: stmt_LoadAttachments,
    Statement: stmt_UpdateAttachments,
    Statement: stmt_InsertAttachments;

hook OnMySQLConnected() {
    static const query_LoadAttachments[] = "\
        SELECT \
            slot, model, bone, \
            offset_x, offset_y, offset_z, \
            rotation_x, rotation_y, rotation_z, \
            scale_x, scale_y, scale_z \
        FROM \
            attachments \
        WHERE \
            u_id = ?"
    ;
    stmt_LoadAttachments = MySQL_PrepareStatement(MySQL_GetHandle(), query_LoadAttachments);

    static const query_updateAttachments[] = "\
        UPDATE \
            attachments \
        SET \
			bone  = ?, \
			offset_x = ?, \
			offset_y = ?, \
			offset_z = ?, \
			rotation_x = ?, \
			rotation_y = ?, \
			rotation_z = ?, \
			scale_x = ?, \
			scale_y = ?, \
			scale_z = ? \
        WHERE \
            u_id = ? AND slot = ?"
    ;
    stmt_UpdateAttachments = MySQL_PrepareStatement(MySQL_GetHandle(), query_updateAttachments);

    static const query_insertAttachments[] = "\
        INSERT INTO \
            attachments \
                (u_id, slot, model, bone, offset_x, offset_y, offset_z, rotation_x, rotation_y, rotation_z, scale_x, scale_y, scale_z) \
        VALUES \
            (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    ;
    stmt_InsertAttachments = MySQL_PrepareStatement(MySQL_GetHandle(), query_insertAttachments);
    return 1;
}

hook OnPlayerConnect(playerid) {
   	new
        empty_data[E_ATTACHMENT_DATA];

    for(new i; i < MAX_ATTACHMENTS; ++i) {
		gAttachmentData[playerid][i] = empty_data;
	}

    for(new i = 0; i < MAX_PLAYER_ATTACHED_OBJECTS; ++i) {
		RemovePlayerAttachedObject(playerid, i);
	}

    Iter_Clear(gAttachmentIndex[playerid]);

	Bit_Vet(gPlayerAttachmentState, playerid);
    return 1;
}

hook OnPlayerEditAttachedObj(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ) {
	if (!response) {
		RemovePlayerAttachedObject(playerid, index);
		SetPlayerAttachedObject(playerid, index,
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ]);

		Bit_Vet(gPlayerAttachmentState, playerid);
		return true;
	}

	if (Bit_Get(gPlayerAttachmentState, playerid))
	{
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX] 	= fOffsetX;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY] 	= fOffsetY;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ] 	= fOffsetZ;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX] 		= fRotX;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY] 		= fRotY;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ] 		= fRotZ;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX] 		= fScaleX;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY] 		= fScaleY;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ] 		= fScaleZ;

		RemovePlayerAttachedObject(playerid, index);
		SetPlayerAttachedObject(playerid, index,
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ]);

        MySQL_BindInt(stmt_UpdateAttachments, 0, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID]);
        MySQL_BindFloat(stmt_UpdateAttachments, 1, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX]);
        MySQL_BindFloat(stmt_UpdateAttachments, 2, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY]);
        MySQL_BindFloat(stmt_UpdateAttachments, 3, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ]);
        MySQL_BindFloat(stmt_UpdateAttachments, 4, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX]);
        MySQL_BindFloat(stmt_UpdateAttachments, 5, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY]);
        MySQL_BindFloat(stmt_UpdateAttachments, 6, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ]);
        MySQL_BindFloat(stmt_UpdateAttachments, 7, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX]);
        MySQL_BindFloat(stmt_UpdateAttachments, 8, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY]);
        MySQL_BindFloat(stmt_UpdateAttachments, 9, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ]);
        MySQL_BindInt(stmt_UpdateAttachments, 10, Player_GetAccountID(playerid));
        MySQL_BindInt(stmt_UpdateAttachments, 11, index);

        MySQL_ExecuteThreaded(stmt_UpdateAttachments);

		SendServerMsgF(playerid, "You have edited attachment id "C_GREY"%i", index);

		Bit_Vet(gPlayerAttachmentState, playerid);
	}
	else
	{
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID] 	= modelid;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID] 		= boneid;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX] 	= fOffsetX;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY] 	= fOffsetY;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ] 	= fOffsetZ;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX] 		= fRotX;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY] 		= fRotY;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ] 		= fRotZ;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX] 		= fScaleX;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY] 		= fScaleY;
		gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ] 		= fScaleZ;

		RemovePlayerAttachedObject(playerid, index);
		SetPlayerAttachedObject(playerid, index,
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ]);

	
        MySQL_BindInt(stmt_InsertAttachments, 0, Player_GetAccountID(playerid));
        MySQL_BindInt(stmt_InsertAttachments, 1, index);
        MySQL_BindFloat(stmt_InsertAttachments, 2, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID]);
        MySQL_BindFloat(stmt_InsertAttachments, 3, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID]);
        MySQL_BindFloat(stmt_InsertAttachments, 4, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX]);
        MySQL_BindFloat(stmt_InsertAttachments, 5, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY]);
        MySQL_BindFloat(stmt_InsertAttachments, 6, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ]);
        MySQL_BindFloat(stmt_InsertAttachments, 7, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX]);
        MySQL_BindFloat(stmt_InsertAttachments, 8, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY]);
        MySQL_BindFloat(stmt_InsertAttachments, 9, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ]);
        MySQL_BindFloat(stmt_InsertAttachments, 10, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX]);
        MySQL_BindFloat(stmt_InsertAttachments, 11, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY]);
        MySQL_BindFloat(stmt_InsertAttachments, 12, gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ]);

        MySQL_ExecuteThreaded(stmt_InsertAttachments);

		SendServerMsgF(playerid, "You have bought an attachment and it has been inserted in id "C_GREY"%i", index);
		GivePlayerMoney(playerid, -gAttachmentPrice[playerid]);
		Iter_Add(gAttachmentIndex[playerid], index);
	}
	return true;
}

hook OnPlayerLogin(playerid) {
	inline const LoadAttachment() {
        new
            slot = 0,
            modelid,
            boneid,
            Float:offsetX,
            Float:offsetY,
            Float:offsetZ,
            Float:rotX,
            Float:rotY,
            Float:rotZ,
            Float:scaleX,
            Float:scaleY,
            Float:scaleZ;

        MySQL_BindResultInt(stmt_LoadAttachments,   0,  slot);
        MySQL_BindResultInt(stmt_LoadAttachments,   1,  modelid);
        MySQL_BindResultInt(stmt_LoadAttachments,   2,  boneid);
        MySQL_BindResultFloat(stmt_LoadAttachments, 3,  offsetX);
        MySQL_BindResultFloat(stmt_LoadAttachments, 4,  offsetY);
        MySQL_BindResultFloat(stmt_LoadAttachments, 5,  offsetZ);
        MySQL_BindResultFloat(stmt_LoadAttachments, 6,  rotX);
        MySQL_BindResultFloat(stmt_LoadAttachments, 7,  rotY);
        MySQL_BindResultFloat(stmt_LoadAttachments, 8,  rotZ);
        MySQL_BindResultFloat(stmt_LoadAttachments, 9,  scaleX);
        MySQL_BindResultFloat(stmt_LoadAttachments, 10, scaleY);
        MySQL_BindResultFloat(stmt_LoadAttachments, 11, scaleZ);

        while(MySQL_Statement_FetchRow(stmt_LoadAttachments)) {
            gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_MODELID]  = modelid;
            gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_BONEID]   = boneid ;
            gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_OFFSETX]  = offsetX;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_OFFSETY]  = offsetY;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_OFFSETZ]  = offsetZ;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_ROTX]     = rotX;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_ROTY]     = rotY;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_ROTZ]     = rotZ;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_SCALEX]   = scaleX ;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_SCALEY]   = scaleY ;
		    gAttachmentData[playerid][slot][E_ATTACHMENT_DATA_SCALEZ]   = scaleZ ;

            Iter_Add(gAttachmentIndex[playerid], slot);
        }
	}
    MySQL_BindInt(stmt_LoadAttachments, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_LoadAttachments, using inline LoadAttachment);
    return 1;
}

static const 
    ERR_INVALID_SLOT[] = "Invalid slot id, try again.";

CMD:attachment(playerid, params[]) {
	if (isnull(params)) {
		SendSyntaxMsg(playerid, "/attachment buy | delete | edit | view | attach | detach");
        return 1;
    }

	new
		index = 0,
		attachmentName[MAX_ATTACHMENT_NAME];

	if (!strcmp(params, "buy", true, 4)) {
		ShowAttachmentsList(playerid, 0);
	}
    
	if (!strcmp(params, "delete", true, 6)) {
		if (sscanf(params, "{s[7]}i", index)) {
            SendSyntaxMsg(playerid, "/attachments delete <slot>");
            return 1;
        }
		if (!Iter_Contains(gAttachmentIndex[playerid], index)) {
			SendErrorMsg(playerid, ERR_INVALID_SLOT);
            return 1;
        }

		Attachment_GetModelName(gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID], attachmentName, sizeof(attachmentName));
		SendServerMsgF(playerid, "Successfully deleted attachment "C_GREY"(%s [slot: %i])", index, attachmentName);

		DeleteAttachment(playerid, index);
	}

	if (!strcmp(params, "edit", true, 4))
	{
		if (sscanf(params, "{s[5]}i", index)) {
            SendSyntaxMsg(playerid, "/attachments edit <slot>");
            return 1;
        }

		if (!Iter_Contains(gAttachmentIndex[playerid], index)) {
            SendErrorMsg(playerid, ERR_INVALID_SLOT);
            return 1;
        }

		Attachment_GetModelName(gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID], attachmentName, sizeof(attachmentName));
		SendServerMsgF(playerid, "You are editing attachment "C_GREY"(%s [slot: %i])", index, attachmentName);

		SetPlayerAttachedObject(playerid, index,
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ]);
		EditAttachedObject(playerid, index);

		Bit_Let(gPlayerAttachmentState, playerid);
	}

	if (!strcmp(params, "view", true, 4)) {
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "================== [Attachments] ==================");
		for(new i = 0; i < MAX_ATTACHMENTS; i++) {
			if (Iter_Contains(gAttachmentIndex[playerid], i)) {
				Attachment_GetModelName(gAttachmentData[playerid][i][E_ATTACHMENT_DATA_MODELID], attachmentName, sizeof(attachmentName));
				SendMsgF(playerid, COLOR_WHITE, "Slot %i: %s", i, attachmentName);
			}
			else {
			 	SendMsgF(playerid, COLOR_WHITE, "Slot %i: EMPTY", i);
			}

		}
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "================== [Attachments] ==================");
	}

	if (!strcmp(params, "attach", true, 6)) {
		if (sscanf(params, "{s[7]}i", index)) {
            SendSyntaxMsg(playerid, "/attachments attach <slot>");
            return 1;
        }

		if (!Iter_Contains(gAttachmentIndex[playerid], index)) {
			SendErrorMsg(playerid, ERR_INVALID_SLOT);
            return 1;
        }

		SetPlayerAttachedObject(playerid, index,
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_BONEID],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_OFFSETZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_ROTZ],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEX],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEY],
			gAttachmentData[playerid][index][E_ATTACHMENT_DATA_SCALEZ]);

		Attachment_GetModelName(gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID], attachmentName, sizeof(attachmentName));
		SendServerMsgF(playerid, "Successfully attached "C_GREY"(%s [slot: %i])", index, attachmentName);
	}
	if (!strcmp(params, "detach", true, 6)) {
		if (sscanf(params, "{s[7]}i", index)) {
			SendSyntaxMsg(playerid, "/attachments detach <slot>");
            return 1;
        }

		if (!Iter_Contains(gAttachmentIndex[playerid], index)) {
			SendErrorMsg(playerid, ERR_INVALID_SLOT);
            return 1;
        }

		RemovePlayerAttachedObject(playerid, index);

		Attachment_GetModelName(gAttachmentData[playerid][index][E_ATTACHMENT_DATA_MODELID], attachmentName, sizeof(attachmentName));
		SendServerMsgF(playerid, "Successfully detached "C_GREY"(%s [slot: %i])", index, attachmentName);
	}
	return 1;
}