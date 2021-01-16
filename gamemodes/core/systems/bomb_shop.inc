#include <YSI_Coding\y_hooks>

const
    Float:gBombShopX = 1857.4403,
    Float:gBombShopY = -1852.6626,
    Float:gBombShopZ = 13.5815,
    Float:gBombShopA = 264.0457;

const
    C4_PRICE = 5_000;

static
    bool:gBombDealerText[MAX_PLAYERS],
    gBombDealerAreaID;

hook OnPlayerConnect(playerid) {
    gBombDealerText[playerid] = false;
    return 1;
}

hook OnGameModeInit() {
    gBombDealerAreaID = CreateDynamicCircle(
        Float:gBombShopX,
        Float:gBombShopY,
        Float:3.5);

    CreateDynamicActor(28,
        gBombShopX,
        gBombShopY,
        gBombShopZ,
        gBombShopA
    );

    CreateDynamic3DTextLabel(
        "Bomb Dealer\n\
        Pablo\n\
        Press "C_YELLOW"~k~~CONVERSATION_YES~ "C_ORANGE"to interact",
        COLOR_ORANGE,
        gBombShopX,
        gBombShopY,
        gBombShopZ + 1.5,
        100.0,
        .testlos = 1
    );

    CreateDynamicMapIcon(
        gBombShopX,
        gBombShopY,
        gBombShopZ,
        8,
        -1,
        .streamdistance = 200.0,
        .style = MAPICON_GLOBAL
    );

    return 1;
}

hook OnPlayerText(playerid, text[]) {
    if(gBombDealerText[playerid] && isnumeric(text)) {
        new
            amount = strval(text),
            price = (C4_PRICE * amount);

        if(GetPlayerMoney(playerid) < price) {
            SendErrorMsgF(playerid, "You don't have enough money to buy "C_GREY"%i "C_WHITE"C4", amount);
            return ~0;
        }

        GivePlayerMoney(playerid, -price);
        Player_GiveC4(playerid, amount);

        SendMsgF(playerid, COLOR_ORANGE, "(bomb dealer) "C_WHITE"Thank you for buying "C_GREY"%i "C_WHITE"C4 Explosive", amount);
        _BombUI_Show(playerid);
        return ~0;
    }
    return 0;
}

hook OnPlayerLeaveDynArea(playerid, areaid) {

    if(areaid == gBombDealerAreaID) {
        TextInfo_HideSpecific(playerid, "BOMBDEALER");
        gBombDealerText[playerid] = false;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    new
        bool:isCloseToBombShop = bool:IsPlayerInDynamicArea(playerid, gBombDealerAreaID);

    if(PRESSED(KEY_YES) && isCloseToBombShop) {
        _BombUI_Show(playerid);
        gBombDealerText[playerid] = true;
    }

    if(PRESSED(KEY_NO) && isCloseToBombShop && gBombDealerText[playerid]) {
        TextInfo_HideSpecific(playerid, "BOMBDEALER");
        gBombDealerText[playerid] = false;
    }
    return 1;
}


static void:_BombUI_Show(playerid) {
    new
        string[35];
    TextInfo_Create(playerid, "BOMBDEALER", "Bomb Dealer");
    format(string, sizeof(string), "~w~You've got ~y~%i ~w~C4~n~~n~", Player_GetC4(playerid));
    TextInfo_Add(playerid, string);
    TextInfo_Add(playerid, "Type in the chat how much you want to ~g~buy");
    TextInfo_Show(playerid);
}