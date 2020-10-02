#include <YSI_Coding\y_hooks>

hook OnGameModeExit()
{
    foreach(new i : Player)
    {
        Weapon_Save(i);
    }
    return 1;
}

Weapon_Load(playerid)
{
    new query[256];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "SELECT * FROM weapons WHERE u_id = %d", Player_GetAccountID(playerid));
    mysql_tquery(MySQL_GetHandle(), query, "OnPlayerLoadWeapons", "i", playerid);
    #if WEAPON_DEBUG
        print("Executing Load Weapons");
    #endif
}

forward OnPlayerLoadWeapons(playerid);
public OnPlayerLoadWeapons(playerid)
{
    new
        weaponid,
        ammo,
        rows,
        query[256];
    cache_get_row_count(rows);
    for(new i; i < rows; i++)
    {
        #if WEAPON_DEBUG
            printf("Rows detected: %d", rows);
        #endif
        cache_get_value_name_int(i, "weapid", weaponid);
        cache_get_value_name_int(i, "ammo", ammo);

        if(!(0 <= weaponid <= 46))
        {
            printf("[WARNING]: OnPlayerLoadWeapons - Unknown Weaponid '%d'. skipping", weaponid);
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "DELETE FROM weapons WHERE u_id = %d AND weapid = %d", Player_GetAccountID(playerid), weaponid);
            mysql_tquery(MySQL_GetHandle(), query);
            continue;
        }
        GivePlayerWeapon(playerid, weaponid, ammo);
        #if WEAPON_DEBUG
            printf("weapon: %d, ammo: %d, u_id: %d", weaponid, ammo, Player_GetAccountID(playerid));
        #endif
    }
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "DELETE FROM weapons WHERE u_id = %d", Player_GetAccountID(playerid));
    mysql_tquery(MySQL_GetHandle(), query);
    return 1;
}

Weapon_Save(playerid)
{
    if(!IsPlayerConnected(playerid)) {
        return 1;
    }
    new
        weapid,
        ammo;

    for(new i; i < 13; i++)
    {
        new query[256];
        GetPlayerWeaponData(playerid, i, weapid, ammo);
        
        if(!weapid) continue;

        mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO weapons (u_id, weapid, ammo) VALUES (%d, %d, %d) ON DUPLICATE KEY UPDATE ammo = %d ", Player_GetAccountID(playerid), weapid, ammo, ammo);
        mysql_tquery(MySQL_GetHandle(), query);
        #if WEAPON_DEBUG
            printf("u_id: %d, weaponid: %d, ammo: %d", Player_GetAccountID(playerid), weapid, ammo);
        #endif
    }
    return 1;
}    

hook OnPlayerLogin(playerid)
{
    Weapon_Load(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    Weapon_Save(playerid);
    return 1;
}