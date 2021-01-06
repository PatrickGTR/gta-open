#define DIALOG_PERKS 69

enum
    E_PERKS_DATA
    {
        E_NAME[32],     E_PURPOSE[64],
        E_COST
    }
;

static
    gPerkData[][E_PERKS_DATA] =
    {
        {"Repair Vehicle", "Restores a vehicle's health to 1000", 5000},
        {"Flip Vehicle", "Flips a vehicle back to wheels if it's backflipped", 1000},
        {"Add NOS", "Adds a NOS to vehicle", 4000}
    }
;

CMD:perks(playerid, params[])
{
    if(!IsPlayerInAnyVehicle(playerid))
        return SendErrorMsg(playerid, "You must be in a vehicle to use this command.");

    new 
        perksStr[256]
    ;

    for(new i = 0; i < sizeof(gPerkData); i++)
        format(perksStr, sizeof perksStr, "%s%s\t%s\t{FFDC2E}$%d\n", perksStr, gPerkData[i][E_NAME], gPerkData[i][E_PURPOSE], gPerkData[i][E_COST]);

    format(perksStr, sizeof perksStr, "{FFFFFF}Perk\t{FFFFFF}Purpose\t{FFFFFF}Cost\n%s", perksStr);

    ShowPlayerDialog(playerid, DIALOG_PERKS, DIALOG_STYLE_TABLIST_HEADERS, "Player Perks", perksStr, "Choose", "Close");
    return 1;    
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_PERKS)
    {
        new 
            vehicleid = GetPlayerVehicleID(playerid)
        ;

        switch (listitem)
        {
            case 0: // Repair vehicle
            {
                if(!IsPlayerInAnyVehicle(playerid)) // Somehow left vehicle?
                    return SendErrorMsg(playerid, "You must be in a vehicle to use this feature.");

                RepairVehicle(vehicleid);

                SendMsgF(playerid, -1, "[VEH-FIX] You have fixed your vehicle for {FFDC2E}$%d", gPerkData[listitem][E_COST]);
            }
            case 1: // Flip vehicle
            {
                if(!IsPlayerInAnyVehicle(playerid)) // Somehow left vehicle?
                    return SendErrorMsg(playerid, "You must be in a vehicle to use this feature.");

                new
                    Float:VehZAngle
                ;

                GetVehicleZAngle(vehicleid, VehZAngle);
                SetVehicleZAngle(vehicleid, VehZAngle);

                SendMsgF(playerid, -1,  "[VEH-FLIP] You have flipped your vehicle for {FFDC2E}$%d", gPerkData[listitem][E_COST]);
            }
            case 2: // Add NOS
            {
                if(!IsPlayerInAnyVehicle(playerid)) // Somehow left vehicle?
                    return SendErrorMsg(playerid, "You must be in a vehicle to use this feature.");

                AddVehicleComponent(vehicleid, 1010);

                SendMsgF(playerid, -1, "[VEH-NOS] You have installed NOS your vehicle for {FFDC2E}$%d", gPerkData[listitem][E_COST]);
            }
        }
    }
    return 1;
}
