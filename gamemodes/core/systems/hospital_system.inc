#include <YSI_Coding\y_hooks>

static
    bool:BoughtChangeSkin[MAX_PLAYERS];

const
    HOSPITAL_CURE_PRICE = 3_000,
    HOSPITAL_HEAL_PRICE = 1_000,
    HOSPITAL_SKIN_CHANGE = 20_000;

hook OnGameModeInit() {
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_YES~"C_WHITE" to view services", COLOR_WHITE, 1173.1469, -1323.4918, 16.3958, 40.0, 0, false);
    CreateActor(70, 1173.1469, -1323.4918, 15.3958, 270.2290);
    return 1;
}

hook OnPlayerSpawn(playerid) {
	if(BoughtChangeSkin[playerid]) {
		BoughtChangeSkin[playerid] = false;
		Class_SelectionState(playerid, false);
		Player_SetSkin(playerid, Player_GetSkin(playerid), true);
	}
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

stock ShowHospitalMenu(playerid) {

    inline const _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext
        if(!response) {
            return 1;
        }

        switch(listitem) {
            case 0: {
                new
                    Float:health;
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
            case 1: {
                if(GetPlayerMoney(playerid) < HOSPITAL_SKIN_CHANGE) {
                    return SendErrorMsg(playerid, "Not enough money!");
                }

                if(GetPlayerWantedLevel(playerid) != 0) {
                    return SendErrorMsg(playerid, "You must be inocent to change skins!");
                }

                BoughtChangeSkin[playerid] = true;
                Class_SelectionState(playerid, true);

                ForceClassSelection(playerid);
                TogglePlayerSpectating(playerid, true);
                TogglePlayerSpectating(playerid, false);

                GivePlayerMoney(playerid, -HOSPITAL_SKIN_CHANGE);
            }
            case 2: {
                if(GetPlayerMoney(playerid) < HOSPITAL_CURE_PRICE) {
                    return SendErrorMsg(playerid, "Not enough money!");
                }

                if(!Disease_PlayerHas(playerid)) {
                    return SendErrorMsg(playerid, "You don't have a Disease");
                }

                Disease_GivePlayer(playerid, DISEASE_NONE);
                GivePlayerMoney(playerid, -HOSPITAL_CURE_PRICE);
            }
        }

    }

    new
        content[128 + 32];

    format(
        content,
        sizeof(content),
        "\
        Action\tPrice\n\
        "C_WHITE"Heal\t"C_GREEN"%m\n\
        "C_WHITE"Skin/Class Change\t"C_GREEN"%m\n\
        "C_WHITE"Cure Disease\t"C_GREEN"%m\
        ", HOSPITAL_HEAL_PRICE, HOSPITAL_SKIN_CHANGE, HOSPITAL_CURE_PRICE
    );

    Dialog_ShowCallback(
        playerid, using inline _response,
        DIALOG_STYLE_TABLIST_HEADERS,
        "Hospital Menu",
        content,
        "Select",
        "Cancel"
        );

    return 1;
}
