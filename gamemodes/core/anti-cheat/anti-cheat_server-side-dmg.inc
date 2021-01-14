/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc, updated & modified by PatrickGTR
 * Module: anticheat/hitpoints.inc
 * Purpose: server sided damage system
*/

/* ** Includes ** */
#include 							<YSI_Coding\y_hooks>

/* ** Definitions ** */
#define AC_DEFAULT_TEAM (1337)

/* ** Variables ** */
enum E_PLAYER_HITPOINTS {
    Float: E_POINTS,
    E_UPDATE_TIME,
    E_UPDATE_FAIL,
    bool: E_SYNCED
};

static const
    s_ValidDamageGiven[] = {
        1, // 0 - Fist
        1, // 1 - Brass knuckles
        1, // 2 - Golf club
        1, // 3 - Nitestick
        0, // 4 - Knife
        1, // 5 - Bat
        1, // 6 - Shovel
        1, // 7 - Pool cue
        1, // 8 - Katana
        1, // 9 - Chainsaw
        1, // 10 - Dildo
        1, // 11 - Dildo 2
        1, // 12 - Vibrator
        1, // 13 - Vibrator 2
        1, // 14 - Flowers
        1, // 15 - Cane
        0, // 16 - Grenade
        0, // 17 - Teargas
        0, // 18 - Molotov
        0, // 19 - Vehicle M4 (custom)
        0, // 20 - Vehicle minigun
        0, // 21
        1, // 22 - Colt 45
        1, // 23 - Silenced
        1, // 24 - Deagle
        1, // 25 - Shotgun
        1, // 26 - Sawed-off
        1, // 27 - Spas
        1, // 28 - UZI
        1, // 29 - MP5
        1, // 30 - AK47
        1, // 31 - M4
        1, // 32 - Tec9
        1, // 33 - Cuntgun
        1, // 34 - Sniper
        0, // 35 - Rocket launcher
        0, // 36 - Heatseeker
        0, // 37 - Flamethrower
        1, // 38 - Minigun
        0, // 39 - Satchel
        0, // 40 - Detonator
        1, // 41 - Spraycan
        1, // 42 - Fire extinguisher
        0, // 43 - Camera
        0, // 44 - Night vision
        0, // 45 - Infrared
        1, // 46 - Parachute
        0, // 47 - Fake pistol
        0, // 48 - Pistol whip (custom)
        0, // 49 - Vehicle
        0, // 50 - Helicopter blades
        0, // 51 - Explosion
        0, // 52 - Car park (custom)
        0, // 53 - Drowning
        0  // 54 - Splat
    },

    Float: s_ValidMaxDamage[ ] = {
        6.6, // 0 - Fist
        6.6, // 1 - Brass knuckles
        6.6, // 2 - Golf club
        6.6, // 3 - Nitestick
        6.7, // 4 - Knife (varies with back stab)
        6.6, // 5 - Bat
        6.6, // 6 - Shovel
        6.6, // 7 - Pool cue
        6.6, // 8 - Katana
        27.1, // 9 - Chainsaw
        6.6, // 10 - Dildo
        6.6, // 11 - Dildo 2
        6.6, // 12 - Vibrator
        6.6, // 13 - Vibrator 2
        6.6, // 14 - Flowers
        6.6, // 15 - Cane
        82.5, // 16 - Grenade
        0.0, // 17 - Teargas
        0.1, // 18 - Molotov
        0.0, // 19 - Vehicle M4 (custom)
        0.0, // 20 - Vehicle minigun
        0.0, // 21
        8.25, // 22 - Colt 45
        13.2, // 23 - Silenced
        46.2, // 24 - Deagle
        49.5, // 25 - Shotgun
        49.5, // 26 - Sawed-off
        39.6, // 27 - Spas
        6.6, // 28 - UZI
        8.3, // 29 - MP5
        9.9, // 30 - AK47
        9.9, // 31 - M4
        6.6, // 32 - Tec9
        24.8, // 33 - Cuntgun
        61.9, // 34 - Sniper
        82.5, // 35 - Rocket launcher
        82.5, // 36 - Heatseeker
        0.1, // 37 - Flamethrower
        46.2, // 38 - Minigun
        0.0, // 39 - Satchel (apparently 20, not synced anyway)
        0.0, // 40 - Detonator
        0.4, // 41 - Spraycan
        0.4, // 42 - Fire extinguisher
        0.0, // 43 - Camera
        0.0, // 44 - Night vision
        0.0, // 45 - Infrared
        6.6  // 46 - Parachute
    },

    Float: s_WeaponRange[ ] = {
        0.0, // 0 - Fist
        0.0, // 1 - Brass knuckles
        0.0, // 2 - Golf club
        0.0, // 3 - Nitestick
        0.0, // 4 - Knife
        0.0, // 5 - Bat
        0.0, // 6 - Shovel
        0.0, // 7 - Pool cue
        0.0, // 8 - Katana
        0.0, // 9 - Chainsaw
        0.0, // 10 - Dildo
        0.0, // 11 - Dildo 2
        0.0, // 12 - Vibrator
        0.0, // 13 - Vibrator 2
        0.0, // 14 - Flowers
        0.0, // 15 - Cane
        0.0, // 16 - Grenade
        0.0, // 17 - Teargas
        0.0, // 18 - Molotov
        90.0, // 19 - Vehicle M4 (custom)
        75.0, // 20 - Vehicle minigun (custom)
        0.0, // 21
        35.0, // 22 - Colt 45
        35.0, // 23 - Silenced
        35.0, // 24 - Deagle
        40.0, // 25 - Shotgun
        35.0, // 26 - Sawed-off
        40.0, // 27 - Spas
        35.0, // 28 - UZI
        45.0, // 29 - MP5
        70.0, // 30 - AK47
        90.0, // 31 - M4
        35.0, // 32 - Tec9
        100.0, // 33 - Cuntgun
        320.0, // 34 - Sniper
        0.0, // 35 - Rocket launcher
        0.0, // 36 - Heatseeker
        0.0, // 37 - Flamethrower
        75.0,  // 38 - Minigun
        0.0, // 39 - Satchel (apparently 20, not synced anyway)
        0.0, // 40 - Detonator
        0.0, // 41 - Spraycan
        0.0, // 42 - Fire extinguisher
        0.0, // 43 - Camera
        0.0, // 44 - Night vision
        0.0, // 45 - Infrared
        0.0  // 46 - Parachute
    }
