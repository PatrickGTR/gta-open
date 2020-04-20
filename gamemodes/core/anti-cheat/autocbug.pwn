/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat/autocbug.pwn
 * Purpose: rapid fire detection
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Definitions ** */
#define AUTOCBUG_TICKS_DEAGLE   	( 500 ) // prev 600
#define AUTOCBUG_TICKS_SHOTGUN  	( 850 )
#define AUTOCBUG_TICKS_COUNTRY  	( 750 )
#define AUTOCBUG_TICKS_SNIPER   	( 750 )

/* ** Variables ** */
static stock
	p_cbugKeyTicks					[ MAX_PLAYERS ],
	p_cbugFireTicks					[ MAX_PLAYERS ],
    p_cbugWarns 					[ MAX_PLAYERS char ]
;

/* ** Callback Hooks ** */
hook OnPlayerConnect( playerid ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_cbugWarns{ playerid } = 0;
	}
	return 1;
}

hook OnPlayerKeyStateChange( playerid, newkeys, oldkeys ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		if( !p_cbugKeyTicks[ playerid ] ) {
			p_cbugKeyTicks[ playerid ] = GetTickCount( ), p_cbugWarns{ playerid } = 0;
		}

		if( ( ( ( newkeys & ( KEY_CROUCH ) ) == ( KEY_CROUCH ) ) || ( ( oldkeys & ( KEY_CROUCH ) ) == ( KEY_CROUCH ) ) ) ) {
			p_cbugKeyTicks[ playerid ] = GetTickCount( ), p_cbugWarns{ playerid } = 0;
		}
	}
	return 1;
}

stock AC_CheckForAutoCbug( playerid, weaponid )
{
	// Anti-Rapid Fire
	if( !p_cbugFireTicks[ playerid ] ) p_cbugFireTicks[ playerid ] = GetTickCount( );
	else
	{
		new
			iTicks = GetTickCount( ),
			iInterval = iTicks - p_cbugFireTicks[ playerid ],
			iKeyInterval = iTicks - p_cbugKeyTicks[ playerid ],
			iHardInterval = 1000
		;

		if( weaponid == WEAPON_DEAGLE || weaponid == WEAPON_SHOTGUN || weaponid == WEAPON_RIFLE || weaponid == WEAPON_SNIPER )
		{
			new
				iCompare = iKeyInterval - iInterval,
				Float: fOwnPacketLoss = NetStats_PacketLossPercent( playerid )
			;

	     	switch( weaponid )
            {
                case WEAPON_DEAGLE: 	iHardInterval = AUTOCBUG_TICKS_DEAGLE;
                case WEAPON_SHOTGUN: 	iHardInterval = AUTOCBUG_TICKS_SHOTGUN;
                case WEAPON_RIFLE: 		iHardInterval = AUTOCBUG_TICKS_COUNTRY;
                case WEAPON_SNIPER: 	iHardInterval = AUTOCBUG_TICKS_SNIPER;
            }

			if( iInterval < iHardInterval && iCompare > 1500 && fOwnPacketLoss < 0.8 ) {
				if( p_cbugWarns{ playerid }++ >= 2 ) {
					printf( "[autocbug detect] %d detected (wep %d, interval %d, compare %d, warns %d)", playerid, weaponid, iInterval, iCompare, p_cbugWarns{ playerid });
					CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_AUTOCBUG, 0 );
				}
			}
		}
		p_cbugFireTicks[ playerid ] = iTicks;
	}
}
