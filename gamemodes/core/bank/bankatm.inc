#include <YSI_Coding\y_hooks>

static enum e_ATM_OPTIONS {
    ATM_NONE,
    ATM_WITHDRAW,
    ATM_DEPOSIT
}

static
    bool:PlayerBankReply[MAX_PLAYERS],
    bool:PlayerHasMenu[MAX_PLAYERS],
    e_ATM_OPTIONS:PlayerATMOption[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerBankReply[playerid] =
    PlayerHasMenu[playerid] = false;
    PlayerATMOption[playerid] = ATM_NONE;
    return 1;
}

hook OnPlayerText(playerid, text[]) {
    if(PlayerBankReply[playerid]) {
        if(isnumeric(text)) {
            new
                value = strval(text);
            if(PlayerATMOption[playerid] == ATM_DEPOSIT)
            {
                if(GetPlayerMoney(playerid) < value) {
                    SendErrorMsg(playerid, "You don't have enough money");
                    return 0;
                }

                // Deduct money from player, add money to player's bank.
                Player_GiveBankMoney(playerid, value, true);
                GivePlayerMoney(playerid, -value);

                // Notify Player
                SendServerMsgF(playerid, "You have deposited %m to your bank account", value);
                SendServerMsgF(playerid, "Bank Account: %m", Player_GetBankMoney(playerid));

                // Update UI.
                ShowATMDepositInfo(playerid);

            }
            if(PlayerATMOption[playerid] == ATM_WITHDRAW) {
                if(Player_GetBankMoney(playerid) < value) {
                    SendErrorMsg(playerid, "You don't have enough money on your bank acc");
                    return 0;
                }

                // Deduct money from bank, add money to player.
                Player_RemoveBankMoney(playerid, value);
                GivePlayerMoney(playerid, value);

                // Notify Player
                SendServerMsgF(playerid, "You have withdrew %m from your bank account", value);
                SendServerMsgF(playerid, "Bank Account: %m", Player_GetBankMoney(playerid));

                // Update UI
                ShowATMWithdrawInfo(playerid);
            }
            return ~0;
        }
    }
    return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(newkeys == KEY_YES && Player_IsNearATM(playerid)) {
        if(PlayerBankReply[playerid]) {
            PlayerATMOption[playerid] = ATM_NONE;
            PlayerBankReply[playerid] = false;
        }
        ShowATMMenu(playerid);
    }
    if(newkeys == KEY_NO && Player_IsNearATM(playerid)) {
        TextMenu_HideSpecific(playerid, "AtmMenu");
        TextInfo_HideSpecific(playerid, "ATMDEP");
        TextInfo_HideSpecific(playerid, "ATMWITH");
        PlayerATMOption[playerid] = ATM_NONE;
        PlayerBankReply[playerid] = false;
    }
    return 1;
}

hook OnPlayerSecondUpdate(playerid)
{
    if(!Player_IsNearATM(playerid) && PlayerHasMenu[playerid]) {
        TextMenu_HideSpecific(playerid, "AtmMenu");
        TextInfo_HideSpecific(playerid, "ATMDEP");
        TextInfo_HideSpecific(playerid, "ATMWITH");
        PlayerATMOption[playerid] = ATM_NONE;
        PlayerBankReply[playerid] = false;
        PlayerHasMenu[playerid] = false;
    }
    return 1;
}

TDMenu:AtmMenu(playerid, listitem) {
    switch(listitem) {
        case 1: {
            ShowATMDepositInfo(playerid);
        }
        case 2: {
            ShowATMWithdrawInfo(playerid);
        }
    }
    return 1;
}

ShowATMMenu(playerid)
{
    new
        string[48];

    TextMenu_Create(playerid, "AtmMenu", "ATM");
    format(string, sizeof(string), "Balance: ~g~%m~w~~n~~n~", Player_GetBankMoney(playerid));
    TextInfo_Add(playerid, string);
    TextMenu_Add(playerid, "~w~Deposit");
    TextMenu_Add(playerid, "~w~Withdraw");
    TextMenu_Show(playerid);
    PlayerHasMenu[playerid] = true;
    return 1;
}

ShowATMDepositInfo(playerid)
{
    new
        string[48];

    TextInfo_Create(playerid, "ATMDEP", "ATM DEPOSIT");
    format(string, sizeof(string), "Balance: ~g~%m~w~~n~~n~", Player_GetBankMoney(playerid));
    TextInfo_Add(playerid, string);
    TextInfo_Add(playerid, "Type in the chat how much you want to ~g~Deposit~w~");
    TextInfo_Show(playerid);
    PlayerATMOption[playerid] = ATM_DEPOSIT;
    PlayerBankReply[playerid] = true;
    return 1;
}

ShowATMWithdrawInfo(playerid)
{
    new
        string[48];

    TextInfo_Create(playerid, "ATMWITH", "ATM WITHDRAW");
    format(string, sizeof(string), "Balance: ~g~%m~w~~n~~n~", Player_GetBankMoney(playerid));
    TextInfo_Add(playerid, string);
    TextInfo_Add(playerid, "Type in the chat how much you want to ~g~Withdraw~w~");
    TextInfo_Show(playerid);
    PlayerATMOption[playerid] = ATM_WITHDRAW;
    PlayerBankReply[playerid] = true;
    return 1;
}