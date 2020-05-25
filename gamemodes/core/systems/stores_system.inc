#include <YSI_Coding\y_timers>

#define MENU_MECH       (3)

static
    bool:PlayerFixingVehicle[MAX_PLAYERS],
    Timer:PlayerFixingVehicleTimer[MAX_PLAYERS];

hook OnGameModeInit()
{
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 295.4240, -82.5273, 1002.5156, 40.0, 6, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 312.8376, -167.7640, 1000.5938, 40.0, 7, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to view services", COLOR_WHITE, 1015.4679, -930.1953, 43.1797, 40.0, 0, 0);
    CreateActor(50, 1015.4679, -930.1953, 42.1797, 184.6950);
    CreateDynamicMapIcon(1015.4679, -930.1953, 42.1797, 27, -1, .streamdistance = 200.0, .style = MAPICON_GLOBAL);
    return 1;
}

forward TextMenuAmmunationMain(playerid, listitem);
public TextMenuAmmunationMain(playerid, listitem)
{
    switch(listitem) {
        case 1: {
            if(GetPlayerMoney(playerid) < 50000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_TEC9, 500);
            GivePlayerMoney(playerid, -50000);
            Ammunation_ShowMenu(playerid);
        }
        case 2: {
            if(GetPlayerMoney(playerid) < 25000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_TEC9, 250);
            GivePlayerMoney(playerid, -25000);
            Ammunation_ShowMenu(playerid);
        }
        case 3: {
            if(GetPlayerMoney(playerid) < 50000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_UZI, 500);
            GivePlayerMoney(playerid, -50000);
            Ammunation_ShowMenu(playerid);
        }
        case 4:
        {
            if(GetPlayerMoney(playerid) < 25000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_UZI, 250);
            GivePlayerMoney(playerid, -25000);
            Ammunation_ShowMenu(playerid);
        }
        case 5:
        {
            if(GetPlayerMoney(playerid) < 50000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_MP5, 500);
            GivePlayerMoney(playerid, -50000);
            Ammunation_ShowMenu(playerid);
        }
        case 6: {
            if(GetPlayerMoney(playerid) < 25000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_MP5, 250);
            GivePlayerMoney(playerid, -25000);
            Ammunation_ShowMenu(playerid);
        }
        case 7: {
            if(GetPlayerMoney(playerid) < 50000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, 500);
            GivePlayerMoney(playerid, -50000);
            Ammunation_ShowMenu(playerid);
        }
        case 8: {
            if(GetPlayerMoney(playerid) < 25000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, 250);
            GivePlayerMoney(playerid, -25000);
            Ammunation_ShowMenu(playerid);
        }
        case 9: {
            if(GetPlayerMoney(playerid) < 50000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_DEAGLE, 500);
            GivePlayerMoney(playerid, -50000);
            Ammunation_ShowMenu(playerid);
        }
        case 10: {
            if(GetPlayerMoney(playerid) < 25000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_DEAGLE, 250);
            GivePlayerMoney(playerid, -25000);
            Ammunation_ShowMenu(playerid);
        }
        case 11: {
            SendClientMessage(playerid, -1, "Next Page");
            Ammunation_ShowMenu(playerid, true);
        }
    }
    return 1;
}

forward TextMenuAmmunationNext(playerid, listitem);
public TextMenuAmmunationNext(playerid, listitem) {
    switch(listitem) {
        case 1: {
            if(GetPlayerMoney(playerid) < 50000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_SNIPER, 100);
            GivePlayerMoney(playerid, -50000);
            Ammunation_ShowMenu(playerid, true);
        }
        case 2: {
            if(GetPlayerMoney(playerid) < 25000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_SNIPER, 50);
            GivePlayerMoney(playerid, -25000);
            Ammunation_ShowMenu(playerid, true);
        }
        case 3: {
            if(GetPlayerMoney(playerid) < 50000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_M4, 500);
            GivePlayerMoney(playerid, -50000);
            Ammunation_ShowMenu(playerid, true);
        }
        case 4: {
            if(GetPlayerMoney(playerid) < 25000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_M4, 250);
            GivePlayerMoney(playerid, -25000);
            Ammunation_ShowMenu(playerid, true);
        }
        case 5: {
            if(GetPlayerMoney(playerid) < 15000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 1);
            GivePlayerMoney(playerid, -15000);
            Ammunation_ShowMenu(playerid, true);
        }
        case 6: {
            if(GetPlayerMoney(playerid) < 1000) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            SetPlayerArmour(playerid, 100);
            GivePlayerMoney(playerid, -1000);
            Ammunation_ShowMenu(playerid, true);
        }
        case 7: {
            Ammunation_ShowMenu(playerid);
            SendClientMessage(playerid, -1, "Previous Page.");
        }
    }
    return 1;
}

