#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

static
	// Background Box
	  Text: gBody[MAX_PLAYERS],
	// Buttons
	  Text: gBtnRight[MAX_PLAYERS],
	  Text: gBtnLeft[MAX_PLAYERS],
	  Text: gBtnClose[MAX_PLAYERS],
	  Text: gBtnPurchase[MAX_PLAYERS],
	//Title / Header
	  Text: gPrevNext[MAX_PLAYERS],
	  Text: gHeaderSide[MAX_PLAYERS],
	  Text: gHeaderBack[MAX_PLAYERS],
	  Text: gHeaderFront[MAX_PLAYERS],
	// Player Textdraw
PlayerText: gVehModelLeft[MAX_PLAYERS],
PlayerText: gVehModelCenter[MAX_PLAYERS],
PlayerText: gVehModelRight[MAX_PLAYERS],
PlayerText: gVehModelHeader[MAX_PLAYERS],
PlayerText: gVehModelPrice[MAX_PLAYERS],

    //Player Setting
  BitArray: gHasDealershipOpened<MAX_PLAYERS>
;

enum {
	BTN_RIGHT,
	BTN_LEFT,
	BTN_PURCHASE,
    BTN_CLOSE
}

UI_ShowDealershipTextDraw(playerid)
{
	TextDrawShowForPlayer(playerid, gBody[playerid]);

	PlayerTextDrawShow(playerid, gVehModelLeft[playerid]);
	PlayerTextDrawShow(playerid, gVehModelCenter[playerid]);
	PlayerTextDrawShow(playerid, gVehModelRight[playerid]);
	PlayerTextDrawShow(playerid, gVehModelHeader[playerid]);
	PlayerTextDrawShow(playerid, gVehModelPrice[playerid]);

	TextDrawShowForPlayer(playerid, gBtnRight[playerid]);
	TextDrawShowForPlayer(playerid, gBtnLeft[playerid]);
	TextDrawShowForPlayer(playerid, gBtnClose[playerid]);
	TextDrawShowForPlayer(playerid, gBtnPurchase[playerid]);

	TextDrawShowForPlayer(playerid, gPrevNext[playerid]);
	TextDrawShowForPlayer(playerid, gHeaderSide[playerid]);
	TextDrawShowForPlayer(playerid, gHeaderBack[playerid]);
	TextDrawShowForPlayer(playerid, gHeaderFront[playerid]);

	SelectTextDraw(playerid, 0xFF4040AA);
    Bit_Set(gHasDealershipOpened, playerid, true);
	return 1;
}

UI_SetDealershipVehicleModel(playerid, vehmodel)
{
	PlayerTextDrawSetPreviewModel(playerid, gVehModelLeft[playerid], vehmodel);
	PlayerTextDrawSetPreviewModel(playerid, gVehModelCenter[playerid], vehmodel);
	PlayerTextDrawSetPreviewModel(playerid, gVehModelRight[playerid], vehmodel);

	PlayerTextDrawShow(playerid, gVehModelLeft[playerid]);
	PlayerTextDrawShow(playerid, gVehModelCenter[playerid]);
	PlayerTextDrawShow(playerid, gVehModelRight[playerid]);
	return 1;
}

UI_SetDealershipVehicleHeader(playerid, vehmodel)
{
	new
        string[32];

    format(string, sizeof(string), "~g~%v", vehmodel);

	return PlayerTextDrawSetString(playerid, gVehModelHeader[playerid], string);
}

UI_SetDealershipVehiclePrice(playerid, price) {

    new
        string[16];

    format(string, sizeof(string), "~g~%m", price);
	PlayerTextDrawSetString(playerid, gVehModelPrice[playerid], string);
}

