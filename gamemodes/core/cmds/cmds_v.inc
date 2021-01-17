#include <YSI_Coding\y_hooks>

CMD:v(playerid, params[])
{
	if(isnull(params))
		return SendSyntaxMsg(playerid, "/v [options: park | lock]");

	if(!strcmp(params, "park"))
	{
		if(!Vehicle_IsOwner(playerid))
			return SendErrorMsg(playerid, "You must be in one of your personal vehicle");

		Vehicle_Park(playerid);
		SendServerMsg(playerid, "Vehicle parked, position saved!");
	}
	if(!strcmp(params, "lock")) {
		new
			vehicleid = GetNearestVehicle(playerid);

		if(vehicle == INVALID_VEHICLE_ID) {
			return SendErrorMsg(playerid, "No nearby vehicles");
		}

		if(!Vehicle_IsOwner(playerid, vehicleid))
			return SendErrorMsg(playerid, "You must be near one of your personal vehicle");

		new
    		engine, lights, alarm, doors, bonnet, boot, objective;
		foreach(new i : PersonalVehicle) {
			if(vehicleid != Vehicle_GetHandler(i)) {
				continue;
			}

			GetVehicleParamsEx(Vehicle_GetHandler(i), engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(Vehicle_GetHandler(i), engine, lights, alarm, (doors) ? (0) : (1), bonnet, boot, objective);
			break;
		}
		SendMsgF(playerid, COLOR_SAMPBLUE, "Vehicle %s", (doors) ? ("Locked") : ("Unlocked"));
	}

	return 1;
}