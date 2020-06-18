#include <YSI_Coding\y_hooks>

#define MAX_ARMY_VEHICLES 100

static
    HydraSpawnTick,
    HunterSpawnTick
;

static 
    armyVehicles[MAX_ARMY_VEHICLES],
    armyVehicleCount
;

static
    bool:PlayerFreeGuns[MAX_PLAYERS]
;

stock bool:IsArmyVehicle(vehicleid)
{
    for (new i = 0; i < MAX_ARMY_VEHICLES; i ++)
    {
        if (armyVehicles[i] == vehicleid)
            return true;
    }
    return false;
}

hook OnGameModeInit()
{
    Create3DTextLabel("Press "C_YELLOW"N"C_WHITE" to open the gate", COLOR_WHITE, 1240.9739, -2035.3715, 59.9941, 40.0, 0, 0);
    Create3DTextLabel("Press "C_YELLOW"N"C_WHITE" to open the gate", COLOR_WHITE, 1086.5114, -2098.7629, 64.5963, 40.0, 0, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to buy a Army Vehicle", COLOR_WHITE, 1156.6572, -2052.0520, 70.1159, 40.0, 0, 0);
    CreateActor(191, 1156.6572, -2052.0520, 69.1159, 90.6172);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to see Medical Menu", COLOR_WHITE, 1157.1663, -2019.1108, 70.1159, 40.0, 0, 0);
    CreateActor(274, 1157.1663, -2019.1108, 69.1159, 84.8518);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to see Army Weapons", COLOR_WHITE, 1202.7822, -2019.3701, 69.4189, 40.0, 0, 0);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(Player_GetClass(playerid) == TEAM_ARMY) {
        PlayerFreeGuns[playerid] = false;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES) && Player_GetClass(playerid) == TEAM_ARMY)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1156.6572, -2052.0520, 69.1159))
        {
            ShowArmyVehicleMenu(playerid);
        }
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1157.1663, -2019.1108, 69.1159))
        {
            ShowArmyMedicalMenu(playerid);
        }
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1202.7822, -2019.3701, 69.4189))
        {
            ShowArmyWeaponMenu(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if(IsArmyVehicle(vehicleid) && Player_GetClass(playerid) != TEAM_ARMY)
    {
        SendErrorMsg(playerid, "You're not a Army You can't enter this vehicle!");
        RemovePlayerFromVehicle(playerid);
    }
    return 1;
}

hook OnVehicleDeath(vehicleid, killerid)
{
    if(IsArmyVehicle(vehicleid))
    {
        DestroyVehicle(vehicleid);
    }
    return 1;
}

forward TextMenuArmyVehicle(playerid, listitem);
public TextMenuArmyVehicle(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            if(GetPlayerMoney(playerid) < 100000) {
                return SendErrorMsg(playerid, "Not enough money!");
            }
            if(gettime() - HydraSpawnTick < 300) {
                return SendErrorMsg(playerid, "Someone has spawned a hydra recently");
            }
            GivePlayerMoney(playerid, -100000);
            CreateArmyVehicle(520, 1153.7114, -2018.7710, 78.3643, 269.3837, -1, -1);
            HydraSpawnTick = gettime();
        }
        case 2:
        {
            if(GetPlayerMoney(playerid) < 100000) {
                return SendErrorMsg(playerid, "Not enough money!");
            }
            if(gettime() - HunterSpawnTick < 300) {
                return SendErrorMsg(playerid, "Someone has spawned a hydra recently");
            }
            GivePlayerMoney(playerid, -100000);
            CreateArmyVehicle(425, 1155.2183, -2052.3164, 77.8981, 270.8756, -1, -1);
            HunterSpawnTick = gettime();
        }
    }
    return 1;
}

forward TextMenuArmyMedical(playerid, listitem);
public TextMenuArmyMedical(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            new Float:health;
            GetPlayerHealth(playerid, health);
            if(GetPlayerMoney(playerid) < 500) {
                return SendErrorMsg(playerid, "Not enough money!");
            }
            if(health == 100) {
                return SendErrorMsg(playerid, "You have Full Health!");
            }
            GivePlayerMoney(playerid, -500);
            SetPlayerHealth(playerid, 100);
        }
    }
    return 1;
}

