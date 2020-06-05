#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>
#include <mysql_prepared>

static
    VehicleHandler[MAX_VEHICLES],
    VehicleOwnerID[MAX_VEHICLES],
    VehicleID[MAX_VEHICLES],
    VehicleModelID[MAX_VEHICLES],
    Float:VehicleX[MAX_VEHICLES],
    Float:VehicleY[MAX_VEHICLES],
    Float:VehicleZ[MAX_VEHICLES],
    Float:VehicleRot[MAX_VEHICLES],
    VehicleColor1[MAX_VEHICLES],
    VehicleColor2[MAX_VEHICLES],
    VehicleInteriorID[MAX_VEHICLES],
    VehicleVWorld[MAX_VEHICLES],
    VehicleMods[MAX_VEHICLES][14],
    VehiclePlate[MAX_VEHICLES][MAX_PLATE_NAME],
    BitArray:vehicle_created<MAX_VEHICLES>;

static
    Statement: stmt_insertVehicle,
    Statement: stmt_checkVehicle;


hook OnMySQLConnected() {

    static const insertQuery[] = "\
    INSERT INTO \
        player_vehicles (u_id, model_id, x, y, z, rot) \
    VALUES \
        (?, ?, ?, ?, ?, ?) \
    ";
    stmt_insertVehicle = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const selectQuery[] = "\
    SELECT \
        vehicle_id, \
        u_id, \
        model_id, \
        x, \
        y, \
        z, \
        rot, \
        color_1, \
        color_2, \
        intid, \
        vworld \
    FROM \
        player_vehicles \
    WHERE \
        u_id = ? \
    ORDER BY \
        vehicle_id DESC \
    ";
    stmt_checkVehicle = MySQL_PrepareStatement(MySQL_GetHandle(), selectQuery);

    return 1;
}

hook OnPlayerLogin(playerid) {

    inline const OnLoadCreatedVehicle() {

    new
        vehicleID,
        ownerID,
        modelID,
        Float:x,
        Float:y,
        Float:z,
        Float:rot,
        color_1,
        color_2,
        intID,
        VWorld;

    MySQL_BindResultInt(stmt_checkVehicle, 0, vehicleID);
    MySQL_BindResultInt(stmt_checkVehicle, 1, ownerID);
    MySQL_BindResultInt(stmt_checkVehicle, 2, modelID);
    MySQL_BindResultFloat(stmt_checkVehicle, 3, x);
    MySQL_BindResultFloat(stmt_checkVehicle, 4, y);
    MySQL_BindResultFloat(stmt_checkVehicle, 5, z);
    MySQL_BindResultFloat(stmt_checkVehicle, 6, rot);
    MySQL_BindResultInt(stmt_checkVehicle, 7, color_1);
    MySQL_BindResultInt(stmt_checkVehicle, 7, color_2);
    MySQL_BindResultInt(stmt_checkVehicle, 8, intID);
    MySQL_BindResultInt(stmt_checkVehicle, 9, VWorld);



    while(MySQL_Statement_FetchRow(stmt_checkVehicle)) {
            foreach(new i : Vehicle)
            {
                if(Bit_Get(vehicle_created, i)) {
                    // skip created vehicles in this API.
                    // we need a free id.
                    continue;
                }
                VehicleOwnerID[i] 	    = ownerID;
                VehicleID[i]	        = vehicleID;
                VehicleModelID[i]		= modelID;
                VehicleX[i]	            = x;
                VehicleY[i]	            = y;
                VehicleZ[i]	            = z;
                VehicleRot[i]		    = rot;

                // generate random colour.
                VehicleColor1[i]	    = color_1;
                VehicleColor2[i]	    = color_2;

                VehicleInteriorID[i]	= intID;
                VehicleVWorld[i]	    = VWorld;

                VehicleHandler[i] = CreateVehicle(modelID, x, y, z, rot, -1, -1, -1, 0);
                SetVehicleNumberPlate(VehicleHandler[i], VehiclePlate[i]);
                LinkVehicleToInterior(VehicleHandler[i], VehicleInteriorID[i]);
                SetVehicleVirtualWorld(VehicleHandler[i], VehicleVWorld[i]);
                ChangeVehicleColor(VehicleHandler[i], VehicleColor1[i], VehicleColor2[i]);

                printf("ownerid: %i - vehicleid", ownerID, vehicleID);
                printf("modelid: %i", modelID);
                printf("x %0.2f y %0.2f z %0.2f rot %0.2f", x, y, z, rot);
                printf("color 1 %i - color 2 %i", color_1, color_2);
                printf("interiorid %i - worldid %i", intID, VWorld);

                Bit_Let(vehicle_created, i);
                break;
                // mysql_tquery(sqlHandle,
                //     sprintf("SELECT "COMPONENT_VEHICLE_ID", "COMPONENT_VEHICLE_ID_FK", "COMPONENT_SLOT_ID" FROM "TABLE_VEHICLE_COMPONENT" WHERE "COMPONENT_VEHICLE_ID_FK" = %i", vehData[i][VEH_ID]), "OnLoadPlayerVehicleComponents", "i", i);
            }
        }
    }

    MySQL_BindInt(stmt_checkVehicle, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_checkVehicle, using inline OnLoadCreatedVehicle);
    return 1;
}

