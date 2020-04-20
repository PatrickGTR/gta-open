/*
 * Irresistible Gaming (c) 2018
 * Developed by JernejL, Lorenc
 * Module: anticheat/hitpoints.inc
 * Purpose: detects abnormal vehicle entering
 */

/* ** Variables ** */
enum E_PLAYER_REMOTEJACK
{
    Float: E_LAST_X,        Float: E_LAST_Y,        Float: E_LAST_Z,
    E_LAST_VEH
};

static stock
    p_remoteJackData                [ MAX_PLAYERS ] [ E_PLAYER_REMOTEJACK ]
;

/* ** Hooks ** */
stock AC_RJ_PutPlayerInVehicle( playerid, vehicleid, seatid )
{
    p_remoteJackData[ playerid ] [ E_LAST_VEH ] = vehicleid;
    return PutPlayerInVehicle( playerid, vehicleid, seatid );
}

#if defined _ALS_PutPlayerInVehicle
    #undef PutPlayerInVehicle
#else
    #define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle AC_RJ_PutPlayerInVehicle

/* ** Functions ** */
stock AC_CheckPlayerRemoteJacking( playerid )
{
    new iVehicle = GetPlayerVehicleID( playerid );

    if( !IsPlayerInAnyVehicle( playerid ) )
        GetPlayerPos( playerid, p_remoteJackData[ playerid ] [ E_LAST_X ], p_remoteJackData[ playerid ] [ E_LAST_Y ], p_remoteJackData[ playerid ] [ E_LAST_Z ] );

    if( ( iVehicle != p_remoteJackData[ playerid ] [ E_LAST_VEH ] ) && ( iVehicle != 0 ) && ( GetPlayerState( playerid ) == PLAYER_STATE_DRIVER ) )
    {
        new
            Float: fDistance = GetVehicleDistanceFromPoint( iVehicle, p_remoteJackData[ playerid ] [ E_LAST_X ], p_remoteJackData[ playerid ] [ E_LAST_Y ], p_remoteJackData[ playerid ] [ E_LAST_Z ] ),
            Float: fOffset = 10.0
        ;

        if( ( GetVehicleModel( iVehicle ) == 577 ) || ( GetVehicleModel( iVehicle ) == 592 )) fOffset = 25.0; // Andromanda | AT-400

        if( fDistance > fOffset )
			CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_REMOTE_JACK, 0 );

        GetPlayerPos( playerid, p_remoteJackData[ playerid ] [ E_LAST_X ], p_remoteJackData[ playerid ] [ E_LAST_Y ], p_remoteJackData[ playerid ] [ E_LAST_Z ] );
        p_remoteJackData[ playerid ] [ E_LAST_VEH ] = iVehicle;
    }
    return 1;
}
