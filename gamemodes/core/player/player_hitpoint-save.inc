#include <YSI_Coding\y_hooks>

static
    Statement:stmt_saveHitpoints,
    Statement:stmt_loadHitpoints,
    Statement:stmt_updateHealth,
    Statement:stmt_updateArmour
;

// Hooked Callbacks
hook OnMySQLConnected() {
    static const loadQuery[] = "\
        SELECT \
            health, \
            armour \
        FROM \
            players \
        WHERE \
            u_id = ? \
    ";
    stmt_loadHitpoints = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const updateQuery[] = "\
        UPDATE \
            players \
        SET \
            health = ?, \
            armour = ? \
        WHERE \
            u_id = ? \
    ";
    stmt_saveHitpoints = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);

    static const updateHealthQuery[] = "\
        UPDATE \
            players \
        SET \
            health = ? \
        WHERE \
            u_id = ? \
    ";
    stmt_updateHealth = MySQL_PrepareStatement(MySQL_GetHandle(), updateHealthQuery);

    static const updateArmourQuery[] = "\
        UPDATE \
            players \
        SET \
            armour = ? \
        WHERE \
            u_id = ? \
    ";
    stmt_updateArmour = MySQL_PrepareStatement(MySQL_GetHandle(), updateArmourQuery);
    return 1;
}

hook OnPlayerFirstSpawn(playerid) {
    Player_HitpointLoad(playerid);
    return 1;
}

hook OnPlayerAutoSave(playerid) {
    Player_HitpointSave(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    Player_HitpointSave(playerid);
    return 1;
}

// Hooked Functions
hook function SetPlayerHealth(playerid, Float:health) {
    MySQL_BindFloat(stmt_updateHealth, 0, health);
    MySQL_BindInt(stmt_updateHealth, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_updateHealth);

    return continue(playerid, health);
}

hook function SetPlayerArmour(playerid, Float:armour) {
    MySQL_BindFloat(stmt_updateArmour, 0, armour);
    MySQL_BindInt(stmt_updateArmour, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_updateArmour);

    return continue(playerid, armour);
}

// Functions
Player_HitpointLoad(playerid) {
    inline HealthLoad() {
        new
            Float:armour,
            Float:health;
            
        MySQL_BindResultFloat(stmt_loadHitpoints, 0, health);
        MySQL_BindResultFloat(stmt_loadHitpoints, 1, armour);

        if(MySQL_Statement_FetchRow(stmt_loadHitpoints)) {
            SetPlayerHealth(playerid, health);
            SetPlayerArmour(playerid, armour);

            dbg(PLAYER_DEBUG_HANDLER, "[Player_HitpointLoad / player_hitpoint-save.inc] hitpoint loaded", 
                _f("health", health),
                _f("armour", armour),
                _p("username", playerid)
            );
        } 
    }
    MySQL_BindInt(stmt_loadHitpoints, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadHitpoints, using inline HealthLoad);
}

Player_HitpointSave(playerid) {
    new 
        Float:health, 
        Float:armour;

    GetPlayerHealth(playerid, health);
    GetPlayerArmour(playerid, armour);

    MySQL_BindFloat(stmt_saveHitpoints, 0, health);
    MySQL_BindFloat(stmt_saveHitpoints, 1, armour);
    MySQL_BindInt(stmt_saveHitpoints, 2, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveHitpoints);
    
    dbg(PLAYER_DEBUG_HANDLER, "[Player_HitpointSave / player_hitpoint-save.inc] hitpoint saved", 
        _f("health", health),
        _f("armour", armour),
        _p("username", playerid)
    );
}

