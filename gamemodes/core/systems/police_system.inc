#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

static
    PlayerJailTime[MAX_PLAYERS],
    PlayerBailBalance[MAX_PLAYERS],
    Statement: stmt_retrieveJail,
    Statement: stmt_releaseJail;



enum E_JAILPOS_DATA
{
    Float:E_JAILPOS_X,
    Float:E_JAILPOS_Y,
    Float:E_JAILPOS_Z,
    Float:E_JAILPOS_A,
}

static
    const JailData[][E_JAILPOS_DATA] =
{
    {264.2428, 86.4775, 1001.0391, 271.6097},
    {263.9785, 82.0106, 1001.0391, 269.8944}
};

hook OnGameModeInit()
{
    static const query_retrieveBal[] = "\
        SELECT \
            jailed_time, \
            bail_balance, \
            bail_required \
        FROM \
            jailed \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveJail = MySQL_PrepareStatement(MySQL_GetHandle(), query_retrieveBal);


    static const queryDelete[] = "\
        DELETE FROM \
            jailed \
        WHERE  \
            u_id = ? \
    ";
    stmt_releaseJail = MySQL_PrepareStatement(MySQL_GetHandle(), queryDelete);
    return 1;
}

stock Player_SendToJail(playerid, seconds, bool:save = false) {
    if(!UI_TimeLeft(playerid, seconds)) {
        return 0;
    }

    new
        Float:x,
        Float:y,
        Float:z,
        Float:ang,
        idx = random(sizeof(JailData));
    x = JailData[idx][E_JAILPOS_X];
    y = JailData[idx][E_JAILPOS_Y];
    z = JailData[idx][E_JAILPOS_Z];
    ang = JailData[idx][E_JAILPOS_A];

    SetPlayerPos(playerid, x, y, z);
    SetPlayerFacingAngle(playerid, ang);
    SetPlayerVirtualWorld(playerid, 16);
    SetPlayerInterior(playerid, 6);

    ClearAnimations(playerid, 1);

    Player_Cuff(playerid, false);
    SetPlayerWantedLevel(playerid, 0);

    ResetPlayerWeapons(playerid);
    if(BurglaryInfo[playerid] != 0) {
        Player_StopRobbery(playerid);
    }

    if(save) {
        new
            string[256];
        static const query[] = "\
            INSERT INTO \
                jailed(u_id, jailed_time) \
            VALUES \
                (%i, %i) \
            ON DUPLICATE KEY UPDATE \
                jailed_time = %i \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), seconds, seconds);
        mysql_tquery(MySQL_GetHandle(), string);
    }
    return 1;
}

stock Player_ReleaseFromJail(playerid, move = true) {

    // this is option is to move the player out of the cell when his time finishes.
    // we set the option to 'false' for our terrorist cell explosion system since
    // the cell door opens and we don't need to move the player.
    if(move) {
        SetPlayerPos(playerid, 254.9862, 86.8028, 1002.4453);
        SetPlayerFacingAngle(playerid, 90.9168);
        SetPlayerVirtualWorld(playerid, 16);
        SetPlayerInterior(playerid, 6);
    }

    PlayerJailTime[playerid] = 0;
    UI_HideTimeLeft(playerid);

    MySQL_BindInt(stmt_releaseJail, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_releaseJail);
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerJailedTimeLoad()
    {
        new
            time,
            balance;

        MySQL_BindResultInt(stmt_retrieveJail, 0, time);
        MySQL_BindResultInt(stmt_retrieveJail, 1, balance);

        if(MySQL_Statement_FetchRow(stmt_retrieveJail)) {
            PlayerJailTime[playerid] = time;
            PlayerBailBalance[playerid] = balance;
        }
    }
    MySQL_BindInt(stmt_retrieveJail, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveJail, using inline OnPlayerJailedTimeLoad);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_SUBMISSION)) {
        if(Player_GetClass(playerid) != TEAM_POLICE) {
            return 0;
        }
        new id = Player_GetClosestWanted(playerid);

        if(id == -1) {
            return 1;
        }

        if(!Player_IsCuffed(id)) {
            return cmd_cuffcw(playerid);
        }
        else {
            return cmd_arrestcw(playerid);
        }
    }
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(PlayerJailTime[playerid] > 0) {
        Player_SendToJail(playerid, PlayerJailTime[playerid], true);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(Player_IsCuffed(playerid) == true) {
        Player_SendToJail(playerid, 300, true);
    }
    return 1;
}

stock Player_IsInJail(playerid) {
    return (PlayerJailTime[playerid] > 0);
}

stock Player_SetBailAmount(playerid, amount) {
    PlayerBailBalance[playerid] = amount;
    return 1;
}

stock Player_GetBailAmount(playerid) {
    return PlayerBailBalance[playerid];
}