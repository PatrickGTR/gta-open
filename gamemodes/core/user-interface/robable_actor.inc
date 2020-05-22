/*
	[DECLARATIONS]
*/

#if !defined _samp_included
	#error Please include a_samp before actor_robbery.
#endif

#if !defined KEY_AIM
	#define KEY_AIM  128
#endif

#if !defined PreloadAnimLib
	#define PreloadAnimLib(%1,%2) ApplyAnimation(%1,%2,"null",0.0,0,0,0,0,0)
#endif

#define MAX_ROBBERY_ACTORS		(50)

#define TYPE_SUCCESS        (0)
#define TYPE_FAILED         (1)
#define TYPE_UNFINISHED     (2)

#define MIN_MONEY_ROB       500
#define MAX_MONEY_ROB       10000
#define ROBBERY_WAIT_TIME   (5)

enum E_ACTOR_ROBBERY_DATA
{
	actor_skin,
	Float:actor_x,
	Float:actor_y,
	Float:actor_z,
	Float:actor_ang,
	actor_vw,
	money_min,
	money_max,

	bool:actor_created,
	actor_robbedRecently
}
static 
	robbery_data[MAX_ROBBERY_ACTORS][E_ACTOR_ROBBERY_DATA],
	i_actor = 0;

forward RunActorAnimationSequence(playerid, actorid, animation_pattern);
forward OnPlayerStartRobbery(playerid, actorid, robbed_recently);
forward OnPlayerFinishRobbery(playerid, actorid, robbedmoney, type);

/*
	Function:
		CreateActorRobbery
	Info:
		Creates the robbery actor according to the position set.
	Param:
	* skinid -> Skin ID of the robbery actor
	* Float:x -> Coordinate X of the robbery actor
	* Float:y -> Coordinate X of the robbery actor
	* Float:z -> Coordinate X of the robbery actor
	* Float:ang -> Facing angle of the robbery actor
	* actor_vwid -> virtualid of the robbery actor
	* r_moneymin -> Minimum money to be robbed from the robbery actor
	* r_moneymax -> Maximum money to be robbed from the robbery actor
*/



#pragma deprecated GetActorRobberyData
stock GetActorRobberyData(actorid, &skinid, &Float:x, &Float:y, &Float:z, &Float:ang, &actor_vwid, &r_moneymin, &r_moneymax) {
	#pragma unused actorid, skinid, x, y, z, ang, actor_vwid, r_moneymin, r_moneymax
}

#pragma deprecated Please use new function name Robbery_CreateActor.
stock CreateActorRobbery(skinid, Float:x, Float:y, Float:z, Float:ang, actor_vwid = 0, r_moneymin = MIN_MONEY_ROB, r_moneymax = MAX_MONEY_ROB) {
	#pragma unused skinid, x, y, z, ang, actor_vwid, r_moneymin, r_moneymax
	return -1;
}

stock Robbery_CreateActor(skinid, Float:x, Float:y, Float:z, Float:ang, actor_vwid = 0, r_moneymin = MIN_MONEY_ROB, r_moneymax = MAX_MONEY_ROB) {
	new actorid = GetActorFreeID();

	if(actorid == -1) {
		print("ERROR: Robbery_CreateActor - MAX_ROBBERY_ACTOR reached, increase the limit size.");
		return -1;
	}

	CreateActor(skinid, x, y, z, ang);
	SetActorVirtualWorld(actorid, actor_vwid);

	robbery_data[actorid][actor_created] = true;
	robbery_data[actorid][actor_skin] = skinid;
	robbery_data[actorid][actor_x] = x;
	robbery_data[actorid][actor_y] = y;
	robbery_data[actorid][actor_z] = z;
	robbery_data[actorid][actor_ang] = ang;
	robbery_data[actorid][actor_vw] = actor_vwid;
	robbery_data[actorid][money_min] = r_moneymin;
	robbery_data[actorid][money_max] = r_moneymax;

	return (i_actor ++); 
}

/*
	Function:
		Robbery_GetActorData
	Info:
		Retrieves the actor data
	Param:
		* actorid -> ID of robbery actor you want to retrieve data from. 
		* &skinid -> Skin ID of the robbery actor
		* &Float:x -> Coordinate X of the robbery actor
		* &Float:y -> Coordinate X of the robbery actor
		* &Float:z -> Coordinate X of the robbery actor
		* &Float:ang -> Facing angle of the robbery actor
		* &actor_vwid -> virtualid of the robbery actor
		* &r_moneymin -> Minimum money to be robbed from the robbery actor
		* &r_moneymax -> Maximum money to be robbed from the robbery actor
*/

