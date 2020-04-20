/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat/pickup_spam.pwn
 * Purpose: checks if a player enters a bunch of pickups really fast
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Variables ** */
static stock
	LastPickupTimestamp				[ MAX_PLAYERS ],
	PreviousPickupID				[ MAX_PLAYERS ],
	Float: p_LastPickupPos 			[ MAX_PLAYERS ] [ 3 ];

/* ** Hooks ** */
hook OnPlayerPickUpDynPickup( playerid, pickupid )
{
	if ( pickupid != PreviousPickupID[ playerid ] )
	{
		new
			iTimestamp = gettime( ); // Call it once, because swag

		if ( LastPickupTimestamp[ playerid ] > iTimestamp )
		{
			new
				Float: distance = GetPlayerDistanceFromPoint( playerid, p_LastPickupPos[ playerid ] [ 0 ], p_LastPickupPos[ playerid ] [ 1 ], p_LastPickupPos[ playerid ] [ 2 ] );

			//if ( distance < 50.0 ) printf( "[AC WARN] Player ID %d has entered a pickup near him really fast. (distance: %0.2fm, time: %ds)", playerid, distance, LastPickupTimestamp[ playerid ] - iTimestamp );
			if ( distance > 50.0 )
			{
				CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_PICKUP_SPAM, 0 );
				return 0;
			}
		}
		LastPickupTimestamp[ playerid ] = iTimestamp + 1;
		PreviousPickupID[ playerid ] = pickupid;
	}
	GetPlayerPos( playerid, p_LastPickupPos[ playerid ] [ 0 ], p_LastPickupPos[ playerid ] [ 1 ], p_LastPickupPos[ playerid ] [ 2 ] );
	return 1;
}
