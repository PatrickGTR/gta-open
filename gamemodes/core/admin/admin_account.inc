
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

#define MAX_ADMIN_LEVELS (5)

enum
{
    ADM_LVL_1 = 1,
    ADM_LVL_2,
    ADM_LVL_3,
    ADM_LVL_4,
    ADM_LVL_5
}

static
		  adminLevel[MAX_PLAYERS],
		  adminCommands[5][2048],
BitArray: adminOnDuty<MAX_PLAYERS>,
Statement: stmt_retrieveAdmin;



hook OnGameModeInit() {

    stmt_retrieveAdmin = MySQL_Prepare();
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerAdminLoad()
	{
		if(cache_num_rows())
		{

			new
				adm_level;

			cache_get_value_name_int(0, "admin_level", adm_level);

			Admin_SetPlayerLevel(playerid, adm_level);
		}
	}
    static const query[] = "\
        SELECT \
            admin_level \
        FROM  \
            admins \
        WHERE \
            u_id = %i \
        "
    ;
	MySQL_TQueryInline(MySQL_GetHandle(), using inline OnPlayerAdminLoad, query, GetPlayerAccountID(playerid));
}

/*

    Admin Messaging
        - SendAdminMessage
        - SendAdminMessageF(fmat[], {Float,_}:...);
*/

stock SendAdminMessage(const fmat[])
{
    foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID && Admin_GetPlayerLevel(i) > 0)
        {
            SendMsgF(i, COLOR_LIGHTGREEN, "** ADMIN ** "C_WHITE"- %s", fmat);
        }
    }
    return 1;
}

stock SendAdminMessageF(const fmat[], {Float,_}:...)
{
    new
        out[144];

    foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID && Admin_GetPlayerLevel(i) > 0)
        {
            formatex(out, sizeof(out), fmat, ___(1));
            SendAdminMessage(out);
        }
    }
    return 1;
}

stock Admin_AddCommandToList(level, const string[])
{
    if (!(ADM_LVL_1 <= level <= ADM_LVL_5))
    {
        printf("ERROR: Cannot register admin command for level %d", level);
        return 0;
    }

    strcat(adminCommands[level - 1], string);
    strcat(adminCommands[level - 1], "\n");
    return 1;
}

stock Admin_SetPlayerLevel(playerid, level)
{
    adminLevel[playerid] = level;

    new string[256];

    static const query[] = "\
    INSERT INTO \
        admins(u_id, admin_level) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        admin_level = %i \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, GetPlayerAccountID(playerid), level, level);
    mysql_tquery(MySQL_GetHandle(), string);
}

stock Admin_GetRankName(playerid)
{
    new admin_RankNames[6][24] =
    {
        "None",          // 0
        "Junior Admin",  // 1
        "General Admin", // 2
        "Senior Admin",  // 3
        "Head Admin",    // 4
        "Developer"      // 5
    };

    return admin_RankNames[Admin_GetPlayerLevel(playerid)];
}

Admin_GetPlayerLevel(playerid)
    return adminLevel[playerid];


stock Admin_SetPlayerDuty(playerid, bool:toggle)
{
    // TODO: Change colour when player is on duty.

    Bit_Set(adminOnDuty, playerid, toggle);
    return 1;
}

stock Admin_IsOnDuty(playerid)
    return Bit_Get(adminOnDuty, playerid);