stock Robbery_GetActorData(actorid, &skinid, &Float:x, &Float:y, &Float:z, &Float:ang, &actor_vwid, &r_moneymin, &r_moneymax) {
	if(actorid == INVALID_ACTOR_ID) {	
		print("ERROR: GetActorRobberyData - Invalid actorid input.");
		return 1;
	}

	skinid = robbery_data[actorid][actor_skin];
	x = robbery_data[actorid][actor_x];
	y = robbery_data[actorid][actor_y];
	z = robbery_data[actorid][actor_z] ;
	ang = robbery_data[actorid][actor_ang] ;
	actor_vwid = robbery_data[actorid][actor_vw];
	r_moneymin = robbery_data[actorid][money_min];
	r_moneymax = robbery_data[actorid][money_max];
	return 1;
}

/*
Function: 
	GetActorFreeID
Info:	
	Retrieves the unused ID of an actor.
Param:
	None
*/

static stock GetActorFreeID() 
{
	for(new i = 0; i < MAX_ROBBERY_ACTORS; i++)  { 
		if(!robbery_data[i][actor_created]) {
			return i;
		}
	}
	return -1;
}

/*
	Robbery IMPL
*/

public RunActorAnimationSequence(playerid, actorid, animation_pattern) {
	switch(animation_pattern) {
		case 0: {
			ClearActorAnimations(actorid);
			ApplyActorAnimation(actorid, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 0);
		
			SetTimerEx("RunActorAnimationSequence", 1000 * ROBBERY_WAIT_TIME, false, "iii", playerid, actorid, 1);
		
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
		
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++) {
				if(!IsPlayerConnected(i)) { 
					continue; 
				}
				PlayerPlaySound(i, 3401, x, y, z);
			}
		}
		case 1: {
			if(!IsPlayerInRangeOfPoint(playerid, 10.0, robbery_data[actorid][actor_x], robbery_data[actorid][actor_y], robbery_data[actorid][actor_z])) {
				CallLocalFunction("OnPlayerFinishRobbery", "iiii", playerid, actorid, 0, TYPE_UNFINISHED);
			}
			else {
				ClearActorAnimations(actorid);
				ApplyActorAnimation(actorid, "SHOP", "SHP_Rob_GiveCash", 4.1, 0, 1, 1, 1, 0);
			
				SetTimerEx("RunActorAnimationSequence", 1000 * ROBBERY_WAIT_TIME, false, "iii", playerid, actorid, 2);
			}
		}
		case 2: {
			ClearActorAnimations(actorid);
			ApplyActorAnimation(actorid, "PED", "DUCK_cower", 4.1, 1, 1, 1, 1, 1);
		
			SetTimerEx("RunActorAnimationSequence", 1000 * 60 * ROBBERY_WAIT_TIME, false, "iii", playerid, actorid, 3);
		
			new robberyChance = random(100);
			if(robberyChance > 40) {
				CallLocalFunction("OnPlayerFinishRobbery", "iiii", playerid, actorid, (random(robbery_data[actorid][money_max] - robbery_data[actorid][money_min]) + robbery_data[actorid][money_min]), TYPE_SUCCESS);
			}
			else {
				CallLocalFunction("OnPlayerFinishRobbery", "iiii", playerid, actorid, 0, TYPE_FAILED);
			}
		}
		case 3: {
			ClearActorAnimations(actorid);
			PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
		}
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
	EnablePlayerCameraTarget(playerid, 1);

	PreloadAnimLib(playerid, "PED");
	PreloadAnimLib(playerid, "SHOP");

	#if defined actorrob_OnPlayerConnect
		return actorrob_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_AIM) == KEY_AIM && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		switch(GetPlayerWeapon(playerid))
		{
			case 22 .. 33: 
			{
				new actorid = GetPlayerCameraTargetActor(playerid);

				if(actorid == INVALID_ACTOR_ID) {
					return 1;
				}

				if(gettime() - robbery_data[actorid][actor_robbedRecently] < 60 * ROBBERY_WAIT_TIME) {
					return CallLocalFunction("OnPlayerStartRobbery", "iii", playerid, actorid, 1);
				}

				robbery_data[actorid][actor_robbedRecently] = gettime();
				RunActorAnimationSequence(playerid, actorid, 0);
			}
		}
	}
   	#if defined actorrob_OnPlayerKeyStateChange
		return actorrob_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else 
   		return 1;
	#endif
}

//OnPlayerKeyStateChange hook directives

#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyState
#endif

#define OnPlayerKeyStateChange actorrob_OnPlayerKeyStateChange

#if defined actorrob_OnPlayerKeyStateChange
    forward actorrob_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

//OnPlayerConnect directives

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect actorrob_OnPlayerConnect
#if defined actorrob_OnPlayerConnect
    forward actorrob_OnPlayerConnect(playerid);
#endif