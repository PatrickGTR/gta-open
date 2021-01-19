#include <YSI_Coding\y_hooks>

const DEATH_TAX_PERCENTAGE = 4;
const WEEKLY_TAX_PERCENTANGE = 10;

hook OnPlayerDeathEx(playerid, killerid, reason) {
    new
        cashInHand = GetPlayerMoney(playerid) + Player_GetBankMoney(playerid),
        tax = (cashInHand / 100) * DEATH_TAX_PERCENTAGE;

    MessageBox_ShowF(
        playerid,
        TYPE_MSGBOX,
        "~r~Life Insurance",
        "~w~Thank you for paying your life insurance.\
        ~n~\
        You have been charged ~r~%m",
        _,
        tax
    );

    GivePlayerMoney(playerid, -tax);
    Server_GiveMoney(tax);
    return 1;
}

hook OnServerWeekReset() {
    new
        cashInHand,
        tax;
    foreach(new playerid : Player) {
        if(!Player_IsLoggedIn(playerid)) {
            continue;
        }

        cashInHand = GetPlayerMoney(playerid) + Player_GetBankMoney(playerid);
        tax = (cashInHand / 100) * WEEKLY_TAX_PERCENTANGE;

        MessageBox_ShowF(
            playerid,
            TYPE_MSGBOX,
            "~r~Weekly Tax",
            "~w~Thank you for paying your weekly tax.\
            ~n~\
            You have been charged ~r~%m\
            ~n~~n~\
            ~w~The money goes to fund random hit placements.",
            _,
            tax
        );
        Server_GiveMoney(tax);
    }
}

stock Server_GetMoney() {
    return GetSVarInt("SERVER_MONEY");
}
Server_GiveMoney(amount) {
    SetSVarInt("SERVER_MONEY", Server_GetMoney() + amount);
}