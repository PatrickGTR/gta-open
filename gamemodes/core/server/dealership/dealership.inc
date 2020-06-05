#include <dealership_vehicles-data>

static
	plyCurrentChoice[MAX_PLAYERS];

CMD:dealership(playerid, params[]) {

    UI_ShowDealershipUI(playerid);
    return 1;
}

UI_ShowDealershipUI(playerid)
{

	plyCurrentChoice[playerid] =  0;

	new index = plyCurrentChoice[playerid];

	UI_ShowDealershipTextDraw(playerid);

	UI_SetDealershipVehicleHeader(playerid, Dealership_GetVehicleModel(index));
    UI_SetDealershipVehiclePrice(playerid, Dealership_GetVehiclePrice(index));
    UI_SetDealershipVehicleModel(playerid, Dealership_GetVehicleModel(index));
}

public OnPlayerClickDealershipTextdraw(playerid, type)
{
	new
		index = 0;
	// FIX -> OOB Issue
	if(type == BTN_RIGHT)
	{
		index = plyCurrentChoice[playerid];

		if(index >= Dealership_GetArraySize())
			return 0;

		index ++;

		UI_SetDealershipVehicleHeader(playerid, Dealership_GetVehicleModel(index));
		UI_SetDealershipVehiclePrice(playerid, Dealership_GetVehiclePrice(index));
		UI_SetDealershipVehicleModel(playerid, Dealership_GetVehicleModel(index));

		plyCurrentChoice[playerid] = index;
	}
	else if(type == BTN_LEFT)
	{

		index = plyCurrentChoice[playerid];

		if(index <= 0)
			return 0;


		index --;

        UI_SetDealershipVehicleHeader(playerid, Dealership_GetVehicleModel(index));
		UI_SetDealershipVehiclePrice(playerid, Dealership_GetVehiclePrice(index));
		UI_SetDealershipVehicleModel(playerid, Dealership_GetVehicleModel(index));

		plyCurrentChoice[playerid] = index;
	}
	else if(type == BTN_PURCHASE)
	{
		index = plyCurrentChoice[playerid];

		if (GetPlayerMoney(playerid) < Dealership_GetVehiclePrice(index))
			return SendErrorMsg(playerid, "You don't have enough money to buy this vehicle!");
	}
	else if(type == BTN_CLOSE)
	{
		SendServerMsg(playerid, "You have closed the dealership menu.");
		plyCurrentChoice[playerid] = -1;
	}
	return 1;
}