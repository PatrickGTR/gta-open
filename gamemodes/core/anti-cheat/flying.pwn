/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat/flying.inc
 * Purpose: fly cheat detection system
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Variables ** */
static const Float: aWaterPlaces[ 20 ] [ 4 ] =
{
    { 30.00, 2313.00, -1417.0, 23.000 }, { 15.00, 1280.00, -773.00, 1083.0 }, { 25.00, 2583.00, 2385.00, 15.000 }, { 20.00, 225.000, -1187.0, 74.000 },
    { 50.00, 1973.00, -1198.0, 17.000 }, { 180.0, 1937.00, 1589.00, 9.0000 }, { 55.00, 2142.00, 1285.00, 8.0000 }, { 45.00, 2150.00, 1132.00, 8.0000 },
    { 55.00, 2089.00, 1915.00, 10.000 }, { 32.00, 2531.00, 1567.00, 9.0000 }, { 21.00, 2582.00, 2385.00, 17.000 }, { 33.00, 1768.00, 2853.00, 10.000 },
    { 47.00, -2721.0, -466.00, 4.0000 }, { 210.0, -671.00, -1898.0, 6.0000 }, { 45.00, 1240.00, -2381.0, 9.0000 }, { 50.00, 1969.00, -1200.0, 18.000 },
    { 10.00, 513.000, -1105.0, 79.000 }, { 20.00, 193.000, -1230.0, 77.000 }, { 30.00, 1094.00, -672.00, 113.00 }, { 20.00, 1278.00, -805.00, 87.000 }
};

static stock
    p_FlyHacksTick 					[ MAX_PLAYERS ],
    p_FlyHacksWarns 				[ MAX_PLAYERS char ]
;

/* ** Callback Hooks ** */
hook OnPlayerConnect( playerid ) {
	if ( 0 <= playerid < MAX_PLAYERS ) {
		p_FlyHacksWarns{ playerid } = 3;
	}
	return 1;
}

/* ** Functions ** */
static stock Float: ac_square( Float: value ) {
	return value * value;
}

stock AC_CheckForFlyHacks( playerid, iTicks )
{
	if( iTicks > p_FlyHacksTick[ playerid ] )
	{
		new
			pSurfingObject = GetPlayerSurfingObjectID( playerid ),
			pSurfingVehicle = GetPlayerSurfingVehicleID( playerid )
		;

		if( pSurfingVehicle == INVALID_VEHICLE_ID && pSurfingObject == INVALID_OBJECT_ID )
	    {
	        new
	        	iAnimation = GetPlayerAnimationIndex( playerid );

	     	if( iAnimation == 1538 || iAnimation == 1539 || iAnimation == 1543 )
	     	{
	     		if( !ac_IsPlayerInWater( playerid ) )
	     		{
	     			if( p_FlyHacksWarns{ playerid }++ >= 2 )
						CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_FLYHACKS, 0 ), p_FlyHacksWarns{ playerid } = 3;
	     		}
	     		else p_FlyHacksWarns{ playerid } = 0;
	     	}
		}

		p_FlyHacksTick[ playerid ] = iTicks + 1000;
	}
}

stock ac_IsPlayerInWater( playerid )
{
    static
    	Float: X, Float: Y, Float: Z, i;

    if( GetPlayerPos( playerid, X, Y, Z ) )
    {
	 	if( ac_IsPointInArea( X, Y, 2347.080, 521.70, 2372.65, 545.1971 ) || ac_IsPointInArea( X, Y, 2286.61, 521.70, 2301.45, 545.1971 ) )
	 		return false; // Kar Fix

	 	if( ac_PointDistance( X, Y, -965.0, 2438.0 ) <= ac_square( 700.0 ) && Z < 44.0 )
	    	return true;

		for( i = 0; i < sizeof( aWaterPlaces ); i++ )
		    if( ac_PointDistance( X, Y, aWaterPlaces[ i ] [ 1 ], aWaterPlaces[ i ] [ 2 ] ) <= ac_square( aWaterPlaces[ i ] [ 0 ] ) && Z < aWaterPlaces[ i ] [ 3 ] )
				return true;

	    return Z < 1.9 ? !( ac_PointDistance( X, Y, 618.4129, 863.3164 ) < ac_square( 200.0 ) ) : false;
	}
	return false;
}
