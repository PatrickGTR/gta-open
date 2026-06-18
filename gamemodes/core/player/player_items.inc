#include <YSI_Coding\y_hooks>

forward PlayerItems_SaveInventory(playerid);

static
    PlayerC4[MAX_PLAYERS],
    PlayerCrack[MAX_PLAYERS],
    PlayerWeed[MAX_PLAYERS],
    PlayerPickLock[MAX_PLAYERS],
    PlayerWallet[MAX_PLAYERS],
    PlayerCondom[MAX_PLAYERS],
    PlayerRope[MAX_PLAYERS],
    PlayerScissors[MAX_PLAYERS],
    PlayerOranges[MAX_PLAYERS],
    PlayerBottles[MAX_PLAYERS],
    PlayerOrangeJuice[MAX_PLAYERS],
    PlayerFruitPicker[MAX_PLAYERS],

    // statements for initializing on OnGameModeInit
    Statement: g_stmt_insert_player_items,
    Statement: g_stmt_load_player_items,
    Statement: g_stmt_save_inventory;

hook OnPlayerConnect(playerid) {
    PlayerC4[playerid]          =
    PlayerCrack[playerid]       =
    PlayerWeed[playerid]        =
    PlayerPickLock[playerid]    =
    PlayerWallet[playerid]      =
    PlayerCondom[playerid]      =
    PlayerRope[playerid]        =
    PlayerScissors[playerid]    =
    PlayerOranges[playerid]     =
    PlayerBottles[playerid]     =
    PlayerOrangeJuice[playerid] =
    PlayerFruitPicker[playerid] = 0;
    return 1;
}

hook OnGameModeInit() {
    g_stmt_insert_player_items = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO player_items (u_id) VALUES (?)");

    static const load_query[] = "\
        SELECT \
            c4, \
            crack, \
            weed, \
            picklock, \
            wallet, \
            rope, \
            condom, \
            scissors, \
            oranges, \
            bottles, \
            orange_juice, \
            fruit_picker \
        FROM \
            player_items \
        WHERE \
            u_id = ? \
        ";
    g_stmt_load_player_items = MySQL_PrepareStatement(MySQL_GetHandle(), load_query);

    g_stmt_save_inventory = MySQL_PrepareStatement(MySQL_GetHandle(),
        "UPDATE player_items SET c4=?, crack=?, weed=?, picklock=?, wallet=?, condom=?, rope=?, scissors=?, oranges=?, bottles=?, orange_juice=?, fruit_picker=? WHERE u_id=?");

    return 1;
}

