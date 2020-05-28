#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

static 
    WeaponPrice[MAX_PLAYERS],
    WeaponID[MAX_PLAYERS],
    WeaponAmmo[MAX_PLAYERS],
    WeaponSeller[MAX_PLAYERS],
    BitArray:HasBeenOffered<MAX_PLAYERS>,
    SellWeaponCooldown[MAX_PLAYERS],
    SellArmourcooldown[MAX_PLAYERS];
	

hook OnPlayerConnect(playerid, reason) {
	SellWeaponCooldown[playerid] = 
	SellArmourcooldown[playerid] = 
    WeaponID[playerid] = 
    WeaponPrice[playerid] = 
    WeaponAmmo[playerid] = -1;
    WeaponSeller[playerid] = INVALID_PLAYER_ID;
	Bit_Set(HasBeenOffered, playerid, false);
    return 1;
}

CMD:sellgun(playerid, params[])
{
	
	new 
		weaponid, 
        targetid, 
        weaponprice, 
        weaponammo;

	if (Player_GetJob(playerid) != TYPE_WEAPONDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "You are not allowed to use this command if you are not a weapon dealer.");
    } 
	if (gettime() - SellWeaponCooldown[playerid] < 40) {
		return SendErrorMsgF(playerid, "You just sold a weapon, please wait "C_GREY"%i seconds ", gettime() - SellWeaponCooldown[playerid]);
    }

	if (sscanf(params, "riii", targetid, weaponid, weaponprice, weaponammo)) {
		return SendSyntaxMsg(playerid, "/sellweapon <playerid> <weaponid> <price> <ammo (max 1,000)>");
    }

	if (!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "The player you are trying to sell weapon is not connected.");
    }

	if (!Player_IsSpawned(targetid)) {
		return SendErrorMsg(playerid, "The player you are trying to sell weapon is not spawned.");
    }

	if (!Player_IsNearPlayer(playerid, targetid, 4.0)) {
		return SendErrorMsg(playerid, "The player you are trying to sell weapon is not near you.");
    }

	if (targetid == playerid) {    
		return SendErrorMsg(playerid, "You can not sell a gun to your self.");
    }

	if (1000 <= weaponprice < 8000) {
		return SendErrorMsg(playerid, "Weapon price could not go lower than 1,000 and higher than 8,000");
    }

	if (!(22 <= weaponid <= 34)) {
		return SendErrorMsg(playerid, "Invalid weapon id. Weapon id can only go up to 22 - 34");
    }

	if (!(0 <= weaponammo <= 1000)) {
		return SendErrorMsg(playerid, "Invalid weapon ammo. Weapon ammo can only go up to 0 - 1000");
    }

	Bit_Set(HasBeenOffered, targetid, true);
	WeaponID[targetid] = weaponid;
	WeaponPrice[targetid] = weaponprice;
	WeaponAmmo[targetid] = weaponammo;
 	WeaponSeller[targetid] = playerid;

	SendMsgF(playerid, COLOR_ORANGE, "** WEAPON **: "C_WHITE" You have offered %p (%i) a %W for "C_GREEN"$%i"C_WHITE", wish you luck that he'll accept it!", targetid, targetid, weaponid, weaponprice);
	SendMsgF(targetid, COLOR_ORANGE, "** WEAPON **: "C_WHITE" Weapon dealer "C_GREY"%p (%i) "C_WHITE"offered you a %W for "C_GREEN"$%i"C_WHITE", /acceptgun to accept his offer.", playerid, playerid, weaponid, weaponprice);
	
	SellWeaponCooldown[playerid] = gettime();
	return true;
}

CMD:acceptgun(playerid, params[])
{
	if (Bit_Get(HasBeenOffered, playerid)) {
		return SendErrorMsg(playerid, "No one offered you a gun.");
    }

	if (GetPlayerMoney(playerid) < WeaponPrice[playerid]) {
		return SendErrorMsgF(playerid, "You do not have "C_GREEN"$%d "C_WHITE"to buy the weapon.", WeaponPrice[playerid]);
    }

	GivePlayerMoney(playerid, -WeaponPrice[playerid]);
	GivePlayerMoney(WeaponSeller[playerid], WeaponPrice[playerid]);

	GivePlayerWeapon(playerid, WeaponID[playerid], WeaponAmmo[playerid]);

	SendMsgF(WeaponSeller[playerid], COLOR_ORANGE, "** WEAPON **: "C_WHITE"%p (%i) accepted your offer, today you earned "C_GREEN"$%i"C_WHITE" for selling guns.", playerid, playerid, WeaponPrice[playerid]);
	SendMsgF(playerid, COLOR_ORANGE, "** WEAPON **: "C_WHITE"You "C_GREEN"successfully "C_WHITE"bought a %W for "C_GREEN"$%i"C_WHITE" from "C_GREY"%p(%i)", WeaponID[playerid], WeaponPrice[playerid], 
	WeaponSeller[playerid], WeaponSeller[playerid]);

	Bit_Set(HasBeenOffered, playerid, false), 
	WeaponID[playerid] = -1, 
	WeaponPrice[playerid] = -1, 
	WeaponAmmo[playerid] = -1, 
	WeaponSeller[playerid] = INVALID_PLAYER_ID;
	return true;
}

