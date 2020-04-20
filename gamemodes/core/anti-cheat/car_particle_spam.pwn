/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat\carparticlespam.pwn
 * Purpose: detection for car particle spamming (where doors particles spam)
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Error Checking ** */
DEFINE_HOOK_REPLACEMENT 			( Vehicle, Veh );

/* ** Variables ** */
static stock
	p_DamageSpamTime				[ MAX_PLAYERS ],
	p_DamageSpamCount				[ MAX_PLAYERS char ];

/* ** Function Hooks ** */
stock AC_RepairVehicle( vehicleid )
{
	foreach ( new playerid : Player ) if ( GetPlayerVehicleID( playerid ) == vehicleid ) {
		p_DamageSpamCount{ playerid } = 0;
	}
	return RepairVehicle( vehicleid );
}

#if defined _ALS_RepairVehicle
    #undef RepairVehicle
#else
    #define _ALS_RepairVehicle
#endif

#define RepairVehicle AC_RepairVehicle

/* ** Hooks ** */
hook OnPlayerDisconnect( playerid, reason )
{
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_DamageSpamCount{ playerid } = 0;
	}
	return 1;
}

hook OnVehDamageStatusUpdate( vehicleid, playerid )
{
	if ( GetPlayerState( playerid ) == PLAYER_STATE_DRIVER )
	{
		static
			damage_status[ 4 ];

   		GetVehicleDamageStatus( vehicleid, damage_status[ 0 ], damage_status[ 1 ], damage_status[ 2 ], damage_status[ 3 ] );

	    if ( damage_status[ 2 ] || damage_status[ 3 ] ) // ignore lights & tires
	        return 1;

		new
			time = GetTickCount( );

		switch( time - p_DamageSpamTime[ playerid ] )
		{
			case 0 .. 500:
			{
				if ( ++ p_DamageSpamCount{ playerid } >= 10 )
				{
					CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_CAR_PARTICLE_SPAM, 0 );
					return 1;
				}
			}
			default: p_DamageSpamCount{ playerid } = 0;
		}
		p_DamageSpamTime[ playerid ] = time;
 	}
	return 1;
}