forward TextMenuArmyWeapon(playerid, listitem);
public TextMenuArmyWeapon(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendServerMsg(playerid, "Weapon Info's");
            ShowArmyWeaponInfoMenu(playerid);
        }
        case 2:
        {
            if(PlayerFreeGuns[playerid] == true) {
                return SendErrorMsg(playerid, "You already have claimed your free guns!");
            }
            ResetPlayerWeapons(playerid);
            GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 1);
            GivePlayerWeapon(playerid, WEAPON_DEAGLE, 2000);
            GivePlayerWeapon(playerid, WEAPON_TEC9, 2000);
            GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, 2000);
            GivePlayerWeapon(playerid, WEAPON_M4, 2000);
            GivePlayerWeapon(playerid, WEAPON_SNIPER, 2000);
            PlayerFreeGuns[playerid] = true;
        }
        case 3:
        {
            if(PlayerFreeGuns[playerid] == true) {
                return SendErrorMsg(playerid, "You already have claimed your free guns!");
            }
            ResetPlayerWeapons(playerid);
            GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 1);
            GivePlayerWeapon(playerid, WEAPON_DEAGLE, 2000);
            GivePlayerWeapon(playerid, WEAPON_MP5, 2000);
            GivePlayerWeapon(playerid, WEAPON_SHOTGSPA, 2000);
            GivePlayerWeapon(playerid, WEAPON_M4, 2000);
            GivePlayerWeapon(playerid, WEAPON_SNIPER, 2000);
            PlayerFreeGuns[playerid] = true;
        }
        case 4:
        {
            if(PlayerFreeGuns[playerid] == true) {
                return SendErrorMsg(playerid, "You already have claimed your free guns!");
            }
            ResetPlayerWeapons(playerid);
            GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 1);
            GivePlayerWeapon(playerid, WEAPON_DEAGLE, 2000);
            GivePlayerWeapon(playerid, WEAPON_MP5, 2000);
            GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, 2000);
            GivePlayerWeapon(playerid, WEAPON_M4, 2000);
            GivePlayerWeapon(playerid, WEAPON_SNIPER, 2000);
            PlayerFreeGuns[playerid] = true;
        }
        case 5:
        {
            if(PlayerFreeGuns[playerid] == true) {
                return SendErrorMsg(playerid, "You already have claimed your free guns!");
            }
            ResetPlayerWeapons(playerid);
            GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 1);
            GivePlayerWeapon(playerid, WEAPON_DEAGLE, 2000);
            GivePlayerWeapon(playerid, WEAPON_MP5, 2000);
            GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 2000);
            GivePlayerWeapon(playerid, WEAPON_M4, 2000);
            GivePlayerWeapon(playerid, WEAPON_RIFLE, 2000);
            PlayerFreeGuns[playerid] = true;
        }
    }
    return 1;
}

stock ShowArmyVehicleMenu(playerid)
{
    TextMenu_Create(playerid, "TextMenuArmyMedical", "Army Vehicles");
    TextMenu_Add(playerid, "~w~Hydra [~g~$100,000~w~]");
    TextMenu_Add(playerid, "~w~Hunter [~g~$100,000~w~]");
    TextMenu_Show(playerid);
    return 1;
}

stock ShowArmyMedicalMenu(playerid)
{
    TextMenu_Create(playerid, "TextMenuArmyVehicle", "Army Medical Services");
    TextMenu_Add(playerid, "~w~Heal [~g~500~w~]");
    TextMenu_Show(playerid);
}

stock ShowArmyWeaponMenu(playerid)
{
    TextMenu_Create(playerid, "TextMenuArmyWeapon", "Army Weapon Locker");
    TextMenu_Add(playerid, "~w~Weapon Load Outs Info");
    TextMenu_Add(playerid, "~w~Weapon Load 1");
    TextMenu_Add(playerid, "~w~Weapon Load 2");
    TextMenu_Add(playerid, "~w~Weapon Load 3");
    TextMenu_Add(playerid, "~w~Weapon Load 4");
    TextMenu_Show(playerid);
    return 1;
}

forward TextMenuArmyWeaponInfo(playerid, listitem);
public TextMenuArmyWeaponInfo(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendServerMsg(playerid, "//=====WEAPON-INFO=====//");
            SendServerMsg(playerid, "1.Chainsaw");
            SendServerMsg(playerid, "2.Desert Eagle");
            SendServerMsg(playerid, "3.Tec 9");
            SendServerMsg(playerid, "4.Sawn Off");
            SendServerMsg(playerid, "5.M4");
            SendServerMsg(playerid, "6.Sniper Rifle");
        }
        case 2:
        {
            SendServerMsg(playerid, "//=====WEAPON-INFO=====//");
            SendServerMsg(playerid, "1.Chainsaw");
            SendServerMsg(playerid, "2.Desert Eagle");
            SendServerMsg(playerid, "3.MP5");
            SendServerMsg(playerid, "4.Sawn Off");
            SendServerMsg(playerid, "5.M4");
            SendServerMsg(playerid, "6.Sniper Rifle");
        }
        case 3:
        {
            SendServerMsg(playerid, "//=====WEAPON-INFO=====//");
            SendServerMsg(playerid, "1.Chainsaw");
            SendServerMsg(playerid, "2.Desert Eagle");
            SendServerMsg(playerid, "3.MP5");
            SendServerMsg(playerid, "4.Automatic Shotgun");
            SendServerMsg(playerid, "5.M4");
            SendServerMsg(playerid, "6.Sniper Rifle");
        }
        case 4:
        {
            SendServerMsg(playerid, "//=====WEAPON-INFO=====//");
            SendServerMsg(playerid, "1.Chainsaw");
            SendServerMsg(playerid, "2.Desert Eagle");
            SendServerMsg(playerid, "3.MP5");
            SendServerMsg(playerid, "4.Shotgun");
            SendServerMsg(playerid, "5.M4");
            SendServerMsg(playerid, "6.Country Rifle");
        }
        case 5:
        {
            ShowArmyWeaponMenu(playerid);
        }
    }
    return 1;
}

stock ShowArmyWeaponInfoMenu(playerid)
{
    TextMenu_Create(playerid, "TextMenuArmyWeaponInfo", "Army Weapon Infos");
    TextMenu_Add(playerid, "~w~Weapon Info 1");
    TextMenu_Add(playerid, "~w~Weapon info 2");
    TextMenu_Add(playerid, "~w~Weapon info 3");
    TextMenu_Add(playerid, "~w~Weapon info 4");
    TextMenu_Add(playerid, "~w~Back to Load Outs");
    TextMenu_Show(playerid);
    return 1;
}

stock CreateArmyVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2)
{
    new v = AddStaticVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2);
    armyVehicles[armyVehicleCount++] = v;
}