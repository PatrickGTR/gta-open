/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat/carwarp.pwn
 * Purpose: car warp cheat detection system
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Variables ** */
static stock
    p_ac_CarWarpTime				[ MAX_PLAYERS ],
    p_ac_CarWarpVehicleID			[ MAX_PLAYERS ]
;

/* ** Hooks ** */
hook OnPlayerStateChange( playerid, newstate, oldstate )
{
  	if ( newstate == PLAYER_STATE_DRIVER )
    {
        if ( GetPlayerVehicleID( playerid ) != p_ac_CarWarpVehicleID[ playerid ] )
        {
        	new
        		server_time = gettime( );

	        if ( p_ac_CarWarpTime[ playerid ] > server_time )
	        {
				CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_RAPIDFIRE, 0 );
	            return Y_HOOKS_BREAK_RETURN_1;
	        }

	        p_ac_CarWarpTime[ playerid ] = server_time + 1;
	        p_ac_CarWarpVehicleID[ playerid ] = GetPlayerVehicleID( playerid );
		}
    }
	return 1;
}
