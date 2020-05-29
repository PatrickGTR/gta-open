#include <YSI_Coding\y_hooks> 

static 
    HitAmount[MAX_PLAYERS],
    HitReason[MAX_PLAYERS][32],
    HitPlacedBy[MAX_PLAYERS][MAX_PLAYER_NAME],
    BitArray:HasHit<MAX_PLAYERS>
;

hook OnPlayerConnect(playerid) {
	_InitHitmanData(playerid);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason, Float: damage, bodypart)
{
    if (killerid != INVALID_PLAYER_ID) {      
        if (Bit_Get(HasHit, playerid) && Player_GetJob(killerid) == TYPE_HITMAN) {
            SendMsgAllF(COLOR_ORANGE, "** HIT **: "C_GREY"%p (%i) "C_WHITE"has completed the hit on "C_GREY"%p (%i) "C_WHITE"and recieved "C_GREEN"$%i.", killerid, killerid, playerid, playerid, HitAmount[playerid]);            
            // Reward killer.
            GivePlayerMoney(killerid, HitAmount[playerid]);
            
            // Reset data.
            _InitHitmanData(playerid);

        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	// TODO: Save player hit instead.
    if (Bit_Get(HasHit, playerid))  {
        SendMsgAllF(COLOR_ORANGE, "** HIT **: "C_WHITE"Contract on "C_GREY"%p (%i) "C_WHITE"has been cancelled, player left.", playerid, playerid );
    }
    return 1;
}

static _InitHitmanData(playerid) {
    Bit_Set(HasHit, playerid, false);
    HitAmount[playerid] = 0;
    HitReason[playerid][0] = EOS;
    HitPlacedBy[playerid][0] = EOS;
}

forward HitmanTextMenu(playerid, listitem);
public HitmanTextMenu(playerid, listitem) {

	new tmpString[24];
	format(tmpString, sizeof(tmpString), "HitmanMenuItem_%i", listitem);
	new targetid = GetPVarInt(playerid, tmpString);

	if(Bit_Get(HasHit, targetid)) {
		new 
			location[MAX_MAP_ZONE_NAME + 12];
		Player_GetLocation(targetid, location);
		SendClientMessage(playerid, COLOR_YELLOW, "Tracking....");
		SendMsgF(playerid, COLOR_GREY, "%p (%i) "C_WHITE"is near "C_GREY"%s", targetid, targetid, location);
		SendClientMessage(playerid, COLOR_GREEN, "Tracked!");
		
	}
	return 1;
} 

CMD:hitlist(playerid, params[]) {
	new 
		count = 0;

	if (Player_GetJob(playerid) != TYPE_HITMAN || Player_GetClass(playerid) != TEAM_CIVILIAN) {
		return SendErrorMsg(playerid, "You are not allowed to use this command if you are not a hitman.");
    }

    new 
        tmpString[100];

	TextMenu_Create(playerid, "HitmanTextMenu", "~y~Hitlist");
    foreach(new i : Player) {
        if(Bit_Get(HasHit, i)) {
            format(tmpString, sizeof(tmpString), 
            "~y~%p(%i) ~g~$%i ~y~By: ~w~%s", 
        	i, i, HitAmount[i], HitPlacedBy[i]);
			TextMenu_Add(playerid, tmpString);

			format(tmpString, sizeof(tmpString), "HitmanMenuItem_%i", count);
			SetPVarInt(playerid, tmpString, i);
            count ++;

			
        }
    }
    if(count == 0) {
    	MessageBox_Show(playerid, TYPE_MSGBOX, "~y~Hitlist", "There are no hits available");
    } else {
		TextMenu_Show(playerid);
	}
	return true;
}

CMD:placehit(playerid, params[])
{
	new 
		targetid, hitamount, reason[32];

	if (Player_GetJob(playerid) == TYPE_HITMAN && Player_GetClass(playerid) == TEAM_CIVILIAN ) {	
		return SendErrorMsg(playerid, "You are not allowed to place hit on others if you are a hitman.");
	}

	if (sscanf(params, "ris[32]", targetid, hitamount, reason)) {
		return SendSyntaxMsg(playerid, "/placehit <playerid> <Amount> <Reason>");
	}

	if(strlen(reason) > 32) {
		return SendErrorMsg(playerid, "Reason too lon, shorten it. "C_YELLOW"TIP: "C_GREY"MAX 32 characters.");
	}

	if (!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "The player you are placing hit on is not connected.");
	}

	if (!Player_IsSpawned(targetid)) {
		return SendErrorMsg(playerid, "The player you are placing hit on is not spawned.");
	}

	if (GetPlayerMoney(playerid) < hitamount) {
		return SendErrorMsg(playerid, "You do not have enough money to pay the hit, earn more money!");
	}

	if (hitamount < 10000) {
		return SendErrorMsg(playerid, "The hitman will not accept your offer, increase the amount of the hit!");
	}

	if (Bit_Get(HasHit, targetid)) {
		return SendErrorMsg(playerid, "The player you are placing hit on already has one.");
	}

	new 
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME);

	strcpy(HitReason[targetid], reason, sizeof(reason));
	strcpy(HitPlacedBy[targetid], name, sizeof(name));
	HitAmount[targetid]  = hitamount;
	Bit_Set(HasHit, targetid, true);
	GivePlayerMoney(playerid, -hitamount);

	SendMsgF(playerid, COLOR_ORANGE, "Hit: "C_WHITE"You successfully placed a hit on "C_GREY"%p (%i) "C_WHITE"for "C_GREEN"$%i"C_WHITE", reason: "C_GREY"%s", targetid, targetid, hitamount, reason);
	SendMsgAllF(COLOR_ORANGE, "Hit: "C_GREY"%p (%i) "C_WHITE"placed a hit on "C_GREY"%p (%i) "C_WHITE"for "C_GREEN"$%i"C_WHITE", reason: "C_GREY"%s", playerid, playerid, targetid, targetid, hitamount, reason);
	return true;
}