;

static
    Float: p_PlayerHealth 			[MAX_PLAYERS][E_PLAYER_HITPOINTS],
    Float: p_PlayerArmour 			[MAX_PLAYERS][E_PLAYER_HITPOINTS],
    Float: p_LastDamageIssued		[MAX_PLAYERS],
    p_LastTookDamage 				[MAX_PLAYERS],
    p_LastDamageIssuer 				[MAX_PLAYERS] = { INVALID_PLAYER_ID, ... },
    p_LastWeaponIssuer 				[MAX_PLAYERS],
    p_LastDeath						[MAX_PLAYERS],
    p_DeathSpam						[MAX_PLAYERS char]
;

/* ** Forwards ** */

// Called after damage has been inflicted
// Same parameters as OnPlayerDamagePlayer, but they can not be modified
forward OnPlayerDamagePlayerDone(playerid, damagedid, Float: amount, weaponid, bodypart);


// OnPlayerGiveDamage + OnPlayerTakeDamage combined, OnPlayerDamagePlayer deprecates those function.
// playerid - The player who is about to get damaged.
// issuerid - The player who issued the damage.
// amount - The amount of damage about to get inflicted
// weaponid - The weapon used to inflict the damage
// bodypart - The bodypart

// Return 0 to prevent the damage from being inflicted
forward OnPlayerDamagePlayer(playerid, issuerid, &Float: amount, weaponid, bodypart);

// The new callback, deprecates the OnPlayerDeath.
// More accurate killerid and reason.
// Gives the last damager if its within 2500ms the killerid rather than INVALID_PLAYER_ID
// this callback also fixes reason, a more specific reason on death.
forward OnPlayerDeathEx(playerid, killerid, reason);

// Function (AC_UpdateKillerData)

stock AC_UpdateDamageInformation(playerid, attackerid, weaponid)
{
    p_LastTookDamage[playerid] = GetTickCount();
    p_LastDamageIssuer[playerid] = attackerid;
    p_LastWeaponIssuer[playerid] = weaponid;
}

// Function (AC_GetPlayerHealth)

stock Float: AC_GetPlayerHealth(playerid) {
    return p_PlayerHealth[playerid] [E_POINTS];
}

// Function (AddPlayerHealth)

