#include <YSI_Coding\y_hooks>
#include <progress2>

static
	PlayerBar:TD_CrackStatus = PlayerBar:INVALID_PLAYER_BAR_ID,
	PlayerText:TD_CrackTitle = PlayerText:INVALID_TEXT_DRAW,
	Timer:crackProducingTimer[MAX_PLAYERS],
	P_CRACKSequence[MAX_PLAYERS] = {0, ...},
	plyIncrement[MAX_PLAYERS] = {0, ...},
	plyJustCreatedCocaine[MAX_PLAYERS],
	BitArray:HasBeganCocaineProduction<MAX_PLAYERS>
;

enum //5 * 8 = 40 seconds to finish.
{
	SEQ_ADDCOCALEAVES = 0,
	SEQ_POURCEMENT,
	SEQ_POURGASOLINE,
	SEQ_MIXINGREDIENTS,
	SEQ_FILTERGASOLINE,
	SEQ_EXTRACOCOALEAVES,
	SEQ_MARINATE,
	SEQ_FINISHED
}

#define DRUG_CREATION_POSX	(720.7772)
#define DRUG_CREATION_POSY	(209.3263)
#define DRUG_CREATION_POSZ	(11552.6592)
#define DRUG_CREATION_POSA	(220.0334)

hook OnGameModeInit() {
    CreateDynamic3DTextLabel("Press "C_YELLOW"N "C_WHITE"\nTo begin creating crack cocaine", COLOR_WHITE, DRUG_CREATION_POSX, DRUG_CREATION_POSY, DRUG_CREATION_POSZ, TEXTLABEL_STREAMDISTANCE, .testlos = 1);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if ((newkeys & KEY_NO) == KEY_NO
		&& GetPlayerState(playerid) == PLAYER_STATE_ONFOOT
		&& IsPlayerInRangeOfPoint(playerid, 2, DRUG_CREATION_POSX, DRUG_CREATION_POSY, DRUG_CREATION_POSZ)) {

		if(Bit_Get(HasBeganCocaineProduction, playerid))
			return SendErrorMsg(playerid, "You already have started producing crack cocaine.");

		Crack_Produce(playerid);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid) {
    TD_CrackStatus = CreatePlayerProgressBar(playerid, 272.000000, 363.000000, 107.500000, 9.199998, -1347440641, 100.0000, 0);
	TD_CrackTitle = CreatePlayerTextDraw(playerid, 270.000000, 350.000000, "Pouring gasoline");
	PlayerTextDrawBackgroundColor(playerid, TD_CrackTitle, 255);
	PlayerTextDrawFont(playerid, TD_CrackTitle, 2);
	PlayerTextDrawLetterSize(playerid, TD_CrackTitle, 0.249999, 1.100000);
	PlayerTextDrawColor(playerid, TD_CrackTitle, -1);
	PlayerTextDrawSetOutline(playerid, TD_CrackTitle, 0);
	PlayerTextDrawSetProportional(playerid, TD_CrackTitle, 1);
	PlayerTextDrawSetShadow(playerid, TD_CrackTitle, 1);
	PlayerTextDrawSetSelectable(playerid, TD_CrackTitle, 0);
   	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDeath(playerid, killerid, reason) {

	if(P_CRACKSequence[playerid] >= 0) {
		Crack_ResetData(playerid);
		stop ProduceCrackUpdate(playerid);
	}
	return 1;
}

Crack_Produce(playerid, seq = SEQ_ADDCOCALEAVES) {
	if(gettime() < plyJustCreatedCocaine[playerid])
		return SendErrorMsgF(playerid, "You've just produced crack cocaine recently, please wait... "C_GREY"%i "C_WHITE"seconds", plyJustCreatedCocaine[playerid] - gettime());

	if(Player_GetJob(playerid) != TYPE_DRUGDEALER)
		return SendErrorMsg(playerid, "You can't produce crack cocaine because you are not a drug dealer.");

	if(Player_GetCrack(playerid) >= MAX_CRACK)
		return SendErrorMsg(playerid, "You are unable to produce more crack cocaine, you've reached the maximum amount you could hold.");

	P_CRACKSequence[playerid] = seq;
	switch(seq) {
		case SEQ_ADDCOCALEAVES: {
			PlayerTextDrawSetString(playerid, TD_CrackTitle, "Pouring Cocoa...");
			PlayerTextDrawShow(playerid, TD_CrackTitle);

			ShowPlayerProgressBar(playerid, TD_CrackStatus);
			P_CRACKSequence[playerid]= SEQ_ADDCOCALEAVES;

			crackProducingTimer[playerid] 	= repeat ProduceCrackUpdate(playerid);

			SendClientMessage(playerid, COLOR_TEAL, "** CRACK COCAINE ** "C_WHITE"You have began producing crack cocaine, please wait until the process is finished.");

			Bit_Set(HasBeganCocaineProduction, playerid, true);

			SetPlayerFacingAngle(playerid, DRUG_CREATION_POSA);
			SetPlayerPos(playerid, DRUG_CREATION_POSX, DRUG_CREATION_POSY, DRUG_CREATION_POSZ);
			ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 1, 1, 1, 0, 1);
		}
		case SEQ_POURCEMENT: {
			PlayerTextDrawSetString(playerid, TD_CrackTitle, "Pouring Cement...");
			PlayerTextDrawShow(playerid, TD_CrackTitle);

			ShowPlayerProgressBar(playerid, TD_CrackStatus);
			P_CRACKSequence[playerid]= SEQ_POURCEMENT;
		}
		case SEQ_POURGASOLINE: {
			PlayerTextDrawSetString(playerid, TD_CrackTitle, "Pouring Gasoline...");
			PlayerTextDrawShow(playerid, TD_CrackTitle);

			ShowPlayerProgressBar(playerid, TD_CrackStatus);
			P_CRACKSequence[playerid]= SEQ_POURGASOLINE;
		}
		case SEQ_MIXINGREDIENTS: {
			PlayerTextDrawSetString(playerid, TD_CrackTitle, "Mixing Ingridients..");
			PlayerTextDrawShow(playerid, TD_CrackTitle);

			ShowPlayerProgressBar(playerid, TD_CrackStatus);
			P_CRACKSequence[playerid]= SEQ_MIXINGREDIENTS;
		}
		case SEQ_FILTERGASOLINE: {
			PlayerTextDrawSetString(playerid, TD_CrackTitle, "Filtering Gasoline");
			PlayerTextDrawShow(playerid, TD_CrackTitle);

			ShowPlayerProgressBar(playerid, TD_CrackStatus);
			P_CRACKSequence[playerid]= SEQ_FILTERGASOLINE;
		}
		case SEQ_EXTRACOCOALEAVES: {
			PlayerTextDrawSetString(playerid, TD_CrackTitle, "Extracting Cocoa");
			PlayerTextDrawShow(playerid, TD_CrackTitle);

			ShowPlayerProgressBar(playerid, TD_CrackStatus);
			P_CRACKSequence[playerid]= SEQ_EXTRACOCOALEAVES;
		}
		case SEQ_MARINATE: {
			PlayerTextDrawSetString(playerid, TD_CrackTitle, "Marinating Cocaine");
			PlayerTextDrawShow(playerid, TD_CrackTitle);

			ShowPlayerProgressBar(playerid, TD_CrackStatus);
			P_CRACKSequence[playerid]= SEQ_MARINATE;
		}
		case SEQ_FINISHED: {
			SendClientMessage(playerid, COLOR_TEAL, "** CRACK COCAINE ** "C_WHITE"You have have produced 50 grams of crack cocaine.");
			Player_GiveCrack(playerid, 5);

			ClearAnimations(playerid, 1);
			Crack_ResetData(playerid);

			plyJustCreatedCocaine[playerid] = gettime() + 60;
			Bit_Set(HasBeganCocaineProduction, playerid, false);
		}
	}
	return 1;
}

Crack_ResetData(playerid) {
	plyIncrement[playerid] = 0;
	PlayerTextDrawHide(playerid, TD_CrackTitle);
	HidePlayerProgressBar(playerid, TD_CrackStatus);
	SetPlayerProgressBarValue(playerid, TD_CrackStatus, 0.0);
	stop crackProducingTimer[playerid];
}

timer ProduceCrackUpdate[1000](playerid) {
	if (plyIncrement[playerid] >= 5) {
		plyIncrement[playerid] = 0;
		PlayerTextDrawHide(playerid, TD_CrackTitle);
		HidePlayerProgressBar(playerid, TD_CrackStatus);
		SetPlayerProgressBarValue(playerid, TD_CrackStatus, 0.0);

		switch(P_CRACKSequence[playerid])
		{
			case SEQ_ADDCOCALEAVES: 	Crack_Produce(playerid, SEQ_POURCEMENT);
			case SEQ_POURCEMENT: 		Crack_Produce(playerid, SEQ_POURGASOLINE);
			case SEQ_POURGASOLINE: 		Crack_Produce(playerid, SEQ_MIXINGREDIENTS);
			case SEQ_MIXINGREDIENTS: 	Crack_Produce(playerid, SEQ_FILTERGASOLINE);
			case SEQ_FILTERGASOLINE: 	Crack_Produce(playerid, SEQ_EXTRACOCOALEAVES);
			case SEQ_EXTRACOCOALEAVES: 	Crack_Produce(playerid, SEQ_MARINATE);
			case SEQ_MARINATE: 			Crack_Produce(playerid, SEQ_FINISHED);
		}
	}

	new
		Float:pb_val = GetPlayerProgressBarValue(playerid, TD_CrackStatus);

	SetPlayerProgressBarValue(playerid, TD_CrackStatus, pb_val + 20);
	plyIncrement[playerid] ++;
	return 1;
}
