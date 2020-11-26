#include <YSI_Coding\y_hooks>

static
	BitArray:Player_SpawnProtection<MAX_PLAYERS>;

hook OnPlayerSpawn(playerid) {
	MessageBox_Show(playerid, TYPE_INFORMATION, "~y~Spawn Protection", "You are spawn protected for 5 seconds.", 5000);
   	defer EndPlayerSpawnProtection(playerid);
   	Bit_Let(Player_SpawnProtection, playerid);
	return 1;
}

timer EndPlayerSpawnProtection[5000](playerid)
{
	MessageBox_Show(playerid, TYPE_INFORMATION, "~y~Spawn Protection", "Your spawn protection has ended, good luck!", 5000);

	CallLocalFunction("OnPlayerSpawnProtectionEnd", "i", playerid);
	Bit_Vet(Player_SpawnProtection, playerid);
    return 1;
}

stock Player_HasSpawnProtect(playerid) {
	return Bit_Get(Player_SpawnProtection, playerid);
}