stock AC_AddPlayerHealth(playerid, Float:amount) {
    p_PlayerHealth[playerid] [E_POINTS] += amount;
    p_PlayerHealth[playerid] [E_SYNCED] = false;

    return SetPlayerHealth(playerid, p_PlayerHealth[playerid][E_POINTS]);
}

// Function Hook (SetPlayerHealth)

stock AC_SetPlayerHealth(playerid, Float:amount) {
    p_PlayerHealth[playerid][E_POINTS] = amount;
    p_PlayerHealth[playerid][E_SYNCED] = false;

    if(amount <= 0.0 && AC_IsPlayerSpawned(playerid))
    {
        if((GetTickCount() - p_LastTookDamage[playerid]) > 2500) {
            p_LastDamageIssuer[ playerid ] = INVALID_PLAYER_ID;
            p_LastWeaponIssuer[ playerid ] = 47;
        }

        AC_SetPlayerSpawned(playerid, false);
        SetTimerEx("OnPlayerDeathEx", 10, false, "ddd", playerid, p_LastDamageIssuer[playerid], p_LastWeaponIssuer[playerid]);
    }
    return SetPlayerHealth(playerid, amount);
}

#if defined _ALS_SetPlayerHealth
    #undef SetPlayerHealth
#else
    #define _ALS_SetPlayerHealth
#endif
#define SetPlayerHealth AC_SetPlayerHealth

// Function Hook (SetPlayerArmour)

stock AC_SetPlayerArmour(playerid, Float:amount) {
    p_PlayerArmour[playerid][E_POINTS] = amount;
    p_PlayerArmour[playerid][E_SYNCED] = false;
    return SetPlayerArmour(playerid, amount);
}

#if defined _ALS_SetPlayerArmour
    #undef SetPlayerArmour
#else
    #define _ALS_SetPlayerArmour
#endif
#define SetPlayerArmour AC_SetPlayerArmour

// Function Hook (SetPlayerTeam)

stock AC_SetPlayerTeam(playerid, teamid)
{
    if(teamid != AC_DEFAULT_TEAM) {
        printf("[ACWarning] You cannot use SetPlayerTeam as you have hitpoint hack detection enabled (teamid %d, default %d).", teamid, AC_DEFAULT_TEAM );
    }
    return SetPlayerTeam(playerid, AC_DEFAULT_TEAM);
}

#if defined _ALS_SetPlayerTeam
    #undef SetPlayerTeam
#else
    #define _ALS_SetPlayerArmour
#endif
#define SetPlayerTeam AC_SetPlayerTeam

/* ** Callback Hooks ** */
hook OnPlayerConnect( playerid ) {
    // Reset variables
    p_PlayerHealth[playerid][E_UPDATE_FAIL] = 0;
    p_PlayerArmour[playerid][E_UPDATE_FAIL] = 0;
    p_DeathSpam{playerid}                   = 0;
    return 1;
}

