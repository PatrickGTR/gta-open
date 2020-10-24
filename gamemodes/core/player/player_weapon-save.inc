
#if SETUP_TABLE
	#include <player_setup-weapon-save>
#endif

#include <YSI_Coding\y_hooks>

static
    Statement:stmt_insertWeapon,
    Statement:stmt_loadWeapon,
    Statement:stmt_deleteSingleWeapon,
    Statement:stmt_deteleWeapons
;

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

    // currently unused, just keep it tho but don't give us warning.
    #pragma unused stmt_deteleWeapons
    return 1;
}

hook OnPlayerSpawn(playerid) {
    Weapon_Load(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    Weapon_Save(playerid);
    return 1;
}

hook function GivePlayerWeapon(playerid, weaponid, ammo) {
    MySQL_BindInt(stmt_insertWeapon, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_insertWeapon, 1, weaponid);
    MySQL_BindInt(stmt_insertWeapon, 2, ammo);
    MySQL_BindInt(stmt_insertWeapon, 3, ammo);
    MySQL_ExecuteThreaded(stmt_insertWeapon);
    
    continue(playerid, weaponid, ammo);
}

Weapon_Load(playerid) {
    inline WeaponLoad() {
        new
            weaponid,
            ammo;

        MySQL_BindResultInt(stmt_loadWeapon, 0, weaponid);
        MySQL_BindResultInt(stmt_loadWeapon, 1, ammo);

        while(MySQL_Statement_FetchRow(stmt_loadWeapon)) {

            if(!(0 <= weaponid <= 46))  {

                dbg(PLAYER_DEBUG_HANDLER, 
                    "[Weapon_Load / player_weapon-save] Unkown weapon. skipping",
                     _i("weaponid", weaponid)
                );

                MySQL_BindInt(stmt_deleteSingleWeapon, 0, Player_GetAccountID(playerid));
                MySQL_BindInt(stmt_deleteSingleWeapon, 1, weaponid);
                MySQL_ExecuteThreaded(stmt_deleteSingleWeapon);
            }

            GivePlayerWeapon(playerid, weaponid, ammo);

            dbg(PLAYER_DEBUG_HANDLER, 
                "[Weapon_Load / player_weapon-save] Weapon loaded",
                    _i("weaponid", weaponid),
                    _i("ammo", ammo),
                    _p("username", playerid)
            );
        }
    }

    MySQL_BindInt(stmt_loadWeapon, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadWeapon, using inline WeaponLoad);

    return 1;
}

Weapon_Save(playerid) {
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

        dbg(PLAYER_DEBUG_HANDLER, 
            "[Weapon_Save / player_weapon-save] Weapon saved",
                _i("weaponid", weaponid),
                _i("ammo", ammo),
                _p("username", playerid)
        );
    }
    return 1; 
}