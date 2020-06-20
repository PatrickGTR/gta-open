// cherry   x   25
// grapes   x  100
// 69       x  250
// bells    x  500
// bar 1    x 1000
// bar 2    x 2000

#include <YSI_Coding\y_hooks>

#define WIN_MULTIPLIER_GLOBAL 	(1.0)

#define MIN_BET 				(5)
#define MAX_BET 				(200)

#define BET_SETP 				(5)

#define G_STATE_NOT_GAMBLING    (0)
#define G_STATE_READY           (1)
#define G_STATE_GAMBLING        (2)
#define G_STATE_DISPLAY         (3) // Currently displaying the message
#define G_STATE_PLAY_AGAIN      (4)

#define DISPLAY_TIME 750
#define GAMBLE_TIMER 75

static
	Text: slot_HeaderTD[MAX_PLAYERS],
	Text: slot_ControlsTD[MAX_PLAYERS],
	Text: slot_BoxTD[MAX_PLAYERS],
	Timer: slot_Timer[MAX_PLAYERS],

	PlayerText: slot_Digit1[MAX_PLAYERS][6],
	PlayerText: slot_Digit2[MAX_PLAYERS][6],
	PlayerText: slot_Digit3[MAX_PLAYERS][6],
	PlayerText: slot_BetTD[MAX_PLAYERS];

static
	PlayerSlotID[MAX_PLAYERS][3],
	SlotCounter[MAX_PLAYERS],
	PlayerGamblingState[MAX_PLAYERS],
	PlayerBet[MAX_PLAYERS],
	PlayerBalance[MAX_PLAYERS];

PlayerText:CreatePlayerGamblingSprite(playerid, Float:x, Float:y, const td_name[], Float:width, Float:height)
{

	new PlayerText:RetSprite = CreatePlayerTextDraw(playerid, x, y, td_name);
	PlayerTextDrawFont(playerid, RetSprite, 4);
	PlayerTextDrawColor(playerid, RetSprite, 0xFFFFFFFF);
	PlayerTextDrawTextSize(playerid, RetSprite, width, height);
	return RetSprite;
}

Text:CreateGamblingBox(Float:x, Float:y, Float:width, Float:height, color)
{
	new
		string[500];
	for(new i = floatround(y); i < floatround(y + height); i++) {
		strcat(string,"~n~_");
	}

	new Text:RetSprite = TextDrawCreate(x, y, string);
	TextDrawFont(RetSprite, 0);
	TextDrawColor(RetSprite, 0xFFFFFFFF);
	TextDrawTextSize(RetSprite, width + x, height + y);
	TextDrawUseBox(RetSprite, 1);
	TextDrawBoxColor(RetSprite, color);
	TextDrawLetterSize(RetSprite, 0.0001, 0.1158);
	return RetSprite;
}

hook OnGameModeInit() {

	new Float:Y = 230.0;

	for(new i = 0; i < MAX_PLAYERS; i++) {
		slot_HeaderTD[i] = TextDrawCreate(302.000000, 184.000000, "Slot Machine");
		TextDrawAlignment(slot_HeaderTD[i], 3);
		TextDrawBackgroundColor(slot_HeaderTD[i], 255);
		TextDrawFont(slot_HeaderTD[i], 0);
		TextDrawLetterSize(slot_HeaderTD[i], 0.680000, 2.500000);
		TextDrawColor(slot_HeaderTD[i], -1);
		TextDrawSetOutline(slot_HeaderTD[i], 1);
		TextDrawSetProportional(slot_HeaderTD[i], 1);
		TextDrawSetSelectable(slot_HeaderTD[i], 0);

		slot_ControlsTD[i] = TextDrawCreate(193.000000, 300.000000, "~g~Press ~w~SPACE ~g~to Gamble~n~Press ~w~RETURN ~g~to Exit~n~Press ~w~LSHIFT ~g~to Increase Bet");
		TextDrawBackgroundColor(slot_ControlsTD[i], 85);
		TextDrawFont(slot_ControlsTD[i], 1);
		TextDrawLetterSize(slot_ControlsTD[i], 0.270000, 1.399999);
		TextDrawColor(slot_ControlsTD[i], -1);
		TextDrawSetOutline(slot_ControlsTD[i], 1);
		TextDrawSetProportional(slot_ControlsTD[i], 1);
		TextDrawSetSelectable(slot_ControlsTD[i], 0);

		slot_BoxTD[i] = CreateGamblingBox(194.0, Y - 20, 3 * 64.0 + 3 * 20, 84, 0x00000099);
	}
	return 1;
}

