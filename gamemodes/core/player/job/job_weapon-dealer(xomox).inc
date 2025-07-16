/* INCLUDES */
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

/* DEFINES */
#define MAX_WEAPON_INDEX    (10)
#define MAX_WEAPON_PRICE    (500000)
#define MIN_WEAPON_PRICE    (5000)

/* VARIABLES */
static
    gWeaponID[MAX_PLAYERS][MAX_WEAPON_INDEX],
    gWeaponPrice[MAX_PLAYERS][MAX_WEAPON_INDEX],
    gWeaponAmmo[MAX_PLAYERS][MAX_WEAPON_INDEX],
    gWeaponCount[MAX_PLAYERS][MAX_WEAPON_INDEX], // The Ammout of the weapon ex: 2x M4 (500 Ammo)
    Bit:gHasBeenOffered[MAX_PLAYERS],
    bool:gNoSell[MAX_PLAYERS],
    Iterator:gWeaponIndex[MAX_PLAYERS]<MAX_WEAPON_INDEX>,
    gDealerID[MAX_PLAYERS],
    gPlayerArmourInInv[MAX_PLAYERS]
;

/* STATEMETS */
static
    Statement:stmt_loadWeaponInv,
    Statement:stmt_saveWeaponInv
;

/* HOOKS */

hook OnMySQLConnected()
{
    static const query_loadWeaponInv[] = "\
    SELECT \
        windex, \
        wcount, \
        weaponid, \
        ammo, \
        price, \
        armour \
    FROM \
        player_weaponInv \
    WHERE \
        u_id = ? \
    ";
    stmt_loadWeaponInv = MySQL_PrepareStatement(MySQL_GetHandle(), query_loadWeaponInv);

    static const query_saveWeaponInv[] = "\
    INSERT INTO player_weaponInv (u_id, windex, wcount, weaponid, ammo, price) \
    VALUES (?, ?, ?, ?, ?, ?, ?)\
    ";
    stmt_saveWeaponInv = MySQL_PrepareStatement(MySQL_GetHandle(), query_saveWeaponInv);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    foreach(new i : gWeaponIndex[playerid])
    {
        gWeaponID[playerid][i] = -1;
        gWeaponPrice[playerid][i] = 0;
        gWeaponAmmo[playerid][i] = 0;
        gWeaponCount[playerid][i] = 0;
        Bit_Set(gHasBeenOffered, playerid, false);
    }
    Iter_Clear(gWeaponIndex[playerid]);
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline _load() {
        new
            index,
            count,
            weaponid,
            ammo,
            price,
            armour;
        MySQL_BindResultInt(stmt_loadWeaponInv, 0, index);
        MySQL_BindResultInt(stmt_loadWeaponInv, 1, count);
        MySQL_BindResultInt(stmt_loadWeaponInv, 2, weaponid);
        MySQL_BindResultInt(stmt_loadWeaponInv, 3, ammo);
        MySQL_BindResultInt(stmt_loadWeaponInv, 4, price);
        MySQL_BindResultInt(stmt_loadWeaponInv, 5, armour);

        while(MySQL_Statement_FetchRow(stmt_loadWeaponInv)) {
            gWeaponID[playerid][index] = weaponid;
            gWeaponPrice[playerid][index] = price;
            gWeaponAmmo[playerid][index] = ammo;
            gWeaponCount[playerid][index] = count;
            gPlayerArmourInInv[playerid] = armour;
            Iter_Add(gWeaponIndex[playerid], index);
        }
    }
    MySQL_BindInt(stmt_loadWeaponInv, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_loadWeaponInv, using inline _load);
    return 1;
}

hook OnPlayerSecondUpdate(playerid)
{
    foreach(new i : gWeaponIndex[playerid])
    {
        if(gWeaponCount[playerid][i] == 0)
        {
            DeleteWeaponIndex(playerid, i);
        }
    }
    return 1;
}

/* COMMANDS */

