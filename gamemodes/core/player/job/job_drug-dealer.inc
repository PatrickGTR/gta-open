static
    // Crack data
    sellCrackCooldown[MAX_PLAYERS],
    BitArray:HasBeenOfferedCrack<MAX_PLAYERS>,
    crackSeller[MAX_PLAYERS],
    crackPrice[MAX_PLAYERS],
    crackAmount[MAX_PLAYERS],
    // Weed Data
    sellWeedCooldown[MAX_PLAYERS],
    BitArray:HasBeenOfferedWeed<MAX_PLAYERS>,
    weedSeller[MAX_PLAYERS],
    weedPrice[MAX_PLAYERS],
    weedAmount[MAX_PLAYERS]
;


#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
    sellCrackCooldown[playerid] =
    crackPrice[playerid] =
    crackAmount[playerid] = -1;
    crackSeller[playerid] = INVALID_PLAYER_ID;
    Bit_Set(HasBeenOfferedCrack, playerid, false);

    sellWeedCooldown[playerid] =
    weedPrice[playerid] =
    weedAmount[playerid] = -1;
    weedSeller[playerid] = INVALID_PLAYER_ID;
    Bit_Set(HasBeenOfferedWeed, playerid, false);
    return 1;
}


CMD:sellcrack(playerid, params[]) {
    if (Player_GetJob(playerid) != TYPE_DRUGDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only drug dealers can use this command");
    }

    new
        targetid,
        price,
        amount;

    if(sscanf(params, "rii", targetid, price, amount)) {
        return SendSyntaxMsg(playerid, "/sellweed <playerid> <price> <amount> (MAX: 5)");
    }

    if(targetid == playerid) {
        return SendErrorMsg(playerid, "Can't sell your own product to yourself");
    }


    if(Player_GetCrack(playerid) > amount) {
        return SendErrorMsgF(playerid, "You only have %i crack on you and you're trying to sell %i!", Player_GetCrack(playerid), amount);
    }

    if(amount > 5) {
        return SendErrorMsg(playerid, "You can only sell 50 grams at once");
    }

    if(5000 > price > 20000) {
        return SendErrorMsg(playerid, "The minimum price is $5,000 and maximum price is $20,000");
    }

    if(Player_GetCrack(targetid) >= MAX_CRACK) {
        return SendErrorMsg(playerid, "You can not sell crack to this player, (s)he has reached the maximum amount (s)he could hold.");
    }

    if(gettime() < sellCrackCooldown[playerid]) {
        return SendErrorMsgF(playerid, "You just sold crack recently, please try in %i seconds!", gettime() - sellCrackCooldown[playerid]);
    }

    sellCrackCooldown[playerid] = gettime() + 60;

    Bit_Set(HasBeenOfferedCrack, targetid, true);
    crackSeller[targetid]	= playerid;
    crackPrice[targetid] 	= price;
    crackAmount[targetid] 	= amount;

    SendMsgF(playerid, COLOR_GREEN, "** CRACK **: "C_WHITE" You have offered "C_GREY"%p (%i) "C_WHITE"with "C_GREY"%i grams "C_WHITE"of crack for "C_GREEN"%m", playerid, playerid, amount * 10);
    SendMsgF(targetid, COLOR_GREEN, "** CRACK **: "C_WHITE" Drug dealer "C_GREY"%p (%i) "C_WHITE"offered you "C_GREY"%i grams "C_WHITE"of crack, use "C_GREY"/buycrack to take his offer.", playerid, playerid, amount * 10);
    return 1;
}

CMD:buycrack(playerid, params[]) {
    if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only Civilians can use this command");
    }

    if(!Bit_Get(HasBeenOfferedCrack, playerid)) {
        return SendErrorMsg(playerid, "No one has offered you to buy crack.");
    }

    if(Player_GetCrack(playerid) >= MAX_CRACK) {
        return SendErrorMsg(playerid, "You are unable to buy crack, you've reached the maximum amount you can hold");
    }

    if(GetPlayerMoney(playerid) < crackPrice[playerid]) {
        return SendErrorMsgF(playerid, "You don't have enough money to buy crack from "C_GREY"%p", playerid);
    }

    Bit_Set(HasBeenOfferedCrack, playerid, false);
    GivePlayerMoney(playerid, -crackPrice[playerid]);
    GivePlayerMoney(crackSeller[playerid], crackPrice[playerid]);
    Player_GiveCrack(playerid, crackAmount[playerid]);

    SendMsgF(crackSeller[playerid], COLOR_GREEN, "** CRACK **: "C_WHITE"%p (%i) accepted your offer, you earned "C_GREEN"$%m"C_WHITE" for selling "C_GREY"%i grams "C_WHITE"of crack.",
        playerid, playerid, crackPrice[playerid], crackAmount[playerid] * 10);

    SendMsgF(playerid, COLOR_GREEN, "** CRACK **: "C_WHITE"You successfully bought "C_GREY"%i grams "C_WHITE"of crack for "C_GREEN"$%m"C_WHITE" from "C_GREY"%p(%i)",
        crackAmount[playerid] * 10, crackPrice[playerid], crackSeller[playerid], crackSeller[playerid]);
    return 1;
}

// WEED

new
    WeedFarmArea;

hook OnScriptInit() {
    WeedFarmArea = CreateDynamicRectangle(
        2442.1895,-1721.3822, 2477.2610,-1707.8583
    );

    CreateDynamicMapIcon(2463.1084, -1715.6919, 13.5065, 46, -1, .style = MAPICON_GLOBAL);
}

