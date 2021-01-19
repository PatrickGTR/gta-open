
#include <YSI_Coding\y_hooks>

static
    Statement:stmt_insertWeapon,
    Statement:stmt_loadWeapon,
    Statement:stmt_deleteSingleWeapon,
    Statement:stmt_deteleWeapons;

hook OnMySQLPreClose() {
    foreach(new i : Player) {
        Weapon_Save(i);
    }
    return 1;
}

hook OnMySQLConnected() {
    static const insertQuery[] = "\
        INSERT INTO \
            player_weapons (u_id, weapid, ammo) \
        VALUES \
            (?, ?, ?) \
        ON DUPLICATE KEY UPDATE ammo = ? \
    ";
    stmt_insertWeapon = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = "\
        SELECT \
            weapid, \
            ammo \
        FROM \
            player_weapons \
        WHERE \
            u_id = ? \
    ";
    stmt_loadWeapon = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const
        deleteSingleQuery[] = "DELETE FROM player_weapons WHERE u_id = ? AND weapid = ?";
    stmt_deleteSingleWeapon = MySQL_PrepareStatement(MySQL_GetHandle(), deleteSingleQuery);

    static const
        deleteAllWeapon[] = "DELETE FROM player_weapons WHERE u_id = ?";
    stmt_deteleWeapons = MySQL_PrepareStatement(MySQL_GetHandle(), deleteAllWeapon);
    return 1;
}

hook OnPlayerFirstSpawn(playerid) {
    Weapon_Load(playerid);
    return 1;
}

hook OnPlayerAutoSave(playerid) {
    Weapon_Save(playerid);
    return 1;
}

static
    BitArray:PlayerWeaponExcludeSave<MAX_PLAYERS>;

hook OnPlayerDisconnect(playerid, reason) {
    Weapon_Save(playerid);
    Bit_Set(PlayerWeaponExcludeSave, playerid, true);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason) {
    ResetPlayerWeapons(playerid);
    MySQL_BindInt(stmt_deteleWeapons, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_deteleWeapons);
    return 1;
}

// TODO: Look at this again.
// Simple solution!
// Think of a better solution to exclude class weapons from saving.
// but for now this does the job.
Weapon_DoNotSaveBegin(playerid) {
    Bit_Set(PlayerWeaponExcludeSave, playerid, false);
}

Weapon_DoNotSaveEnd(playerid) {
    Bit_Set(PlayerWeaponExcludeSave, playerid, true);
}

hook function GivePlayerWeapon(playerid, weaponid, ammo) {
    if(Bit_Get(PlayerWeaponExcludeSave, playerid)) {
        MySQL_BindInt(stmt_insertWeapon, 0, Player_GetAccountID(playerid));
        MySQL_BindInt(stmt_insertWeapon, 1, weaponid);
        MySQL_BindInt(stmt_insertWeapon, 2, ammo);
        MySQL_BindInt(stmt_insertWeapon, 3, GetPlayerAmmo(playerid) + ammo);
        MySQL_ExecuteThreaded(stmt_insertWeapon);
    }
    continue(playerid, weaponid, ammo);
}

void:Weapon_DeleteEntry(playerid, weaponid) {
    MySQL_BindInt(stmt_deleteSingleWeapon, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_deleteSingleWeapon, 1, weaponid);
    MySQL_ExecuteThreaded(stmt_deleteSingleWeapon);
}

void:Weapon_Load(playerid) {
    inline const OnWeaponLoad() {
        new
            weaponid,
            ammo;

        MySQL_BindResultInt(stmt_loadWeapon, 0, weaponid);
        MySQL_BindResultInt(stmt_loadWeapon, 1, ammo);

        while(MySQL_Statement_FetchRow(stmt_loadWeapon)) {

            if(!(0 <= weaponid <= 46))  {

                Logger_Dbg(PLAYER_DEBUG_HANDLER,
                    "[Weapon_Load / player_weapon-save.inc] Unkown weapon. skipping",
                     Logger_I("weaponid", weaponid)
                );
                Weapon_DeleteEntry(playerid, weaponid);
            }

            // delete data if there is no ammo left.
            if(ammo == 0) {
                Logger_Dbg(PLAYER_DEBUG_HANDLER,
                    "[Weapon_Load / player_weapon-save.inc] Weapon loaded without ammo, deleting entry",
                    Logger_I("weaponid", weaponid)
                );
                Weapon_DeleteEntry(playerid, weaponid);
            }
            else {
                GivePlayerWeapon(playerid, weaponid, ammo);

                Logger_Dbg(PLAYER_DEBUG_HANDLER,
                    "[Weapon_Load / player_weapon-save.inc] Weapon loaded",
                        Logger_I("weaponid", weaponid),
                        Logger_I("ammo", ammo),
                        Logger_P(playerid)
                );
            }

        }
    }

    MySQL_BindInt(stmt_loadWeapon, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadWeapon, using inline OnWeaponLoad);
}

void:Weapon_Save(playerid) {
    new
        weaponid,
        ammo;

    for(new i; i < 13; i++) {
        GetPlayerWeaponData(playerid, i, weaponid, ammo);

        if(!weaponid) {
            continue;
        }

        MySQL_BindInt(stmt_insertWeapon, 0, Player_GetAccountID(playerid));
        MySQL_BindInt(stmt_insertWeapon, 1, weaponid);
        MySQL_BindInt(stmt_insertWeapon, 2, ammo);
        MySQL_BindInt(stmt_insertWeapon, 3, ammo);
        MySQL_ExecuteThreaded(stmt_insertWeapon);

        Logger_Dbg(PLAYER_DEBUG_HANDLER,
            "[Weapon_Save / player_weapon-save.inc] Weapon saved",
                Logger_I("weaponid", weaponid),
                Logger_I("ammo", ammo),
                Logger_P(playerid)
        );
    }
}