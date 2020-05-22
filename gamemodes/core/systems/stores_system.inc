#include <ui_TextDrawMenu.inc>
#include <YSI_Coding\y_timers>

#define MENU_AMMU       (0)
#define MENU_MECH       (1)

new 
    FixingVeh[MAX_PLAYERS],
    Timer:FixVehTimer[MAX_PLAYERS]
;

hook OnGameModeInit()
{
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 295.4240, -82.5273, 1002.5156, 40.0, 6, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 312.8376, -167.7640, 1000.5938, 40.0, 7, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to view services", COLOR_WHITE, 1015.4679, -930.1953, 43.1797, 40.0, 0, 0);
    CreateActor(50, 1015.4679, -930.1953, 42.1797, 184.6950);
    CreateDynamicMapIcon(1015.4679, -930.1953, 42.1797, 27, -1, .streamdistance = 200.0, .style = MAPICON_GLOBAL);
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
    if(menuid == MENU_MECH)
    {
        switch(listitem)
        {
            case 1:
            {
                if(!IsPlayerInAnyVehicle(playerid)) {
                    return SendServerMsg(playerid, "You're not in any vehicle");
                }
                if(GetPlayerMoney(playerid) < 1520) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GameTextForPlayer(playerid, "~w~Fixing your vehicle don't move", 5000, 3);
                FixingVeh[playerid] = 1;
                FixVehTimer[playerid] = defer FixVehTime(playerid);
            }
            case 2:
            {
                if(Player_GetInstaFix(playerid) != 0) {
                    return SendServerMsg(playerid, "You already have instafix!");
                }
                if(GetPlayerMoney(playerid) < 15000) {
                    return SendServerMsg(playerid, "Not Enough Money!");
                }
                GivePlayerMoney(playerid, -15000);
                Player_SetInstaFix(playerid, 1);
            }
        }
    }
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156) || !IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938))
    {
        TextMenuHide(playerid, MENU_AMMU);
    }
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1015.4679, -930.1953, 42.1797))
    {
        if(FixingVeh[playerid] == 1)
        {
            stop FixVehTimer[playerid];
            GameTextForPlayer(playerid, "~r~You moved canceled the fix", 3000, 3);
            FixingVeh[playerid] = 0;
        }
        TextMenuHide(playerid, MENU_MECH);
    }
    return 1;
}

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES))
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156) || IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938))
        {
            ShowAmmuMenu(playerid);
        }
    }
    if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 5.0, 1015.4679, -930.1953, 42.1797))
    {
        ShowMechServices(playerid);
    }
    return 1;
}

stock ShowAmmuMenu(playerid) {
    new
        AMMU[615],
        bool:form = true;
    if(form)
    {
        strcat(AMMU,"~y~1.~w~Tec 9 500 ammo [~g~$50,000~w~]~n~");
        strcat(AMMU,"~y~2.~w~Tec 9 250 ammo [~g~$25,000~w~]~n~");
        strcat(AMMU,"~y~3.~w~Mac 10 500 ammo [~g~$50,000~w~]~n~");
        strcat(AMMU,"~y~4.~w~Mac 10 250 ammo [~g~$25,000~w~]~n~");
        strcat(AMMU,"~y~5.~w~MP5 500 ammo [~g~$50,000~w~]~n~");
        strcat(AMMU,"~y~6.~w~MP5 250 ammo [~g~$25,000~w~]~n~");
        strcat(AMMU,"~y~7.~w~Sawn Off 500 ammo [~g~$50,000~w~]~n~");
        strcat(AMMU,"~y~8.~w~Sawn Off 250 ammo [~g~$25,000~w~]~n~");
        strcat(AMMU,"~y~9.~w~Deagle 500 ammo [~g~$50,000~w~]~n~");
        strcat(AMMU,"~y~10.~w~Deagle 250 ammo [~g~$25,000~w~]~n~");
        strcat(AMMU,"~y~11.~w~Sniper 100 ammo [~g~$25,000~w~]~n~");
        strcat(AMMU,"~y~12.~w~Sniper 50 ammo [~g~$10,000~w~]~n~");
        strcat(AMMU,"~y~13.~w~M4 500 ammo [~g~$50,000~w~]~n~");
        strcat(AMMU,"~y~14.~w~M4 250 ammo [~g~$25,000~w~]~n~");
        strcat(AMMU,"~y~15.~w~Chainsaw [~g~$15,000~w~]~n~");
        strcat(AMMU,"~y~16.~w~Armour [~g~$1,000~w~]");
        form = false;
    }
    TextMenuShowForPlayer(playerid, MENU_AMMU, "~b~AMMUNATION", AMMU, 16);
    return 1;
}

stock ShowMechServices(playerid) 
{
    new
        MECH[600],
        bool:form = true;
    if(form)
    {
        strcat(MECH,"~y~1.~w~Fix your vehicle [~g~1520~w~]~n~");
        strcat(MECH,"~y~2.~w~Insta fix [~g~15000~w~]~n~");
        form = false;
    }
    TextMenuShowForPlayer(playerid, MENU_MECH, "~b~MECHANIC SERVICES", MECH, 2);
    return 1;
}

timer FixVehTime[5000](playerid)
{
    FixingVeh[playerid] = 0;
    RepairVehicle(GetPlayerVehicleID(playerid));
    return 1;
}