UI_HideDealershipTextDraw(playerid)
{
	TextDrawHideForPlayer(playerid, gBody[playerid]);

	TextDrawHideForPlayer(playerid, gBtnRight[playerid]);
	TextDrawHideForPlayer(playerid, gBtnLeft[playerid]);
	TextDrawHideForPlayer(playerid, gBtnClose[playerid]);
	TextDrawHideForPlayer(playerid, gBtnPurchase[playerid]);
	TextDrawHideForPlayer(playerid, gPrevNext[playerid]);

	TextDrawHideForPlayer(playerid, gHeaderSide[playerid]);
	TextDrawHideForPlayer(playerid, gHeaderBack[playerid]);
	TextDrawHideForPlayer(playerid, gHeaderFront[playerid]);

	PlayerTextDrawHide(playerid, gVehModelLeft[playerid]);
	PlayerTextDrawHide(playerid, gVehModelCenter[playerid]);
	PlayerTextDrawHide(playerid, gVehModelRight[playerid]);
	PlayerTextDrawHide(playerid, gVehModelHeader[playerid]);
	PlayerTextDrawHide(playerid, gVehModelPrice[playerid]);

    Bit_Set(gHasDealershipOpened, playerid, false);
	CancelSelectTextDraw(playerid);
	return 1;
}

forward OnPlayerClickDealershipTextdraw(playerid, type);

hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if(Bit_Get(gHasDealershipOpened, playerid))
    {
	   	if(clickedid == gBtnRight[playerid])
		{
			CallLocalFunction("OnPlayerClickDealershipTextdraw", "ii", playerid, BTN_RIGHT);
		}
		else if(clickedid == gBtnLeft[playerid])
		{
            CallLocalFunction("OnPlayerClickDealershipTextdraw", "ii", playerid, BTN_LEFT);
		}
		else if(clickedid == gBtnClose[playerid] || clickedid == INVALID_TEXT_DRAW)
		{
			CancelSelectTextDraw(playerid);
			UI_HideDealershipTextDraw(playerid);

            CallLocalFunction("OnPlayerClickDealershipTextdraw", "ii", playerid, BTN_CLOSE);
		}
		else if(clickedid == gBtnPurchase[playerid])
		{
			CallLocalFunction("OnPlayerClickDealershipTextdraw", "ii", playerid, BTN_PURCHASE);
		}
    }
    return 1;
}

