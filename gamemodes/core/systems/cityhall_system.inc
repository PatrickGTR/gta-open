#include <YSI_Coding\y_hooks>

static
    BotAnna,
    TaxRefundTick[MAX_PLAYERS];

const
    CHANGE_SKILL_PRICE  = 15_000;

hook OnGameModeInit() {
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 359.7139, 173.5916, 1009.3893, 40.0, 26, 0);
    BotAnna = CreateActor(141, 359.7139, 173.5916, 1008.3893, 271.1871);
    SetActorVirtualWorld(BotAnna, 26);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_YES)) {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 359.7139, 173.5916, 1008.3893)) {
            ShowCHMenu(playerid);
        }
    }
    return 1;
}

hook OnPlayerSecondUpdate(playerid) {
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 359.7139, 173.5916, 1008.3893)) {
        TextMenu_HideSpecific(playerid, "TextMenuCityHall");
    }
    return 1;
}

forward TextMenuCityHall(playerid, listitem);
public TextMenuCityHall(playerid, listitem) {
    switch(listitem) {
        case 1: 
        {
            new string[256];
            if(gettime() - TaxRefundTick[playerid] < 1440) {
                return SendErrorMsg(playerid, "You can only take 1 refund per day.");
            }
            if(Player_GetBankDept(playerid) != 0) {
                TextInfo_Create(playerid, "TRINFO", "Tax Refund");
                format(string, sizeof(string), "~y~Bank Dept.: ~r~%d~n~", Player_GetBankDept(playerid));
                TextInfo_Add(playerid, string);
                TextInfo_Add(playerid, "~w~You have Existing Bank Dept.~n~");
                TextInfo_Add(playerid, "__________________Tax Refund: ~r~Denied.");
                TaxRefundTick[playerid] = gettime();
                TextInfo_Show(playerid);
                return 0;
            }
            if(Player_GetBankTax(playerid) <= 100000) {
                TextInfo_Create(playerid, "TRINFO", "Tax Refund");
                format(string, sizeof(string), "~r~Bank Tax Balance: ~b~%d~n~", Player_GetBankTax(playerid));
                TextInfo_Add(playerid, string);
                TextInfo_Add(playerid, "Your tax balance must be 1M+ for you to claim it~n~");
                TextInfo_Add(playerid, "__________________Tax Refund: ~r~Denied.");
                TaxRefundTick[playerid] = gettime();
                TextInfo_Show(playerid);
                return -1;
            }
            GivePlayerMoney(playerid, Player_GetBankTax(playerid));
            TextInfo_Create(playerid, "TRINFO", "Tax Refund");
            format(string, sizeof(string), "~r~Bank Tax Balance: ~b~%d~n~", Player_GetBankTax(playerid));
            TextInfo_Add(playerid, string);
            format(string, sizeof(string), "__________________Tax Refund: ~g~$%d", Player_GetBankTax(playerid));
            TextInfo_Add(playerid, string);
            TextInfo_Show(playerid);
            TaxRefundTick[playerid] = gettime();
            Player_RemoveBankTax(playerid, Player_GetBankTax(playerid));
        }
        case 2: {
            if(GetPlayerMoney(playerid) < CHANGE_SKILL_PRICE) {
                return SendErrorMsg(playerid, "Not Enough Money!");
            }
            if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
                return SendErrorMsg(playerid, "Only civilians can change skill.");
            }
            Player_SetJob(playerid, TYPE_NO_JOB);
            Player_ShowJobMenu(playerid);
            GivePlayerMoney(playerid, -CHANGE_SKILL_PRICE);
            ShowCHMenu(playerid);
        }
    }
    return 1;
}
//Add more services.
stock ShowCHMenu(playerid) {
    TextMenu_Create(playerid, "TextMenuCityHall", "City Hall");
    TextMenu_Add(playerid, "~w~Tax refund");
    TextMenu_Add(playerid, "~w~Skill Change [~g~$15000~w~]");
    TextMenu_Show(playerid);
    return 1;
}