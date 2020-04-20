/*
	valstr fix
	Thanks to slice.
*/
stock FIX_valstr(dest[], value, bool:pack = false)
{
    // format can't handle cellmin properly
    static const cellmin_value[] = !"-2147483648";
 
    if (value == cellmin)
        pack && strpack(dest, cellmin_value, 12) || strunpack(dest, cellmin_value, 12);
    else
        format(dest, 12, "%d", value), pack && strpack(dest, dest, 12);
}
#define valstr FIX_valstr


/*
	Kick & Ban fix
*/
#define Kick(%0) SetTimerEx("kickfix", 40, false, "d", %0)
#define Ban(%0) SetTimerEx("banfix", 50, false, "d", %0)

native KickxTimer(playerid) = Kick;
native BanxTimer(playerid) = Ban;
 

forward kickfix(playerid); public kickfix(playerid)
{
    KickxTimer(playerid);
}
 
forward banfix(playerid); public banfix(playerid){
    BanxTimer(playerid);
}

/* 
	Player attachments fix
*/

#if !defined KEY_AIM
	#define KEY_AIM 128
#endif

enum E_PLAYER_ATTACHMENT
{
	bool:E_PLAYER_ATTACHMENT_USED,
 	E_PLAYER_ATTACHMENT_MODEL,
    E_PLAYER_ATTACHMENT_BONE,
    Float:E_PLAYER_ATTACHMENT_X,
   	Float:E_PLAYER_ATTACHMENT_Y,
   	Float:E_PLAYER_ATTACHMENT_Z,
   	Float:E_PLAYER_ATTACHMENT_RX,
   	Float:E_PLAYER_ATTACHMENT_RY,
   	Float:E_PLAYER_ATTACHMENT_RZ,
   	Float:E_PLAYER_ATTACHMENT_SX,
   	Float:E_PLAYER_ATTACHMENT_SY,
   	Float:E_PLAYER_ATTACHMENT_SZ,
	E_PLAYER_ATTACHMENT_COLOR1,
	E_PLAYER_ATTACHMENT_COLOR2
};
static playerAttachment[MAX_PLAYERS][MAX_PLAYER_ATTACHED_OBJECTS][E_PLAYER_ATTACHMENT];

public OnPlayerConnect(playerid)
{
    for (new i; i < MAX_PLAYER_ATTACHED_OBJECTS; i++)
    {
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_USED] = false;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_MODEL] = 0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_BONE] = 0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_X] = 0.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_Y] = 0.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_Z] = 0.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_RX] = 0.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_RY] = 0.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_RZ] = 0.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_SX] = 1.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_SY] = 1.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_SZ] = 1.0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_COLOR1] = 0;
   	 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_COLOR2] = 0;
	}

	#if defined ATT_OnPlayerConnect
		return ATT_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect ATT_OnPlayerConnect
#if defined ATT_OnPlayerConnect
	forward ATT_OnPlayerConnect(playerid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if ((newkeys & KEY_AIM) == KEY_AIM)
		{
		    switch (GetPlayerWeapon(playerid))
			{
				case WEAPON_SNIPER, WEAPON_ROCKETLAUNCHER, WEAPON_HEATSEEKER, WEAPON_CAMERA:
				{
				    for (new i; i < MAX_PLAYER_ATTACHED_OBJECTS; i++)
					{
						if (IsPlayerAttachedObjectSlotUsed(playerid, i))
						{
					    	RemovePlayerAttachedObject(playerid, i);
						}
			        }
			    }
			}
		}
		else if ((newkeys & KEY_AIM) != KEY_AIM && (oldkeys & KEY_AIM) == KEY_AIM)
		{
		    for (new i; i < MAX_PLAYER_ATTACHED_OBJECTS; i++)
			{
				if (!IsPlayerAttachedObjectSlotUsed(playerid, i) && playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_USED])
			    {
					SetPlayerAttachedObject(playerid, i,
						playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_MODEL],
						playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_BONE],
						playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_X], playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_Y], playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_Z],
				 		playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_RX], playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_RY], playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_RZ],
					 	playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_SX], playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_SY], playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_SZ],
						playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_COLOR1],
						playerAttachment[playerid][i][E_PLAYER_ATTACHMENT_COLOR2]);
				}
			}
		}
	}

	#if defined ATT_OnPlayerKeyStateChange
       	return ATT_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange ATT_OnPlayerKeyStateChange
#if defined ATT_OnPlayerKeyStateChange
    forward ATT_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock ATT_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0)
{
    new ret = SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2);
    if (ret)
	{
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_USED] = true;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_MODEL] = modelid;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_BONE] = bone;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_X] = fOffsetX;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_Y] = fOffsetY;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_Z] = fOffsetZ;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_RX] = fRotX;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_RY] = fRotY;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_RZ] = fRotZ;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_SX] = fScaleX;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_SY] = fScaleY;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_SZ] = fScaleZ;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_COLOR1] = materialcolor1;
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_COLOR2] = materialcolor2;
	}
	return ret;
}
#if defined _ALS_SetPlayerAttachedObject
    #undef SetPlayerAttachedObject
#else
	#define _ALS_SetPlayerAttachedObject
#endif
#define SetPlayerAttachedObject ATT_SetPlayerAttachedObject

stock ATT_RemovePlayerAttachedObject(playerid, index)
{
   	new ret = RemovePlayerAttachedObject(playerid, index);
   	if (ret)
	{
		playerAttachment[playerid][index][E_PLAYER_ATTACHMENT_USED] = false;
	}
	return ret;
}
#if defined _ALS_RemovePlayerAttachedObject
    #undef RemovePlayerAttachedObject
#else
    #define _ALS_RemovePlayerAttachedObject
#endif
#define RemovePlayerAttachedObject ATT_RemovePlayerAttachedObject