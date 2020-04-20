/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: irresistible\anticheat\player_bugger.pwn
 * Purpose: method(s) for preventing players to be bugged
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Variables ** */
static stock
	p_DesyncTime 					[ MAX_PLAYERS ],
	Float: p_PlayerBuggerX			[ MAX_PLAYERS ],
	Float: p_PlayerBuggerY			[ MAX_PLAYERS ],
	Float: p_PlayerBuggerZ			[ MAX_PLAYERS ]
;

/* ** Hooks ** */
hook OnPlayerUpdate( playerid )
{
    // automatically resort to using the 'fastest' one
    #if defined GetServerTime
        new server_time = GetServerTime( );
    #else
        new server_time = gettime( );
    #endif

    // desync feature
	if ( server_time < p_DesyncTime[ playerid ] )
		return Y_HOOKS_BREAK_RETURN_0;

    static
		Float: X, 	Float: Y, 	Float: Z,
		Float: vX, 	Float: vY, 	Float: vZ
    ;

    // Fugga.cs
	GetPlayerVelocity( playerid, vX, vY, vZ );

	if ( ( ( vX < -10.0 || vX > 10.0 ) && ( vZ > 1.0 || vZ < -1.0 ) ) || ( ( vX < -3.0 || vX > 3.0 ) && ( vY < -3.0 || vY > 3.0 ) && ( vZ > 3.0 || vZ < -3.0 ) ) ) {
		p_DesyncTime[ playerid ] = server_time + 3;
		return Y_HOOKS_BREAK_RETURN_0;
	}

    // PlayerBugger.cs
	GetPlayerPos( playerid, X, Y, Z );

	if ( X >= 99999.0 || Y >= 99999.0 || Z >= 99999.0 || X <= -99999.0 || Y <= -99999.0 || Z <= -99999.0 ) {
	  	SendClientMessage( playerid, 0xa9c4e4ff, "Warning: Excessive X, Y, Z has been breached thus last location set." );
		SetPlayerPos( playerid, p_PlayerBuggerX[ playerid ], p_PlayerBuggerY[ playerid ], p_PlayerBuggerZ[ playerid ] );
	} else {
	    p_PlayerBuggerX[ playerid ] = X;
	    p_PlayerBuggerY[ playerid ] = Y;
	    p_PlayerBuggerZ[ playerid ] = Z;
	}

    // CarSwing.cs
	if ( IsPlayerInAnyVehicle( playerid ) && GetPlayerState( playerid ) == PLAYER_STATE_DRIVER ) {

		GetPlayerPos( playerid, X, Y, Z );
  		GetVehicleVelocity( GetPlayerVehicleID( playerid ), vX, vY, vZ );

		if ( ( vX > 3.0 || vY > 3.0 || vZ > 3.0 || vX < -3.0 || vY < -3.0 || vZ < -3.0 ) && ( vX != X && vY != Y && vZ != Z ) ) {
			p_DesyncTime[ playerid ] = server_time + 3;
			return Y_HOOKS_BREAK_RETURN_0;
		}
	}
    return 1;
}