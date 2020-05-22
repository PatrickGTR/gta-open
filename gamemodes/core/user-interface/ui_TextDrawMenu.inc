/*

Textdraw Menu v1.1
Made by Jelly23

*/

#include <a_samp>

/*Textdraws & Variables*/
static PlayerText:J_TMenu[MAX_PLAYERS][2],
MenuID[MAX_PLAYERS],pHasItems[MAX_PLAYERS];

/*Response callback*/
forward OnTextMenuResponse(playerid,menuid,listitem);


public OnPlayerConnect(playerid)
{
	MenuID[playerid] = -1;
	pHasItems[playerid] = 0;
    J_TMenu[playerid][0] = CreatePlayerTextDraw(playerid, 143.249816, 130.266815, "Header");
	PlayerTextDrawLetterSize(playerid, J_TMenu[playerid][0], 0.541876, 1.489166);
	PlayerTextDrawAlignment(playerid, J_TMenu[playerid][0], 2);
	PlayerTextDrawColor(playerid, J_TMenu[playerid][0], COLOR_BLUE);
	PlayerTextDrawSetShadow(playerid, J_TMenu[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, J_TMenu[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, J_TMenu[playerid][0], 255);
	PlayerTextDrawFont(playerid, J_TMenu[playerid][0], 3);
	PlayerTextDrawSetProportional(playerid, J_TMenu[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, J_TMenu[playerid][0], 0);

	J_TMenu[playerid][1] = CreatePlayerTextDraw(playerid, 30.724655, 129.533676, "Content");
	PlayerTextDrawLetterSize(playerid, J_TMenu[playerid][1], 0.251874, 0.940833);
	PlayerTextDrawTextSize(playerid, J_TMenu[playerid][1], 266.977142, 0.000000);
	PlayerTextDrawAlignment(playerid, J_TMenu[playerid][1], 1);
	PlayerTextDrawColor(playerid, J_TMenu[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, J_TMenu[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, J_TMenu[playerid][1], 120);
	PlayerTextDrawSetShadow(playerid, J_TMenu[playerid][1], 1);
	PlayerTextDrawSetOutline(playerid, J_TMenu[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, J_TMenu[playerid][1], 255);
	PlayerTextDrawFont(playerid, J_TMenu[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, J_TMenu[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, J_TMenu[playerid][1], 1);
	#if defined J_OnPlayerConnect
	    return J_OnPlayerConnect(playerid);
	#else
	    return 1;
	#endif
}

public OnPlayerText(playerid, text[])
{
    if(MenuID[playerid] != -1)
    {
        if(pHasItems[playerid] != 0)
        {
            if(J_IsNumeric(text))
			{
			    if(strval(text) > 0 && strval(text) <= pHasItems[playerid])
			    {
					new var;
					var = MenuID[playerid];
					MenuID[playerid] = -1;
					pHasItems[playerid] = 0;
					PlayerTextDrawHide(playerid,J_TMenu[playerid][0]);
					PlayerTextDrawHide(playerid,J_TMenu[playerid][1]);
					
					OnTextMenuResponse(playerid,var,strval(text));
					return 0;
			    }
			}
        }
    }
    #if defined J_OnPlayerText
	    return J_OnPlayerText(playerid, text);
	#else
	    return 1;
	#endif
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
 	{
 	    if(MenuID[playerid] != -1)
 	    {
	  		if(newkeys == KEY_NO)
	    	{
				MenuID[playerid] = -1;
				pHasItems[playerid] = 0;
				PlayerTextDrawHide(playerid,J_TMenu[playerid][0]);
				PlayerTextDrawHide(playerid,J_TMenu[playerid][1]);
			}
		}
	}
    #if defined J_OnPlayerKeyStateChange
	    return J_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
	    return 1;
	#endif
}

static J_IsNumeric(const string[])
{
        for (new i = 0, j = strlen(string); i < j; i++)
        {
                if (string[i] > '9' || string[i] < '0') return 0;
        }
        return 1;
}
stock TextMenuShowForPlayer(playerid,menuid,const header[],content[],items=0)
{
	new J_Menustring[1028];
	MenuID[playerid] = menuid;
    PlayerTextDrawSetString(playerid, J_TMenu[playerid][0], header);
    if(items != 0)
    {
        pHasItems[playerid] = items;
    	format(J_Menustring, sizeof(J_Menustring), "~n~~n~~n~%s~n~~n~~w~___________Press_~y~T_~w~Or_~y~F6~w~_and_type_option_number~n~_________________Press_~y~N_~w~to_close_this_box~n~~n~", content);
	}
	else
	{
	    pHasItems[playerid] = 0;
        format(J_Menustring, sizeof(J_Menustring), "~n~~n~~n~%s~n~~n~~w~_________________Press_~y~N_~w~to_close_this_box~n~~n~", content);
	}
	PlayerTextDrawSetString(playerid, J_TMenu[playerid][1], J_Menustring);
	PlayerTextDrawShow(playerid,J_TMenu[playerid][0]);
	PlayerTextDrawShow(playerid,J_TMenu[playerid][1]);
}
stock TextMenuHideForPlayer(playerid)
{
	MenuID[playerid] = -1;
	pHasItems[playerid] = 0;
	PlayerTextDrawHide(playerid,J_TMenu[playerid][0]);
	PlayerTextDrawHide(playerid,J_TMenu[playerid][1]);
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect 	J_OnPlayerConnect

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange 	J_OnPlayerKeyStateChange

#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText 	J_OnPlayerText

#if defined J_OnPlayerText
	forward J_OnPlayerText(playerid, text[]);
#endif

#if defined J_OnPlayerConnect
	forward J_OnPlayerConnect(playerid);
#endif

#if defined J_OnPlayerKeyStateChange
	forward J_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif