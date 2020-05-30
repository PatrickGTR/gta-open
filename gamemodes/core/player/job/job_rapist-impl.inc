static 
    Timer:PlayerDiseaseTimer[MAX_PLAYERS],
    DiseaseType[MAX_PLAYERS];

enum {
    DISEASE_NONE = 0,
    DISEASE_GONORRHEA,
    DISEASE_HIV,
    DISEASE_AIDS,
    DISEASE_CHLAMYDIA,
    DISEASE_HERPES
}

Disease_PlayerHas(playerid) 
{
    return (DiseaseType[playerid] > 0);
}

Disease_GivePlayer(playerid, type)
{
    switch(type)
    {
        case DISEASE_NONE: {
            DiseaseType[playerid] = DISEASE_NONE;
            stop PlayerDiseaseTimer[playerid];
        }
        case DISEASE_GONORRHEA: DiseaseType[playerid] = DISEASE_GONORRHEA;
        case DISEASE_HIV: DiseaseType[playerid] = DISEASE_HIV;
        case DISEASE_AIDS: DiseaseType[playerid] = DISEASE_AIDS;
        case DISEASE_CHLAMYDIA: DiseaseType[playerid] = DISEASE_CHLAMYDIA;
        case DISEASE_HERPES: DiseaseType[playerid] = DISEASE_HERPES;
        default: DiseaseType[playerid] = DISEASE_NONE;
    }
    PlayerDiseaseTimer[playerid] = repeat UpdatePlayerDiseaseDamage(playerid);
    return true;
}

Disease_GetName(playerid) {
    new 
        diseaseName[10];
    switch(DiseaseType[playerid])
    {
        case DISEASE_NONE:  {
            strcpy(diseaseName, "None");
        }
        case DISEASE_GONORRHEA: {
            strcpy(diseaseName, "Gonorrhea");
        }
        case DISEASE_HIV: {
			strcpy(diseaseName, "HIV"); 
		}
        case DISEASE_AIDS: {
			strcpy(diseaseName, "AIDS");
		}
        case DISEASE_CHLAMYDIA: {
			strcpy(diseaseName, "Chlamydia");
		}
        case DISEASE_HERPES: {
		 	strcpy(diseaseName, "Herpes");
		}
    }
    return diseaseName;
}

Float:Disease_GetDamage(type)
{
    switch(type)
    {
        case DISEASE_NONE: return 0.0;
        case DISEASE_GONORRHEA: return 0.5;
        case DISEASE_HIV: return 0.8;
        case DISEASE_AIDS: return 1.0;
        case DISEASE_CHLAMYDIA: return 0.7;
        case DISEASE_HERPES: return 0.1;
    }
    return 0.0;
}

timer UpdatePlayerDiseaseDamage[1000 * 5](playerid)
{
    if (Disease_PlayerHas(playerid))
    {
        new 
			Float:ply_health;

        GetPlayerHealth(playerid, ply_health);
        SetPlayerHealth(playerid, ply_health - Disease_GetDamage(DiseaseType[playerid]));
    }
}

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
	Disease_GivePlayer(playerid, DISEASE_NONE);
	return 1;	
}

hook OnPlayerDeathEx(playerid, killerid, reason, Float: damage, bodypart)
{
    if (Disease_PlayerHas(playerid) && killerid == INVALID_PLAYER_ID)
    {
        SendMsgAllF(COLOR_LIGHTGREEN, "** RAPE DEATH **: "C_GREY"%p (%i) "C_WHITE"died because of "C_LGREEN"%s.", playerid, playerid, Disease_GetName(playerid));
        Disease_GivePlayer(playerid, DISEASE_NONE);

        stop PlayerDiseaseTimer[playerid];
    }
	return 1;
}
