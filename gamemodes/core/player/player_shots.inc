#include <YSI_Coding\y_hooks>

static
    ChestCount[MAX_PLAYERS],
    TorsoCount[MAX_PLAYERS],
    LeftArmCount[MAX_PLAYERS],
    RightArmCount[MAX_PLAYERS],
    LeftLegCount[MAX_PLAYERS],
    RightLegCount[MAX_PLAYERS],
    HeadCount[MAX_PLAYERS],
    MissCount[MAX_PLAYERS];

static
    Statement:stmt_LoadShots,
    Statement:stmt_SaveShots,
    Statement:stmt_InsertShots;

hook OnGameModeInit() {

    new
        MySQL:handle = MySQL_GetHandle();

    static const insertQuery[] = "INSERT INTO player_shots_stats (uid) VALUES (?)";
    stmt_InsertShots = MySQL_PrepareStatement(handle, insertQuery);

    static const loadQuery[] = "\
    SELECT \
        chest, \
        torso, \
        left_arm, \
        right_arm, \
        left_leg, \
        right_leg, \
        head, \
        misses \
    FROM \
        player_shots_stats \
    WHERE \
        uid = ? \
    ";
    stmt_LoadShots = MySQL_PrepareStatement(handle, loadQuery);

    static const updateQuery[] = "\
    UPDATE \
        player_shots_stats \
    SET \
        chest = ?, \
        torso = ?, \
        left_arm = ?, \
        right_arm = ?, \
        left_leg = ?, \
        right_leg = ?, \
        head = ?, \
        misses = ? \
    WHERE \
        uid = ? \
    ";
    stmt_SaveShots = MySQL_PrepareStatement(handle, updateQuery);

    return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart) {
    if(issuerid != INVALID_PLAYER_ID) {
        switch(bodypart) {
            case WEAPON_BODY_PART_CHEST:        ChestCount[playerid]    += 1;
            case WEAPON_BODY_PART_TORSO:        TorsoCount[playerid]    += 1;
            case WEAPON_BODY_PART_LEFT_ARM:     LeftArmCount[playerid]  += 1;
            case WEAPON_BODY_PART_RIGHT_ARM:    RightArmCount[playerid] += 1;
            case WEAPON_BODY_PART_LEFT_LEG:     RightLegCount[playerid] += 1;
            case WEAPON_BODY_PART_RIGHT_LEG:    LeftLegCount[playerid]  += 1;
            case WEAPON_BODY_PART_HEAD:         HeadCount[playerid]     += 1;
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    _SaveShotData(playerid);
    return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
    if(hittype == BULLET_HIT_TYPE_NONE) {
        MissCount[playerid] += 1;
    }
    return 1;
}

hook OnPlayerRegister(playerid) {
    MySQL_BindInt(stmt_InsertShots, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_InsertShots);
    return 1;
}

hook OnPlayerAutoSave(playerid) {
    _SaveShotData(playerid);
    return 1;
}

hook OnPlayerLogin(playerid) {

    inline const OnLoadShots() {
        MySQL_BindResultInt(stmt_LoadShots, 0, ChestCount[playerid]);
        MySQL_BindResultInt(stmt_LoadShots, 1, TorsoCount[playerid]);
        MySQL_BindResultInt(stmt_LoadShots, 2, LeftArmCount[playerid]);
        MySQL_BindResultInt(stmt_LoadShots, 3, RightArmCount[playerid]);
        MySQL_BindResultInt(stmt_LoadShots, 4, RightLegCount[playerid]);
        MySQL_BindResultInt(stmt_LoadShots, 5, LeftLegCount[playerid]);
        MySQL_BindResultInt(stmt_LoadShots, 6, HeadCount[playerid]);
        MySQL_BindResultInt(stmt_LoadShots, 7, MissCount[playerid]);

        MySQL_Statement_FetchRow(stmt_LoadShots);

        Logger_Dbg(
            PLAYER_DEBUG_HANDLER,
            "[OnPlayerLogin / player_shots.inc] player shot data loaded",
            Logger_I("Chest", ChestCount[playerid]),
            Logger_I("Torso", TorsoCount[playerid]),
            Logger_I("Left Arm", LeftArmCount[playerid]),
            Logger_I("Right Arm", RightArmCount[playerid]),
            Logger_I("Right Leg", RightLegCount[playerid]),
            Logger_I("Left Leg", LeftLegCount[playerid]),
            Logger_I("Head", HeadCount[playerid]),
            Logger_I("Miss", MissCount[playerid])
        );
    }

    MySQL_BindInt(stmt_LoadShots, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_LoadShots, using inline OnLoadShots);
    return 1;
}


static _SaveShotData(playerid) {
    MySQL_BindInt(stmt_SaveShots, 0, ChestCount[playerid]);
    MySQL_BindInt(stmt_SaveShots, 1, TorsoCount[playerid]);
    MySQL_BindInt(stmt_SaveShots, 2, LeftArmCount[playerid]);
    MySQL_BindInt(stmt_SaveShots, 3, RightArmCount[playerid]);
    MySQL_BindInt(stmt_SaveShots, 4, RightLegCount[playerid]);
    MySQL_BindInt(stmt_SaveShots, 5, LeftLegCount[playerid]);
    MySQL_BindInt(stmt_SaveShots, 6, HeadCount[playerid]);
    MySQL_BindInt(stmt_SaveShots, 7, MissCount[playerid]);

    MySQL_BindInt(stmt_SaveShots, 8, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel(stmt_SaveShots);

    Logger_Dbg(
        PLAYER_DEBUG_HANDLER,
        "[_SaveShotData / player_shots.inc] player shot data saved",
        Logger_I("Chest", ChestCount[playerid]),
        Logger_I("Torso", TorsoCount[playerid]),
        Logger_I("Left Arm", LeftArmCount[playerid]),
        Logger_I("Right Arm", RightArmCount[playerid]),
        Logger_I("Right Leg", RightLegCount[playerid]),
        Logger_I("Left Leg", LeftLegCount[playerid]),
        Logger_I("Head", HeadCount[playerid]),
        Logger_I("Miss", MissCount[playerid])
    );
}

static _GetOverallShots(playerid) {
    return (
        ChestCount[playerid] +
        TorsoCount[playerid] +
        LeftArmCount[playerid] +
        RightArmCount[playerid] +
        LeftLegCount[playerid] +
        RightLegCount[playerid] +
        HeadCount[playerid] +
        MissCount[playerid]
    );
}

CMD:shots(playerid, params[])
{

    new
        bool: no_id = false,
        str[512];

    if(isnull(params)) {
        no_id = true;
    }

    if(no_id) {
        format(str, sizeof(str), "\
            Chest: %d\n\
            Torso: %d\n\
            Left Arm: %d\n\
            Right Arm: %d\n\
            Left Leg: %d\n\
            Right Leg: %d\n\
            Head: %d\n\
            Missed: %d\n\
            Overall shots: %d\
        ",
            ChestCount[playerid],
            TorsoCount[playerid],
            LeftArmCount[playerid],
            RightArmCount[playerid],
            LeftLegCount[playerid],
            RightLegCount[playerid],
            HeadCount[playerid],
            MissCount[playerid],
            _GetOverallShots(playerid)
        );

        Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Shot Statistics", str, "Close", "");
        return 1;
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Invalid ID");
    }

    new
        targetid = strval(params);

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Invalid player");
    }

    format(str, sizeof(str), "\
        Chest: %d\n\
        Torso: %d\n\
        Left Arm: %d\n\
        Right Arm: %d\n\
        Left Leg: %d\n\
        Right Leg: %d\n\
        Head: %d\n\
        Missed: %d\n\
        Overall shots: %d\
    ",
        ChestCount[targetid],
        TorsoCount[targetid],
        LeftArmCount[targetid],
        RightArmCount[targetid],
        LeftLegCount[targetid],
        RightLegCount[targetid],
        HeadCount[targetid],
        MissCount[targetid],
        _GetOverallShots(targetid)
    );

    new
        title[64];
    format(title, sizeof(title), "Shot Statistics of %p(%i)", playerid, playerid);
    Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, title, str, "Close", "");
	return 1;
}