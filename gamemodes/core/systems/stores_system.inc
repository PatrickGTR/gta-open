#define MENU_MECH       (3)

static
    bool:PlayerFixingVehicle[MAX_PLAYERS],
    Timer:PlayerFixingVehicleTimer[MAX_PLAYERS];

hook OnGameModeInit()
{
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 295.4240, -82.5273, 1002.5156, 40.0, 6, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to purchase items", COLOR_WHITE, 312.8376, -167.7640, 1000.5938, 40.0, 7, 0);
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to view services", COLOR_WHITE, 1015.4679, -930.1953, 43.1797, 40.0, 0, 0);
    CreateActor(50, 1015.4679, -930.1953, 42.1797, 184.6950); //Mechanic
    CreateDynamicMapIcon(1015.4679, -930.1953, 42.1797, 27, -1, .streamdistance = 200.0, .style = MAPICON_GLOBAL);
    return 1;
}

static const
    gAmmunationData[][] = {
    // Layout
    // Weapon ID | Weapon_Prize | Ammunition
        {WEAPON_TEC9, 500, 250},        // 0
        {WEAPON_UZI, 500, 250},         // 1
        {WEAPON_MP5, 500, 250},         // 2
        {WEAPON_SAWEDOFF, 500, 100},    // 3
        {WEAPON_DEAGLE, 800, 100},      // 4
        {WEAPON_SNIPER, 1200, 50},      // 5
        {WEAPON_M4, 2000, 350},         // 6
        {WEAPON_CHAINSAW, 2500, 1}     // 7
    };

TDMenu:TextMenuAmmunationMain(playerid, listitem)
{
    new
        tmpString[24],
        index;

    format(tmpString, sizeof(tmpString), "AmmunationMenuItem_%i", listitem);
    index = GetPVarInt(playerid, tmpString);

    if(listitem == 8) {
        if(Player_GetJob(playerid) != TYPE_WEAPONDEALER) {
            Ammunation_ShowMenu(playerid);
            return SendErrorMsg(playerid, "You're not a weapon dealer");
        }
        Player_ShowWeaponShop(playerid, 1);
        return 1;
    }

    if(index == 0) {
        // do nothing
        return 1;
    }

    GivePlayerWeapon(playerid, gAmmunationData[index][0], gAmmunationData[index][2]);
    GivePlayerMoney(playerid, gAmmunationData[index][1]);
    Ammunation_ShowMenu(playerid);
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

    }
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938)) {
        if(Player_IsInAmmu(playerid)) {
            return 1;
        }
        TextMenu_HideSpecific(playerid, "TextMenuAmmunationMain");
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

stock Ammunation_ShowMenu(playerid) {

    TextMenu_Create(playerid, "TextMenuAmmunationMain", "Ammunation");
    new
        string[64];
    for(new i = 1; i < sizeof(gAmmunationData); i++) {
        format(
                string,
                sizeof(string),
                "~w~%W ~g~%m - ~y~ammunation: ~w~%i",
                gAmmunationData[i][0],
                gAmmunationData[i][1],
                gAmmunationData[i][2]
        );
        TextMenu_Add(playerid, string);

        format(string, sizeof(string), "AmmunationMenuItem_%i", i);
        SetPVarInt(playerid, string, i);
    }
    TextMenu_Add(playerid, "~y~Buy Weapon For Inventory");
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