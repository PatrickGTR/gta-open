#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

#define MAX_OWNED_VEHICLES (MAX_PLAYERS * MAX_VEHICLE_PER_PLAYER)

static
    VehicleHandler[MAX_OWNED_VEHICLES],
    VehicleOwnerName[MAX_OWNED_VEHICLES][MAX_PLAYER_NAME],
    VehicleOwnerID[MAX_OWNED_VEHICLES],
    VehicleUID[MAX_OWNED_VEHICLES],
    VehicleModelID[MAX_OWNED_VEHICLES],
    Float:VehicleX[MAX_OWNED_VEHICLES],
    Float:VehicleY[MAX_OWNED_VEHICLES],
    Float:VehicleZ[MAX_OWNED_VEHICLES],
    Float:VehicleRot[MAX_OWNED_VEHICLES],
    VehicleColor1[MAX_OWNED_VEHICLES],
    VehicleColor2[MAX_OWNED_VEHICLES],
    VehicleInteriorID[MAX_OWNED_VEHICLES],
    VehicleVWorld[MAX_OWNED_VEHICLES],
    VehicleMods[MAX_OWNED_VEHICLES][16],
    VehiclePlate[MAX_OWNED_VEHICLES][MAX_PLATE_NAME];

stock
    Iterator:PersonalVehicle<MAX_OWNED_VEHICLES>;

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
            pv.u_id, \
            model_id, \
            x, \
            y, \
            z, \
            rot, \
            color_1, \
            color_2, \
            intid, \
            vworld, \
            p.username \
        FROM \
            player_vehicles pv \
        INNER JOIN \
            players p \
        ON \
            p.u_id = pv.u_id \
        WHERE \
            pv.u_id = ? \
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
    foreach(new i : PersonalVehicle) {
        if (VehicleHandler[i] == vehicleid) {
            new
                slot = GetVehicleComponentType(componentid);

            MySQL_BindInt(stmt_insertUpdateComponent, 0, VehicleUID[i]);
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
    foreach(new i : PersonalVehicle) {
        if (VehicleHandler[i] == vehicleid) {

            MySQL_BindInt(stmt_updateColor, 0, color1);
            MySQL_BindInt(stmt_updateColor, 1, color1);

            MySQL_BindInt(stmt_updateColor, 2, VehicleUID[i]);
            MySQL_ExecuteThreaded(stmt_updateColor);

            VehicleColor1[i] = color1;
            VehicleColor2[i] = color2;

        }
    }
    return 1;
}

hook OnVehicleStreamIn(vehicleid, forplayerid) {
    foreach(new i : PersonalVehicle) {
        if (VehicleHandler[i] != vehicleid) {
            continue;
        }

        for(new x = 0; x < sizeof(VehicleMods[]); x ++) {
            if(!IS_IN_RANGE(VehicleMods[i][x], 1000, 1193)) {
                continue;
            }
            AddVehicleComponent(VehicleHandler[i], VehicleMods[i][x]);
        }
    }
    return 1;
}

Vehicle_GetPlayerTotal(playerid) {
    new
        count = 0;
    foreach(new i : PersonalVehicle) {
        if(Player_GetAccountID(playerid) == VehicleOwnerID[i]) {
            count ++;
        }
    }
    return count;
}

Vehicle_Create(playerid, modelid, Float:x, Float:y, Float:z, Float:rot) {
    inline const OnSaveCreatedVehicle() {
        new
            idx = Iter_Alloc(PersonalVehicle);

        VehicleOwnerID[idx] 	    = Player_GetAccountID(playerid);
        VehicleUID[idx]	            = cache_insert_id();
        VehicleModelID[idx]		    = modelid;

        VehicleX[idx]	            = x;
        VehicleY[idx]	            = y;
        VehicleZ[idx]	            = z;
        VehicleRot[idx]		        = rot;

        VehicleColor1[idx]	        = random(255);
        VehicleColor2[idx]	        = random(255);

        VehicleInteriorID[idx]	    = 0;
        VehicleVWorld[idx]	        = 0;

        for(new i = 0; i < 14; i++) {
            VehicleMods[idx][i] = 0;
        }

        strcpy(VehiclePlate[idx], "GTA-OPEN");
        strcpy(VehicleOwnerName[idx], ReturnPlayerName(playerid));

        VehicleHandler[idx] = CreateVehicle(modelid, x, y, z, rot, VehicleColor1[idx], VehicleColor2[idx], -1, 0);
        SetVehicleNumberPlate(VehicleHandler[idx], VehiclePlate[idx]);
        LinkVehicleToInterior(VehicleHandler[idx], VehicleInteriorID[idx]);
        SetVehicleVirtualWorld(VehicleHandler[idx], VehicleVWorld[idx]);

        defer PutPlayerInSaveVehicle(playerid, VehicleHandler[idx]);
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

stock Vehicle_GetHandler(index) {
    return VehicleHandler[index];
}

stock Vehicle_Park(playerid) {
    new
        vehicleid,
        index,
        playerInVehicleID = GetPlayerVehicleID(playerid);

    foreach(new i : PersonalVehicle) {
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

    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[Vehicle_Park / vehicle_impl.inc] owned vehicle parked",
        Logger_P(playerid),
        Logger_I("account id", Player_GetAccountID(playerid)),
        Logger_I("vehicle id", VehicleUID[index]),
        Logger_F("x", x),
        Logger_F("y", y),
        Logger_F("z", z),
        Logger_F("a", a)
    );


    MySQL_BindFloat(stmt_updatePosition, 0, x);
    MySQL_BindFloat(stmt_updatePosition, 1, y);
    MySQL_BindFloat(stmt_updatePosition, 2, z);
    MySQL_BindFloat(stmt_updatePosition, 3, a);

    MySQL_BindInt(stmt_updatePosition, 4, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_updatePosition, 5, VehicleUID[index]);

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
            VWorld,
            ownerName[MAX_PLAYER_NAME];

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
        MySQL_BindResult(stmt_checkVehicle, 11, ownerName);

        while(MySQL_Statement_FetchRow(stmt_checkVehicle)) {
            new
                idx = Iter_Alloc(PersonalVehicle);

            VehicleOwnerID[idx] 	    = ownerID;
            VehicleUID[idx]	            = vehicleID;
            VehicleModelID[idx]		    = modelID;
            VehicleX[idx]	            = x;
            VehicleY[idx]	            = y;
            VehicleZ[idx]	            = z;
            VehicleRot[idx]		        = rot;
            VehicleColor1[idx]	        = color_1;
            VehicleColor2[idx]	        = color_2;
            VehicleInteriorID[idx]	    = intID;
            VehicleVWorld[idx]	        = VWorld;

            strcpy(VehicleOwnerName[idx], ownerName);

            VehicleHandler[idx] = CreateVehicle(modelID, x, y, z, rot, -1, -1, -1, 0);
            SetVehicleNumberPlate(VehicleHandler[idx], VehiclePlate[idx]);
            LinkVehicleToInterior(VehicleHandler[idx], VehicleInteriorID[idx]);
            SetVehicleVirtualWorld(VehicleHandler[idx], VehicleVWorld[idx]);
            ChangeVehicleColor(VehicleHandler[idx], VehicleColor1[idx], VehicleColor2[idx]);

            Logger_Dbg(PLAYER_DEBUG_HANDLER, "[Vehicle_Load / vehicle_impl.inc] owned vehicle loaded",
                Logger_P(playerid),
                Logger_I("account id", Player_GetAccountID(playerid)),
                Logger_I("vehicle id", VehicleUID[idx])
            );

            new
                component_id,
                index = 0;
            MySQL_BindResultInt(stmt_checkComponent, 0, component_id);
            inline const OnLoadVehicleComponent() {
                while(MySQL_Statement_FetchRow(stmt_checkComponent)) {
                    VehicleMods[idx][index ++] = component_id;
                }
            }
            MySQL_BindInt(stmt_checkComponent, 0, VehicleUID[idx]);
            MySQL_ExecuteThreaded_Inline(stmt_checkComponent, using inline OnLoadVehicleComponent);
        }
    }
    MySQL_BindInt(stmt_checkVehicle, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_checkVehicle, using inline OnLoadCreatedVehicle);
}

stock Vehicle_IsOwner(playerid, vehicleid = INVALID_VEHICLE_ID)
{
    if(vehicleid == INVALID_VEHICLE_ID) {
        vehicleid = GetPlayerVehicleID(playerid);
    }

    foreach(new i : PersonalVehicle) {
        if(VehicleHandler[i] != vehicleid) {
            continue;
        }

        if(!IsVehicleStreamedIn(VehicleHandler[i], playerid)) {
            return 0;
        }

        if(VehicleOwnerID[i] == Player_GetAccountID(playerid)) {
            return 1;
        }
    }
    return 0;
}

Vehicle_GetOwnerName(index) {
    return VehicleOwnerName[index];
}

Vehicle_Destroy(playerid) {
    foreach(new i : PersonalVehicle) {
        if(VehicleOwnerID[i] != Player_GetAccountID(playerid)) {
            continue;
        }

        Logger_Dbg(PLAYER_DEBUG_HANDLER, "[Vehicle_Destroy / vehicle_impl.inc] owned vehicle destroyed",
            Logger_P(playerid),
            Logger_I("account id", Player_GetAccountID(playerid)),
            Logger_I("total", Vehicle_GetPlayerTotal(playerid))
        );

        VehicleX[i]	            =
        VehicleY[i]	            =
        VehicleZ[i]	            =
        VehicleRot[i]		    = 0.0;
        VehicleModelID[i]		=
        VehicleOwnerID[i] 	    =
        VehicleUID[i]	        =
        VehicleColor1[i]	    =
        VehicleColor2[i]	    =
        VehicleInteriorID[i]	=
        VehicleVWorld[i]	    = 0;

        Iter_Remove(PersonalVehicle, i);
        DestroyVehicle(VehicleHandler[i]);
    }
}