hook OnPlayerSpawn(playerid) {
    // Health/Armour Hack
    p_PlayerHealth[playerid][E_UPDATE_FAIL] 	= 0;
    p_PlayerHealth[playerid][E_POINTS] 			= 100.0;

    p_PlayerArmour[playerid][E_UPDATE_FAIL] 	= 0;
    p_PlayerArmour[playerid][E_POINTS] 			= 0.0;

    SetPlayerTeam(playerid, AC_DEFAULT_TEAM); // Set everyone the same team
    return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart) {
    new
        is_npc = IsPlayerNPC(issuerid);

    p_LastTookDamage[ playerid ] = GetTickCount();
    p_LastDamageIssuer[ playerid ] = issuerid;
    p_LastWeaponIssuer[ playerid ] = weaponid;
    p_LastDamageIssued[ playerid ] = amount;

    // Allow hunter damage/sparrow
    if(!(issuerid != INVALID_PLAYER_ID && IsPlayerInAnyVehicle(issuerid) && GetPlayerVehicleSeat(issuerid) == 0 && (weaponid == WEAPON_M4 || weaponid == WEAPON_MINIGUN)) && !is_npc)
    {
        // Ignore unreliable and invalid damage
        if(weaponid < 0 || weaponid >= sizeof(s_ValidDamageGiven) || s_ValidDamageGiven[weaponid])
            return Y_HOOKS_BREAK_RETURN_0;
    }

    if(AC_IsPlayerSpawned(playerid))
    {
        if(issuerid != INVALID_PLAYER_ID && ! is_npc)
        {
            if(CallLocalFunction("OnPlayerDamagePlayer", "iiiii", playerid, issuerid, amount, weaponid, bodypart))
            {
                new
                    Float: tmp,
                    Float: tmp_amount = amount;

                if(p_PlayerArmour[ playerid ] [ E_POINTS ])
                {
                    if((tmp = p_PlayerArmour[playerid][E_POINTS] - tmp_amount) < 0.0)  {
                        tmp_amount -= p_PlayerArmour[playerid][E_POINTS];
                        p_PlayerArmour[playerid][E_POINTS] = 0.0;
                    } else  {
                        p_PlayerArmour[playerid][E_POINTS] = tmp;
                        tmp_amount = 0.0;
                    }
                }

                if((p_PlayerHealth[playerid][E_POINTS] -= tmp_amount) < 0.0) {
                    AC_SetPlayerSpawned(playerid, false);
                    CallRemoteFunction("OnPlayerDeathEx", "ddd", playerid, issuerid, weaponid);
                }

                SetPlayerArmour(playerid, p_PlayerArmour[ playerid ] [ E_POINTS ]);
                SetPlayerHealth(playerid, p_PlayerHealth[ playerid ] [ E_POINTS ]);

                CallRemoteFunction("OnPlayerDamagePlayerDone", "ddfdd", issuerid, playerid, amount, weaponid, bodypart);
            }
        }
        else
        {
            new
                Float: tmp,
                Float: tmp_amount = amount;

            if(!(weaponid == 53 || weaponid == 54 || weaponid == 50 ) && p_PlayerArmour[playerid][E_POINTS])
            {
                if((tmp = p_PlayerArmour[playerid][E_POINTS] - tmp_amount) < 0.0)  {
                    tmp_amount -= p_PlayerArmour[playerid][E_POINTS];
                    p_PlayerArmour[playerid][E_POINTS] = 0.0;
                } else  {
                    p_PlayerArmour[playerid][E_POINTS] = tmp;
                    tmp_amount = 0.0;
                }
            }

            if((p_PlayerHealth[playerid][E_POINTS] -= tmp_amount) <= (weaponid == 37 ? 0.99999 : 0.0)) {
                // find any possible killers prior
                if((GetTickCount() - p_LastTookDamage[playerid]) > 2500) {
                    p_LastDamageIssuer[playerid] = issuerid;
                    p_LastWeaponIssuer[playerid] = weaponid;
                }

                AC_SetPlayerSpawned( playerid, false);

                if(weaponid == 37 || weaponid == 51) {
                    SetPlayerHealth( playerid, -1 ); // Death bug fix
                }

                CallRemoteFunction("OnPlayerDeathEx", "ddd", playerid, p_LastDamageIssuer[ playerid ], p_LastWeaponIssuer[ playerid ]);
            }
        }
    }
    return 1;
}

hook OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{
    // Ignore unreliable and invalid damage
    if (weaponid < 0 || weaponid >= sizeof(s_ValidDamageGiven) || !s_ValidDamageGiven[weaponid])
        return Y_HOOKS_BREAK_RETURN_0;

    if(weaponid < 0 || weaponid >= sizeof(s_ValidMaxDamage) || amount > s_ValidMaxDamage[weaponid] + 2.0) // 2.0 safety margin
        return Y_HOOKS_BREAK_RETURN_0;

    if(damagedid == INVALID_PLAYER_ID)
        return Y_HOOKS_BREAK_RETURN_0;

    if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat( playerid ) == 0 && (weaponid == WEAPON_M4 || weaponid == WEAPON_MINIGUN))
        return Y_HOOKS_BREAK_RETURN_0;

    if (!IsPlayerNPC(damagedid))
    {
        if(!AC_IsPlayerSpawned(damagedid))
            return Y_HOOKS_BREAK_RETURN_0;

        if((!IsPlayerStreamedIn( playerid, damagedid ) && ! (GetTickCount() - AC_GetLastUpdateTime(playerid) >= 2595)) || !IsPlayerStreamedIn(damagedid, playerid))
            return Y_HOOKS_BREAK_RETURN_0;

        if(CallLocalFunction("OnPlayerDamagePlayer", "iifii", damagedid, playerid, amount, weaponid, bodypart))
        {
            new
                Float: tmp,
                Float: distance = ac_GetDistanceBetweenPlayers( playerid, damagedid ), // Calc distance between players
                Float: tmp_amount = amount; // this amount is extremely unreliable

            if(distance > s_WeaponRange[weaponid] + 2.0)
                return Y_HOOKS_BREAK_RETURN_0;

            if(p_PlayerArmour[damagedid] [E_POINTS])
            {
                if((tmp = p_PlayerArmour[damagedid][E_POINTS] - tmp_amount) < 0.0)  {
                    tmp_amount -= p_PlayerArmour[ damagedid ] [ E_POINTS ];
                    p_PlayerArmour[damagedid][E_POINTS] = 0.0;
                } else  {
                    p_PlayerArmour[damagedid] [E_POINTS] = tmp;
                    tmp_amount = 0.0;
                }
            }

            if((p_PlayerHealth[damagedid][E_POINTS] -= tmp_amount) < 0.0) {
                AC_SetPlayerSpawned(damagedid, false);
                CallRemoteFunction("OnPlayerDeathEx", "ddd", damagedid, playerid, weaponid);
            }

            SetPlayerArmour(damagedid, p_PlayerArmour[damagedid][E_POINTS]);
            SetPlayerHealth(damagedid, p_PlayerHealth[damagedid][E_POINTS]);

            CallRemoteFunction("OnPlayerDamagePlayerDone", "ddfdd", playerid, damagedid, amount, weaponid, bodypart);
        }
    }
    return 1;
}