Vehicle_GetPlayerTotal(playerid) {

    new
        count = 0;

    foreach(new i : Vehicle) {

        if(!Bit_Get(vehicle_created, i))  {
            // skip vehicles that aren't created using this API.
            continue;
        }

        if(Player_GetAccountID(playerid) == VehicleOwnerID[i]) {
            count ++;
        }
    }
    return count;
}


Vehicle_Create(playerid, modelid, Float:x, Float:y, Float:z, Float:rot)
{
    inline const OnSaveCreatedVehicle() {
        foreach(new i : Vehicle) {
            if(Bit_Get(vehicle_created, i)) {
                // skip created vehicles in this API.
                // we need a free id.
                continue;
            }

            VehicleOwnerID[i] 	    = Player_GetAccountID(playerid);
            VehicleID[i]	        = cache_insert_id();
            VehicleModelID[i]		= modelid;
            VehicleX[i]	            = x;
            VehicleY[i]	            = y;
            VehicleZ[i]	            = z;
            VehicleRot[i]		    = rot;

            // generate random colour.
            VehicleColor1[i]	    = -1;
            VehicleColor2[i]	    = -1;

            VehicleInteriorID[i]	= 0;
            VehicleVWorld[i]	    = 0;

            for(new mod_id = 0; mod_id < 14; mod_id++) {
                VehicleMods[i][mod_id] = 0;
            }

            strcopy(VehiclePlate[i], "[AM]SFCNR");

            VehicleHandler[i] = CreateVehicle(modelid, x, y, z, rot, -1, -1, -1, 0);
            SetVehicleNumberPlate(VehicleHandler[i], VehiclePlate[i]);
            LinkVehicleToInterior(VehicleHandler[i], VehicleInteriorID[i]);
            SetVehicleVirtualWorld(VehicleHandler[i], VehicleVWorld[i]);
            ChangeVehicleColor(VehicleHandler[i], VehicleColor1[i], VehicleColor2[i]);

            defer PutPlayerInSaveVehicle(playerid, VehicleHandler[i]);

            Bit_Let(vehicle_created, i);
            break;

        }
    }

    MySQL_BindInt(stmt_insertVehicle, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_insertVehicle, 1, modelid);
    MySQL_BindFloat(stmt_insertVehicle, 2, x);
    MySQL_BindFloat(stmt_insertVehicle, 3, y);
    MySQL_BindFloat(stmt_insertVehicle, 4, z);
    MySQL_BindFloat(stmt_insertVehicle, 5, rot);
	MySQL_ExecuteThreaded_Inline(stmt_insertVehicle, using inline OnSaveCreatedVehicle);
}

timer PutPlayerInSaveVehicle[1000](playerid, vehicleid)
{
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	PutPlayerInVehicle(playerid, vehicleid, 0);
}

stock ParkVehicle(playerid, vehicleid)
{
	new
		Float: x,
		Float: y,
		Float: z,
		Float: a,
		qString[256];

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);

	mysql_format(sqlHandle, qString, sizeof(qString), "UPDATE "TABLE_PLAYER_VEHICLES" SET \
		"VEHICLE_POSX" = %0.4f, \
		"VEHICLE_POSY" = %0.4f, \
		"VEHICLE_POSZ" = %0.4f , \
		"VEHICLE_POSROT" = %0.4f WHERE "VEHICLE_OWNERID" = %i AND "VEHICLE_ID" = %i", x, y, z, a, GetPlayerAccountID(playerid), vehData[vehicleid][VEH_ID]);

	mysql_tquery(sqlHandle, qString);

	SendServerMessage(playerid, "Vehicle parked, position saved!");
	return 1;
}

stock IsPlayerInPersonalVehicle(playerid)
{
	new
		ply_vehicleID = GetPlayerVehicleID(playerid);

	foreach(new i : Vehicle)
	{
		if(vehData[i][VEH_DATA] != ply_vehicleID)
			continue;

		if(!IsVehicleStreamedIn(vehData[i][VEH_DATA], playerid))
			return 0;

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return 0;

		if(vehData[i][VEH_OWNERID] == GetPlayerAccountID(playerid))
			return 1;
	}
	return 0;
}

stock Vehicle_Destroy(playerid) {

    dbg(PLAYER_DEBUG_HANDLER, "owned vehicle destroyed",
        _p("username", playerid),
        _i("uid", Player_GetAccountID(playerid)),
        _i("total", Vehicle_GetPlayerTotal(playerid))
    );

	foreach(new i : Vehicle) {
		if(!Bit_Get(vehicle_created, i)) {
            continue;
        }
		if(VehicleOwnerID[i] != Player_GetAccountID(playerid)) {
            continue;
        }

        VehicleX[i]	            =
        VehicleY[i]	            =
        VehicleZ[i]	            =
        VehicleRot[i]		    = 0.0;
        VehicleModelID[i]		=
        VehicleOwnerID[i] 	    =
        VehicleID[i]	        =
        VehicleColor1[i]	    =
        VehicleColor2[i]	    =
        VehicleInteriorID[i]	=
        VehicleVWorld[i]	    = 0;

        DestroyVehicle(VehicleHandler[i]);
        Bit_Vet(vehicle_created, i);
	}
}
