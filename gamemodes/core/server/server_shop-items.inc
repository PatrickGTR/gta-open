enum E_ITEM_SHOP_DATA {
    E_ITEM_NAME[24],
    E_ITEM_VALUE
}

#define MAX_ITEMS 15

static const itemsTwentyFourSeven[][E_ITEM_SHOP_DATA] = {
    {"Picklock", 2000},
    {"Condom",   500},
    {"Wallet",   500},
    {"Rope",     500},
    {"Scissors", 250}
};

static
    twentyFourArea,
    gasStationArea;

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	twentyFourArea = CreateDynamicSphere(-28.9200, -184.2601, 1003.5469, 2.50);
    gasStationArea = CreateDynamicSphere(-23.4678, -55.2389, 1003.5469, 2.50);

    CreateDynamic3DTextLabel("Press "C_YELLOW"Y"C_WHITE"to open shop menu", COLOR_WHITE, -28.9200, -184.2601, 1003.5469, TEXTLABEL_STREAMDISTANCE, .testlos = 1);
    CreateDynamic3DTextLabel("Press "C_YELLOW"Y"C_WHITE"to open shop menu", COLOR_WHITE, -23.4678, -55.2389, 1003.5469, TEXTLABEL_STREAMDISTANCE, .testlos = 1);
    return 1;
}

static void:Item_ShowAmount(playerid, option) {
    new
        item,
        itemName[24];

    switch(option) {
        case 0: {
            item = Player_GetPicklock(playerid);
            itemName = "picklock";
        }
        case 1: {
            item = Player_GetCondom(playerid);
            itemName = "condom";
        }
        case 2: {
            item = Player_GetWallet(playerid);
            itemName = "wallet";
        }
        case 3: {
            item = Player_GetRope(playerid);
            itemName = "rope";
        }
        case 4: {
            item = Player_GetScissors(playerid);
            itemName = "scissor";
        }
        default: {
            item = -1;
            itemName =  "N/A";
        }
    }

    inline const _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem

        if(!response) {
            return;
        }

        new
            amount = strval(inputtext),
            itemPrice = (itemsTwentyFourSeven[clamp(option, 0, sizeof(itemsTwentyFourSeven) - 1)][E_ITEM_VALUE] * amount);

        if(amount > MAX_ITEMS) {
            SendErrorMsgF(playerid, "invalid input, max is "C_GREY"%i", MAX_ITEMS);
            return;
        }

        if((item + amount) > MAX_ITEMS) {
            SendErrorMsg(playerid, "You have reached the limit that you can carry.");
            return;
        }

        if(GetPlayerMoney(playerid) < itemPrice) {
            SendErrorMsgF(playerid, "You can't afford to buy "C_GREY"%i %s "C_WHITE"for "C_GREEN"%m", amount, itemName, itemPrice);
            return;
        }

        switch(option) {
            case 0: Player_GivePicklock(playerid, amount);
            case 1: Player_GiveCondom(playerid, amount);
            case 2: Player_GiveWallet(playerid, amount);
            case 3: Player_GiveRope(playerid, amount);
            case 4: Player_GiveScissors(playerid, amount);
        }

        GivePlayerMoney(playerid, -itemPrice);
        SendServerMsgF(playerid, "You have purchased "C_GREY"%i "C_WHITE"%s%s", amount, itemName, (amount > 1) ? ("s.") : ("."));
    }

    new
        string[64];

    format(string, sizeof(string), "Insert the amount of %s(s) you want.", itemName);
    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_INPUT,
        "Amount",
        string,
        "Enter",
        "Back"
    );
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_YES)) {
        if(IsPlayerInDynamicArea(playerid, twentyFourArea) || IsPlayerInDynamicArea(playerid, gasStationArea)) {
            new
                tmp_string[32],
                string[sizeof(tmp_string) * sizeof(itemsTwentyFourSeven)];

            inline const _ShopResponse(pid, dialogid, response, listitem, string:inputtext[]) {
                #pragma unused pid, dialogid, inputtext, listitem

                if(!response) {
                    return 1;
                }

                Item_ShowAmount(playerid, listitem);
            }

            strcat(string, "Item\tPrice\n");
            for(new i = 0; i < sizeof(itemsTwentyFourSeven); ++i) {
                format(tmp_string, sizeof(tmp_string), "%s\t"C_GREEN"%m\n",
                    itemsTwentyFourSeven[i][E_ITEM_NAME], itemsTwentyFourSeven[i][E_ITEM_VALUE]);

                strcat(string, tmp_string, sizeof(string));
            }
            Dialog_ShowCallback(
                playerid,
                using inline _ShopResponse,
                DIALOG_STYLE_TABLIST_HEADERS,
                "Shop Items",
                string,
                "Select",
                "Close"
            );
        }
    }
    return 1;
}