// Functions (Player)
stock AC_CheckForHealthHacks( playerid, iTicks )
{
    new
        Float: currentHealth,
        Float: currentArmour;

    GetPlayerHealth(playerid, currentHealth);
    GetPlayerArmour(playerid, currentArmour);

    // Lag Calculations
    new
        Float: fHitDamage = p_LastDamageIssued[playerid],
        Float: fArmourDamage,
        Float: fHealthDamage;

    if(fHitDamage > currentArmour) {
        fArmourDamage = currentArmour;
        fHealthDamage = fHitDamage - currentArmour;
    }
    else {
        fArmourDamage = fHitDamage;
    }

    // Begin Health Hack Detection
    if(iTicks > p_PlayerHealth[playerid][E_UPDATE_TIME]) {
        new
            clientSideHealth 	= floatround(currentHealth, floatround_floor),
            serverSideHealth 	= floatround(p_PlayerHealth[playerid][E_POINTS], floatround_floor);

        if(clientSideHealth == serverSideHealth) {
            p_PlayerHealth[playerid][E_SYNCED] = true;
        }

        if(!p_PlayerHealth[playerid][E_SYNCED]) {
            if(clientSideHealth > serverSideHealth) {
                p_PlayerHealth[playerid][E_UPDATE_FAIL] ++;

                // Attempt to set player health to server sided.
                if(p_PlayerHealth[playerid][E_UPDATE_FAIL] >= 0 && p_PlayerHealth[playerid][E_UPDATE_FAIL] <= 9) {
                    SetPlayerHealth(playerid, p_PlayerHealth[playerid] [E_POINTS]);
                }

                if(p_PlayerHealth[playerid][E_UPDATE_FAIL] >= 10) {
                    SendClientMessage(playerid, 0xa9c4e4ff, "You have been kicked as you are desynced from the server. Please relog!");
                    printf("[Heath AC] Player %d was desynced thus kicked.", playerid);
                    Kick(playerid);
                }
            }
        }
        else {
            p_PlayerHealth[playerid][E_UPDATE_FAIL] = 0;

            // server hp can't be more than client.
            // set server hp to client hp if server is more than client.
            if(serverSideHealth > clientSideHealth) {
                p_PlayerHealth[playerid][E_POINTS] = currentHealth;
            }

            if(clientSideHealth > serverSideHealth && clientSideHealth <= 255 && clientSideHealth > 0) {
                SetPlayerHealth(playerid, p_PlayerHealth[playerid][E_POINTS]);
            }

            clientSideHealth = floatround(currentHealth, floatround_floor);
            serverSideHealth = floatround(p_PlayerHealth[playerid][E_POINTS], floatround_floor);

            new
                dmgOne = floatround(clientSideHealth - fHealthDamage, floatround_floor),
                dmgTwo = floatround(clientSideHealth - fHealthDamage, floatround_ceil);

            if(!(clientSideHealth == serverSideHealth || dmgOne == serverSideHealth || dmgTwo == serverSideHealth)) {
                SetPlayerHealth(playerid, p_PlayerHealth[playerid][E_POINTS]);
            }
        }
        p_PlayerHealth[playerid][E_UPDATE_TIME] = iTicks + 1000;
    }

    // Begin Armour Hack Detection
    if(iTicks > p_PlayerArmour[playerid] [E_UPDATE_TIME]) {
        new clientSideArmour 	= floatround(currentArmour, floatround_floor);
        new serverSideArmour 	= floatround(p_PlayerArmour[playerid][E_POINTS], floatround_floor);

        if(clientSideArmour == serverSideArmour)
            p_PlayerArmour[playerid][E_SYNCED] = true;

        if(!p_PlayerArmour[playerid][E_SYNCED]) {
            if(clientSideArmour > serverSideArmour) {
                p_PlayerArmour[playerid] [E_UPDATE_FAIL] ++;

                // Attempt to set player armour to server sided.
                if(p_PlayerArmour[playerid] [E_UPDATE_FAIL] >= 0 && p_PlayerArmour[playerid] [E_UPDATE_FAIL] <= 9) {
                    SetPlayerArmour(playerid, p_PlayerArmour[playerid][E_POINTS]);
                }

                if(p_PlayerArmour[playerid] [E_UPDATE_FAIL] >= 10) {
                    SendClientMessage(playerid, 0xa9c4e4ff, "You have been kicked as you are desynced from the server. Please relog!");
                    printf("[AC Armour] Player %d was desynced thus kicked.", playerid);
                    Kick(playerid);
                }
            }
        }
        else {
            p_PlayerArmour[playerid][E_UPDATE_FAIL] = 0;

            // server armour can't be more than client.
            // set server armour to client armour if server is more than client.
            if(serverSideArmour > clientSideArmour) {
                p_PlayerArmour[ playerid ] [ E_POINTS ] = currentArmour;
            }

            if(clientSideArmour > serverSideArmour && clientSideArmour <= 255 && clientSideArmour > 0) {
                SetPlayerArmour( playerid, p_PlayerArmour[ playerid ] [ E_POINTS ] );
            }

            clientSideArmour = floatround(currentArmour, floatround_floor);
            serverSideArmour = floatround(p_PlayerArmour[playerid] [E_POINTS], floatround_floor);

            new
                dmgOne = floatround( clientSideArmour - fArmourDamage, floatround_floor ),
                dmgTwo = floatround( clientSideArmour - fArmourDamage, floatround_ceil );

            if(!(clientSideArmour == serverSideArmour || dmgOne == serverSideArmour || dmgTwo == serverSideArmour)) {
                SetPlayerArmour( playerid, p_PlayerArmour[ playerid ] [ E_POINTS ] );
            }
        }
        p_PlayerArmour[ playerid ] [ E_UPDATE_TIME ] = iTicks + 1000;
    }
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(!IsPlayerNPC(playerid))
    {
        new
            server_time = gettime();

        // Anti-fakekill
        switch(server_time - p_LastDeath[playerid])
        {
            case 0 .. 3:
            {
                if (p_DeathSpam{playerid} ++ == 3)
                {
                    CallLocalFunction("OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_FAKEKILL, p_DeathSpam{playerid});
                    return Y_HOOKS_BREAK_RETURN_1;
                }
            }
            default: p_DeathSpam{playerid} = 0;
        }

        p_LastDeath[ playerid ] = server_time;

        // Died in Vehicle
        if (GetPlayerVehicleID(playerid) != INVALID_PLAYER_ID && AC_IsPlayerSpawned(playerid)) {
            if((GetTickCount() - p_LastTookDamage[playerid]) > 2500) {
                p_LastDamageIssuer[playerid] = INVALID_PLAYER_ID;
                p_LastWeaponIssuer[playerid] = 51;
            }
            CallRemoteFunction("OnPlayerDeathEx", "ddd", playerid, p_LastDamageIssuer[playerid], p_LastWeaponIssuer[playerid]);
        }

        // Reset spawned variable
        AC_SetPlayerSpawned(playerid, false);
    }
    return 1;
}

/* ** Functions ** */
stock ForcePlayerKill(playerid, killerid, weaponid) {
    p_LastTookDamage[playerid] 	    = GetTickCount();
    p_LastDamageIssuer[playerid]    = killerid;
    p_LastWeaponIssuer[playerid]    = weaponid;
    p_LastDamageIssued[playerid]    = 100.0;

    SetPlayerHealth(playerid, -1);
}

/* ** Modules ** */
#include <anti-cheat_vending-machines>
