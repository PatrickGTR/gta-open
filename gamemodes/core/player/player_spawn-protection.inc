#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_bit>

static 
	BitArray:Player_SpawnProtection<MAX_PLAYERS>;

hook OnPlayerSpawn(playerid) {
	SendClientMessage(playerid, COLOR_GREEN, "[!] You are spawn protected for 5 seconds.");
   	defer EndPlayerSpawnProtection(playerid);
   	Bit_Let(Player_SpawnProtection, playerid);
}

timer EndPlayerSpawnProtection[5000](playerid)
{
	SendClientMessage(playerid, COLOR_GREEN, "[!] Your spawn protection has ended, good luck!");
	CallLocalFunction("OnPlayerSpawnProtectionEnd", "i", playerid);
	Bit_Vet(Player_SpawnProtection, playerid);
    return 1;
}

IsPlayerSpawnProtected(playerid) {
	return Bit_Get(Player_SpawnProtection, playerid);
}
