#include <dealership_vehicles-data>

static
	plyCurrentChoice[MAX_PLAYERS];

#define SPAWN_AIRX 			(542.2044)
#define SPAWN_AIRY 			(-1299.0394)
#define SPAWN_AIRZ 			(32.7165)
#define SPAWN_AIRA 			(359.5135)

#define SPAWN_NORMALX  		(556.0718)
#define SPAWN_NORMALY  		(-1282.3813)
#define SPAWN_NORMALZ  		(16.8717)
#define SPAWN_NORMALA  		(0.0165)


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

		if (GetPlayerMoney(playerid) < Dealership_GetVehiclePrice(index)) {
			return SendErrorMsg(playerid, "You don't have enough money to buy this vehicle!");
		}

		if (Vehicle_GetPlayerTotal(playerid) >= MAX_VEHICLE_PER_PLAYER) {
			return SendErrorMsgF(playerid, "You have reached the limit of vehicles you can own. "C_GREY"LIMIT: %i", MAX_VEHICLE_PER_PLAYER);
		}

		if (Dealership_GetVehicleType(index) == TYPE_AIR)
		{
			Vehicle_Create(playerid, Dealership_GetVehicleModel(index), SPAWN_AIRX, SPAWN_AIRY, SPAWN_AIRZ, SPAWN_AIRA);
		}
		else
		{
			Vehicle_Create(playerid, Dealership_GetVehicleModel(index), SPAWN_NORMALX, SPAWN_NORMALY, SPAWN_NORMALZ, SPAWN_NORMALA);
		}

		UI_HideDealershipTextDraw(playerid);
		GivePlayerMoney(playerid, Dealership_GetVehiclePrice(index));
	}
	else if(type == BTN_CLOSE)
	{
		SendServerMsg(playerid, "You have closed the dealership menu.");
		plyCurrentChoice[playerid] = -1;
	}
	return 1;
}