hook OnPlayerConnect(playerid) {
	PlayerGamblingState[playerid] = G_STATE_NOT_GAMBLING;

	slot_BetTD[playerid] = CreatePlayerTextDraw(playerid, 337.000000, 199.000000, "~w~Balance ~g~$100,00 ~w~Your Bet ~g~$100");
	PlayerTextDrawBackgroundColor(playerid, slot_BetTD[playerid], 85);
	PlayerTextDrawFont(playerid, slot_BetTD[playerid], 1);
	PlayerTextDrawLetterSize(playerid, slot_BetTD[playerid], 0.200000, 0.999998);
	PlayerTextDrawColor(playerid, slot_BetTD[playerid], -1);
	PlayerTextDrawSetOutline(playerid, slot_BetTD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, slot_BetTD[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, slot_BetTD[playerid], 0);

	new Float:Y = 230.0;

	// Cherries (x25)
	slot_Digit1[playerid][0] = CreatePlayerGamblingSprite(playerid, 214.0, Y, "LD_SLOT:cherry", 64, 64);
	slot_Digit2[playerid][0] = CreatePlayerGamblingSprite(playerid, 288.0, Y, "LD_SLOT:cherry", 64, 64);
	slot_Digit3[playerid][0] = CreatePlayerGamblingSprite(playerid, 362.0, Y, "LD_SLOT:cherry", 64, 64);

	// grapes (x100)
	slot_Digit1[playerid][1] = CreatePlayerGamblingSprite(playerid, 214.0, Y, "LD_SLOT:grapes", 64, 64);
	slot_Digit2[playerid][1] = CreatePlayerGamblingSprite(playerid, 288.0, Y, "LD_SLOT:grapes", 64, 64);
	slot_Digit3[playerid][1] = CreatePlayerGamblingSprite(playerid, 362.0, Y, "LD_SLOT:grapes", 64, 64);

	// 69's (x250)
	slot_Digit1[playerid][2] = CreatePlayerGamblingSprite(playerid, 214.0, Y, "LD_SLOT:r_69", 64, 64);
	slot_Digit2[playerid][2] = CreatePlayerGamblingSprite(playerid, 288.0, Y, "LD_SLOT:r_69", 64, 64);
	slot_Digit3[playerid][2] = CreatePlayerGamblingSprite(playerid, 362.0, Y, "LD_SLOT:r_69", 64, 64);

	// bells (x500)
	slot_Digit1[playerid][3] = CreatePlayerGamblingSprite(playerid, 214.0, Y, "LD_SLOT:bell", 64, 64);
	slot_Digit2[playerid][3] = CreatePlayerGamblingSprite(playerid, 288.0, Y, "LD_SLOT:bell", 64, 64);
	slot_Digit3[playerid][3] = CreatePlayerGamblingSprite(playerid, 362.0, Y, "LD_SLOT:bell", 64, 64);

	// Bars [1 bar] (x1000)
	slot_Digit1[playerid][4] = CreatePlayerGamblingSprite(playerid, 214.0, Y, "LD_SLOT:bar1_o", 64, 64);
	slot_Digit2[playerid][4] = CreatePlayerGamblingSprite(playerid, 288.0, Y, "LD_SLOT:bar1_o", 64, 64);
	slot_Digit3[playerid][4] = CreatePlayerGamblingSprite(playerid, 362.0, Y, "LD_SLOT:bar1_o", 64, 64);

	// Bars [2 bar] (x2000)
	slot_Digit1[playerid][5] = CreatePlayerGamblingSprite(playerid, 214.0, Y, "LD_SLOT:bar2_o", 64, 64);
	slot_Digit2[playerid][5] = CreatePlayerGamblingSprite(playerid, 288.0, Y, "LD_SLOT:bar2_o", 64, 64);
	slot_Digit3[playerid][5] = CreatePlayerGamblingSprite(playerid, 362.0, Y, "LD_SLOT:bar2_o", 64, 64);
}

hook OnPlayerDisconnect(playerid, reason) {
    SlotMachine_Exit(playerid);

	SlotMachine_Hide(playerid);

	TextDrawHideForPlayer(playerid, slot_HeaderTD[playerid]);
	TextDrawHideForPlayer(playerid, slot_BoxTD[playerid]);
	TextDrawHideForPlayer(playerid, slot_ControlsTD[playerid]);

	stop slot_Timer[playerid];
	return 1;
}

SlotMachine_Show(playerid, slot1, slot2, slot3) {
	SlotMachine_Hide(playerid);

	PlayerTextDrawShow(playerid, slot_Digit1[playerid][clamp(slot1, 0, sizeof(slot_Digit1[]))]);
	PlayerTextDrawShow(playerid, slot_Digit2[playerid][clamp(slot2, 0, sizeof(slot_Digit2[]))]);
	PlayerTextDrawShow(playerid, slot_Digit3[playerid][clamp(slot3, 0, sizeof(slot_Digit3[]))]);
}

SlotMachine_Hide(playerid) {
    PlayerTextDrawHide(playerid, slot_Digit1[playerid][0]);
	PlayerTextDrawHide(playerid, slot_Digit2[playerid][0]);
	PlayerTextDrawHide(playerid, slot_Digit3[playerid][0]);

	PlayerTextDrawHide(playerid, slot_Digit1[playerid][1]);
	PlayerTextDrawHide(playerid, slot_Digit2[playerid][1]);
	PlayerTextDrawHide(playerid, slot_Digit3[playerid][1]);

	PlayerTextDrawHide(playerid, slot_Digit1[playerid][2]);
	PlayerTextDrawHide(playerid, slot_Digit2[playerid][2]);
	PlayerTextDrawHide(playerid, slot_Digit3[playerid][2]);

	PlayerTextDrawHide(playerid, slot_Digit1[playerid][3]);
	PlayerTextDrawHide(playerid, slot_Digit2[playerid][3]);
	PlayerTextDrawHide(playerid, slot_Digit3[playerid][3]);

	PlayerTextDrawHide(playerid, slot_Digit1[playerid][4]);
	PlayerTextDrawHide(playerid, slot_Digit2[playerid][4]);
	PlayerTextDrawHide(playerid, slot_Digit3[playerid][4]);

	PlayerTextDrawHide(playerid, slot_Digit1[playerid][5]);
	PlayerTextDrawHide(playerid, slot_Digit2[playerid][5]);
	PlayerTextDrawHide(playerid, slot_Digit3[playerid][5]);
}

SlotMachine_Use(playerid, firstBet = MIN_BET,  startBalance = 0)
{
	if(PlayerGamblingState[playerid] != G_STATE_NOT_GAMBLING) {
		return 0;
	}

	PlayerGamblingState[playerid] = G_STATE_READY;
	TextDrawShowForPlayer(playerid, slot_HeaderTD[playerid]);
	TextDrawShowForPlayer(playerid, slot_ControlsTD[playerid]);
	TextDrawShowForPlayer(playerid, slot_BoxTD[playerid]);

	PlayerTextDrawShow(playerid, slot_BetTD[playerid]);

	PlayerSlotID[playerid][0] = random(5);
	PlayerSlotID[playerid][1] = random(5);
	PlayerSlotID[playerid][2] = random(5);

	SlotMachine_Show(playerid, PlayerSlotID[playerid][0], PlayerSlotID[playerid][1], PlayerSlotID[playerid][2]);

	PlayerBet[playerid] = firstBet;

	GivePlayerMoney(playerid, -startBalance);

	PlayerBalance[playerid] = startBalance;

	Updateslot_BetTD(playerid);

	TogglePlayerControllable(playerid, 0);
	return 1;
}

SlotMachine_Exit(playerid) {
	if(PlayerGamblingState[playerid] == G_STATE_NOT_GAMBLING) {
		return 0;
	}

	SlotMachine_Hide(playerid);
	PlayerGamblingState[playerid] = G_STATE_NOT_GAMBLING;

	TogglePlayerControllable(playerid, 1);

	TextDrawHideForPlayer(playerid, slot_HeaderTD[playerid]);
	TextDrawHideForPlayer(playerid, slot_ControlsTD[playerid]);
	TextDrawHideForPlayer(playerid, slot_BoxTD[playerid]);

	PlayerTextDrawHide(playerid, slot_BetTD[playerid]);

	new
		string[40];
	if(PlayerBalance[playerid] > 0) {
		format(string, sizeof(string),"~w~Withdrawn~n~~g~%m", PlayerBalance[playerid]);
	}
	else {
		format(string, sizeof(string),"~r~You lost your money. Stop playing.", PlayerBalance[playerid]);
	}

    GameTextForPlayer(playerid, string, 5000, 4);

    GivePlayerMoney(playerid, PlayerBalance[playerid]);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(PRESSED(KEY_SPRINT)) {
	    // Randomize if in Slotmachine
	    if(PlayerGamblingState[playerid] == G_STATE_READY) {

	        if(PlayerBet[playerid] > GetPlayerMoney(playerid) + PlayerBalance[playerid]) {
	            GameTextForPlayer(playerid,"~r~You don't have enough money!",5000,4);
	            return 1;
	        }

	        if(PlayerBalance[playerid] - PlayerBet[playerid] < 0) {
	            GameTextForPlayer(playerid,"~r~Your balance is too low!",5000,4);
	            return 1;
	        }

	        SlotCounter[playerid] = 40 + random(18);

            PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);

            slot_Timer[playerid] = repeat PlayerBeginGambling(playerid);

            PlayerGamblingState[playerid] = G_STATE_GAMBLING;

         	PlayerBalance[playerid] -= PlayerBet[playerid];

			Updateslot_BetTD(playerid);
	    }
	}

	if(PRESSED(KEY_SECONDARY_ATTACK)) {
	    if(PlayerGamblingState[playerid] == G_STATE_READY) {
	    	SlotMachine_Exit(playerid);
	    }
	}

	if(PRESSED(KEY_JUMP)) {
	    if(PlayerGamblingState[playerid] == G_STATE_READY) {
	    	PlayerBet[playerid] = GetNextValidBet(PlayerBet[playerid]);
	    	Updateslot_BetTD(playerid);
	    }
	}
	return 1;
}

