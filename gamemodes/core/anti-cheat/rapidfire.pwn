/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat\rapidfire.pwn
 * Purpose: rapid fire detection as well as invalid bullet filtering
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Variables ** */
static stock
	p_RapidFireTickCount			[ MAX_PLAYERS ],
	p_RapidFireShots				[ MAX_PLAYERS char ]
;

/* ** Hooks ** */
hook OnPlayerDisconnect( playerid, reason ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_RapidFireShots{ playerid } = 0;
	}
	return 1;
}

hook OnPlayerWeaponShot( playerid, weaponid, hittype, hitid, Float: fX, Float: fY, Float: fZ )
{
	new
		keys, ud, lr;

	GetPlayerKeys( playerid, keys, ud, lr );

	// Simple. But effective. Anti-Shooting Hacks.
	if ( ! ( keys & KEY_FIRE )  ) {
		return Y_HOOKS_BREAK_RETURN_0;
	}

	// Invalid weapon id
	if ( ! ( 22 <= weaponid <= 34 ) && weaponid != 38 ) {
		return Y_HOOKS_BREAK_RETURN_0;
	}

	// Invalid hit (very far offset from player)
	if ( hittype == BULLET_HIT_TYPE_PLAYER && ( ( fX >= 10.0 || fX <= -10.0 ) || ( fY >= 10.0 || fY <= -10.0 ) || ( fZ >= 10.0 || fZ <= -10.0 ) ) ) {
		return Y_HOOKS_BREAK_RETURN_0;
	}

	// Anti-Rapid Fire
	if ( ! p_RapidFireTickCount[ playerid ] ) p_RapidFireTickCount[ playerid ] = GetTickCount( );
	else
	{
		new
			iInterval = GetTickCount( ) - p_RapidFireTickCount[ playerid ];

		if ( ( iInterval <= 35 && ( weaponid != 38 && weaponid != 28 && weaponid != 32 ) ) || ( iInterval <= 370 && ( weaponid == 34 || weaponid == 33 ) ) )
		{
			if ( p_RapidFireShots{ playerid } ++ >= 5 ) {
				CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_RAPIDFIRE, 0 );
		    	return Y_HOOKS_BREAK_RETURN_0;
			}
		}
		else
		{
			p_RapidFireShots{ playerid } = 0;
		}

		p_RapidFireTickCount[ playerid ] = GetTickCount( );
	}
	return 1;
}
