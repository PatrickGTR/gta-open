// SAMP
#include <open.mp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 50

#define WEAPON_BODY_PART_CHEST 3
#define WEAPON_BODY_PART_TORSO 4
#define WEAPON_BODY_PART_LEFT_ARM 5
#define WEAPON_BODY_PART_RIGHT_ARM 6
#define WEAPON_BODY_PART_LEFT_LEG 7
#define WEAPON_BODY_PART_RIGHT_LEG 8
#define WEAPON_BODY_PART_HEAD 9

// BCrypt
#define BCRYPT_COST 12

// Set to true if table aren't set up.
#define SETUP_TABLE 			(true)

// MySQL Prepared Statement
#define MYSQL_PREPARE_DEBUG 	(false)
#define MAX_STATEMENTS 100

// SA-MP Logger
#define PLAYER_DEBUG_HANDLER    "player"
#define SERVER_DEBUG_HANDLER    "server"
#define ADMIN_DEBUG_HANDLER     "admin"

// YSI
#define CGEN_MEMORY (20000) // needs looking at, no clue why we had to increase this. YSI said so.
#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_NO_VERSION_CHECK
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_CACHE_MESSAGE

// In-game settings / limits
#define MAX_PLATE_NAME          24
#define MAX_BAN_REASON          32
#define MAX_VEHICLE_PER_PLAYER  2
#define MAX_CRACK               5
#define MAX_WEED                5
#define MAX_ITEM                10
#define MAX_ATMS                50

// Gang limits
#define MAX_GANGS 10
#define MAX_GANG_NAME 17 // 16 + 1

// Server Settings
#define SERVER_NAME 			"Grand Theft Open"
#define SERVER_MODE 			"Cops and Robbers"
#define SERVER_LANGUAGE			"English"
#define SERVER_WEBSITE			"www.open.mp"

#define SCRIPT_VERSION_MAJOR	1
#define SCRIPT_VERSION_MINOR	0
#define SCRIPT_VERSION_PATCH	0

// Streamer
#define TEXTLABEL_STREAMDISTANCE    (200)
#define CHECKPOINT_STREAMDISTANCE   (200)
#define MAPICON_STREAMDISTANCE      (500)

// Gang
#define INVALID_GANG_ID (-1)
#define INVALID_GANG_RANK   (0)

// MySQL Datetime (dd, mm, yyyy)
#define SQL_DATETIME_FORMAT     "%d %M %Y at %r"
#define SQL_DATE_FORMAT         "%d %M %Y"

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

enum {
    ENEX_STREAMER_IDENTIFIER = 100,     // Entrance/Exits around San Fierro
    HOUSES_STREAMER_IDENTIFIER,         // Entrance/Exit for houses around San Andreas.
    FURNITURE_STREAMER_IDENTIFIER       // Furniture Objects
}

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
    TEAM_CIVILIAN = 0,
    TEAM_POLICE,
    TEAM_ARMY,
    TEAM_MEDIC
}