CMD:weapons(playerid, params[])
{
    new dealerid = Player_GetClosestPlayer(playerid, 5.0);
    if(!IsPlayerConnected(dealerid)) return SendErrorMsg(playerid, "There is no players close to you");
    if(Player_GetClass(playerid) != TEAM_CIVILIAN) return SendErrorMsg(playerid, "You have to be a civilian to use this.");
    if(Player_GetJob(dealerid) != TYPE_WEAPONDEALER) return SendErrorMsg(playerid, "This player is not a weapon dealer");
    if(gNoSell[dealerid]) return SendErrorMsg(playerid, "Dealer is not selling atm.");
    ShowDealerInvToPlayer(playerid, dealerid);
    return 1;
}
ALTCMD:ws(weapons);

CMD:weaponinventory(playerid, params[])
{
    if(Player_GetJob(playerid) != TYPE_WEAPONDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) return SendErrorMsg(playerid, "You're not a weapon dealer");
    Player_ShowWeaponInv(playerid);
    return 1;
}
ALTCMD:wi(weaponinventory);
ALTCMD:weapinv(weaponinventory);

CMD:nosell(playerid, params)
{
    if(Player_GetJob(playerid) != TYPE_WEAPONDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) return SendErrorMsg(playerid, "You're not a weapon dealer");
    if(!gNoSell[playerid]) {
        SendServerMsg(playerid, "You're now selling weapons.");
        gNoSell[playerid] = true;
    } else if(gNoSell[playerid]) {
        SendServerMsg(playerid, "You're not selling weapons now.");
        gNoSell[playerid] = false;
    }
    return 1;
}

/* FUNCTIONS */

TDMenu:DealerInventory(playerid, listitem)
{
    new tmpString[24];
    format(tmpString, sizeof(tmpString), "DealerMenuItem_%i", listitem);
    new index = GetPVarInt(playerid, tmpString);
    new dealerid = gDealerID[playerid];

    if(dealerid != INVALID_PLAYER_ID)
    {
        if(GetPlayerMoney(playerid) < gWeaponPrice[dealerid][index]) return SendErrorMsg(playerid, "You don't have any money to buy this");
        GivePlayerMoney(playerid, -gWeaponPrice[dealerid][index]);
        GivePlayerMoney(dealerid, gWeaponPrice[dealerid][index]);
        GivePlayerWeapon(playerid, gWeaponID[dealerid][index], gWeaponAmmo[dealerid][index]);
        if(gWeaponCount[dealerid][index] > 1) {
            gWeaponCount[dealerid][index] --;
            new tmpstr[152];
            mysql_format(MySQL_GetHandle(), tmpstr, sizeof(tmpstr), "UPDATE player_weaponInv SET wcount = '%d' WHERE u_id = '%d' & windex = '%d'", gWeaponCount[playerid][index], Player_GetAccountID(playerid), index);
            mysql_tquery(MySQL_GetHandle(), tmpstr);
        } else {
            DeleteWeaponIndex(dealerid, index, true);
        }
        gDealerID[playerid] = INVALID_PLAYER_ID;
    }

    return 1;
}

static ShowDealerInvToPlayer(playerid, dealerid)
{
    new
        count = 0,
        tmpString[100],
        weaponname[16]
    ;
    TextMenu_Create(playerid, "DealerInventory", "Weapons");
    foreach(new i : gWeaponIndex[dealerid])
    {
        GetWeaponName(gWeaponID[dealerid][i], weaponname, sizeof weaponname);
        format(tmpString, sizeof(tmpString), "Weapon: ~g~%s ~w~Ammo: ~g~%d ~w~Price: ~g~$%d", weaponname, gWeaponAmmo[dealerid][i], gWeaponPrice[dealerid][i]);
        TextMenu_Add(playerid, tmpString);

        count ++;
        format(tmpString, sizeof(tmpString), "DealerMenuItem_%i", count);
        SetPVarInt(playerid, tmpString, i);
    }
    if(count == 0) {
        SendServerMsg(playerid, "Player Doesn't have any weapon items");
    } else {
        gDealerID[playerid] = dealerid;
        TextMenu_Show(playerid);
    }
    return 1;
}