hook OnGameModeInit() {
	for(new i = 0; i < MAX_PLAYERS; i++) {
        gBody[i] = TextDrawCreate(135.0, 150.0, "LD_SPAC:white");
        TextDrawLetterSize(gBody[i], 0.0, 0.0);
        TextDrawTextSize(gBody[i], 350.0, 113.0);
        TextDrawAlignment(gBody[i], 1);
        TextDrawColor(gBody[i], 153);
        TextDrawBackgroundColor(gBody[i], 255);
        TextDrawFont(gBody[i], 4);
        TextDrawSetProportional(gBody[i], 0);
        TextDrawSetShadow(gBody[i], 0);

		gBtnRight[i] = TextDrawCreate(161.0, 142.0, "LD_Beat:right");
		TextDrawTextSize(gBtnRight[i], 21.0, 15.0);
		TextDrawAlignment(gBtnRight[i], 1);
		TextDrawColor(gBtnRight[i], -1);
		TextDrawBackgroundColor(gBtnRight[i], 255);
		TextDrawFont(gBtnRight[i], 4);
		TextDrawSetProportional(gBtnRight[i], 0);
		TextDrawSetSelectable(gBtnRight[i], true);

		gBtnLeft[i] = TextDrawCreate(135.0, 142.0, "LD_BEAT:left");
		TextDrawTextSize(gBtnLeft[i], 21.0, 15.0);
		TextDrawAlignment(gBtnLeft[i], 1);
		TextDrawColor(gBtnLeft[i], -1);
		TextDrawBackgroundColor(gBtnLeft[i], 255);
		TextDrawFont(gBtnLeft[i], 4);
		TextDrawSetProportional(gBtnLeft[i], 0);
		TextDrawSetSelectable(gBtnLeft[i], true);

		gBtnClose[i] = TextDrawCreate(474.0, 142.0, "X");
		TextDrawLetterSize(gBtnClose[i], 0.4, 0.4 * 3);
		TextDrawAlignment(gBtnClose[i], 1);
		TextDrawColor(gBtnClose[i], -1);
		TextDrawSetOutline(gBtnClose[i], 1);
		TextDrawBackgroundColor(gBtnClose[i], 255);
		TextDrawFont(gBtnClose[i], 2);
		TextDrawSetProportional(gBtnClose[i], 1);
		TextDrawSetSelectable(gBtnClose[i], true);

		gBtnPurchase[i] = TextDrawCreate(405.0, 253.0, "PURCHASE");
		TextDrawLetterSize(gBtnPurchase[i], 0.4, 0.4 * 3);
		TextDrawAlignment(gBtnPurchase[i], 1);
		TextDrawColor(gBtnPurchase[i], -1);
		TextDrawSetOutline(gBtnPurchase[i], 1);
		TextDrawBackgroundColor(gBtnPurchase[i], 255);
		TextDrawFont(gBtnPurchase[i], 1);
		TextDrawSetProportional(gBtnPurchase[i], 1);
		TextDrawSetSelectable(gBtnPurchase[i], true);

		gPrevNext[i] = TextDrawCreate(179.0, 134.000061, "Prev____Next");
		TextDrawLetterSize(gPrevNext[i], 0.2, 0.2 * 3);
		TextDrawAlignment(gPrevNext[i], 3);
		TextDrawColor(gPrevNext[i], -1378294017);
		TextDrawSetShadow(gPrevNext[i], 1);
		TextDrawBackgroundColor(gPrevNext[i], 255);
		TextDrawFont(gPrevNext[i], 1);
		TextDrawSetProportional(gPrevNext[i], 1);

		gHeaderSide[i] = TextDrawCreate(400.0, 160.0, "Side");
		TextDrawLetterSize(gHeaderSide[i], 0.4, 0.4 * 3);
		TextDrawAlignment(gHeaderSide[i], 1);
		TextDrawColor(gHeaderSide[i], -1);
		TextDrawSetOutline(gHeaderSide[i], 1);
		TextDrawBackgroundColor(gHeaderSide[i], 255);
		TextDrawFont(gHeaderSide[i], 2);
		TextDrawSetProportional(gHeaderSide[i], 1);

		gHeaderBack[i] = TextDrawCreate(288.0, 160.0, "Back");
		TextDrawLetterSize(gHeaderBack[i], 0.4, 0.4 * 3);
		TextDrawAlignment(gHeaderBack[i], 1);
		TextDrawColor(gHeaderBack[i], -1);
		TextDrawSetOutline(gHeaderBack[i], 1);
		TextDrawBackgroundColor(gHeaderBack[i], 255);
		TextDrawFont(gHeaderBack[i], 2);
		TextDrawSetProportional(gHeaderBack[i], 1);

		gHeaderFront[i] = TextDrawCreate(170.0, 160.0, "Front");
		TextDrawLetterSize(gHeaderFront[i], 0.4, 0.4 * 3);
		TextDrawAlignment(gHeaderFront[i], 1);
		TextDrawColor(gHeaderFront[i], -1);
		TextDrawSetOutline(gHeaderFront[i], 1);
		TextDrawBackgroundColor(gHeaderFront[i], 255);
		TextDrawFont(gHeaderFront[i], 2);
		TextDrawSetProportional(gHeaderFront[i], 1);
	}
    return 1;
}

