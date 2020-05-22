#include <ui_TextDrawMenu.inc>

#define MENU_AMMU       (0)

hook OnGameModeInit()
{
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 295.4240, -82.5273, 1002.5156, 40.0, 6, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 312.8376, -167.7640, 1000.5938, 4000, 7, 0);
    return 1;
}

forward OnTextMenuResponse(playerid,menuid,listitem);
public OnTextMenuResponse(playerid,menuid,listitem)
{
    if(menuid == MENU_AMMU)
    {
        switch(listitem)
        {
            case 1:
            {
                if(GetPlayerMoney(playerid) < 50000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_TEC9, 500);
                GivePlayerMoney(playerid, -50000);
            }
            case 2:
            {
                if(GetPlayerMoney(playerid) < 25000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_TEC9, 250);
                GivePlayerMoney(playerid, -25000);
            }
            case 3:
            {
                if(GetPlayerMoney(playerid) < 50000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_UZI, 500);
                GivePlayerMoney(playerid, -50000);
            }
            case 4:
            {
                if(GetPlayerMoney(playerid) < 25000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_UZI, 250);
                GivePlayerMoney(playerid, -25000);
            }
            case 5:
            {
                if(GetPlayerMoney(playerid) < 50000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_MP5, 500);
                GivePlayerMoney(playerid, -50000);
            }
            case 6:
            {
                if(GetPlayerMoney(playerid) < 25000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_MP5, 250);
                GivePlayerMoney(playerid, -25000);
            }
            case 7:
            {
                if(GetPlayerMoney(playerid) < 50000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, 500);
                GivePlayerMoney(playerid, -50000);
            }
            case 8:
            {
                if(GetPlayerMoney(playerid) < 25000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, 250);
                GivePlayerMoney(playerid, -25000);
            }
            case 9:
            {
                if(GetPlayerMoney(playerid) < 50000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_DEAGLE, 500);
                GivePlayerMoney(playerid, -50000);
            }
            case 10:
            {
                if(GetPlayerMoney(playerid) < 25000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_DEAGLE, 250);
                GivePlayerMoney(playerid, -25000);
            }
            case 11:
            {
                if(GetPlayerMoney(playerid) < 50000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_SNIPER, 500);
                GivePlayerMoney(playerid, -50000);
            }
            case 12:
            {
                if(GetPlayerMoney(playerid) < 25000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_SNIPER, 250);
                GivePlayerMoney(playerid, -25000);
            }
            case 13:
            {
                if(GetPlayerMoney(playerid) < 50000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_M4, 500);
                GivePlayerMoney(playerid, -50000);
            }
            case 14:
            {
                if(GetPlayerMoney(playerid) < 25000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_M4, 250);
                GivePlayerMoney(playerid, -25000);
            }
            case 15:
            {
                if(GetPlayerMoney(playerid) < 15000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 1);
                GivePlayerMoney(playerid, -15000);
            }
            case 16:
            {
                if(GetPlayerMoney(playerid) < 1000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                SetPlayerArmour(playerid, 100);
                GivePlayerMoney(playerid, -1000);
            }
        }
    }
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156) || IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938))
    {
        TextMenuHideForPlayer(playerid);
    }
    return 1;
}

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156))
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156) || IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938))
        {
            ShowAmmuMenu(playerid);
        }
    }
    return 1;
}

stock ShowAmmuMenu(playerid) {
    new
        AMMU[615],
        bool:form = true;
    if(form)
    {
        strcat(AMMU,"~y~1.~w~Tec 9 500 ammo [~g~50000~w~]~n~");
        strcat(AMMU,"~y~2.~w~Tec 9 250 ammo [~g~25000~w~]~n~");
        strcat(AMMU,"~y~3.~w~Mac 10 500 ammo [~g~50000~w~]~n~");
        strcat(AMMU,"~y~4.~w~Mac 10 250 ammo [~g~25000~w~]~n~");
        strcat(AMMU,"~y~5.~w~MP5 500 ammo [~g~50000~w~]~n~");
        strcat(AMMU,"~y~6.~w~MP5 250 ammo [~g~25000~w~]~n~");
        strcat(AMMU,"~y~7.~w~Sawn Off 500 ammo [~g~50000~w~]~n~");
        strcat(AMMU,"~y~8.~w~Sawn Off 250 ammo [~g~25000~w~]~n~");
        strcat(AMMU,"~y~9.~w~Deagle 500 ammo [~g~50000~w~]~n~");
        strcat(AMMU,"~y~10.~w~Deagle 250 ammo [~g~25000~w~]~n~");
        strcat(AMMU,"~y~11.~w~Sniper 100 ammo [~g~25000~w~]~n~");
        strcat(AMMU,"~y~12.~w~Sniper 50 ammo [~g~10000~w~]~n~");
        strcat(AMMU,"~y~13.~w~M4 500 ammo [~g~50000~w~]~n~");
        strcat(AMMU,"~y~14.~w~M4 250 ammo [~g~25000~w~]~n~");
        strcat(AMMU,"~y~15.~w~Chainsaw [~g~15000~w~]~n~");
        strcat(AMMU,"~y~16.~w~Armour [~g~1000~w~]");
        form = false;
    }
    TextMenuShowForPlayer(playerid, MENU_AMMU, "~b~AMMUNATION", AMMU, 16);
    return 1;
}