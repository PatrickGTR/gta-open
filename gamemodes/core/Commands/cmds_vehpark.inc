CMD:v(playerid, params[])
{
	if(isnull(params))
		return SendSyntaxMsg(playerid, "/v [options: park]");

	if(!strcmp(params, "park"))
	{
		if(!IsPlayerInPersonalVehicle(playerid))
			return SendErrorMsg(playerid, "You must be in one of your personal vehicle to use "C_GREY"/v park");

		Vehicle_Park(playerid);
		SendServerMsg(playerid, "Vehicle parked, position saved!");
	}
	return 1;
}