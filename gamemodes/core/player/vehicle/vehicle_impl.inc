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
    VehicleMods[MAX_VEHICLES][16],
    VehiclePlate[MAX_VEHICLES][MAX_PLATE_NAME],
    BitArray:vehicle_created<MAX_VEHICLES>;

static
    Statement: stmt_insertVehicle,
    Statement: stmt_checkVehicle,
    Statement: stmt_checkComponent,
    Statement: stmt_updatePosition,
    Statement: stmt_updateColor,
    Statement: stmt_insertUpdateComponent;


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

    static const componentQuery[] = "\
        SELECT \
            component_id \
        FROM \
            vehicle_components \
        WHERE vehicle_id = ? \
    ";
    stmt_checkComponent = MySQL_PrepareStatement(MySQL_GetHandle(), componentQuery);

    static const updatePositionQuery[] = "\
        UPDATE \
            player_vehicles \
        SET \
            x = ?, \
            y = ?, \
            z = ? , \
            rot = ? \
        WHERE \
            u_id = ? \
        AND \
            vehicle_id = ? \
    ";
    stmt_updatePosition = MySQL_PrepareStatement(MySQL_GetHandle(), updatePositionQuery);

    static const updateColorQuery[] = "\
        UPDATE \
            player_vehicles \
        SET \
            color_1 = ?, \
            color_2 = ? \
        WHERE \
            vehicle_id = ? \
    ";
    stmt_updateColor = MySQL_PrepareStatement(MySQL_GetHandle(), updateColorQuery);

    static const insertUpdateComponentQuery[] = "\
        INSERT INTO \
            vehicle_components (vehicle_id, component_id, slot) \
        VALUES \
            (?, ?, ?) \
        ON DUPLICATE KEY UPDATE \
            component_id = ? \
    ";
    stmt_insertUpdateComponent = MySQL_PrepareStatement(MySQL_GetHandle(), insertUpdateComponentQuery);
    return 1;
}

hook OnVehicleMod(playerid, vehicleid, componentid) {
    foreach(new i : Vehicle) {
        if(!Bit_Get(vehicle_created, i)) {
            continue;
        }

        if (VehicleHandler[i] == vehicleid) {
            new
                slot = GetVehicleComponentType(componentid);

            MySQL_BindInt(stmt_insertUpdateComponent, 0, VehicleID[i]);
            MySQL_BindInt(stmt_insertUpdateComponent, 1, componentid);
            MySQL_BindInt(stmt_insertUpdateComponent, 2, slot);

            MySQL_BindInt(stmt_insertUpdateComponent, 3, componentid);
            MySQL_ExecuteThreaded(stmt_insertUpdateComponent);

            //This assigns the new value to our variable.
            VehicleMods[i][slot] = componentid;
        }
    }
    return 1;
}

hook OnVehicleRespray(playerid, vehicleid, color1, color2) {
    foreach(new i : Vehicle) {
        if(!Bit_Get(vehicle_created, i))
            continue;

        if (VehicleHandler[i] == vehicleid) {

            MySQL_BindInt(stmt_updateColor, 0, color1);
            MySQL_BindInt(stmt_updateColor, 1, color1);

            MySQL_BindInt(stmt_updateColor, 2, VehicleID[i]);
            MySQL_ExecuteThreaded(stmt_updateColor);

            VehicleColor1[i] = color1;
            VehicleColor2[i] = color2;

        }
    }
    return 1;
}