CMD:plantweed(playerid, params[]) {

    if (Player_GetJob(playerid) != TYPE_DRUGDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only drug dealers can use this command");
    }

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
        return SendErrorMsg(playerid, "You need to be on-foot.");
    }

    if(!IsPlayerInDynamicArea(playerid, WeedFarmArea)) {
        return SendErrorMsg(playerid, "You need to be in weed farm to plant.");
    }

    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(playerid, x, y, z);

    Weed_Create(playerid, x, y, z);
    return 1;
}

CMD:harvestweed(playerid, params[]) {
    if (Player_GetJob(playerid) != TYPE_DRUGDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only drug dealers can use this command");
    }

    new
        weedId = Weed_GetClosest(playerid);

    if (weedId == -1) {
        return SendErrorMsg(playerid, "You are not close to any of your weed plant!");
    }

    if (Weed_GetPercent(playerid, weedId) < 100) {
        return SendErrorMsg(playerid, "Unable to harvest cannabis plant, it hasn't fully grown yet!");
    }

    Weed_ResetData(playerid, weedId);
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, false, false, false, false, 0, SYNC_ALL);

    Player_GiveWeed(playerid, 1);
    SendClientMessage(playerid, COLOR_GREEN, "** WEED PICKUP ** "C_WHITE"You have harvested 10 grams of weed.");
    return 1;
}

CMD:sellweed(playerid, params[]) {
    if (Player_GetJob(playerid) != TYPE_DRUGDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only drug dealers can use this command");
    }

    new
        targetid,
        price,
        amount;

    if(sscanf(params, "uii", targetid, price, amount)) {
        return SendSyntaxMsg(playerid, "/sellweed <playerid> <price> <amount> (MAX: 5 = (50g))");
    }

    if(targetid == playerid) {
        return SendErrorMsg(playerid, "Can't sell your own product to yourself");
    }

    if(Player_GetWeed(playerid) > amount) {
        return SendErrorMsgF(playerid, "You only have %i weed on you and you're trying to sell %i!", Player_GetWeed(playerid), amount);
    }

    if(amount > 5) {
        return SendErrorMsg(playerid, "You can only sell 50 grams at once");
    }

    if(5_000 > price > 10_000) {
        return SendErrorMsg(playerid, "The minimum price is $5,000 and maximum price is $10,000");
    }

    if(Player_GetWeed(targetid) >= MAX_WEED) {
        return SendErrorMsg(playerid, "You can not sell weed to this player, (s)he has reached the maximum amount (s)he could hold.");
    }

    if(gettime() < sellWeedCooldown[playerid]) {
        return SendErrorMsgF(playerid, "You just sold weed recently, please try in %i seconds!", gettime() - sellWeedCooldown[playerid]);
    }

    sellWeedCooldown[playerid] = gettime() + 60;

    Bit_Set(HasBeenOfferedWeed, targetid, true);
    weedSeller[targetid]	= playerid;
    weedPrice[targetid] 	= price;
    weedAmount[targetid] 	= amount;

    new
        grams = (amount * 10);

    SendMsgF(
        playerid,
        COLOR_GREEN,
        "** WEED **: "C_WHITE" You have offered "C_GREY"%p (%i) "C_WHITE"with "C_GREY"%i grams "C_WHITE"of weed for "C_GREEN"%m",
        playerid,
        playerid,
        grams,
        amount
    );
    SendMsgF(
        targetid,
        COLOR_GREEN,
        "** WEED **: "C_GREY"%p (%i) "C_WHITE"offered you "C_GREY"%i grams "C_WHITE"of weed for "C_GREEN"%m"C_WHITE", use "C_GREY"/buyweed "C_WHITE"to take his offer.",
        playerid,
        playerid,
        amount,
        grams
    );
    return 1;
}

CMD:buyweed(playerid, params[]) {
    if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only Civilians can use this command");
    }

    if(!Bit_Get(HasBeenOfferedWeed, playerid)) {
        return SendErrorMsg(playerid, "No one has offered you to buy weed.");
    }

    if(Player_GetWeed(playerid) >= MAX_WEED) {
        return SendErrorMsg(playerid, "You are unable to buy weed, you've reached the maximum amount you can hold");
    }

    if(GetPlayerMoney(playerid) < weedPrice[playerid]) {
        return SendErrorMsgF(playerid, "You don't have enough money to buy weed from ~y~%p", playerid);
    }

    Bit_Set(HasBeenOfferedWeed, playerid, false);
    GivePlayerMoney(playerid, -weedPrice[playerid]);
    GivePlayerMoney(weedSeller[playerid], weedPrice[playerid]);
    Player_GiveWeed(playerid, weedAmount[playerid]);

    new
        grams = (weedAmount[playerid] * 10);

    SendMsgF(
        weedSeller[playerid],
        COLOR_GREEN,
        "** WEED **: "C_WHITE"You earned "C_GREEN"$%m"C_WHITE" for selling "C_GREY"%i grams "C_WHITE"of weed from "C_GREY"%p(%i)",
        weedPrice[playerid],
        grams,
        playerid,
        playerid
    );

    SendMsgF(
        playerid,
        COLOR_GREEN,
        "** WEED **: "C_WHITE"You bought "C_GREY"%i grams "C_WHITE"of weed for "C_GREEN"$%m"C_WHITE" from "C_GREY"%p(%i)",
        grams,
        weedPrice[playerid],
        weedSeller[playerid],
        weedSeller[playerid]
    );
    return 1;
}