
#include <YSI_Coding\y_hooks>

#define MAX_ADMIN_LEVELS (5)

enum
{
    ADM_LVL_1 = 1,
    ADM_LVL_2,
    ADM_LVL_3,
    ADM_LVL_4,
    ADM_LVL_5
}

// accessed globally
new adminCommands[5][2048];

static
    PlayerAdminLevel[MAX_PLAYERS],
    BitArray: adminOnDuty<MAX_PLAYERS>,
    Statement: stmt_retrieveAdmin
;



hook OnGameModeInit() {
    static const query_retrieveAdmin[] = "\
        SELECT \
            admin_level \
        FROM  \
            admins \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveAdmin = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveAdmin);
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerAdminLevel[playerid] = 0 ;
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerAdminLoad() {
        new
            adminLevel;

        MySQL_BindResultInt(stmt_retrieveAdmin, 0, adminLevel);

        if(MySQL_Statement_FetchRow(stmt_retrieveAdmin)) {
            Admin_SetPlayerLevel(playerid, adminLevel);
        }

    }
    MySQL_BindInt(stmt_retrieveAdmin, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveAdmin, using inline OnPlayerAdminLoad);
}

/*

    Admin Messaging
        - SendAdminMessage
        - SendAdminMessageF(fmat[], {Float,_}:...);
*/

stock SendAdminMsg(const fmat[])
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

stock SendAdminMsgF(const fmat[], {Float,_}:...)
{
    new
        out[144];

    foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID && Admin_GetPlayerLevel(i) > 0)
        {
            formatex(out, sizeof(out), fmat, ___(1));
            SendAdminMsg(out);
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
    PlayerAdminLevel[playerid] = level;

    new string[256];

    static const query[] = "\
    INSERT INTO \
        admins(u_id, admin_level) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        admin_level = %i \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), level, level);
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
    return PlayerAdminLevel[playerid];


stock Admin_SetPlayerDuty(playerid, bool:toggle)
{
    // TODO: Change colour when player is on duty.

    Bit_Set(adminOnDuty, playerid, toggle);
    return 1;
}

stock Admin_IsOnDuty(playerid)
    return Bit_Get(adminOnDuty, playerid);

timer KickTimer[500](playerid)
{
    Kick(playerid);
}