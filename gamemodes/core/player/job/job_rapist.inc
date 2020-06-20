#include <job_rapist-impl>

static
    HasJustUseRape[MAX_PLAYERS];

CMD:rape(playerid, params[])
{
	if (Player_GetJob(playerid) != TYPE_RAPIST || Player_GetClass(playerid) != TEAM_CIVILIAN) {
		return SendErrorMsg(playerid, "You are not allowed to use this command if you are not a rapist.");
    }

	if (isnull(params)) {
		return SendSyntaxMsg(playerid, "/rape <playerid>");
    }

	new
		targetid = strval(params);

	if (targetid == INVALID_PLAYER_ID) {
		return SendErrorMsg(playerid, "The player you are trying to rape is not connected.");
    }

	if (!Player_IsSpawned(targetid)) {
		return SendErrorMsg(playerid, "The player you are trying to rape is not spawned.");
    }

	if (Disease_PlayerHas(targetid)) {
		return SendErrorMsg(playerid, "The player you are trying to rape is already infected.");
    }

	if (!Player_IsNearPlayer(playerid, targetid, 4.0)) {
		return SendErrorMsg(playerid, "The player you are trying to rape is not near you.");
    }

	if (targetid == playerid) {
		return SendErrorMsg(playerid, "You can not rape your own self.");
    }

	if (gettime() - HasJustUseRape[playerid] < 20) {
		return SendErrorMsgF(playerid, "Please wait "C_GREY"%i seconds "C_WHITE"before using the command again.", gettime() - HasJustUseRape[playerid]);
    }

	if (Player_GetCondom(targetid) > 0)
	{
		Player_GiveCondom(targetid, -1);
		SendMsgF(playerid, COLOR_LIGHTGREEN, "** RAPE **: "C_GREY"You tried to rape "C_GREY"%p (%i) "C_WHITE"but failed because he had Condoms.", targetid, targetid);
  	 	SendMsgF(targetid, COLOR_LIGHTGREEN, "** RAPE **: "C_GREY"%p(%i) "C_WHITE"tried to rape you, luckily you have a condom, you have "C_GREY"%i "C_WHITE"condoms left", playerid, playerid, Player_GetCondom(playerid));
  	 	return true;
 	}

	Disease_GivePlayer(targetid, random(5) + 1);

	SendMsgAllF(COLOR_LIGHTGREEN, "** RAPE **: "C_GREY"%p (%i) "C_WHITE"has infected "C_GREY"%p (%i) "C_WHITE"with "C_LGREEN"%s", playerid, playerid, targetid, targetid, Disease_GetName(targetid));

	SendMsgF(playerid, COLOR_LIGHTGREEN, "** RAPE **: "C_WHITE"You successfully raped "C_GREY"%p (%i) "C_WHITE"and infected him/her with "C_LGREEN"%s", targetid, targetid, Disease_GetName(targetid));
	SendMsgF(targetid, COLOR_LIGHTGREEN, "** RAPE **: "C_GREY"%p (%i) "C_WHITE"infected you with "C_LGREEN"%s"C_WHITE", get to the hospital and get cured asap!", playerid, playerid, Disease_GetName(targetid));

	HasJustUseRape[playerid] = gettime();
	return true;
}