CMD:bank(playerid)
{
    new string[128];
    TextInfo_Create(playerid, "BankInfo", "Bank Info");
    format(string, sizeof(string), "~b~Account Balance: ~g~%d", Player_GetBankMoney(playerid));
    TextInfo_Add(playerid, string);
    format(string, sizeof(string), "~b~Tax Balance: ~g~%d", Player_GetBankTax(playerid));
    TextInfo_Add(playerid, string);
    format(string, sizeof(string), "~b~Bank Dept.: ~r~%d", Player_GetBankDept(playerid));
    TextInfo_Add(playerid, string);
    TextInfo_Show(playerid);
    return 1;
}