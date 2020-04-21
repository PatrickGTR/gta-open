// Patrick Dave Subang (c) 2020 April 
// Github -> https://github.com/PatrickGTR

// Credits to these people, made the production easier.
// Southclaw, Y_Les, maddinatO, SyS, Zeex, Slice, Lorenc

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 50
#define BCRYPT_COST 12
#define MAX_BAN_REASON (32)

#define strcpy(%0,%1) strcat((%0[0] = '\0', %0), %1)

#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_NO_VERSION_CHECK
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_CACHE_MESSAGE

#define SERVER_NAME 			"GTA:DM v1.0.0"

#define MYSQL_PREPARE_DEBUG 	(true)
#define SETUP_TABLE 			(true)

// (dd, mm, yyyy)
#define SQL_DATETIME_FORMAT     "%d %M %Y at %r"
#define SQL_DATE_FORMAT         "%d %M %Y"

new Float:Spawns[][] =
{
	{-87.4950,1217.3195,19.7422,185.2165},
	{-165.9810,1050.8811,19.7422,165.5720},
	{-158.8103,1128.7385,19.7422,344.7046},
	{-204.9586,1119.3209,19.7422,269.6488},
	{-231.5153,1052.6196,19.7344,282.4956},
	{-165.9810,1050.8811,19.7422,165.5720},
	{-110.0530,1133.4197,19.7422,3.8179},
	{-141.6544,1176.3391,19.7500,351.0439}
};

// Utils Modules
#include <utils>

// Anti Cheat Module
#include <anti-cheat_main>

// Server Module
#include <server_db-conf>

// User Interface 
#include <user-interface>

// Account Module
#include <account>

// Admin Module
#include <admin>

// Chat & Messaging
#include <chat>

// Player
//#include <player_spawn-protection> 

#include <logger>
main() {
	log("gamemode initialised.");
	logger_debug("player", true);
	logger_debug("admin", true);
}

public OnGameModeInit()
{
	SetGameModeText(SERVER_NAME);
	SetWorldTime(23);
	SetWeather(0);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	UsePlayerPedAnims();
	
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerSkin(playerid, 0);
	SpawnPlayer(playerid);
	return 1;
}

public OnPlayerConnect(playerid)
{
	SetPlayerColor(playerid, COLOR_GREY);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	new rand = random(sizeof(Spawns));
	SetPlayerPos(playerid, Spawns[rand][0], Spawns[rand][1], Spawns[rand][2]);

	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
    PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
	return 1;
}