/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc Pekaj
 * Module: anticheat/main.inc
 * Purpose: core file to include anticheat items
 */

/* ** Error checking ** */
#if !defined AC_INCLUDED
	#define AC_INCLUDED
#else
	#endinput
#endif

/* ** Includes ** */
#include 							< YSI_Coding\y_hooks >

/* ** Definitions ** */
#define AC_MAX_DETECTIONS 			( 13 )

/* ** Variables ** */
enum
{
	CHEAT_TYPE_WEAPON,
	CHEAT_TYPE_CARWARP,
	//CHEAT_TYPE_MONEY,
	//CHEAT_TYPE_PLAYERBUGGER,
	//CHEAT_TYPE_SPECTATE,
	CHEAT_TYPE_FAKEKILL,
	CHEAT_TYPE_REMOTE_JACK,
	//CHEAT_TYPE_PING_LIMIT,
	CHEAT_TYPE_SPEED_HACK,
	//CHEAT_TYPE_JETPACK,
	CHEAT_TYPE_HEALTH,
	CHEAT_TYPE_ARMOUR,
	CHEAT_TYPE_AIRBRAKE,
	CHEAT_TYPE_PROAIM,
	CHEAT_TYPE_AUTOCBUG,
	CHEAT_TYPE_FLYHACKS,
	CHEAT_TYPE_RAPIDFIRE,
	CHEAT_TYPE_CAR_PARTICLE_SPAM,
	CHEAT_TYPE_PICKUP_SPAM
};

static stock
    bool: p_acSpawned  				[ MAX_PLAYERS char ],
    p_acUpdateTime 					[ MAX_PLAYERS ]
;

/* ** Forwards ** */
forward OnPlayerCheatDetected( playerid, detection, params );
forward bool: AC_IsPlayerSpawned( playerid );

/* ** Callback Hooks ** */
hook OnPlayerUpdate( playerid )
{
	if( ! AC_IsPlayerSpawned( playerid ) && !Class_SelectionStatus(playerid) )
		return ~0; // Not Spawned, No SYNC!

	if( !IsPlayerNPC( playerid ) )
	{
		new
			iState = GetPlayerState( playerid );

		p_acUpdateTime[ playerid ] = GetTickCount( );

		if( iState != PLAYER_STATE_SPECTATING )
		{
        	AC_CheckForAirbrake			( playerid, p_acUpdateTime[ playerid ], iState );
			AC_CheckForHealthHacks		( playerid, p_acUpdateTime[ playerid ] );
        	AC_CheckForFlyHacks			( playerid, p_acUpdateTime[ playerid ] );
        	AC_CheckPlayerRemoteJacking ( playerid );
		}
	}
	return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	new
		iState = GetPlayerState( playerid );

	if( iState == PLAYER_STATE_WASTED || ! AC_IsPlayerSpawned( playerid ) )
		return Y_HOOKS_BREAK_RETURN_0; // Why bother, he's dead!

	// AC_CheckForAutoCbug( playerid, weaponid );
	// AC_CheckForSilentAimbot( playerid, hittype, hitid );
	return 1;
}

hook OnPlayerConnect( playerid ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_acSpawned{ playerid } = false;
	}
	return 1;
}

hook OnPlayerSpawn( playerid ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_acSpawned{ playerid } = true;
	}
	return 1;
}

hook OnPlayerRequestClass( playerid, classid ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_acSpawned{ playerid } = false;
	}
	return 1;
}

/* ** Functions ** */
stock AC_DetectedCheatToString( iDetection ) {
	new
		szString[ 16 ] = "unknown";

	switch( iDetection ) {
		case CHEAT_TYPE_ARMOUR: 		szString = "Armour Hacks";
		case CHEAT_TYPE_HEALTH:			szString = "Health Hacks";
		case CHEAT_TYPE_WEAPON: 		szString = "Weapon Hacks";
		case CHEAT_TYPE_AIRBRAKE: 		szString = "Airbrake";
		case CHEAT_TYPE_PROAIM: 		szString = "Silent Aimbot";
		case CHEAT_TYPE_AUTOCBUG: 		szString = "Auto CBUG";
		case CHEAT_TYPE_FLYHACKS: 		szString = "Fly Hacks";
		case CHEAT_TYPE_REMOTE_JACK:	szString = "Remote Jacking";
	}
	return szString;
}

stock ac_IsPointInArea( Float: X, Float: Y, Float: minx, Float: maxx, Float: miny, Float: maxy )
 	return ( X > minx && X < maxx && Y > miny && Y < maxy );

stock Float: ac_PointDistance( Float: X, Float: Y, Float: dstX, Float: dstY )
	return ( ( X - dstX ) * ( X - dstX ) ) + ( ( Y - dstY ) * ( Y - dstY ) );

stock Float: ac_GetDistanceBetweenPlayers( iPlayer1, iPlayer2, &Float: fDistance = Float: 0x7F800000 )
{
    static
    	Float: fX, Float: fY, Float: fZ;

    if( GetPlayerVirtualWorld( iPlayer1 ) == GetPlayerVirtualWorld( iPlayer2 ) && GetPlayerPos( iPlayer2, fX, fY, fZ ) )
		fDistance = GetPlayerDistanceFromPoint( iPlayer1, fX, fY, fZ );

    return fDistance;
}

stock AC_GetLastUpdateTime( playerid ) {
	return p_acUpdateTime[ playerid ];
}

stock bool: AC_IsPlayerSpawned( playerid ) {
	return p_acSpawned{ playerid };
}

stock AC_SetPlayerSpawned( playerid, bool: spawned ) {
	p_acSpawned{ playerid } = spawned;
}

/* ** Modules (remove to disable) ** */
#include <anti-cheat_money>
#include <anti-cheat_thermal-vision>
#include <anti-cheat_player-bugger>
#include <anti-cheat_bot-attack>
#include <anti-cheat_server-side-dmg>
#include <anti-cheat_weapon>
#include <anti-cheat_carmod>
#include <anti-cheat_airbreak>
//#include "proaim.pwn"
//#include "autocbug.pwn"
#include <anti-cheat_flying>
#include <anti-cheat_remotejack>
//#include "rapidfire.pwn"
#include <anti-cheat_carwarp>
//#include "car_particle_spam.pwn"
//#include "pickup_spam.pwn"


