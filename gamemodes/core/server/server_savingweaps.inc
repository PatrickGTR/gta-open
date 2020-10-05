#include <YSI_Coding\y_hooks>
/* DO NOT INCLUDE PROBLEMS INSIDE OF THIS INCLUDE! */
static
    Statement:stmt_insertWeapon,
    Statement:stmt_loadWeapon,
    Statement:stmt_deleteSingleWeapon,
    Statement:stmt_deteleWeapons
;

hook OnGameModeExit()
{
    foreach(new i : Player)
    {
        Weapons_Save(i);
    }
    return 1;
}

hook OnMySQLConnected()
{
    static const insertQuery[] = "\
    INSERT INTO \
        weapons (u_id, weapid, ammo) \
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
        weapons \
    WHERE \
        u_id = ? \
    ";
    stmt_loadWeapon = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const deleteSingleQuery[] = "\
    DELETE FROM weapons WHERE u_id = ? AND weapid = ?";
    stmt_deleteSingleWeapon = MySQL_PrepareStatement(MySQL_GetHandle(), deleteSingleQuery);

    static const deleteAllWeapon[] = "\
    DELETE FROM \
        weapons \
    WHERE \
        u_id = ? \
    ";
    stmt_deteleWeapons = MySQL_PrepareStatement(MySQL_GetHandle(), deleteAllWeapon);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    Weapons_Load(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    Weapons_Save(playerid);
    return 1;
}

hook function GivePlayerWeapon(playerid, weaponid, ammo)
{
    MySQL_BindInt(stmt_insertWeapon, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_insertWeapon, 1, weaponid);
    MySQL_BindInt(stmt_insertWeapon, 2, ammo);
    MySQL_BindInt(stmt_insertWeapon, 3, ammo);
    MySQL_ExecuteThreaded(stmt_insertWeapon);
    
    continue(playerid, weaponid, ammo);
}

Weapons_Load(playerid)
{
    inline WeaponLoad()
    {
        MySQL_Statement_RowsLeft(stmt_loadWeapon);
        for(new Statement:i; i < stmt_loadWeapon; i++) {
            new
                Weapid,
                Ammo;
            MySQL_BindResultInt(i, 0, Weapid);
            MySQL_BindResultInt(i, 1, Ammo);

            if(MySQL_Statement_FetchRow(i)) {
                if(!(0 <= Weapid <= 46)) 
                {
                    printf("[WARNING]: OnPlayerLoadWeapons - Unknown Weaponid '%d'. skipping", Weapid);
                    MySQL_BindInt(stmt_deleteSingleWeapon, 0, Player_GetAccountID(playerid));
                    MySQL_BindInt(stmt_deleteSingleWeapon, 1, Weapid);
                    MySQL_ExecuteThreaded(stmt_deleteSingleWeapon);
                }
                GivePlayerWeapon(playerid, Weapid, Ammo);
                #if WEAPON_DEBUG
                    printf("weapon: %d, ammo: %d, u_id: %d", Weapid, Ammo, Player_GetAccountID(playerid));
                #endif
            }
            MySQL_BindInt(stmt_deteleWeapons, 0, Player_GetAccountID(playerid));
            MySQL_ExecuteThreaded(stmt_deteleWeapons);
        }
    }
    MySQL_BindInt(stmt_loadWeapon, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadWeapon, using inline WeaponLoad);
}

Weapons_Save(playerid)
{
    if(!IsPlayerConnected(playerid)) {
        return 1;
    }
    new
        weapid,
        ammo;

    for(new i; i < 13; i++)
    {
        GetPlayerWeaponData(playerid, i, weapid, ammo);
        
        if(!weapid) continue;

        MySQL_BindInt(stmt_insertWeapon, 0, Player_GetAccountID(playerid));
        MySQL_BindInt(stmt_insertWeapon, 1, weapid);
        MySQL_BindInt(stmt_insertWeapon, 2, ammo);
        MySQL_BindInt(stmt_insertWeapon, 3, ammo);
        MySQL_ExecuteThreaded(stmt_insertWeapon);
        #if WEAPON_DEBUG
            printf("u_id: %d, weaponid: %d, ammo: %d", Player_GetAccountID(playerid), weapid, ammo);
        #endif
    }
    return 1;
}