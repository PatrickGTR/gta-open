#define LOTTO_MAX_JACKPOT 		(25000) //+25, 000
#define LOTTO_MIN_JACKPOT		(10000) //+10, 100
#define LOTTO_START     		(50000) //50, 00 starting lotto price
#define MAX_LOTTO_INPUT			(MAX_PLAYERS)

#define TICKET_PRICE      		(1000)

new
	LottoJackpot = LOTTO_START,
	BitArray:lottoUsedNumbers<MAX_LOTTO_INPUT>,
	BitArray:PlayerBoughtTicket<MAX_PLAYERS>,
	PlayerLottoNumber[MAX_PLAYERS] = {0, ...},
    lottoDrawCounter = 0,
    lottoLastTick = 0;

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {

    // initiate the global data on start up.
    lottoLastTick = gettime();
    lottoDrawCounter = 0;
    LottoJackpot = LOTTO_START;
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerLottoNumber[playerid] = 0;
    Bit_Set(PlayerBoughtTicket, playerid, false);
    return 1;
}

hook OnServerSecondUpdate() {

    // only show the message every 2 minutes
    if(gettime() - lottoLastTick < (60 * 2)) {
        // go to next hook.
        return 1;
    }

    // draw every 10 minutes.
    if(lottoDrawCounter == 5) {
        new
            genRandomNum = 10,//random(MAX_LOTTO_INPUT - 1) + 1,
            winnerID = INVALID_PLAYER_ID;

        foreach(new i : Player) {

            // set winner id.
            if(PlayerLottoNumber[i] == genRandomNum) {
                winnerID = i;
            }

            // reset all data
            PlayerLottoNumber[i] = 0;
            Bit_Vet(PlayerBoughtTicket, i);
        }

        for(new i; i < MAX_LOTTO_INPUT; i++) {
            Bit_Vet(lottoUsedNumbers, i);
        }

        if(winnerID != INVALID_PLAYER_ID) {
            MessageBox_ShowAllF(
                TYPE_INFORMATION,
                "~y~Lotto Informataion",
                "~y~WINNER WINNER CHICKEN DINNER! ~p~%p ~w~won ~g~%m ~w~from the lottery!~n~\
                ~w~Make sure you get a ticket for next draw ~p~/lotto [1 - %i]",
                _,
                winnerID, LottoJackpot, MAX_LOTTO_INPUT
            );

            GivePlayerMoney(winnerID, LottoJackpot);
            LottoJackpot = LOTTO_START;

            ApplyAnimation(winnerID, "OTB", "wtchrace_win", 4.1, false, true, true, false, 3300); // Winning animation
        }

        if(winnerID == INVALID_PLAYER_ID) {

            // increase the prize.
            LottoJackpot = LottoJackpot + random(LOTTO_MAX_JACKPOT - LOTTO_MIN_JACKPOT) + LOTTO_MIN_JACKPOT;

            // Notify players.
            MessageBox_ShowAllF(
                TYPE_INFORMATION,
                "~y~Lotto Information",
                "There was no lotto winner for this draw. The jackpot will go up to ~g~%m~n~\
                ~w~use ~p~/lotto [1 - %i] ~w~to buy a ticket and get the chance to win the money!",
                _,
                LottoJackpot, MAX_LOTTO_INPUT
            );
        }
        lottoDrawCounter = 0;
        lottoLastTick = gettime();
        return 1;
    }

    MessageBox_ShowAllF(
        TYPE_INFORMATION,
        "~y~Lotto Information",
        "~w~Current lotto jackpoint is ~g~%m~n~\
        ~w~use ~p~/lotto [1 - %i] ~w~to buy a ticket and get the chance to win the money!",
        _,
        LottoJackpot, MAX_LOTTO_INPUT
    );
    lottoLastTick = gettime();
    lottoDrawCounter ++;
	return 1;
}

CMD:lotto(playerid, params[]) {
    if(isnull(params) || !IsNumeric(params)) {
      	SendMsgF(playerid, COLOR_YELLOW, "Usage: "C_WHITE"/lotto <1 - %i>", MAX_LOTTO_INPUT);
      	SendMsgF(playerid, COLOR_WHITE, "The current Jackpot is "C_GREEN"%m", LottoJackpot);
        return 1;
    }

    new
    	lottoID = strval(params);

    if(GetPlayerMoney(playerid) < TICKET_PRICE) {
    	return SendErrorMsg(playerid, "You don't have enough money to buy a ticket!");
    }

    if(lottoID <= 0 || lottoID > MAX_LOTTO_INPUT) {
    	return SendErrorMsgF(playerid, "You can only pick a number between 1 and %i", MAX_LOTTO_INPUT);
    }

    if(Bit_Get(lottoUsedNumbers, lottoID)) {
		return SendErrorMsgF(playerid, "The lotto "C_GREY"#%i "C_WHITE"has already been used, try a different number!", lottoID);
    }

    if(Bit_Get(PlayerBoughtTicket, playerid)) {
    	return SendErrorMsg(playerid, "You already have a purchased a lotto ticket!");
    }


    Bit_Let(lottoUsedNumbers, lottoID);
    Bit_Let(PlayerBoughtTicket, playerid);
    PlayerLottoNumber[playerid] = lottoID;

    GivePlayerMoney(playerid, -TICKET_PRICE); //Takes away the ticket cost.

    SendMsgF(playerid, COLOR_YELLOW, "** LOTTO ** "C_WHITE"You have bought a lottery ticket! Your lotto "C_GREY"#%i"C_WHITE", just wait for the next draw for reults!", lottoID);
    SendMsgF(playerid, COLOR_YELLOW, "** LOTTO ** "C_WHITE"Draws are held every "C_GREY"10 "C_WHITE"minutes and the winners are announced. The current jackpot is "C_GREEN"%m", LottoJackpot);
    return 1;
}