#include <YSI_Coding\y_hooks>

static
	BitArray:Player_SpawnProtection<MAX_PLAYERS>;

hook OnPlayerSpawn(playerid) {
	SendClientMessage(playerid, COLOR_YELLOW, "[SPAWN-PROTECTION] You are spawn protected for 5 seconds.");
   	defer EndPlayerSpawnProtection(playerid);
   	Bit_Let(Player_SpawnProtection, playerid);
	return 1;
}

timer EndPlayerSpawnProtection[5000](playerid)
{
	SendClientMessage(playerid, COLOR_YELLOW, "[SPAWN-PROTECTION] Your spawn protection has ended, good luck!");
	CallLocalFunction("OnPlayerSpawnProtectionEnd", "i", playerid);
	Bit_Vet(Player_SpawnProtection, playerid);
    return 1;
}

stock Player_HasSpawnProtect(playerid) {
	return Bit_Get(Player_SpawnProtection, playerid);
}