TDMenu:WeaponInventory(playerid, listitem)
{
    new tmpString[24], weaponname[16];
    format(tmpString, sizeof tmpString, "WeaponInv_%i", listitem);
    new index = GetPVarInt(playerid, tmpString);
    GetWeaponName(gWeaponID[playerid][index], weaponname, sizeof weaponname);

    inline _response(pid, dialogid, response, listitem2, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem2
        if(!response) {
            SendServerMsg(playerid, "Returned to menu.");
            Player_ShowWeaponInv(playerid);
            return 1;
        }
        else {
            if(!IsNumeric(inputtext)) return SendErrorMsg(playerid, "This is not a number");
            new value = strval(inputtext);
            if(value < MIN_WEAPON_PRICE || value > MAX_WEAPON_PRICE) return SendErrorMsgF(playerid, "Max weapon price is %d and min is %d", MAX_WEAPON_PRICE, MIN_WEAPON_PRICE);
            gWeaponPrice[playerid][index] = value;
            SendServerMsgF(playerid, "You have set %s (%d Ammo)'s price to %d", weaponname, gWeaponAmmo[playerid][index], value);
            new tmpstr[152];
            mysql_format(MySQL_GetHandle(), tmpstr, sizeof(tmpstr), "UPDATE player_weaponInv SET price = '%d' WHERE u_id = '%d' & windex = '%d'", value, Player_GetAccountID(playerid), index);
            mysql_tquery(MySQL_GetHandle(), tmpstr);
            Player_ShowWeaponInv(playerid);
        }
    }

    format(tmpString, sizeof(tmpString), "Current price of %s (%d Ammo) is $%d", weaponname, gWeaponAmmo[playerid][index], gWeaponPrice[playerid][index]);
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, "Enter the price for this weapon...", tmpString, "Done", "Close");
    return 1;
}

static Player_ShowWeaponInv(playerid)
{
    new
        count = 0,
        tmpString[100],
        weaponname[16]
    ;
    TextMenu_Create(playerid, "WeaponInventory", "Weapon Inventory");
    foreach(new i : gWeaponIndex[playerid])
    {
        GetWeaponName(gWeaponID[playerid][i], weaponname, sizeof weaponname);
        format(tmpString, sizeof(tmpString), "Weapon: ~g~%s ~w~Ammo: ~g~%d ~w~Price: ~g~$%d Query: ~g~%d", weaponname, gWeaponAmmo[playerid][i], gWeaponPrice[playerid][i], gWeaponCount[playerid][i]);
        TextMenu_Add(playerid, tmpString);

        count++;
        format(tmpString, sizeof(tmpString), "WeaponInv_%i", count);
        SetPVarInt(playerid, tmpString, i);
    }
    if(count == 0) {
        SendServerMsg(playerid, "You don't have any weapon in your inventory");
    } else {
        SendServerMsg(playerid, "Select an item if you wish to change the price");
        TextMenu_Show(playerid);
    }
    return 1;
}

// Returns nothing.
static DeleteWeaponIndex(playerid, index, bool:save = false)
{
    if(!Iter_Contains(gWeaponIndex[playerid], index)) return 0;
    gWeaponID[playerid][index] = -1;
    gWeaponPrice[playerid][index] = 0;
    gWeaponAmmo[playerid][index] = 0;
    gWeaponCount[playerid][index] = 0;
    Iter_Remove(gWeaponIndex[playerid], index);
    if(save) {
        new tmpString[128];
        mysql_format(MySQL_GetHandle(), tmpString, sizeof(tmpString), "DELETE FROM player_weaponInv WHERE u_id = '%d' & index = '%d'", Player_GetAccountID(playerid), index);
        mysql_tquery(MySQL_GetHandle(), tmpString);
    }
    return 1;
}

