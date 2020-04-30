#undef MAX_PLAYERS
#define MAX_PLAYERS 50
#define BCRYPT_COST 12
#define MAX_BAN_REASON (32)

#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_NO_VERSION_CHECK
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_CACHE_MESSAGE

#define SERVER_NAME 			"Grand Theft Open"
#define SERVER_VERSION			"1.0.0"
#define SERVER_MODE 			"Cops and Robbers"
#define SERVER_LANGUAGE			"English"
#define SERVER_WEBSITE			"www.sa-mp.com"

#define NEXT_PAGE (25)

#define TEXTLABEL_STREAMDISTANCE    (100)
#define CHECKPOINT_STREAMDISTANCE   (100)
#define MAPICON_STREAMDISTANCE      (500)

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
