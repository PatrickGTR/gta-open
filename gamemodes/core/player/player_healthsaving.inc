#include <YSI_Coding\y_hooks>

static
    Statement:stmt_saveHealth,
    Statement:stmt_loadHeatlh,
    Statement:stmt_insertHealth
;

hook OnMySQLConnected()
{
    static const insertQuery[] = "\
    INSERT INTO \
        players_health (u_id, health, armour) \
    VALUES \
        (?, ?, ?) \
    ";
    stmt_insertHealth = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = "\
    SELECT \
        health, \
        armour \
    FROM \
        players_health \
    WHERE \
        u_id = ? \
    ";
    stmt_loadHeatlh = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const updateQuery[] = "\
    UPDATE \
        players_health \
    SET \
        health = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_saveHealth = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    Player_HealthLoad(playerid);
    return 1;
}

Player_HealthLoad(playerid)
{
    inline HealthLoad()
    {
        new
            Float:Armour,
            Float:Health;
        MySQL_BindResultFloat(stmt_loadHeatlh, 0, Health);
        MySQL_BindResultFloat(stmt_loadHeatlh, 1, Armour);

        if(MySQL_Statement_FetchRow(stmt_loadHeatlh)) {
            SetPlayerHealth(playerid, Health);
            SetPlayerArmour(playerid, Armour);
        } 
        else {
            GetPlayerHealth(playerid, Health);
            GetPlayerArmour(playerid, Armour);
            MySQL_BindInt(stmt_insertHealth, 0, Player_GetAccountID(playerid));
            MySQL_BindFloat(stmt_insertHealth, 1, Health);
            MySQL_BindFloat(stmt_insertHealth, 2, Armour);
            MySQL_ExecuteThreaded(stmt_insertHealth);
        }
    }
    MySQL_BindInt(stmt_loadHeatlh, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadHeatlh, using inline HealthLoad);
}

hook function SetPlayerHealth(playerid, Float:health)
{
    MySQL_BindFloat(stmt_saveHealth, 0, health);
    MySQL_BindInt(stmt_saveHealth, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveHealth);
    continue(playerid, health);
}

hook OnPlayerDisconnect(playerid, reason)
{
    new Float:health;
    GetPlayerHealth(playerid, health);
    MySQL_BindFloat(stmt_saveHealth, 0, health);
    MySQL_BindInt(stmt_saveHealth, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveHealth);
    return 1;
}