hook OnPlayerConnect(playerid) {
	gVehModelCenter[playerid] = CreatePlayerTextDraw(playerid, 250.0, 160.0, "");
	PlayerTextDrawTextSize(playerid, gVehModelCenter[playerid], 115.0, 112.0);
	PlayerTextDrawAlignment(playerid, gVehModelCenter[playerid], 1);
	PlayerTextDrawColor(playerid, gVehModelCenter[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, gVehModelCenter[playerid], 0);
	PlayerTextDrawFont(playerid, gVehModelCenter[playerid], 5);
	PlayerTextDrawSetProportional(playerid, gVehModelCenter[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, gVehModelCenter[playerid], 400);
	PlayerTextDrawSetPreviewRot(playerid, gVehModelCenter[playerid], 0.0, 0.0, 140.0, 0.899999);
	PlayerTextDrawSetPreviewVehCol(playerid, gVehModelCenter[playerid], 1, 1);

	gVehModelRight[playerid] = CreatePlayerTextDraw(playerid, 365.0, 160.0, "");
	PlayerTextDrawTextSize(playerid, gVehModelRight[playerid], 115.0, 112.0);
	PlayerTextDrawAlignment(playerid, gVehModelRight[playerid], 1);
	PlayerTextDrawColor(playerid, gVehModelRight[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, gVehModelRight[playerid], 0);
	PlayerTextDrawFont(playerid, gVehModelRight[playerid], 5);
	PlayerTextDrawSetProportional(playerid, gVehModelRight[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, gVehModelRight[playerid], 400);
	PlayerTextDrawSetPreviewRot(playerid, gVehModelRight[playerid], 0.0, 0.0, 45.0, 0.899999);
	PlayerTextDrawSetPreviewVehCol(playerid, gVehModelRight[playerid], 1, 1);

	gVehModelLeft[playerid] = CreatePlayerTextDraw(playerid, 135.0, 160.0, "");
	PlayerTextDrawTextSize(playerid, gVehModelLeft[playerid], 115.0, 112.0);
	PlayerTextDrawAlignment(playerid, gVehModelLeft[playerid], 1);
	PlayerTextDrawColor(playerid, gVehModelLeft[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, gVehModelLeft[playerid], 0);
	PlayerTextDrawFont(playerid, gVehModelLeft[playerid], 5);
	PlayerTextDrawSetProportional(playerid, gVehModelLeft[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, gVehModelLeft[playerid], 400);
	PlayerTextDrawSetPreviewRot(playerid, gVehModelLeft[playerid], -20.0, 0.0, 0.0, 0.899999);
	PlayerTextDrawSetPreviewVehCol(playerid, gVehModelLeft[playerid], 1, 1);

	gVehModelHeader[playerid] = CreatePlayerTextDraw(playerid, 310.0, 142.0, "Landstalker");
	PlayerTextDrawLetterSize(playerid, gVehModelHeader[playerid], 0.500000, 1.500000);
	PlayerTextDrawTextSize(playerid, gVehModelHeader[playerid], 0.0, 227.0);
	PlayerTextDrawAlignment(playerid, gVehModelHeader[playerid], 2);
	PlayerTextDrawColor(playerid, gVehModelHeader[playerid], -1);
	PlayerTextDrawSetOutline(playerid, gVehModelHeader[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, gVehModelHeader[playerid], 255);
	PlayerTextDrawFont(playerid, gVehModelHeader[playerid], 3);
	PlayerTextDrawSetProportional(playerid, gVehModelHeader[playerid], 1);

	gVehModelPrice[playerid] = CreatePlayerTextDraw(playerid, 313.0, 125.0, "~g~$3,500,000");
	PlayerTextDrawLetterSize(playerid, gVehModelPrice[playerid], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, gVehModelPrice[playerid], 2);
	PlayerTextDrawColor(playerid, gVehModelPrice[playerid], -1);
	PlayerTextDrawSetOutline(playerid, gVehModelPrice[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, gVehModelPrice[playerid], 255);
	PlayerTextDrawFont(playerid, gVehModelPrice[playerid], 3);
	PlayerTextDrawSetProportional(playerid, gVehModelPrice[playerid], 1);
    return 1;
}