forward TextMenuMechanic(playerid, listitem);
public TextMenuMechanic(playerid, listitem)
{
    switch(listitem) {
        case 1: {
            if(!IsPlayerInAnyVehicle(playerid)) {
                return SendServerMsg(playerid, "You're not in any vehicle");
            }
            if(GetPlayerMoney(playerid) < 1520) {
                return SendServerMsg(playerid, "Not Enough Money!");
            }
            GameTextForPlayer(playerid, "~w~Fixing your vehicle don't move", 5000, 3);
            PlayerFixingVehicle[playerid] = true;
            PlayerFixingVehicleTimer[playerid] = defer VehicleFixTimer(playerid);
        }
        case 2:{
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
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156)) {
        if(Player_IsInAmmu(playerid)) {
            return 1;
        }
        TextMenu_HideSpecific(playerid, "TextMenuAmmunationMain");
        TextMenu_HideSpecific(playerid, "TextMenuAmmunationNext");

    }
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938)) {
        if(Player_IsInAmmu(playerid)) {
            return 1;
        }
        TextMenu_HideSpecific(playerid, "TextMenuAmmunationMain");
        TextMenu_HideSpecific(playerid, "TextMenuAmmunationNext");
    }
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1015.4679, -930.1953, 42.1797)) {
        if(PlayerFixingVehicle[playerid]) {
            stop PlayerFixingVehicleTimer[playerid];
            GameTextForPlayer(playerid, "~r~You moved, fix canceled", 3000, 3);
            PlayerFixingVehicle[playerid] = false;
        }
        TextMenu_HideSpecific(playerid, "TextMenuMechanic");
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_YES)) {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156) || IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938)) {
            Ammunation_ShowMenu(playerid);
        }
    }
    if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 5.0, 1015.4679, -930.1953, 42.1797)) {
        ShowMechServices(playerid);
    }
    return 1;
}

stock Ammunation_ShowMenu(playerid, bool:next = false) {
    
    if(!next) {
        TextMenu_Create(playerid, "TextMenuAmmunationMain", "Ammunation");
        TextMenu_Add(playerid, "~w~Tec 9 500 ammo [~g~$50,000~w~]");
        TextMenu_Add(playerid, "~w~Tec 9 250 ammo [~g~$25,000~w~]");
        TextMenu_Add(playerid, "~w~Mac 10 500 ammo [~g~$50,000~w~]");
        TextMenu_Add(playerid, "~w~Mac 10 250 ammo [~g~$25,000~w~]");
        TextMenu_Add(playerid, "~w~MP5 500 ammo [~g~$50,000~w~]");
        TextMenu_Add(playerid, "~w~MP5 250 ammo [~g~$25,000~w~]");
        TextMenu_Add(playerid, "~w~Sawn Off 500 ammo [~g~$50,000~w~]");
        TextMenu_Add(playerid, "~w~Sawn Off 250 ammo [~g~$25,000~w~]");
        TextMenu_Add(playerid, "~w~Deagle 500 ammo [~g~$50,000~w~]");
        TextMenu_Add(playerid, "~w~Deagle 250 ammo [~g~$25,000~w~]");
        TextMenu_Add(playerid, "~y~Next Page");
    }
    else {
        TextMenu_Create(playerid, "TextMenuAmmunationNext", "Ammunation");
        TextMenu_Add(playerid, "~w~Sniper 100 ammo [~g~$25,000~w~]");
        TextMenu_Add(playerid, "~w~Sniper 50 ammo [~g~$10,000~w~]");
        TextMenu_Add(playerid, "~w~M4 500 ammo [~g~$50,000~w~]");
        TextMenu_Add(playerid, "~w~M4 250 ammo [~g~$25,000~w~]");
        TextMenu_Add(playerid, "~w~Chainsaw [~g~$15,000~w~]");
        TextMenu_Add(playerid, "~w~Armour [~g~$1,000~w~]");
        TextMenu_Add(playerid, "~y~Prev Page");
    }

    TextMenu_Show(playerid);
    return 1;
}

stock ShowMechServices(playerid) 
{
    TextMenu_Create(playerid, "TextMenuMechanic", "Mechanic Services");
    TextMenu_Add(playerid, "~w~Fix your vehicle [~g~1520~w~]");
    TextMenu_Add(playerid, "~w~Insta fix [~g~15000~w~]");
    TextMenu_Show(playerid);
    return 1;
}

timer VehicleFixTimer[5000](playerid)
{
    PlayerFixingVehicle[playerid] = false;
    RepairVehicle(GetPlayerVehicleID(playerid));
    GameTextForPlayer(playerid, "Your vehicle has been fixed", 2000, 3);
    return 1;
}