CMD:sellarmour(playerid, params[])
{
	new 
		targetid, armourprice, armouramount; 

	if (Player_GetJob(playerid) != TYPE_WEAPONDEALER || Player_GetClass(playerid) != TEAM_CIVILIAN) {
		return SendErrorMsg(playerid, "You are not allowed to use this command if you are not a weapon dealer.");
    }

	if (gettime() - SellArmourcooldown[playerid] < 40)  {
		return SendErrorMsgF(playerid, "You just sold a weapon, please wait %i seconds ", gettime() - SellArmourcooldown[playerid]);
    }

	if (sscanf(params, "rii", targetid, armourprice, armouramount)) {
		return SendSyntaxMsg(playerid, "/sellarmour <playerid> <Price> <Amount>");
    }

	if (!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "The player you are trying to sell weapon is not connected.");
    }

	if (!Player_IsSpawned(targetid)) {
		return SendErrorMsg(playerid, "The player you are trying to sell weapon is not spawned.");
    }

	if (!Player_IsNearPlayer(playerid, targetid, 4.0)) {
		return SendErrorMsg(playerid, "The player you are trying to sell armour is not near you.");
    }

	if (targetid == playerid)  {
		return SendErrorMsg(playerid, "You can not sell an armour to your self.");
    }

	if (!(0 <= armouramount <= 100)) {
		return SendErrorMsg(playerid, "Invalid armour amount. armour can only go up to 1 - 100"); 
    }

    new 
        Float:armour = Player_GetArmour(targetid);
	if (armour >= 80.0) {
		return SendErrorMsgF(playerid, "The player you are trying to sell armour has got enough (%.1f).", armour);
    }

	Bit_Set(HasBeenOffered, targetid, true);
	WeaponPrice[targetid] = armourprice, 
	WeaponAmmo[targetid] = armouramount, 
	WeaponSeller[targetid] = playerid;

	SendMsgF(playerid, COLOR_ORANGE, "** WEAPON **: "C_WHITE" You have offered "C_GREY"%p (%i) "C_WHITE"an armour(%i) for "C_GREEN"$%i"C_WHITE", wish you luck that he'll accept it!", targetid, targetid, armouramount, armourprice);
	SendMsgF(targetid, COLOR_ORANGE, "** WEAPON **: "C_WHITE" Weapon dealer "C_GREY"%p (%i) "C_WHITE"offered you an armour(%i) for "C_GREEN"$%i"C_WHITE", /acceptarmour to accept his offer.", playerid, playerid, armouramount, armourprice);
	
	SellArmourcooldown[playerid] = gettime();
	return true;
}

CMD:acceptarmour(playerid, params[])
{
	if (HasBeenOffered[playerid]) {
		return SendErrorMsg(playerid, "No one offered you armour.");
    }

	if (GetPlayerMoney(playerid) < WeaponPrice[playerid]) {
		return SendErrorMsgF(playerid, "You do not "C_GREEN"$%d "C_WHITE"to buy the weapon.", WeaponPrice[playerid]);
    }

	GivePlayerMoney(playerid, -WeaponPrice[playerid] );
	GivePlayerMoney(WeaponSeller[playerid], WeaponPrice[playerid]);

	new 
		Float:playerCurrentArmour;

	GetPlayerArmour(playerid, playerCurrentArmour);

	SetPlayerArmour(playerid, playerCurrentArmour + WeaponAmmo[playerid]);
	

	SendMsgF(WeaponSeller[playerid], COLOR_ORANGE, "** WEAPON **: "C_WHITE"%p (%i) accepted your offer, today you earned "C_GREEN"$%i"C_WHITE" for selling an armour.", playerid, playerid, WeaponPrice[playerid]);
	SendMsgF(playerid, COLOR_ORANGE, "** WEAPON **: "C_WHITE"You "C_GREEN"successfully "C_WHITE"bought an armour(%i) for "C_GREEN"$%i"C_WHITE" from "C_GREY"%p(%i)", WeaponAmmo[playerid], WeaponPrice[playerid], 
	WeaponSeller[playerid], WeaponSeller[playerid]);

	Bit_Set(HasBeenOffered, playerid, false), 
	WeaponPrice[playerid] = -1, 
	WeaponAmmo[playerid] = -1, 
	WeaponSeller[playerid] = INVALID_PLAYER_ID;
	return true;
}