hook OnVehicleStreamIn(vehicleid, forplayerid) {

    foreach(new i : Vehicle) {
        if(!Bit_Get(vehicle_created, i)) {
            continue;
        }

        if (VehicleHandler[i] != vehicleid) {
            continue;
        }

        for(new x = 0; x < sizeof(VehicleMods[]); x ++) {
            if(!IS_IN_RANGE(VehicleMods[i][x], 1000, 1193)) {
                continue;
            }
            AddVehicleComponent(VehicleHandler[i], VehicleMods[i][x]);
            printf("adding component %i to vehicle id %i", VehicleMods[i][x], VehicleHandler[i]);
        }
    }
    printf("vehicle id %i streamed in", vehicleid);
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


Vehicle_Create(playerid, modelid, Float:x, Float:y, Float:z, Float:rot) {
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


            VehicleColor1[i]	    = -1;
            VehicleColor2[i]	    = -1;

            VehicleInteriorID[i]	= 0;
            VehicleVWorld[i]	    = 0;

            for(new mod_id = 0; mod_id < 14; mod_id++) {
                VehicleMods[i][mod_id] = 0;
            }

            strcpy(VehiclePlate[i], "GTA-OPEN");

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

timer PutPlayerInSaveVehicle[1000](playerid, vehicleid) {
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    PutPlayerInVehicle(playerid, vehicleid, 0);
}

stock Vehicle_Park(playerid) {
    new
        vehicleid,
        index,
        playerInVehicleID = GetPlayerVehicleID(playerid);
    foreach(new i : Vehicle) {

        if(!Bit_Get(vehicle_created, i)) {
            continue;
        }

        if(VehicleHandler[i] != playerInVehicleID) {
            continue;
        }

        vehicleid = VehicleHandler[i];
        index = i;
        break;
    }

    new
        Float: x,
        Float: y,
        Float: z,
        Float: a;

    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, a);


    MySQL_BindFloat(stmt_updatePosition, 0, x);
    MySQL_BindFloat(stmt_updatePosition, 1, y);
    MySQL_BindFloat(stmt_updatePosition, 2, z);
    MySQL_BindFloat(stmt_updatePosition, 3, a);

    MySQL_BindInt(stmt_updatePosition, 4, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_updatePosition, 5, VehicleID[index]);

    MySQL_ExecuteThreaded(stmt_updatePosition);
    return 1;
}

stock Vehicle_Load(playerid) {
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
    MySQL_BindResultInt(stmt_checkVehicle, 8, color_2);
    MySQL_BindResultInt(stmt_checkVehicle, 9, intID);
    MySQL_BindResultInt(stmt_checkVehicle, 10, VWorld);

    while(MySQL_Statement_FetchRow(stmt_checkVehicle)) {
            foreach(new i : Vehicle) {
                if(Bit_Get(vehicle_created, i)) {
                    // skip created vehicles that are created by vehicles_ api.
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

                Bit_Let(vehicle_created, i);

                dbg(PLAYER_DEBUG_HANDLER, "owned vehicle loaded",
                    _p("username", playerid),
                    _i("uid", Player_GetAccountID(playerid)),
                    _i("vehicle id", VehicleID[i])
                );

                new
                    component_id,
                    index = 0;
                MySQL_BindResultInt(stmt_checkComponent, 0, component_id);
                inline const OnLoadVehicleComponent() {
                    while(MySQL_Statement_FetchRow(stmt_checkComponent)) {

                        VehicleMods[i][index] = component_id;

                        defer DelayAddVehicleComponent(VehicleHandler[i], VehicleMods[i][index], 500 + (index * 100));
                        index ++;
                    }
                }
                MySQL_BindInt(stmt_checkComponent, 0, VehicleID[i]);
                MySQL_ExecuteThreaded_Inline(stmt_checkComponent, using inline OnLoadVehicleComponent);

                // break once vehicle_created isn't skipped.
                break;
            }
        }
    }
    MySQL_BindInt(stmt_checkVehicle, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_checkVehicle, using inline OnLoadCreatedVehicle);
}

timer DelayAddVehicleComponent[seconds](vehicleid, componentid, seconds) {
    #pragma unused seconds
    AddVehicleComponent(vehicleid, componentid);
}

stock IsPlayerInPersonalVehicle(playerid)
{
    new
        ply_vehicleID = GetPlayerVehicleID(playerid);

    foreach(new i : Vehicle) {
        if(!Bit_Get(vehicle_created, i)) {
            continue;
        }

        if(VehicleHandler[i] != ply_vehicleID) {
            continue;
        }

        if(!IsVehicleStreamedIn(VehicleHandler[i], playerid)) {
            return 0;
        }

        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
            return 0;
        }

        if(VehicleOwnerID[i] == Player_GetAccountID(playerid)) {
            return 1;
        }
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