timer PlayerBeginGambling[GAMBLE_TIMER](playerid)
{
	if(PlayerGamblingState[playerid] != G_STATE_GAMBLING) {
	    log("Strange error @ gambler");
	    stop slot_Timer[playerid];
	    PlayerGamblingState[playerid] = G_STATE_NOT_GAMBLING;
	    return 0;
	}

	SlotCounter[playerid] --;

	new
		slot = SlotCounter[playerid];

	if(slot < 10) {
	    PlayerSlotID[playerid][2] += random(3) + 1;
	}
	else if(slot < 20) {
	    PlayerSlotID[playerid][1] += random(3) + 1;
	    PlayerSlotID[playerid][2] += random(3) + 1;
	}
	else {
	    PlayerSlotID[playerid][0] += random(3) + 1;
	    PlayerSlotID[playerid][1] += random(3) + 1;
	    PlayerSlotID[playerid][2] += random(3) + 1;
	}

	if(PlayerSlotID[playerid][0] >= 6) {
		PlayerSlotID[playerid][0] = 0;
	}
	if(PlayerSlotID[playerid][1] >= 6) {
		PlayerSlotID[playerid][1] = 0;
	}
	if(PlayerSlotID[playerid][2] >= 6) {
		PlayerSlotID[playerid][2] = 0;
	}

    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);

	SlotMachine_Show(playerid, PlayerSlotID[playerid][0], PlayerSlotID[playerid][1], PlayerSlotID[playerid][2]);

	if(SlotCounter[playerid] == 0) {
	    stop slot_Timer[playerid];

		PlayerGamblingState[playerid] = G_STATE_DISPLAY;

	    if(PlayerSlotID[playerid][0] == PlayerSlotID[playerid][1] && PlayerSlotID[playerid][0] == PlayerSlotID[playerid][2]) {
	        new
				multiplier = 1;

	        switch(PlayerSlotID[playerid][0]) {
	            case 0: multiplier = 25;    // Cherries
	            case 1: multiplier = 100;   // Grapes
	            case 2: multiplier = 250;   // 69's
	            case 3: multiplier = 500;   // Bells
	            case 4: multiplier = 1000;  // Bar
	            case 5: multiplier = 2000;  // Double Bars
	        }

	        new money = floatround(PlayerBet[playerid] * multiplier * WIN_MULTIPLIER_GLOBAL);
	        new str[128];
	        format(str,sizeof(str),"~w~Winner~n~~g~%m", money);
	        GameTextForPlayer(playerid,str,5000,4);

	        PlayerBalance[playerid] += money;

	        Updateslot_BetTD(playerid);

	        PlayerSlotID[playerid][0] = random(5); // Randomize the slots again
			PlayerSlotID[playerid][1] = random(5);
			PlayerSlotID[playerid][2] = random(5);
	    }
	    else {
	        if (PlayerSlotID[playerid][0] == PlayerSlotID[playerid][1] || PlayerSlotID[playerid][1] == PlayerSlotID[playerid][2] || PlayerSlotID[playerid][0] == PlayerSlotID[playerid][2]) {
	        	GameTextForPlayer(playerid,"~w~Almost!", 3000, 4);
	        }
	        else {
				GameTextForPlayer(playerid,"~r~Bad luck!", 3000, 4);
			}
		}

	    defer PlayerPlaySlotAgain(playerid);
	    return 1;
	}
	return 0;
}

