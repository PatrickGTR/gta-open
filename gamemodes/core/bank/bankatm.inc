#include <YSI_Coding\y_hooks>

static
    bool:BankReply[MAX_PLAYERS],
    bool:deposit[MAX_PLAYERS],
    bool:withdraw[MAX_PLAYERS]
;

hook OnPlayerText(playerid, text[])
{
    if(BankReply[playerid])
    {
        if(isnumeric(text))
        {
            new value = strval(text);
            if(deposit[playerid])
            {
                if(GetPlayerMoney(playerid) < value) {
                    SendErrorMsg(playerid, "You don't have enough money");
                    return -1;
                }
                Player_GiveBankMoney(playerid, value, true);
                GivePlayerMoney(playerid, -value);
                SendServerMsgF(playerid, "You have deposited %d to your bank account", value);
                SendServerMsgF(playerid, "Bank Account: %d", Player_GetBankMoney(playerid));
            }
            else if(withdraw[playerid])
            {
                if(Player_GetBankMoney(playerid) < value) {
                    SendErrorMsg(playerid, "You don't have enough money on your bank acc");
                    return -1;
                }
                Player_RemoveBankMoney(playerid, value);
                GivePlayerMoney(playerid, value);
                SendServerMsgF(playerid, "You have withdrew %d from your bank account", value);
                SendServerMsgF(playerid, "Bank Account: %d", Player_GetBankMoney(playerid));
            }
            return ~0;
        }
    }
    return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == KEY_YES && IsPlayerNearATM(playerid))
    {
        if(BankReply[playerid]) {
            deposit[playerid] = false;
            withdraw[playerid] = false;
            BankReply[playerid] = false;
        }
        ShowATMMenu(playerid);
    }
    if(newkeys == KEY_NO && IsPlayerNearATM(playerid))
    {
        TextMenu_HideSpecific(playerid, "AtmMenu");
        TextInfo_HideSpecific(playerid, "ATMDEP");
        TextInfo_HideSpecific(playerid, "ATMWITH");
        deposit[playerid] = false;
        withdraw[playerid] = false;
        BankReply[playerid] = false;
    }
    return 1;
}

hook OnPlayerSecondUpdate(playerid)
{
    if(!IsPlayerNearATM(playerid))
    {
        TextMenu_HideSpecific(playerid, "AtmMenu");
        TextInfo_HideSpecific(playerid, "ATMDEP");
        TextInfo_HideSpecific(playerid, "ATMWITH");
        deposit[playerid] = false;
        withdraw[playerid] = false;
        BankReply[playerid] = false;
    }
    return 1;
}

forward AtmMenu(playerid, listitem);
public AtmMenu(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            ShowATMDepositInfo(playerid);
        }
        case 2:
        {
            ShowATMWithdrawInfo(playerid);
        }
    }
    return 1;
}

ShowATMMenu(playerid)
{
    new string[128];
    TextMenu_Create(playerid, "AtmMenu", "ATM");
    format(string, sizeof(string), "_________________________Bank: ~b~$%d~w~~n~~n~", Player_GetBankMoney(playerid));
    TextInfo_Add(playerid, string);
    TextMenu_Add(playerid, "~w~Deposit");
    TextMenu_Add(playerid, "~w~Withdraw");
    TextMenu_Show(playerid);
    return 1;
}

ShowATMDepositInfo(playerid)
{
    new string[128];
    TextInfo_Create(playerid, "ATMDEP", "ATM DEPOSIT");
    format(string, sizeof(string), "_________________________Bank: ~b~$%d~w~~n~~n~", Player_GetBankMoney(playerid));
    TextInfo_Add(playerid, string);
    TextInfo_Add(playerid, "___Type in the chat how much you want to ~g~Deposit~w~");
    TextInfo_Show(playerid);
    deposit[playerid] = true;
    BankReply[playerid] = true;
    return 1;
}

ShowATMWithdrawInfo(playerid)
{
    new string[128];
    TextInfo_Create(playerid, "ATMWITH", "ATM WITHDRAW");
    format(string, sizeof(string), "_________________________Bank: ~b~$%d~w~~n~~n~", Player_GetBankMoney(playerid));
    TextInfo_Add(playerid, string);
    TextInfo_Add(playerid, "___Type in the chat how much you want to ~g~Withdraw~w~");
    TextInfo_Show(playerid);
    withdraw[playerid] = true;
    BankReply[playerid] = true;
    return 1;
}