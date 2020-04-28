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

#define SERVER_NAME 			"Grand Theft Open"
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

enum {
    TYPE_NO_JOB = -1,
    TYPE_DRUGDEALER = 0,
    TYPE_WEAPONDEALER,
    TYPE_HITMAN,
    TYPE_TERRORIST,
    TYPE_RAPIST,
    TYPE_MECHANIC
}

enum {
    TEAM_CIVILIAN = NO_TEAM ,
    TEAM_POLICE = 0,
    TEAM_ARMY,
    TEAM_MEDIC
}

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

// Player Module
#include <player>

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
	return 1;
}

public OnPlayerConnect(playerid)
{
	SetPlayerColor(playerid, COLOR_GREY);
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
    PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
	return 1;
}

CMD:kill(playerid, params[]) {
	SetPlayerHealth(playerid, 0.0);
	return 1;
}

CMD:setwanted(playerid, params[]) {

	new level = strval(params); 

	if(level <= 0) {
		SetPlayerWantedLevel(playerid, 0);
	} else {
		Player_GiveWantedLevel(playerid, level);
	}

	//UI_UpdatePlayerWanted(playerid, level);
	return 1;
}