timer PlayerPlaySlotAgain[DISPLAY_TIME](playerid) {
	PlayerGamblingState[playerid] = G_STATE_READY;

	new keys,lr,ud;
	GetPlayerKeys(playerid,keys,ud,lr);
	if(keys & KEY_SPRINT) {
		CallLocalFunction("OnPlayerKeyStateChange", "ii", KEY_SPRINT, 0);
	}
}



GetNextValidBet(value) {
	return (value + BET_SETP > MAX_BET) ? (MIN_BET) : (value + BET_SETP);
}

Updateslot_BetTD(playerid) {
    new str[128];
    new prefix[4];

    if(PlayerBalance[playerid] == 0) {
		strcat(prefix,"~r~");
	}
    if(PlayerBalance[playerid]  > 0) {
		strcat(prefix,"~g~");
	}

    format(str,sizeof(str),"~w~Balance ~g~%s%m ~w~Your Bet ~g~%m", prefix, PlayerBalance[playerid], PlayerBet[playerid]);
	PlayerTextDrawSetString(playerid, slot_BetTD[playerid],str);
}

CMD:gamble(playerid, params[]) {
	if (isnull(params))
		return SendClientMessage(playerid,-1,"Use /gamble [money] to put money into the Slot Machine!");

    new money = strval(params);

    if (money < MIN_BET)
    	return SendClientMessage(playerid,-1,"You have to put more money into the Slot Machine!");

    if (money > GetPlayerMoney(playerid))
     return SendClientMessage(playerid,-1,"You don't have enough money!");

    if (money < 0)
    	return SendClientMessage(playerid,-1,"Invalid amount!");

	SlotMachine_Use(playerid, _, money);
	return 1;
}