// Returns
// -1 if there is no slots.
// 0 If there is a existing weapon.
// 1 if there is no existing weapon.
static GivePlayerInvWeapon(playerid, weaponid, ammo)
{
    new index = Iter_Free(gWeaponIndex[playerid]);
    //Search for a existing weapon that has same weapon and ammo and just add a query to it instead of creating a new line.
    foreach(new i : gWeaponIndex[playerid])
    {
        if(gWeaponID[playerid][i] == weaponid && gWeaponAmmo[playerid][i] == ammo)
        {
            gWeaponCount[playerid][i]++;
            new tmpString[152];
            mysql_format(MySQL_GetHandle(), tmpString, sizeof(tmpString), "UPDATE player_weaponInv SET wcount = '%d' WHERE u_id = '%d' & windex = '%d'", gWeaponCount[playerid][i], Player_GetAccountID(playerid), i);
            mysql_tquery(MySQL_GetHandle(), tmpString);
            return 1;
        }
    }
    // If there is no existing weapon we add
    if(index == ITER_NONE) {
        return -1;
    }
    Iter_Add(gWeaponIndex[playerid], index);
    gWeaponID[playerid][index] = weaponid;
    gWeaponCount[playerid][index]++;
    gWeaponAmmo[playerid][index] = ammo;
    gWeaponPrice[playerid][index] = 5000;
    MySQL_BindInt(stmt_saveWeaponInv, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_saveWeaponInv, 1, index);
    MySQL_BindInt(stmt_saveWeaponInv, 2, gWeaponCount[playerid][index]);
    MySQL_BindInt(stmt_saveWeaponInv, 3, weaponid);
    MySQL_BindInt(stmt_saveWeaponInv, 4, ammo);
    MySQL_BindInt(stmt_saveWeaponInv, 5, gWeaponPrice[playerid][index]);
    MySQL_ExecuteThreaded(stmt_saveWeaponInv);
    return 1;
}

