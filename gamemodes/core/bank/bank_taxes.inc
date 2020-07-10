#include <YSI_Coding\y_hooks>

static
    percentage[MAX_PLAYERS],
    bankpercentage[MAX_PLAYERS];

stock Player_Tax(playerid)
{
    if(Player_GetBankMoney(playerid) > 100000 && IsPlayerConnected(playerid))
    {
        if(VIP_GetPlayerLevel(playerid) != 0) {
            return 0;
        }
        new string[256];
        percentage[playerid] = (Player_GetBankMoney(playerid)/100) * 25;
        bankpercentage[playerid] = (percentage[playerid]/100) * 50;
        Player_RemoveBankMoney(playerid, percentage[playerid]);
        TextInfo_Create(playerid, "Taxes", "Taxes");
        if(Player_GetBankDept(playerid) != 0) {
            new newPDept = percentage[playerid] - Player_GetBankDept(playerid);
            if(newPDept < 0) {
                Player_RemoveBankDept(playerid, percentage[playerid]);
            }
            else if(newPDept == 0) {
                Player_RemoveBankDept(playerid, percentage[playerid]);
            }
            else if(newPDept > 0) {
                Player_RemoveBankDept(playerid, Player_GetBankDept(playerid));
            }
            format(string, sizeof(string), "~r~Dept. Left: ~b~%d~n~", Player_GetBankDept(playerid));
            TextInfo_Add(playerid, string);
            format(string, sizeof(string), "~w~Deduced From Bank: ~r~$%d~n~", percentage[playerid]);
            TextInfo_Add(playerid, string);
        }
        else if(Player_GetBankDept(playerid) == 0) {
            format(string, sizeof(string), "~y~Tax Balance Added: ~g~$%d~n~~w~", bankpercentage[playerid]);
            TextInfo_Add(playerid, string);
            Player_AddBankTax(playerid, bankpercentage[playerid], true);
            format(string, sizeof(string), "~y~Total Tax Balance: ~g~$%d~n~~w~", Player_GetBankTax(playerid));
            TextInfo_Add(playerid, string);
            format(string, sizeof(string), "~w~Deduced From Bank: ~r~$%d", bankpercentage[playerid]);
            TextInfo_Add(playerid, string);
        }
        TextInfo_Show(playerid);
    }
    percentage[playerid] = 0;
    bankpercentage[playerid] = 0;
    return 1;
}