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
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_YES~"C_WHITE" to purchase items", COLOR_WHITE, 295.4240, -82.5273, 1002.5156, 40.0, 6, false);
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_YES~"C_WHITE" to purchase items", COLOR_WHITE, 312.8376, -167.7640, 1000.5938, 40.0, 7, false);
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

static ShowPistolMenu(playerid) {
    inline _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext

        if(!response) {
            Store_ShowAmmunationMenu(playerid);
            return;
        }

        if(GetPlayerMoney(playerid) < WeaponPistol[listitem][1]) {
            SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponPistol[listitem][0]);
            return;
        }

        GivePlayerWeapon(playerid, WeaponPistol[listitem][0], WeaponPistol[listitem][2]);
        GivePlayerMoney(playerid, -WeaponPistol[listitem][1]);

        SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponPistol[listitem][0], WeaponPistol[listitem][1]);
    }

    new
        string[256];
    strcat(string, "Weapon\tPrice\tAmmo\n");
    for(new i = 0; i < sizeof(WeaponPistol); ++i) {
        format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponPistol[i][0], WeaponPistol[i][1], WeaponPistol[i][2]);
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_TABLIST_HEADERS, "Pistols", string, "Select", "Back");
}

static ShowSubMachineMenu(playerid) {
    inline _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext

        if(!response) {
            Store_ShowAmmunationMenu(playerid);
            return;
        }


        if(GetPlayerMoney(playerid) < WeaponSub[listitem][1]) {
            SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponSub[listitem][0]);
            return;
        }

        GivePlayerWeapon(playerid, WeaponSub[listitem][0], WeaponSub[listitem][2]);
        GivePlayerMoney(playerid, -WeaponSub[listitem][1]);
        SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponSub[listitem][0], WeaponSub[listitem][1]);
    }

    new
        string[256];
    strcat(string, "Weapon\tPrice\tAmmo\n");
    for(new i = 0; i < sizeof(WeaponSub); ++i) {
        format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponSub[i][0], WeaponSub[i][1], WeaponSub[i][2]);
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_TABLIST_HEADERS, "Sub-Machine Guns", string, "Select", "Back");
}

static ShowShotgunMenu(playerid) {
    inline _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext

        if(!response) {
            Store_ShowAmmunationMenu(playerid);
            return;
        }

        if(GetPlayerMoney(playerid) < WeaponShotgun[listitem][1]) {
            SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponShotgun[listitem][0]);
            return;
        }

        GivePlayerWeapon(playerid, WeaponShotgun[listitem][0], WeaponShotgun[listitem][2]);
        GivePlayerMoney(playerid, -WeaponShotgun[listitem][1]);
        SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponShotgun[listitem][0], WeaponShotgun[listitem][1]);
    }
    new
        string[256];
    strcat(string, "Weapon\tPrice\tAmmo\n");
    for(new i = 0; i < sizeof(WeaponShotgun); ++i) {
        format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponShotgun[i][0], WeaponShotgun[i][1], WeaponShotgun[i][2]);
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_TABLIST_HEADERS, "Shotgun", string, "Select", "Back");
}

static ShowAssaultRifleMenu(playerid) {
    inline _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext

        if(!response) {
            Store_ShowAmmunationMenu(playerid);
            return;
        }

        if(GetPlayerMoney(playerid) < WeaponAssRifle[listitem][1]) {
            SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponAssRifle[listitem][0]);
            return;
        }

        GivePlayerWeapon(playerid, WeaponAssRifle[listitem][0], WeaponAssRifle[listitem][2]);
        GivePlayerMoney(playerid, -WeaponAssRifle[listitem][1]);
        SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponAssRifle[listitem][0], WeaponAssRifle[listitem][1]);
    }
    new
        string[256];
    strcat(string, "Weapon\tPrice\tAmmo\n");
    for(new i = 0; i < sizeof(WeaponAssRifle); ++i) {
        format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponAssRifle[i][0], WeaponAssRifle[i][1], WeaponAssRifle[i][2]);
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_TABLIST_HEADERS, "Assault Rifle", string, "Select", "Back");
}

static ShowRifleMenu(playerid) {
    inline _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext

        if(!response) {
            Store_ShowAmmunationMenu(playerid);
            return;
        }

        if(GetPlayerMoney(playerid) < WeaponRifles[listitem][1]) {
            SendErrorMsgF(playerid, "You don't have enough money to buy %W", WeaponRifles[listitem][0]);
            return;
        }

        GivePlayerWeapon(playerid, WeaponRifles[listitem][0], WeaponRifles[listitem][2]);
        GivePlayerMoney(playerid, -WeaponRifles[listitem][1]);
        SendServerMsgF(playerid, "You bought a "C_GREY"%W "C_WHITE"for "C_GREEN"%m", WeaponRifles[listitem][0], WeaponRifles[listitem][1]);
    }

    new
        string[256];
    strcat(string, "Weapon\tPrice\tAmmo\n");
    for(new i = 0; i < sizeof(WeaponRifles); ++i) {
        format(string, sizeof(string), "%s%W\t"C_GREEN"%m\t"C_WHITE"%i bullets\n", string, WeaponRifles[i][0], WeaponRifles[i][1], WeaponRifles[i][2]);
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_TABLIST_HEADERS, "Pistols", string, "Select", "Back");
}

Store_ShowAmmunationMenu(playerid) {
    inline _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext

        if(!response)
            return 0;

        switch(listitem) {
            case 0: ShowPistolMenu(playerid);
                //Pistol
            case 1: ShowSubMachineMenu(playerid);
                //Sub Machine Gun
            case 2: ShowShotgunMenu(playerid);
                //Shotguns
            case 3: ShowAssaultRifleMenu(playerid);
                //Assault Rifle
            case 4: ShowRifleMenu(playerid);
                //Rifles
        }
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, "Ammunation", "Pistols\nSub-machine guns\nShotguns\nAssault rifles\nRifles", "Select", "Close");
    return 1;
}
