#include <YSI_Coding\y_hooks>

static enum E_DETECTIONS
{
    E_ARMOUR,
    E_HEALTH,
    E_WEAPON,
    E_AIRBREAK,
    E_PROAIM,
    E_AUTOCBUG,
    E_FLYHACKS
};

static
    gPlayerACDetections[MAX_PLAYERS][E_DETECTIONS]
;

public OnPlayerCheatDetected( playerid, detection, params )
{
    SendAnticheatMsgF("%p (%d) is might be using %d", playerid, playerid, AC_DetectedCheatToString(detection));
    switch(detection)
    {
        case CHEAT_TYPE_ARMOUR: gPlayerACDetections[playerid][E_ARMOUR]++;
        case CHEAT_TYPE_HEALTH: gPlayerACDetections[playerid][E_HEALTH]++;
        case CHEAT_TYPE_WEAPON: gPlayerACDetections[playerid][E_WEAPON]++;
        case CHEAT_TYPE_AIRBRAKE: gPlayerACDetections[playerid][E_AIRBREAK]++;
        case CHEAT_TYPE_PROAIM: gPlayerACDetections[playerid][E_PROAIM]++;
        case CHEAT_TYPE_AUTOCBUG: gPlayerACDetections[playerid][E_AUTOCBUG]++;
        case CHEAT_TYPE_FLYHACKS: gPlayerACDetections[playerid][E_FLYHACKS]++;
    }
    return 1;
}

hook OnPlayerSecondUpdate(playerid)
{
    for(new E_DETECTIONS:i; i < E_DETECTIONS:7; i++) {
        if(gPlayerACDetections[playerid][i] >= AC_MAX_DETECTIONS)
        {
            SendMsgAllF(COLOR_MODERATION, "[ANTI-CHEAT]: %p (%d) has been automaticaly kicked for %s ", playerid, playerid, AC_GetCheatTypeFromID(i));
            SendMsgF(playerid, COLOR_MODERATION, "[ANTI-CHEAT]: You have automatically been kicked for %s", AC_GetCheatTypeFromID(i));
            defer KickTimer(playerid);
            break;
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    for(new E_DETECTIONS:i; i < E_DETECTIONS:7; i++) {
        gPlayerACDetections[playerid][i] = 0;
    }
    return 1;
}

ACMD:[1]cheats(playerid, params[])
{
    new targetid;
    if(sscanf(params, "u", targetid)) return SendSyntaxMsg(playerid, "/cheats (name/id)");
    new tmpStr[128];
    TextInfo_Create(playerid, "PCHEATS", "Total Cheats");
    format(tmpStr, sizeof tmpStr, "Armour Hacks: %d", gPlayerACDetections[targetid][E_ARMOUR]);
    TextInfo_Add(playerid, tmpStr);
    format(tmpStr, sizeof tmpStr, "Health Hacks: %d", gPlayerACDetections[targetid][E_HEALTH]);
    TextInfo_Add(playerid, tmpStr);
    format(tmpStr, sizeof tmpStr, "Weapon Hacks: %d", gPlayerACDetections[targetid][E_WEAPON]);
    TextInfo_Add(playerid, tmpStr);
    format(tmpStr, sizeof tmpStr, "Airbreak Hacks: %d", gPlayerACDetections[targetid][E_AIRBREAK]);
    TextInfo_Add(playerid, tmpStr);
    format(tmpStr, sizeof tmpStr, "Proaim Hacks: %d", gPlayerACDetections[targetid][E_PROAIM]);
    TextInfo_Add(playerid, tmpStr);
    format(tmpStr, sizeof tmpStr, "AutoCBUG Hacks: %d", gPlayerACDetections[targetid][E_AUTOCBUG]);
    TextInfo_Add(playerid, tmpStr);
    format(tmpStr, sizeof tmpStr, "Flyhacks Hacks: %d", gPlayerACDetections[targetid][E_FLYHACKS]);
    TextInfo_Add(playerid, tmpStr);
    TextInfo_Show(playerid);
    return 1;
}

static AC_GetCheatTypeFromID(E_DETECTIONS:id) {
    new szString[ 16 ] = "unknown";
    switch(id) {
        case E_ARMOUR: szString = "Armour Hacks";
        case E_HEALTH: szString = "Health Hacks";
        case E_WEAPON: szString = "Weapon Hacks";
        case E_AIRBREAK: szString = "Airbreak";
        case E_PROAIM: szString = "Silent Aimbot";
        case E_FLYHACKS: szString = "Fly Hacks";
    }
    return szString;
}