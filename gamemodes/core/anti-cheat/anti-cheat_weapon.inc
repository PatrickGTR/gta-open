/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat/weapon.inc
 * Purpose: server sided weapon system
 */

/* ** Includes ** */
#include 							< YSI_Coding\y_hooks >

/* ** Definitions ** */
#if !defined MAX_CLASSES
	#define MAX_CLASSES 			( 300 )
#endif

#if !defined AC_MAX_WEAPONS
	#define AC_MAX_WEAPONS 			( 55 )
#endif

/* ** Variables ** */
enum E_CLASS_DATA {
	E_WEAPONS[ 3 ]
};

static stock
	mAvailableSpawns 				[ MAX_CLASSES ] [ E_CLASS_DATA ],
	bool: p_PlayerHasWeapon 		[ MAX_PLAYERS ] [ AC_MAX_WEAPONS char ],
	p_SelectedClassID 				[ MAX_PLAYERS ],
	p_PlayerWeaponUpdateTime 		[ MAX_PLAYERS ],
	p_CurrentArmedWeapon 			[ MAX_PLAYERS char ],
	Iterator: classes 				< MAX_CLASSES >
;

/* ** Callback Hooks ** */
hook OnPlayerConnect( playerid ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		for ( new i = 0; i < AC_MAX_WEAPONS; i++ ) {
			p_PlayerHasWeapon[ playerid ] { i } = false;
		}
	}
	return 1;
}

hook OnPlayerDeath( playerid, killerid, reason )
{
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_PlayerWeaponUpdateTime[ playerid ] = GetTickCount( ) + 2000;
	}
	return 1;
}

hook OnPlayerSpawn( playerid )
{
	if ( 0 <= playerid < MAX_PLAYERS )
	{
		for ( new i = 0; i < 3; i++ )
		{
			new
				weaponid = mAvailableSpawns[ p_SelectedClassID[ playerid ] ] [ E_WEAPONS ] [ i ];

			if( weaponid != -1 && weaponid < AC_MAX_WEAPONS ) {
				p_PlayerHasWeapon[ playerid ] { weaponid } = true;
			}
		}
		p_PlayerWeaponUpdateTime[ playerid ] = GetTickCount( ) + 2000;
	}
	return 1;
}

hook OnPlayerStateChange( playerid, newstate, oldstate ) // Weapon Hacks - credits to wups
{
	if ( 0 <= playerid < MAX_PLAYERS )
	{
		if( newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER )
		{
			switch ( GetVehicleModel( GetPlayerVehicleID( playerid ) ) )
			{
				case 457:
					p_PlayerHasWeapon[ playerid ] { 2 } = true;

				case 592, 577, 511, 512, 520, 593, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469, 539:
					p_PlayerHasWeapon[ playerid ] { 46 } = true;

				case 596, 597, 598, 599:
					p_PlayerHasWeapon[ playerid ] { 25 } = true;
			}
		}
   	}
	return 1;
}

