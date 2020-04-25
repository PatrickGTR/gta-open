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

#define TEXTLABEL_STREAMDISTANCE    (50)
#define CHECKPOINT_STREAMDISTANCE   (50)
#define MAPICON_STREAMDISTANCE      (300)

#define MYSQL_PREPARE_DEBUG 	(true)
#define SETUP_TABLE 			(true)

// (dd, mm, yyyy)
#define SQL_DATETIME_FORMAT     "%d %M %Y at %r"
#define SQL_DATE_FORMAT         "%d %M %Y"

new Float:Spawns[][] =
{
	{ 810.63520, -1340.0682, 13.5386, 37.33070},
	{ 1124.6071, -1427.5155, 15.7969, 350.9336},
	{ 585.81520, -1247.9160, 17.9521, 335.6035},
	{ 2025.2626, -1423.2682, 16.9922, 135.4516},
	{ 2509.2468, -1679.2029, 13.5469, 50.24740},
	{ 1457.1467, -1011.7307, 26.8438, 51.79910},
	{ 2017.8206, -1279.4851, 23.9820, 47.38920},
	{ 1935.7644, -1794.6068, 13.5469, 295.5515},
	{ 1371.4569, -1090.6387, 24.5459, 92.84640},
	{ 2298.4055, -1500.3264, 25.3047, 199.6940},
	{ 1178.0417, -1323.6000, 14.1005, 285.5701},
	{ 1757.44350, -1456.7, 13.5469, 282.4133}

};

// Utils Modules
#include <utils>

// Anti Cheat Module
#include <anti-cheat_main>

// Server Module
#include <server>

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