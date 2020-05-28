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

CMD:hitlist(playerid, params[]) {
	new 
		count = 0;

	// if (Player_GetJob(playerid) != TYPE_HITMAN || Player_GetClass(playerid) != TEAM_CIVILIAN) {
	// 	return SendErrorMsg(playerid, "You are not allowed to use this command if you are not a hitman.");
    // }

    new 
        tmpString[100],
        hitList[512];


    foreach(new i : Player) {
        if(Bit_Get(HasHit, i)) {
            format(tmpString, sizeof(tmpString), 
            "~y~Username: ~w~%p (%i) ~y~Reason: ~w~%s ~y~Amount: ~g~$%i~n~", 
            count, i, i, HitPlacedBy[i],  HitReason[i], HitAmount[i]);
            strcat(hitList, tmpString, sizeof(hitList));

            count ++;
        }
    }
    if(count == 0) {
        strcat(hitList, "There are no hits available", sizeof(hitList));
    }

    MessageBox_Show(playerid, TYPE_MSGBOX, "~y~Hitlist", hitList);

	// SendClientMessage(playerid, COLOR_GREEN, "______________________ "C_ORANGE"[ BEGIN ] "C_GREEN"______________________");
	// foreach(new i : Player)
	// {
	// 	if (Bit_Get(HasHit, i))
	// 	{
	// 		SendMsgF(playerid, COLOR_WHITE, "Username: %p (%i) - Placed By: %s - Reason: %s- Amount: "C_GREEN"$%i", i, i, HitPlacedBy[i],  HitReason[i], HitAmount[i]);
	// 		++ count;
	// 	}
	// }
	// if (count != 1) SendClientMessage(playerid, COLOR_WHITE, "There are no hits available");
	// SendClientMessage(playerid, COLOR_GREEN, "______________________ "C_ORANGE"[ END ] "C_GREEN"______________________");
	return true;
}


// CMD:track(playerid, params[])
// {	
// 	if (Player_GetJob(playerid) != TYPE_HITMAN || Player_GetClass(playerid) != TEAM_CIVILIAN)
// 		return SendErrorMsg(playerid, "You are not allowed to use this command if you are not a hitman.");
// 
// 	if (isnull(params))
// 		return SendSyntaxMsg(playerid, "/track <playerid>");
// 
// 	new targetid = strval(params);
// 
// 	if (targetid == playerid)
// 		return SendErrorMsg(playerid, "You are not allowed to track yourself.");
// 
// 	if (!IsPlayerConnected(targetid))
// 		return SendErrorMsg(playerid, "The player you are trying to track is not connected.");
// 
// 	if (!Player_IsSpawned(targetid))
// 		return SendErrorMsg(playerid, "The player you are trying to track is not spawned.");
// 
// 	if (GetPlayerInterior(targetid) > 1)
// 	{
// 		SendMsgF(playerid, COLOR_WHITE, "Location of "C_GREY"%p "C_WHITE"near "C_GREY"inside an interior", targetid);
// 	}
// 	else SendMsgF(playerid, COLOR_WHITE, "Location of "C_GREY"%p "C_WHITE"near "C_GREY"%s", targetid, GetPlayerLocation(playerid));
// 	return true;
// }	

CMD:placehit(playerid, params[])
{
	new 
		targetid, hitamount, reason[32];

	// if (Player_GetJob(playerid) == TYPE_HITMAN && Player_GetClass(playerid) == TEAM_CIVILIAN )
	// 	return SendErrorMsg(playerid, "You are not allowed to place hit on others if you are a hitman.");

	if (sscanf(params, "ris[32]", targetid, hitamount, reason))
		return SendSyntaxMsg(playerid, "/placehit <playerid> <Amount> <Reason>");

	if (!IsPlayerConnected(targetid))
		return SendErrorMsg(playerid, "The player you are placing hit on is not connected.");

	if (!Player_IsSpawned(targetid))
		return SendErrorMsg(playerid, "The player you are placing hit on is not spawned.");

	if (GetPlayerMoney(playerid) < hitamount)
		return SendErrorMsg(playerid, "You do not have enough money to pay the hit, earn more money!");

	if (hitamount < 10000)
		return SendErrorMsg(playerid, "The hitman will not accept your offer, increase the amount of the hit!");

	if (Bit_Get(HasHit, targetid))
		return SendErrorMsg(playerid, "The player you are placing hit on already has one.");


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