hook OnPlayerRegister(playerid) {
    MySQL_BindInt(g_stmt_insert_player_items, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(g_stmt_insert_player_items);
    return 1;
}

hook OnPlayerLogin(playerid) {
    inline const OnItemLoad() {
        MySQL_BindResultInt(g_stmt_load_player_items, 0, PlayerC4[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 1, PlayerCrack[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 2, PlayerWeed[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 3, PlayerPickLock[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 4, PlayerWallet[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 5, PlayerCondom[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 6, PlayerRope[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 7, PlayerScissors[playerid]);
        // farming player inventory
        MySQL_BindResultInt(g_stmt_load_player_items, 8, PlayerOranges[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 9, PlayerBottles[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 10, PlayerOrangeJuice[playerid]);
        MySQL_BindResultInt(g_stmt_load_player_items, 11, PlayerFruitPicker[playerid]);


        if(!MySQL_Statement_FetchRow(g_stmt_load_player_items)) {
            Logger_Dbg(
                "player_items",
                "[OnPlayerLogin / player_items.inc] Oops player_items did not load properly.",
                Logger_P(playerid),
                Logger_I("uid", Player_GetAccountID(playerid))
            );
        }
    }

    MySQL_BindInt(g_stmt_load_player_items, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(g_stmt_load_player_items, using inline OnItemLoad);
    return 1;
}

// C4
stock void:Player_GiveC4(playerid, amount) {
    PlayerC4[playerid] += amount;

    _SaveItem(playerid, "c4", amount);
}

stock Player_GetC4(playerid) {
    return PlayerC4[playerid];
}

// Crack
stock void:Player_GiveCrack(playerid, amount) {
    PlayerCrack[playerid] += amount;

    _SaveItem(playerid, "crack", amount);
}

stock Player_GetCrack(playerid) {
    return PlayerCrack[playerid];
}

// Picklock
stock void:Player_GivePicklock(playerid, amount) {
    PlayerPickLock[playerid] += amount;

    _SaveItem(playerid, "picklock", amount);
}

stock Player_GetPicklock(playerid) {
    return PlayerPickLock[playerid];
}

// Wallet
stock void:Player_GiveWallet(playerid, amount) {
    PlayerWallet[playerid] += amount;

    _SaveItem(playerid, "wallet", amount);
}

stock Player_GetWallet(playerid) {
    return PlayerWallet[playerid];
}

// Weed
stock void:Player_GiveWeed(playerid, amount) {
    PlayerWeed[playerid] += amount;

    _SaveItem(playerid, "weed", amount);
}

stock Player_GetWeed(playerid) {
    return PlayerWeed[playerid];
}

// Condom
stock void:Player_GiveCondom(playerid, amount) {
    PlayerCondom[playerid] += amount;

    _SaveItem(playerid, "condom", amount);
}

stock Player_GetCondom(playerid) {
    return PlayerCondom[playerid];
}

// Rope
stock void:Player_GiveRope(playerid, amount) {
    PlayerRope[playerid] += amount;

    _SaveItem(playerid, "rope", amount);
}

stock Player_GetRope(playerid) {
    return PlayerRope[playerid];
}

// Scissors
stock void:Player_GiveScissors(playerid, amount) {
    PlayerScissors[playerid] += amount;

    _SaveItem(playerid, "scissors", amount);
}

stock Player_GetScissors(playerid) {
    return PlayerScissors[playerid];
}

// farming inv
// Oranges
stock void:Player_GiveOranges(playerid, amount) {
    PlayerOranges[playerid] += amount;
    PlayerItems_SaveInventory(playerid);
}

stock void:Player_RemoveOranges(playerid, amount) {
    PlayerOranges[playerid] -= amount;
    if(PlayerOranges[playerid] < 0) PlayerOranges[playerid] = 0;
    PlayerItems_SaveInventory(playerid);
}

stock Player_GetOranges(playerid) {
    return PlayerOranges[playerid];
}

// Bottles
stock void:Player_GiveBottles(playerid, amount) {
    PlayerBottles[playerid] += amount;
    PlayerItems_SaveInventory(playerid);
}

stock void:Player_RemoveBottles(playerid, amount) {
    PlayerBottles[playerid] -= amount;
    if(PlayerBottles[playerid] < 0) PlayerBottles[playerid] = 0;
    PlayerItems_SaveInventory(playerid);
}

stock Player_GetBottles(playerid) {
    return PlayerBottles[playerid];
}

// Orange Juice
stock void:Player_GiveOrangeJuice(playerid, amount) {
    PlayerOrangeJuice[playerid] += amount;
    PlayerItems_SaveInventory(playerid);
}

stock void:Player_RemoveOrangeJuice(playerid, amount) {
    PlayerOrangeJuice[playerid] -= amount;
    if(PlayerOrangeJuice[playerid] < 0) PlayerOrangeJuice[playerid] = 0;
    PlayerItems_SaveInventory(playerid);
}

stock Player_GetOrangeJuice(playerid) {
    return PlayerOrangeJuice[playerid];
}

// Fruit Picker
stock void:Player_GiveFruitPicker(playerid, amount) {
    PlayerFruitPicker[playerid] += amount;
    PlayerItems_SaveInventory(playerid);
}

stock void:Player_RemoveFruitPicker(playerid, amount) {
    PlayerFruitPicker[playerid] -= amount;
    if(PlayerFruitPicker[playerid] < 0) PlayerFruitPicker[playerid] = 0;
    PlayerItems_SaveInventory(playerid);
}

stock Player_GetFruitPicker(playerid) {
    return PlayerFruitPicker[playerid];
}



// Internal Function - Save single item
static void:_SaveItem(playerid, const itemName[], value) {
    new
        Statement: stmt_saveItem;

    stmt_saveItem = MySQL_PrepareStatement(
        MySQL_GetHandle(),
        "UPDATE player_items SET ? = ? + ? WHERE u_id = ?"
    );

    MySQL_Bind(stmt_saveItem, 0, itemName);
    MySQL_Bind(stmt_saveItem, 1, itemName);
    MySQL_BindInt(stmt_saveItem, 2, value);
    MySQL_BindInt(stmt_saveItem, 3, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveItem);
}

// Save complete inventory to database
public PlayerItems_SaveInventory(playerid) {
    new accountID = Player_GetAccountID(playerid);

    if(accountID <= 0) return 0;

    MySQL_BindInt(g_stmt_save_inventory, 0, PlayerC4[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 1, PlayerCrack[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 2, PlayerWeed[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 3, PlayerPickLock[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 4, PlayerWallet[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 5, PlayerCondom[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 6, PlayerRope[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 7, PlayerScissors[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 8, PlayerOranges[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 9, PlayerBottles[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 10, PlayerOrangeJuice[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 11, PlayerFruitPicker[playerid]);
    MySQL_BindInt(g_stmt_save_inventory, 12, accountID);

    MySQL_ExecuteThreaded(g_stmt_save_inventory);

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    PlayerItems_SaveInventory(playerid);
    return 1;
}

static _ItemPlayerHoldingValue(playerid, itemId) {
    switch(itemId) {
        case 0: return Player_GetC4(playerid);
        case 1: return Player_GetCrack(playerid);
        case 2: return Player_GetWeed(playerid);
        case 3: return Player_GetPicklock(playerid);
        case 4: return Player_GetWallet(playerid);
        case 5: return Player_GetCondom(playerid);
        case 6: return Player_GetRope(playerid);
        case 7: return Player_GetScissors(playerid);
        case 8: return Player_GetOranges(playerid);
        case 9: return Player_GetBottles(playerid);
        case 10: return Player_GetOrangeJuice(playerid);
        case 11: return Player_GetFruitPicker(playerid);
    }
    return -1;
}

static void:_GiveItem(playerid, itemId, amount) {
    switch(itemId) {
        case 0: Player_GiveC4(playerid, amount);
        case 1: Player_GiveCrack(playerid, amount);
        case 2: Player_GiveWeed(playerid, amount);
        case 3: Player_GivePicklock(playerid, amount);
        case 4: Player_GiveWallet(playerid, amount);
        case 5: Player_GiveCondom(playerid, amount);
        case 6: Player_GiveRope(playerid, amount);
        case 7: Player_GiveScissors(playerid, amount);
        case 8: Player_GiveOranges(playerid, amount);
        case 9: Player_GiveBottles(playerid, amount);
        case 10: Player_GiveOrangeJuice(playerid, amount);
        case 11: Player_GiveFruitPicker(playerid, amount);
    }
}

// Command
ACMD:[4]giveitem(playerid, params[]) {
    new
        targetid,
        type[13],
        amount;

    if(sscanf(params, "us[13]i", targetid, type, amount)) {
        return SendSyntaxMsg(playerid, "/giveitem [playerid] [type] [amount]");
    }

    static const validItems[][] = {
        "c4",
        "crack",
        "weed",
        "picklock",
        "wallet",
        "condom",
        "rope",
        "scissors",
        "oranges",
        "bottles",
        "orangejuice",
        "fruitpicker"
    };

    static const itemLimit[] = {
        MAX_ITEM,
        MAX_CRACK,
        MAX_WEED,
        MAX_ITEM,
        MAX_ITEM,
        MAX_ITEM,
        MAX_ITEM,
        MAX_ITEM,
        MAX_ORANGES,
        MAX_BOTTLES,
        MAX_ORANGEJUICE,
        MAX_FRUITPICKER
    };

    new
        bool:isValid = false,
        itemId = -1;

    for(new i = 0; i < sizeof(validItems); i ++) {
        if(!strcmp(type, validItems[i])) {
            isValid = true;
            itemId = i;
            break;
        }
    }

    if(!isValid) {
        return SendErrorMsg(
                playerid,
                "invalid type \
                ~n~valid types: \
                ~n~[~y~c4, crack, weed, picklock, wallet, condom, rope, scissors, orange, bottles, orangejuice, fruitpicker~w~]"
            );
    }

    if(amount > 10 || amount < 1) {
        return SendErrorMsg(playerid, "invalid range 1 - 10");
    }

    if(amount > (itemLimit[itemId] - _ItemPlayerHoldingValue(playerid, itemId))) {
        return SendErrorMsgF(
                playerid,
                "value too high\
                ~n~tip: player can hold ~y~%i ~p~%s",
                (itemLimit[itemId] - _ItemPlayerHoldingValue(playerid, itemId)),
                validItems[itemId]
            );
    }

    _GiveItem(targetid, itemId, amount);

    SendServerMsgF(playerid, "You have given %p[%i] x"C_YELLOW"%i "C_GREY"%s", targetid, targetid, amount, validItems[itemId]);
    SendServerMsgF(playerid, "%p[%i] have given you x"C_YELLOW"%i "C_GREY"%s", playerid, playerid, amount, validItems[itemId]);
    return 1;
}

CMD:crack(playerid, params[]) {
    if(Player_GetCrack(playerid) < 1) {
        return SendErrorMsg(playerid, "You don't have any crack cocaine on you.");
    }

    new
        Float:hp,
        Float:armour;

    GetPlayerHealth(playerid, hp);
    GetPlayerArmour(playerid, armour);

    // Crack Effect: Give 50 HP and 50 Armour, and visual drunk effect
    hp += 50.0;
    if(hp > 100.0) hp = 100.0;
    SetPlayerHealth(playerid, hp);

    armour += 50.0;
    if(armour > 100.0) armour = 100.0;
    SetPlayerArmour(playerid, armour);

    SetPlayerDrunkLevel(playerid, 5000); // Drunken effect

    // Apply smoking animation
    ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, false, true, true, false, 0, SYNC_ALL);

    Player_GiveCrack(playerid, -1);
    
    SendClientMessage(playerid, COLOR_GREEN, "** DRUGS ** "C_WHITE"You smoked a hit of crack. Your health and armour increased, but you feel dizzy!");
    return 1;
}

