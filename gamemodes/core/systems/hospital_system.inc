#include <YSI_Coding\y_hooks>

static
    bool:BoughtChangeSkin[MAX_PLAYERS];

const
    HOSPITAL_HEAL_PRICE = 1_000,
    HOSPITAL_SKIN_CHANGE = 50_000;

hook OnGameModeInit() {
    Create3DTextLabel("Press "C_YELLOW"Y"C_WHITE" to view services", COLOR_WHITE, 1173.1469, -1323.4918, 16.3958, 40.0, 0, 0);
    CreateActor(70, 1173.1469, -1323.4918, 15.3958, 270.2290);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_YES)) {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 1173.1469, -1323.4918, 15.3958)) {
            ShowHospitalMenu(playerid);
        }
    }
    return 1;
}

hook OnPlayerSecondUpdate(playerid) {
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1173.1469, -1323.4918, 15.3958)) {
        TextMenu_HideSpecific(playerid, "TextMenuHospital");
    }
    return 1;
}

forward TextMenuHospital(playerid, listitem);
public TextMenuHospital(playerid, listitem) {
    switch(listitem) {
        case 1: {
            new Float:health;
            GetPlayerHealth(playerid, health);
            if(GetPlayerMoney(playerid) < HOSPITAL_HEAL_PRICE) {
                return SendErrorMsg(playerid, "Not enough money!");
            }
            if(health >= 100.0) {
                return SendErrorMsg(playerid, "You have full health can't heal right now.");
            }
            SetPlayerHealth(playerid, 100);
            GivePlayerMoney(playerid, -HOSPITAL_HEAL_PRICE);
        }
        case 2: {
            if(GetPlayerMoney(playerid) < HOSPITAL_SKIN_CHANGE) {
                return SendErrorMsg(playerid, "Not enough money!");
            }
            if(GetPlayerWantedLevel(playerid) != 0) {
                return SendErrorMsg(playerid, "You must be inocent to change skins!");
            }
            BoughtChangeSkin[playerid] = true;
            Class_SelectionState(playerid, true);
            SetPlayerHealth(playerid, 0);
            ForceClassSelection(playerid);
            GivePlayerMoney(playerid, HOSPITAL_SKIN_CHANGE);
        }
        case 3: {
            if(GetPlayerMoney(playerid) < 3000) {
                return SendErrorMsg(playerid, "Not enough money!");
            }
            if(!Disease_PlayerHas(playerid)) {
                return SendErrorMsg(playerid, "You don't have a Disease");
            }
            GivePlayerMoney(playerid, -3000);
            Disease_GivePlayer(playerid, DISEASE_NONE);
        }
    }
    return 1;
}

stock ShowHospitalMenu(playerid) {
    TextMenu_Create(playerid, "TextMenuHospital", "Hospital");
    TextMenu_Add(playerid, "~w~Heal [~g~$1000~w~]");
    TextMenu_Add(playerid, "~w~Change Skin [~g~$50000~w~]");
    TextMenu_Add(playerid, "~w~Cure Disease [~g~$3000~w~]");
    TextMenu_Show(playerid);
    return 1;
}

stock Player_BoughtSkin(playerid) {
	return BoughtChangeSkin[playerid];
}

stock Player_SetBoughtSkin(playerid, bool:status) {
	BoughtChangeSkin[playerid] = status;
}