hook OnPlayerExitVehicle( playerid, vehicleid )
{
	if ( 0 <= playerid < MAX_PLAYERS )
	{
		switch( GetVehicleModel( vehicleid ) ) // Weapon Hacks - credits to wups
		{
			case 457:
				p_PlayerHasWeapon[ playerid ] { 2 } = true;

			case 592, 577, 511, 512, 520, 593, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469, 539:
				p_PlayerHasWeapon[ playerid ] { 46 } = true;

			case 596, 597, 598, 599:
				p_PlayerHasWeapon[ playerid ] { 25 } = true;
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange( playerid, newkeys, oldkeys )
{
	if( !IsPlayerNPC( playerid ) )
	{
		if ( ( newkeys & KEY_FIRE ) && AC_IsPlayerSpawned( playerid ) ) {
			new iWeapon = GetPlayerWeapon( playerid );
			new iTickCount = GetTickCount( );

			if ( iTickCount > p_PlayerWeaponUpdateTime[ playerid ] && 0 <= iWeapon < AC_MAX_WEAPONS )
			{
				if( !p_PlayerHasWeapon[ playerid ] { iWeapon } && ( iWeapon != 0 && iWeapon != 40 ) && ! ( IsPlayerInAnyVehicle( playerid ) && p_CurrentArmedWeapon{ playerid } != iWeapon ) ) {
					CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_WEAPON, iWeapon );
					// printf("[weapon] %d seems to weapon hack (weapon id %d).", playerid, iWeapon );
				}
			}
		}
	}
	return 1;
}

hook OnPlayerRequestClass( playerid, classid ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_SelectedClassID[ playerid ] = classid;
	}
	return 1;
}

/* ** Function Hooks ** */
// Function Hook (GivePlayerWeapon)

stock AC_GivePlayerWeapon( playerid, weaponid, ammo )
{
	p_PlayerWeaponUpdateTime[ playerid ] = GetTickCount( ) + 2000;

	if( 0 <= weaponid < AC_MAX_WEAPONS ) {
		p_PlayerHasWeapon[ playerid ] { weaponid } = true;
		p_CurrentArmedWeapon{ playerid } = weaponid;
	}
    return GivePlayerWeapon( playerid, weaponid, ammo );
}

#if defined _ALS_GivePlayerWeapon
    #undef GivePlayerWeapon
#else
    #define _ALS_GivePlayerWeapon
#endif
#define GivePlayerWeapon AC_GivePlayerWeapon

// Function Hook (SetPlayerArmedWeapon)

stock AC_SetPlayerArmedWeapon( playerid, weaponid )
{
	if ( 0 <= weaponid <= AC_MAX_WEAPONS && p_CurrentArmedWeapon{ playerid } != weaponid ) {
		p_PlayerWeaponUpdateTime[ playerid ] = GetTickCount( ) + 2000;
		p_CurrentArmedWeapon{ playerid } = weaponid;
	}
    return SetPlayerArmedWeapon( playerid, weaponid );
}

#if defined _ALS_SetPlayerArmedWeapon
    #undef SetPlayerArmedWeapon
#else
    #define _ALS_SetPlayerArmedWeapon
#endif
#define SetPlayerArmedWeapon AC_SetPlayerArmedWeapon

// Function Hook (ResetPlayerWeapons)

stock AC_ResetPlayerWeapons( playerid )
{
	p_PlayerWeaponUpdateTime[ playerid ] = GetTickCount( ) + 2000;

	for ( new i = 0; i < AC_MAX_WEAPONS; i++ )
		p_PlayerHasWeapon[ playerid ] { i } = false;

    return ResetPlayerWeapons( playerid );
}

#if defined _ALS_ResetPlayerWeapons
    #undef ResetPlayerWeapons
#else
    #define _ALS_ResetPlayerWeapons
#endif
#define ResetPlayerWeapons AC_ResetPlayerWeapons

// Function Hook (SetSpawnInfo)

stock AC_SetSpawnInfo( playerid, team, skin, Float: x, Float: y, Float: z, Float: Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo )
{
	if ( weapon1 != -1 && weapon1 < AC_MAX_WEAPONS ) p_PlayerHasWeapon[ playerid ] { weapon1 } = true;
	if ( weapon2 != -1 && weapon2 < AC_MAX_WEAPONS ) p_PlayerHasWeapon[ playerid ] { weapon2 } = true;
	if ( weapon3 != -1 && weapon3 < AC_MAX_WEAPONS ) p_PlayerHasWeapon[ playerid ] { weapon3 } = true;

    return SetSpawnInfo( playerid, team, skin, x, y, z, Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo );
}

#if defined _ALS_SetSpawnInfo
    #undef SetSpawnInfo
#else
    #define _ALS_SetSpawnInfo
#endif
#define SetSpawnInfo AC_SetSpawnInfo

// Function Hook (AddPlayerClass)

stock AC_AddPlayerClass( skin, Float: x, Float: y, Float: z, Float: Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo )
{
	new
		classid = Iter_Free(classes);

	if( classid != -1 )
	{
		mAvailableSpawns[ classid ] [ E_WEAPONS ] [ 0 ] = weapon1;
		//mAvailableSpawns[ classid ] [ E_WEAPONS_AMMO ] [ 0 ] = static_cast<int>(params[7]);

		mAvailableSpawns[ classid ] [ E_WEAPONS ] [ 1 ] = weapon2;
		//mAvailableSpawns[ classid ] [ E_WEAPONS_AMMO ] [ 1 ] = static_cast<int>(params[9]);

		mAvailableSpawns[ classid ] [ E_WEAPONS ] [ 2 ] = weapon3;
		//mAvailableSpawns[ classid ] [ E_WEAPONS_AMMO ] [ 2 ] = static_cast<int>(params[11]);

		Iter_Add(classes, classid);
	}
    return AddPlayerClass( skin, x, y, z, Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo );
}

#if defined _ALS_AddPlayerClass
    #undef AddPlayerClass
#else
    #define _ALS_AddPlayerClass
#endif
#define AddPlayerClass AC_AddPlayerClass

// Function Hook (AddPlayerClass)

stock AC_AddPlayerClassEx( teamid, skin, Float:x, Float:y, Float:z, Float:Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo )
{
	new
		classid = Iter_Free(classes);

	if( classid != -1 )
	{
		mAvailableSpawns[ classid ] [ E_WEAPONS ] [ 0 ] = weapon1;
		//mAvailableSpawns[ classid ] [ E_WEAPONS_AMMO ] [ 0 ] = static_cast<int>(params[7]);

		mAvailableSpawns[ classid ] [ E_WEAPONS ] [ 1 ] = weapon2;
		//mAvailableSpawns[ classid ] [ E_WEAPONS_AMMO ] [ 1 ] = static_cast<int>(params[9]);

		mAvailableSpawns[ classid ] [ E_WEAPONS ] [ 2 ] = weapon3;
		//mAvailableSpawns[ classid ] [ E_WEAPONS_AMMO ] [ 2 ] = static_cast<int>(params[11]);

		Iter_Add(classes, classid);
	}
    return AddPlayerClassEx( teamid, skin, x, y, z, Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo )
}

#if defined _ALS_AddPlayerClassEx
    #undef AddPlayerClassEx
#else
    #define _ALS_AddPlayerClassEx
#endif
#define AddPlayerClassEx AC_AddPlayerClassEx
