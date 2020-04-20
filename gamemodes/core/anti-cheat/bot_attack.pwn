/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat\bot_attack.pwn
 * Purpose: mitigates bot attacks with random IP addresses
 */

/* ** Includes ** */
#include 							< YSI\y_hooks >

/* ** Constants ** */
static const BOT_ATTACK_BLOCK_TIME = 120000; // 2 minutes

/* ** Variables ** */
static stock botattack_ServerInitTS = 0;
static stock botattack_LastConnection = 0;
static stock botattack_ConnectionSpamCount = 0;

/* ** Hooks ** */
hook OnScriptInit( )
{
	botattack_ServerInitTS = gettime( );
	return 1;
}

hook OnIncomingConnection( playerid, ip_address[ ], port )
{
	// block id if invalid player ID ... otherwise our bots go
	if ( ! ( 0 <= playerid < MAX_PLAYERS ) ) {
		BlockIpAddress( ip_address, BOT_ATTACK_BLOCK_TIME );
	}

	new
		current_time = gettime( );

	// script will only work if the server is online for more than 5 minutes
	if ( current_time - botattack_ServerInitTS >= 300 )
	{
		// if the last connection was within 2 seconds
		if ( current_time - botattack_LastConnection <= 2 )
		{
			// and we had more than 5 connections in this interval
			if ( ++ botattack_ConnectionSpamCount >= 5 )
			{
				BlockIpAddress( ip_address, BOT_ATTACK_BLOCK_TIME );
				return 1;
			}
		}
		else
		{
			botattack_ConnectionSpamCount = 0;
		}

		botattack_LastConnection = current_time;
	}
	return 1;
}
