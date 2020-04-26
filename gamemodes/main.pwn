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

#define SERVER_NAME 			"Grand Thefte Open"
#define SERVER_VERSION			"1.0.0"
#define SERVER_MODE 			"Cops and Robbers"
#define SERVER_LANGUAGE			"English"
#define SERVER_WEBSITE			"www.sa-mp.com"

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
	SendRconCommand("hostname "SERVER_NAME" v"SERVER_VERSION"");
	SendRconCommand("gamemodetext "SERVER_MODE"");
	SendRconCommand("language "SERVER_LANGUAGE"");
	SendRconCommand("weburl "SERVER_WEBSITE"");

	SetWorldTime(23);
	SetWeather(0);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	UsePlayerPedAnims();
	
	// Civilian Skin
    AddPlayerClass(56,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(119, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(55,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(60,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(11,  0, 0, 0, 0, 0, 0, 0, 0, 0 , 0);
	AddPlayerClass(2,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(299, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(296, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(297, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(294, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(293, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(289, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(272, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(264, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(268, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(259, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(221, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(134, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(29,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(22,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(19,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	// Police Officer Skins
	AddPlayerClass(280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(281, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(282, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(283, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(284, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(285, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	// Army Skins
	AddPlayerClass(121, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass(287, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Medic Skins
	AddPlayerClass( 274, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass( 275, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClass( 276, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnPlayerRequestClass(playerid, classid) {
	SetPlayerPos(playerid, 180.892608, 1830.717895, 23.242187);
    SetPlayerFacingAngle(playerid, 255.810241);
    SetPlayerCameraLookAt(playerid, 180.892608, 1830.717895, 23.242187);
    SetPlayerCameraPos(playerid, 180.892608 + (5 * floatsin(-255.810241, degrees)), 1830.717895 + (5 * floatcos(-255.810241, degrees)), 23.242187);
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
	SetPlayerWantedLevel(playerid, 100);
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
    PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
	return 1;
}