
DeleteAttachment(playerid, slot)
{
	new
		empty_data[E_ATTACHMENT_DATA];

    new query[128];

    mysql_format(MySQL_GetHandle(), query, sizeof(query), "DELETE FROM attachments WHERE u_id = %i AND slot = %i", Player_GetAccountID(playerid), slot);
	mysql_tquery(MySQL_GetHandle(), query);

    gAttachmentData[playerid][slot] = empty_data;
	RemovePlayerAttachedObject(playerid, slot);
	Iter_Remove(gAttachmentIndex[playerid], slot);
}

static void:_AttachmentList(playerid, page) {
	new
		name[MAX_ATTACHMENT_NAME];

	inline const dialogAttachment(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, listitem

		if (!response) {
			ShowAttachmentsList(playerid);
			return;
		}

		new
			index = 0,
			modelid = strval(inputtext),
			freeslot = Iter_Free(gAttachmentIndex[playerid]);


		for(new i = 0; i < Attachment_GetTotalModels(); i++) {
			if(Attachment_GetModelID(i) == modelid) {
				index = i;
				break;
			}
		}

		if (freeslot == ITER_NONE) {
			SendErrorMsg(playerid, "You have used all of your attachment slots.");
			return;
		}

		Attachment_GetModelName(Attachment_GetModelID(index), name, sizeof(name));
		if(GetPlayerMoney(playerid) < Attachment_GetModelPrice(index)) {
			SendErrorMsgF(playerid, "You don't have "C_GREEN"%m "C_WHITE"to buy "C_GREY"%s", Attachment_GetModelPrice(index), name);
			return;
		}

		SetPlayerAttachedObject(playerid, freeslot, Attachment_GetModelID(index), Attachment_GetModelBoneID(index));
		EditAttachedObject(playerid, freeslot);

		// Notify
		SendServerMsgF(playerid, "You bought a "C_GREY"%s "C_WHITE"for "C_GREEN"%m", name, Attachment_GetModelPrice(index));

		// Assign
		gAttachmentPrice[playerid] = Attachment_GetModelPrice(index);
	}

	new
		tempString[64],
		bigString[2048];

	for(new i = 0; i < Attachment_GetTotalModels(); i++) {
		if(Attachment_GetType(i) != page) {
			continue;
		}

		Attachment_GetModelName(Attachment_GetModelID(i), name, sizeof(name));
		format(tempString, sizeof(tempString), "%i\t~w~%s~n~%s%m\n",
			Attachment_GetModelID(i),
			name,
			(GetPlayerMoney(playerid) < Attachment_GetModelPrice(i)) ? ("~r~") : ("~g~"),
			Attachment_GetModelPrice(i)
		);
		strcat(bigString, tempString, sizeof(bigString));
	}
	Dialog_ShowCallback(
		playerid,
		using inline dialogAttachment,
		DIALOG_STYLE_PREVIEW_MODEL,
		"Attachment Store",
		bigString,
		"Select",
		"Back"
	);
}


void:ShowAttachmentsList(playerid)
{


	inline const ChooseStyle(pid, dialogid, response, listitem, string:inputtext[]) {
		#pragma unused pid, dialogid, inputtext


        if (!response) {
        	SendServerMsg(playerid, "Attachment Type Dialog, closed.");
			return;
        }

		_AttachmentList(playerid, listitem);

	}

	Dialog_ShowCallback(
		playerid,
		using inline ChooseStyle,
		DIALOG_STYLE_LIST,
		"Please choose which style...",
		"Hats \n\
		Glasses \n\
		Bandana \n\
		Headphones \n\
		Mask \n\
		Bag \n\
		Helmet \n\
		Guitars",
		"Select",
		"Close"
	);
}