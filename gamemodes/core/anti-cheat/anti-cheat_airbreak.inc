/*
 * Irresistible Gaming (c) 2018
 * Developed by Emmet_, Lorenc
 * Module: anticheat/carwarp.pwn
 * Purpose: car warp cheat detection system
 */

/* ** Includes ** */
#include                            < YSI_Coding\y_hooks >

/* ** Variables ** */
static stock
    Float: p_abLastPosition         [ MAX_PLAYERS ] [ 3 ],
    p_abLastTick                    [ MAX_PLAYERS ],
    p_abPosTick                     [ MAX_PLAYERS ],
    p_abDetected                    [ MAX_PLAYERS char ],
    p_abResetTimer                  [ MAX_PLAYERS ]
;

/* ** Forwards ** */
public AC_ResetABDetected( playerid );

/* ** Function Hooks ** */

// Function Hook (PutPlayerInVehicle)

stock AC_AB_PutPlayerInVehicle( playerid, vehicleid, seatid )
{
    p_abLastTick[ playerid ] = GetTickCount( ) + 3000;
    return PutPlayerInVehicle( playerid, vehicleid, seatid );
}

#if defined _ALS_PutPlayerInVehicle
    #undef PutPlayerInVehicle
#else
    #define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle AC_AB_PutPlayerInVehicle

// Function Hook (SetPlayerPos)

stock AC_SetPlayerPos( playerid, Float: x, Float: y, Float: z )
{
    p_abLastTick[ playerid ] = GetTickCount( ) + 3000;
    return SetPlayerPos( playerid, x, y, z );
}

#if defined _ALS_SetPlayerPos
    #undef SetPlayerPos
#else
    #define _ALS_SetPlayerPos
#endif
#define SetPlayerPos AC_SetPlayerPos

// Function Hook (SetPlayerPosFindZ)

stock AC_SetPlayerPosFindZ(playerid, Float:x, Float:y, Float:z)
{
    p_abLastTick[ playerid ] = GetTickCount( ) + 3000;
	return SetPlayerPosFindZ( playerid, x, y, z );
}

#if defined _ALS_SetPlayerPosFindZ
    #undef SetPlayerPosFindZ
#else
    #define _ALS_SetPlayerPosFindZ
#endif
#define SetPlayerPosFindZ AC_SetPlayerPosFindZ

/* ** Callback Hooks ** */
hook OnPlayerDeath( playerid, killerid, reason ) {
    if ( 0 <= playerid < MAX_PLAYERS ) {
        p_abLastTick[ playerid ] = GetTickCount( ) + 3000;
    }
    return 1;
}

hook OnPlayerConnect( playerid ) {
    if ( 0 <= playerid < MAX_PLAYERS ) {
        p_abDetected{ playerid } = 0;
        p_abResetTimer[ playerid ] = -1;
        p_abLastTick[ playerid ] = GetTickCount( ) + 3000;
    }
    return 1;
}

hook OnPlayerSpawn( playerid ) {
    if ( 0 <= playerid < MAX_PLAYERS ) {
        p_abDetected{ playerid } = 0;
        p_abLastTick[ playerid ] = GetTickCount( ) + 3000;
    }
    return 1;
}

hook OnPlayerStateChange( playerid, newstate, oldstate ) {
    if ( 0 <= playerid < MAX_PLAYERS ) {
        p_abLastTick[ playerid ] = GetTickCount( ) + 3000;
    }
    return 1;
}

/* ** Hooks ** */
stock AC_CheckForAirbrake( playerid, iTicks, iState )
{
    if( iState == 0 || iState == 2 || iState == 3 || iState == 7 || iState == 9 )
		p_abLastTick[ playerid ] = iTicks + 1000;

    else if( !IsPlayerInAnyVehicle( playerid ) && GetPlayerSurfingVehicleID( playerid ) == INVALID_VEHICLE_ID && GetPlayerSurfingObjectID( playerid ) == INVALID_VEHICLE_ID ) // && !IsPlayerNPC( playerid )
    {
        new
            Float: iPacketLoss = NetStats_PacketLossPercent( playerid );

        if( iTicks > p_abLastTick[ playerid ] && iPacketLoss < 0.8 )
        {
            static
                Float: x, Float: y, Float: z,
                Float: distance
           	;

            GetPlayerPos( playerid, x, y, z );

            if( floatabs( p_abLastPosition[ playerid ] [ 2 ] - z ) < 1.0 )
            {
                distance = GetPlayerDistanceFromPoint( playerid, p_abLastPosition[ playerid ] [ 0 ], p_abLastPosition[ playerid ] [ 1 ], p_abLastPosition[ playerid ] [ 2 ] );
                if( floatabs( distance ) >= 75.0 && ( floatabs( p_abLastPosition[ playerid ] [ 1 ] - y ) >= 50.0 || floatabs( p_abLastPosition[ playerid ] [ 0 ] - x ) >= 50.0 ) )
                {
                    if( ++p_abDetected{ playerid } >= 3 )
						CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_AIRBRAKE, 0 );

                    if( p_abResetTimer[ playerid ] == -1 )
                        p_abResetTimer[ playerid ] = SetTimerEx( "AC_ResetABDetected", 60000, false, "d", playerid );
                }
            }
            p_abLastTick[ playerid ] = iTicks + 1000;
        }

        if( iTicks > p_abPosTick[ playerid ] )
        {
            p_abPosTick[ playerid ] = iTicks + 1000;
       		GetPlayerPos( playerid, p_abLastPosition[ playerid ] [ 0 ], p_abLastPosition[ playerid ] [ 1 ], p_abLastPosition[ playerid ] [ 2 ] );
        }
    }
    return 1;
}

public AC_ResetABDetected( playerid ) {
    p_abDetected{ playerid } = 0;
    p_abResetTimer[ playerid ] = -1;
}
