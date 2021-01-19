#include <YSI_Coding\y_hooks>

#define MAX_AMMUNATION_AMMO 250

static const WeaponPistol[][] = {
    {22, 1000, MAX_AMMUNATION_AMMO},
    {23, 1500, MAX_AMMUNATION_AMMO},
    {24, 4500, MAX_AMMUNATION_AMMO}
};

static const WeaponSub[][] =  {
    {28, 2000, MAX_AMMUNATION_AMMO},
    {32, 2000, MAX_AMMUNATION_AMMO},
    {29, 2500, MAX_AMMUNATION_AMMO}
};

static const WeaponShotgun[][] = {
    {27, 3500, MAX_AMMUNATION_AMMO},
    {26, 4500, MAX_AMMUNATION_AMMO},
    {25, 2500, MAX_AMMUNATION_AMMO}
};

static const WeaponAssRifle[][] = {
    {30, 4500, MAX_AMMUNATION_AMMO},
    {31, 4500, MAX_AMMUNATION_AMMO}
};

static const WeaponRifles[][] =  {
    {33, 3500, MAX_AMMUNATION_AMMO},
    {34, 5000, MAX_AMMUNATION_AMMO}
};

hook OnGameModeInit() {
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_YES~"C_WHITE" to purchase items", COLOR_WHITE, 295.4240, -82.5273, 1002.5156, 40.0, 6, 0);
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_YES~"C_WHITE" to purchase items", COLOR_WHITE, 312.8376, -167.7640, 1000.5938, 40.0, 7, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_YES)) {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156) || IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938)) {
            Store_ShowAmmunationMenu(playerid);
        }
    }
    return 1;
}

Store_ShowAmmunationMenu(playerid) {
    inline DialogWeaponResponse(plyid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused plyid, dialogid, inputtext

        if(!response)
            return false;

        new
            string[512];

        switch(listitem) {
            case 0: {
                inline OnPistolResponse(response2, listitem2, string:inputtext2[])
                {
                    #pragma unused inputtext2

                    if(!response2)
                        return Store_ShowAmmunationMenu(playerid);


                    if(GetPlayerMoney(playerid) < WeaponPistol[listitem2][1])
                        return SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponPistol[listitem2][0]);

                    GivePlayerWeapon(playerid, WeaponPistol[listitem2][0], WeaponPistol[listitem2][2]);
                    GivePlayerMoney(playerid, -WeaponPistol[listitem2][1]);

                    SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponPistol[listitem2][0], WeaponPistol[listitem2][1]);
                }

                strcat(string, "Weapon\tPrice\tAmmo\n");
                for(new i = 0; i < sizeof(WeaponPistol); ++i) {
                    format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponPistol[i][0], WeaponPistol[i][1], WeaponPistol[i][2]);
                }
                Dialog_ShowCallback(playerid, using inline OnPistolResponse, DIALOG_STYLE_TABLIST_HEADERS, "Pistols", string, "Select", "Back");
                //Pistol
            }
            case 1: {
                inline OnSubMachineResponse(response2, listitem2, string:inputtext2[]) {
                    #pragma unused inputtext2

                    if(!response2)
                        return Store_ShowAmmunationMenu(playerid);


                    if(GetPlayerMoney(playerid) < WeaponSub[listitem2][1])
                        return SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponSub[listitem2][0]);

                    GivePlayerWeapon(playerid, WeaponSub[listitem2][0], WeaponSub[listitem2][2]);
                    GivePlayerMoney(playerid, -WeaponSub[listitem2][1]);
                    SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponSub[listitem2][0], WeaponSub[listitem2][1]);
                }

                strcat(string, "Weapon\tPrice\tAmmo\n");
                for(new i = 0; i < sizeof(WeaponSub); ++i) {
                    format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponSub[i][0], WeaponSub[i][1], WeaponSub[i][2]);
                }
                Dialog_ShowCallback(playerid, using inline OnSubMachineResponse, DIALOG_STYLE_TABLIST_HEADERS, "Sub-Machine Guns", string, "Select", "Back");
                //Sub Machine Gun
            }
            case 2: {
                inline OnShotgunResponse(response2, listitem2, string:inputtext2[]) {
                    #pragma unused inputtext2

                    if(!response2)
                        return Store_ShowAmmunationMenu(playerid);


                    if(GetPlayerMoney(playerid) < WeaponShotgun[listitem2][1])
                        return SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponShotgun[listitem2][0]);

                    GivePlayerWeapon(playerid, WeaponShotgun[listitem2][0], WeaponShotgun[listitem2][2]);
                    GivePlayerMoney(playerid, -WeaponShotgun[listitem2][1]);
                    SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponShotgun[listitem2][0], WeaponShotgun[listitem2][1]);
                }

                strcat(string, "Weapon\tPrice\tAmmo\n");
                for(new i = 0; i < sizeof(WeaponShotgun); ++i) {
                    format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponShotgun[i][0], WeaponShotgun[i][1], WeaponShotgun[i][2]);
                }
                Dialog_ShowCallback(playerid, using inline OnShotgunResponse, DIALOG_STYLE_TABLIST_HEADERS, "Pistols", string, "Select", "Back");
                //Shotguns
            }
            case 3: {
                inline OnAssaultRifleResponse(response2, listitem2, string:inputtext2[]) {
                    #pragma unused inputtext2

                    if(!response2)
                        return Store_ShowAmmunationMenu(playerid);


                    if(GetPlayerMoney(playerid) < WeaponAssRifle[listitem2][1])
                        return SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponAssRifle[listitem2][0]);

                    GivePlayerWeapon(playerid, WeaponAssRifle[listitem2][0], WeaponAssRifle[listitem2][2]);
                    GivePlayerMoney(playerid, -WeaponAssRifle[listitem2][1]);
                    SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponAssRifle[listitem2][0], WeaponAssRifle[listitem2][1]);
                }

                strcat(string, "Weapon\tPrice\tAmmo\n");
                for(new i = 0; i < sizeof(WeaponAssRifle); ++i) {
                    format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponAssRifle[i][0], WeaponAssRifle[i][1], WeaponAssRifle[i][2]);
                }
                Dialog_ShowCallback(playerid, using inline OnAssaultRifleResponse, DIALOG_STYLE_TABLIST_HEADERS, "Pistols", string, "Select", "Back");
                //Assault Rifle
            }
            case 4: {

                inline OnRifleResponse(response2, listitem2, string:inputtext2[]) {
                    #pragma unused inputtext2

                    if(!response2)
                        return Store_ShowAmmunationMenu(playerid);

                    if(GetPlayerMoney(playerid) < WeaponRifles[listitem2][1])
                        return SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponRifles[listitem2][0]);

                    GivePlayerWeapon(playerid, WeaponRifles[listitem2][0], WeaponRifles[listitem2][2]);
                    GivePlayerMoney(playerid, -WeaponRifles[listitem2][1]);
                    SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponRifles[listitem2][0], WeaponRifles[listitem2][1]);
                }

                strcat(string, "Weapon\tPrice\tAmmo\n");
                for(new i = 0; i < sizeof(WeaponRifles); ++i) {
                    format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponRifles[i][0], WeaponRifles[i][1], WeaponRifles[i][2]);
                }
                Dialog_ShowCallback(playerid, using inline OnRifleResponse, DIALOG_STYLE_TABLIST_HEADERS, "Pistols", string, "Select", "Back");
                //Rifles
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline DialogWeaponResponse, DIALOG_STYLE_LIST, "Ammunation", "Pistols\nSub-machine guns\nShotguns\nAssault rifles\nRifles", "Select", "Close");
    return 1;
}
