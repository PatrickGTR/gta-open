
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

#define NEXT_BUTTON ""C_YELLOW"NEXT >>"
#define BACK_BUTTON ""C_RED"<< BACK"
ShowAttachmentsList(playerid, slot)
{
	new 
		string[1024], 
		name[MAX_ATTACHMENT_NAME];
	
	// Format 
	// Index | Attachment 		 | Price
	// 0	 | Green Hockey Mask | $2,500
	strcat(string, "Index\tAttachment\tPrice\n");
	for(new i = slot; i < slot + NEXT_PAGE; i++) {
		if (i < Attachment_GetTotalModels()) {

			Attachment_GetModelName(Attachment_GetModelID(i), name, sizeof(name));

			format(string, sizeof(string), "%s%d\t%s\t%C$%d\n", 
				string, 
				i, 
				name, 
				(GetPlayerMoney(playerid) < Attachment_GetModelPrice(i)) ? (COLOR_RED) : (COLOR_GREEN),
				Attachment_GetModelPrice(i)
			);
		}
	}

	if(!((slot + NEXT_PAGE) > Attachment_GetTotalModels())) {
		strcat(string, ""NEXT_BUTTON"\n");
	}
	// do not add the go back page if we are on 
	// the first page.
	if((slot + NEXT_PAGE) -1 != (NEXT_PAGE - 1)) {
		strcat(string, ""BACK_BUTTON"\n");
	}

	inline const dialogAttachment(pid, dialogid, response, listitem, string:inputtext[])
	{
    	#pragma unused pid, dialogid

    	if (!response) {
			return 1; 
		}

		// Next page
		if(!strcmp(inputtext, NEXT_BUTTON, false)) {
			ShowAttachmentsList(playerid, slot + NEXT_PAGE);
			return 1;
		}

		// Go back
		if(!strcmp(inputtext, BACK_BUTTON, false)) {
			ShowAttachmentsList(playerid, slot - NEXT_PAGE);
			return 1;
		}

		new 
			idx = slot + listitem,
			freeslot = Iter_Free(gAttachmentIndex[playerid]);

		if (freeslot == ITER_NONE) {
			SendErrorMsg(playerid, "You have used all of your attachment slots.");
			return 1;
		}

		if(GetPlayerMoney(playerid) < Attachment_GetModelPrice(idx)) {
			SendErrorMsgF(playerid, "You don't have "C_GREEN"%m "C_WHITE"to buy "C_GREY"%s");
			return 1;
		}

		SetPlayerAttachedObject(playerid, freeslot, Attachment_GetModelID(idx), Attachment_GetModelBoneID(idx));
		EditAttachedObject(playerid, freeslot);

		new attachmentName[MAX_ATTACHMENT_NAME];
		Attachment_GetModelName(Attachment_GetModelID(idx), attachmentName, sizeof(attachmentName));

		// Notify
		SendServerMsgF(playerid, "You bought a "C_GREY"%s "C_WHITE"for "C_GREEN"%m", attachmentName, Attachment_GetModelPrice(idx));
			
		// Assign
		gAttachmentPrice[playerid] = Attachment_GetModelPrice(idx);
    }
	Dialog_ShowCallback(playerid, using inline dialogAttachment, DIALOG_STYLE_TABLIST_HEADERS, "Attachment Store", string, "Purchase", "Leave");
	return 1;
} 