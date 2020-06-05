#include <YSI_Coding\y_hooks>

static 
    BotAnna
;

hook OnGameModeInit()
{
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 359.7139, 173.5916, 1009.3893, 40.0, 26, 0);
    BotAnna = CreateActor(141, 359.7139, 173.5916, 1008.3893, 271.1871);
    SetActorVirtualWorld(BotAnna, 26);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES))
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 359.7139, 173.5916, 1008.3893))
        {
            ShowCHMenu(playerid);
        }
    }
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 359.7139, 173.5916, 1008.3893))
    {
        TextMenu_HideSpecific(playerid, "TextMenuCityHall");
    }
    return 1;
}

forward TextMenuCityHall(playerid, listitem);
public TextMenuCityHall(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            if(GetPlayerMoney(playerid) < 15000) {
                return SendErrorMsg(playerid, "Not Enough Money!");
            }
            GivePlayerMoney(playerid, -15000);
            Player_ShowJobMenu(playerid);
            ShowCHMenu(playerid);
        }
    }
    return 1;
}
//Add more services.
stock ShowCHMenu(playerid) 
{
    TextMenu_Create(playerid, "TextMenuCityHall", "City Hall");
    TextMenu_Add(playerid, "Skill Change [~g~$15000~w~]");
    TextMenu_Show(playerid);
    return 1;
}