/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat/proaim.pwn
 * Purpose: silent aimbot detection
 */

/* ** Macros ** */
#define ac_GetDistanceBetweenPoints(%0,%1,%2,%3,%4,%6) \
	(VectorSize(%0-%3,%1-%4,%2-%6))

/* ** Variables ** */
static stock
    p_silentAimbotLastCalled 		[ MAX_PLAYERS ]
;

/* ** Functions ** */
stock AC_CheckForSilentAimbot( playerid, hittype, hitid )
{
    static
    	Float: fVictimX, Float: fVictimY, Float: fVictimZ,
		Float: fCameraX, Float: fCameraY, Float: fCameraZ,
		Float: fVectorX, Float: fVectorY, Float: fVectorZ,
        Float: fHitPosX, Float: fHitPosY, Float: fHitPosZ
   	;

    if( hittype == BULLET_HIT_TYPE_PLAYER && IsPlayerConnected( hitid ) && ! IsPlayerNPC( hitid ) )
    {
	   	GetPlayerPos( hitid, fVictimX, fVictimY, fVictimZ );
		GetPlayerCameraPos( playerid, fCameraX, fCameraY, fCameraZ );
		GetPlayerCameraFrontVector( playerid, fVectorX, fVectorY, fVectorZ );
	    GetPlayerLastShotVectors( playerid, fHitPosX, fHitPosY, fHitPosZ, fHitPosX, fHitPosY, fHitPosZ );

	    //printf("%f = %f, %f = %f, %f = %f\n", fX + fVictimX, fHitPosX, fY + fVictimY, fHitPosY, fZ + fVictimZ, fHitPosZ );

	    fCameraX += 4.0 * fVectorX;
	    fCameraY += 4.0 * fVectorY;
	    fCameraZ += 4.0 * fVectorZ;

	    new Float: fCamera = 	ac_GetDistanceBetweenPoints( fHitPosX, fHitPosY, fHitPosZ, fCameraX, fCameraY, fCameraZ );
	    new Float: fRadius = 	ac_GetDistanceBetweenPoints( fHitPosX, fHitPosY, fHitPosZ, fVictimX, fVictimY, fVictimZ );
	    new Float: fPlayerDis = GetPlayerDistanceFromPoint( playerid, fVictimX, fVictimY, fVictimZ );

        if( GetPlayerSurfingVehicleID( playerid ) == INVALID_VEHICLE_ID && GetPlayerSurfingVehicleID( hitid ) == INVALID_VEHICLE_ID && !IsPlayerInAnyVehicle( hitid ) )
        {
            new
				Float: fHitPacketLoss = NetStats_PacketLossPercent( hitid ),
				Float: fOwnPacketLoss = NetStats_PacketLossPercent( playerid ),
				iLastUpdateInterval   = GetTickCount( ) - AC_GetLastUpdateTime( hitid ) // AFK Check
			;

		    if( fCamera < 1.20 && fPlayerDis > 4.0 && fPlayerDis < 300.0 && fRadius > 4.0 && fOwnPacketLoss < 0.8 && fHitPacketLoss < 0.8 && iLastUpdateInterval < 3000 ) {
		    	new
		    		iTicks = GetTickCount( );

		    	if( iTicks - p_silentAimbotLastCalled[ playerid ] <= 5000 ) {
		    		printf("[PRO-AIM] Detected %d - last %dms", playerid, iTicks - p_silentAimbotLastCalled[ playerid ]);
					CallLocalFunction( "OnPlayerCheatDetected", "ddd", playerid, CHEAT_TYPE_PROAIM, 0 );
		    	}

				p_silentAimbotLastCalled[ playerid ] = iTicks;
		    }
	    }
    }
}
