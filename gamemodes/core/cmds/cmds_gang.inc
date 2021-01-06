
CMD:gangs(playerid, params[]) {
    Gang_ShowGangs(playerid);
    return 1;
}

CMD:gang(playerid, params[]) {
    if(isnull(params))
		return SendSyntaxMsg(playerid, "/gang create | colour | disband | invite | kick | accept");

	if(!strcmp(params, "create", false, 6)) {
		new
			gangName[MAX_GANG_NAME];

		if(sscanf(params, "{s[7]}s["#MAX_GANG_NAME"]", gangName))
			return SendSyntaxMsg(playerid, "/gang create <gang name>");

    	if(!IS_IN_RANGE(strlen(gangName), 5, MAX_GANG_NAME - 1)) {
			return SendErrorMsg(playerid, "Gang names can't be more than 16 or less than 5 characters");
        }

        new
            ret = Gang_Create(playerid, gangName);

        if(ret == 0) {
			return SendErrorMsg(playerid, "Gang name already exists");
        }

		if(ret == -2) {
            return SendErrorMsg(playerid, "Unable to create more gang, limit has been reached. Contact an admin.");
        }

        SendMsgF(playerid, COLOR_PINK, "** GANG ** "C_WHITE"You have successfully created a gang called "C_PINK"'%s'", gangName);
        SendMsgF(playerid, COLOR_PINK, "** GANG ** "C_WHITE"You could invite players using "C_GREY"/gang invite"C_WHITE" and kick players using "C_GREY"/gang kick");
        SendMsgF(playerid, COLOR_PINK, "** GANG ** "C_WHITE"You could change your gang colour using "C_GREY"/gang colour"C_WHITE", the default colour is 'WHITE'");

        SendMsgAllF(COLOR_PINK, "** GANG ** "C_GREY"%p(%i) "C_WHITE"has created a new gang called "C_PINK"'%s'", playerid, playerid, gangName);
	}
    else if(!strcmp(params, "disband", false, 7)){
        new
            ret = Gang_Disband(playerid, Player_GetGangID(playerid));

        if(ret == -1) {
            return SendErrorMsg(playerid, "You are not the leader of this gang.");
        }
    }
    else if(!strcmp(params, "leave", false, 5)) {
        new
            ret = Gang_Leave(playerid);

        if(ret == -1) {
            return SendErrorMsg(playerid, "You are not in any gang.");
        }

        SendMsgF(playerid, COLOR_PINK, "** GANG ** "C_WHITE"You have successfully left your gang.");
    }
    else if(!strcmp(params, "invite", false, 6)) {
        new
            targetid;

        if(sscanf(params, "{s[7]}r", targetid))
			return SendSyntaxMsg(playerid, "/gang invite <playerid>");

        new
            ret = Gang_InvitePlayer(playerid, targetid);

        if(!ret) {
            return SendErrorMsg(playerid, "Player does not exists.");
        }

        if(ret == -1) {
            return SendErrorMsg(playerid, "Player is already in a gang.");
        }

        if(ret == -2) {
            return SendErrorMsg(playerid, "You are not a leader of this gang.");
        }
        SendMsgF(playerid, COLOR_PINK, "** GANG ** "C_WHITE"You have invited "C_GREY"%p[%i] "C_WHITE"to join your gang.", targetid, targetid);
		SendMsgF(targetid, COLOR_PINK, "** GANG ** "C_WHITE"You have been invited by "C_GREY"%p[%i] "C_WHITE"to join his/her gang.", playerid, playerid);
        SendMsgF(targetid, COLOR_PINK, "** GANG ** "C_WHITE"Use "C_GREY"/gang accept "C_WHITE"to accept the invitation.", playerid, playerid);
    }
    else if(!strcmp(params, "accept", false, 6)) {

        new
            gangID,
            gangColour,
            inviterID,
            gangName[MAX_GANG_NAME],
            ret = Gang_AcceptInvite(playerid, gangID, gangColour, inviterID, gangName);

        if(!ret) {
            return SendErrorMsg(playerid, "No one has invited you to join a gang.");
        }

        if(ret == -1) {
            return SendErrorMsg(playerid, "The player who invited you is not in the game anymore.");
        }

        SendMsgF(inviterID, COLOR_PINK, "** GANG ** "C_GREY"%p[%i] "C_WHITE"has accepted your gang invite.", playerid, playerid);
		SendMsgF(playerid, COLOR_PINK, "** GANG ** "C_WHITE"You have joined Gang ID: ["C_GREY"%i"C_WHITE"] - Gang Name: "C_GREY"'%s'", gangID, gangName);
		SetPlayerColor(playerid,  gangColour);

    }
    else if(!strcmp(params, "members", false, 7)) {
        Gang_ShowMembers(playerid);
    }
    return 1;
}
