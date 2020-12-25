#include <YSI_Coding\y_hooks>

static
    PlayerJailTime[MAX_PLAYERS],
    PlayerJailTick[MAX_PLAYERS],
    PlayerBailBalance[MAX_PLAYERS],
    Statement: stmt_retrieveJail,
    Statement: stmt_releaseJail;

static enum E_JAILPOS_DATA {
    Float:E_JAILPOS_X,
    Float:E_JAILPOS_Y,
    Float:E_JAILPOS_Z,
    Float:E_JAILPOS_A,
}

static const JailData[][E_JAILPOS_DATA] = {
    {264.2428, 86.4775, 1001.0391, 271.6097},
    {263.9785, 82.0106, 1001.0391, 269.8944}
};

hook OnGameModeInit() {
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

static void:_Player_SaveJailTime(playerid, seconds) {
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


static void:_Player_SendToJailPos(playerid) {
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
}

stock Player_SendToJail(playerid, seconds, bool:save = false) {
    if(!UI_TimeLeft(playerid, seconds)) {
        return 0;
    }
    _Player_SendToJailPos(playerid);

    ClearAnimations(playerid, 1);

    Player_Cuff(playerid, false);
    SetPlayerWantedLevel(playerid, 0);
    PlayerJailTime[playerid] = seconds;
    PlayerJailTick[playerid] = gettime();
    UI_TimeLeft(playerid, seconds);

    ResetPlayerWeapons(playerid);

    // temporary fix
    // TODO: revamp burglary system!
    // if(BurglaryInfo[playerid] != 0) {
    //     Player_StopRobbery(playerid);
    // }

    if(save) {
        _Player_SaveJailTime(playerid, seconds);
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

hook OnPlayerLogin(playerid) {
    inline OnPlayerJailedTimeLoad() {
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

hook OnPlayerSpawn(playerid) {
    if(PlayerJailTime[playerid] > 0) {
        Player_SendToJail(playerid, PlayerJailTime[playerid], true);
        SendServerMsg(playerid, "You've left when jailed, you are server the remaining time.");
    }
    if(Player_GetBailAmount(playerid) > 0) {
        _Player_SendToJailPos(playerid);

        TextInfo_Create(playerid, "JAILBAIL", "Jail");
        TextInfo_Add(playerid, "You have unpaid fees use ~y~/bail");
        TextInfo_Add(playerid, "~w~to pay your fees and free yourself");
        TextInfo_Show(playerid);

        // by pass Player_IsInJail check.
        // do not remove.
        PlayerJailTime[playerid] = 1;
    }
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerJailTime[playerid] =
    PlayerJailTick[playerid] =
    PlayerBailBalance[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    if(Player_IsCuffed(playerid)) {
        new
            level = GetPlayerWantedLevel(playerid),
            punishmentTime = (level > 0) ? ((level * 2) * 2) : (100 * 10);
        Player_SendToJail(playerid, punishmentTime, true);
    }

    if(Player_IsInJail(playerid)) {
        _Player_SaveJailTime(playerid, Player_TimeLeftInJail(playerid));
    }
    return 1;
}

hook OnPlayerSecondUpdate(playerid) {
    if(Player_TimeLeftInJail(playerid) == 0) {
        TextInfo_Create(playerid, "JAILBAIL", "Jail");
        TextInfo_Add(playerid, "Your time has ended use ~y~/bail");
        TextInfo_Add(playerid, "~w~to pay your fees and free yourself");
        TextInfo_Show(playerid);
    }
    return 1;
}

stock Player_TimeLeftInJail(playerid) {
    return (PlayerJailTime[playerid] - (gettime() - PlayerJailTick[playerid]));
}

stock Player_HasServedSentence(playerid) {
    return ((gettime() -  PlayerJailTick[playerid]) >= PlayerJailTime[playerid]);
}

stock Player_IsInJail(playerid) {
    return (PlayerJailTime[playerid] > 0 && Player_HasServedSentence(playerid));
}

stock Player_SetBailAmount(playerid, amount) {
    PlayerBailBalance[playerid] = amount;
    return 1;
}

stock Player_GetBailAmount(playerid) {
    return PlayerBailBalance[playerid];
}