/* WEAPONS FOR WEAPON DEALERS */
TDMenu:WeaponShowPage1(playerid, listitem)
{
    switch(listitem) {
        case 1: {
            if(GetPlayerMoney(playerid) < 15000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -15000);
            GivePlayerInvWeapon(playerid, 24, 250);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 2: {
            if(GetPlayerMoney(playerid) < 30000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -30000);
            GivePlayerInvWeapon(playerid, 24, 500);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 3: {
            if(GetPlayerMoney(playerid) < 10000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -10000);
            GivePlayerInvWeapon(playerid, 26, 250);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 4: {
            if(GetPlayerMoney(playerid) < 25000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -25000);
            GivePlayerInvWeapon(playerid, 24, 500);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 5: {
            if(GetPlayerMoney(playerid) < 5000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -5000);
            GivePlayerInvWeapon(playerid, 22, 100);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 6: {
            if(GetPlayerMoney(playerid) < 50000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -50000);
            GivePlayerInvWeapon(playerid, 22, 250);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 7: {
            if(GetPlayerMoney(playerid) < 5000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -5000);
            GivePlayerInvWeapon(playerid, 23, 100);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 8: {
            if(GetPlayerMoney(playerid) < 10000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -10000);
            GivePlayerInvWeapon(playerid, 23, 250);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 9: {
            if(GetPlayerMoney(playerid) < 6000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -6000);
            GivePlayerInvWeapon(playerid, 25, 50);
            Player_ShowWeaponShop(playerid, 1);
        }
        case 10: {
            Player_ShowWeaponShop(playerid, 2);
        }
    }
    return 1;
}

TDMenu:WeaponShowPage2(playerid, listitem)
{
    switch(listitem)
    {
        case 1: {
            if(GetPlayerMoney(playerid) < 12000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -12000);
            GivePlayerInvWeapon(playerid, 25, 100);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 2: {
            if(GetPlayerMoney(playerid) < 13000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -13000);
            GivePlayerInvWeapon(playerid, 27, 100);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 3: {
            if(GetPlayerMoney(playerid) < 26000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -26000);
            GivePlayerInvWeapon(playerid, 27, 250);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 4: {
            if(GetPlayerMoney(playerid) < 25000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -25000);
            GivePlayerInvWeapon(playerid, 28, 250);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 5: {
            if(GetPlayerMoney(playerid) < 50000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -50000);
            GivePlayerInvWeapon(playerid, 28, 500);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 6: {
            if(GetPlayerMoney(playerid) < 25000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -25000);
            GivePlayerInvWeapon(playerid, 32, 250);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 7: {
            if(GetPlayerMoney(playerid) < 50000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -50000);
            GivePlayerInvWeapon(playerid, 32, 500);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 8: {
            if(GetPlayerMoney(playerid) < 15000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -15000);
            GivePlayerInvWeapon(playerid, 31, 250);
            Player_ShowWeaponShop(playerid, 2);
        }
        case 9: {
            Player_ShowWeaponShop(playerid, 1);
        }
        case 10: {
            Player_ShowWeaponShop(playerid, 3);
        }
    }
    return 1;
}

TDMenu:WeaponShowPage3(playerid, listitem)
{
    switch(listitem)
    {
        case 1: {
            if(GetPlayerMoney(playerid) < 10000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -10000);
            GivePlayerInvWeapon(playerid, 30, 250);
            Player_ShowWeaponShop(playerid, 3);
        }
        case 2: {
            if(GetPlayerMoney(playerid) < 5000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -5000);
            GivePlayerInvWeapon(playerid, 33, 50);
            Player_ShowWeaponShop(playerid, 3);
        }
        case 3: {
            if(GetPlayerMoney(playerid) < 10000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -10000);
            GivePlayerInvWeapon(playerid, 33, 100);
            Player_ShowWeaponShop(playerid, 3);
        }
        case 4: {
            if(GetPlayerMoney(playerid) < 6000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -6000);
            GivePlayerInvWeapon(playerid, 34, 50);
            Player_ShowWeaponShop(playerid, 3);
        }
        case 5: {
            if(GetPlayerMoney(playerid) < 12000) return SendErrorMsg(playerid, "You don't have enough money");
            GivePlayerMoney(playerid, -12000);
            GivePlayerInvWeapon(playerid, 34, 100);
            Player_ShowWeaponShop(playerid, 3);
        }
        case 6: {
            Player_ShowWeaponShop(playerid, 2);
        }
    }
    return 1;
}

Player_ShowWeaponShop(playerid, page)
{
    switch(page)
    {
        case 1: {
            TextMenu_Create(playerid, "WeaponShowPage1", "Weapons");
            TextMenu_Add(playerid, "Deagle (250 Ammo)\t~g~$15000");
            TextMenu_Add(playerid, "Deagle (500 Ammo)\t~g~$30000");
            TextMenu_Add(playerid, "Sawn Off (250 Ammo)\t~g~$10000");
            TextMenu_Add(playerid, "Sawn Off (500 Ammo)\t~g~$25000");
            TextMenu_Add(playerid, "9mm (100 Ammo)\t~g~$5000");
            TextMenu_Add(playerid, "9mm (250 Ammo)\t~g~$10000");
            TextMenu_Add(playerid, "Silenced 9mm (100 Ammo)\t~g~$5000");
            TextMenu_Add(playerid, "Silenced 9mm (250 Ammo)\t~g~$10000");
            TextMenu_Add(playerid, "Shotgun (50 Ammo)\t~g~$6000");
            TextMenu_Add(playerid, "Next Page");
        }
        case 2: {
            TextMenu_Create(playerid, "WeaponShowPage2", "Weapons");
            TextMenu_Add(playerid, "Shotgun (100 Ammo)\t~g~$12000");
            TextMenu_Add(playerid, "Automatic Shotgun (100 Ammo)\t~g~$13000");
            TextMenu_Add(playerid, "Automatic Shotgun (250 Ammo)\t~g~$26000");
            TextMenu_Add(playerid, "UZI (250 Ammo)\t~g~$25000");
            TextMenu_Add(playerid, "UZI (500 Ammo)\t~g~$50000");
            TextMenu_Add(playerid, "Tec9 (250 Ammo)\t~g~$25000");
            TextMenu_Add(playerid, "Tec9 (500 Ammo)\t~g~$50000");
            TextMenu_Add(playerid, "M4 (250 Ammo)\t~g~$15000");
            TextMenu_Add(playerid, "Previous Page");
            TextMenu_Add(playerid, "Next Page");
        }
        case 3: {
            TextMenu_Create(playerid, "WeaponShowPage3", "Weapons");
            TextMenu_Add(playerid, "AK-47 (250 Ammo)\t~g~$10000");
            TextMenu_Add(playerid, "Country Rifle (50 Ammo)\t~g~$5000");
            TextMenu_Add(playerid, "Country Rifle (100 Ammo)\t~g~$10000");
            TextMenu_Add(playerid, "Sniper Rifle (50 Ammo)\t~g~$6000");
            TextMenu_Add(playerid, "Sniper Rifle (100 Ammo)\t~g~$12000");
            TextMenu_Add(playerid, "Previous Page");
        }
    }
    TextMenu_Show(playerid);
}