#include <furniture_data>
#include <furniture_impl>
#include <furniture_cmd>

#include <YSI_Coding\y_hooks>

static
    Statement: stmt_updateFurniture,
    Statement: stmt_insertFurniture;

/*
    SELECT
        hf.furniture_id,
        hf.house_id,
        hf.x,
        hf.y,
        hf.z,
        hf.rx,
        hf.ry,
        hf.rz,
        hf.intid,
        hf.vworld
    FROM
        house_furniture as hf
    INNER JOIN
        player_houses as ph
    ON
        hf.house_id = ph.house_id
    WHERE
        ph.u_id = 1
*/

hook OnMySQLConnected() {

    // Improvement!
    // Load object when user connect instead of loadin it through gamemode init.
    // Delete object when user disconnect, this case we save memory usage.
    inline LoadFurnitureObjects() {
        new
            rows = cache_num_rows();

        if(rows) {
            new
                furniture_id,
                house_id,
                object_id,
                Float: x,
                Float: y,
                Float: z,
                Float: rx,
                Float: ry,
                Float: rz,
                intid,
                vworld;

            for(new i = 0; i < rows; i++) {
                cache_get_value_name_int(i, "furniture_id", furniture_id);
                cache_get_value_name_int(i, "house_id", house_id);
                cache_get_value_name_int(i, "object_id",   object_id);

                cache_get_value_name_float(i, "x",  x);
                cache_get_value_name_float(i, "y",  y);
                cache_get_value_name_float(i, "z",  z);

                cache_get_value_name_float(i, "rx",  rx);
                cache_get_value_name_float(i, "ry",  ry);
                cache_get_value_name_float(i, "rz",  rz);

                cache_get_value_name_int(i, "intid",   intid);
                cache_get_value_name_int(i, "vworld",    vworld);

                Furniture_Create(furniture_id, house_id, object_id, x, y, z, rx, ry, rz, vworld, intid);
            }
        }
    }
    MySQL_TQueryInline(MySQL_GetHandle(), using inline LoadFurnitureObjects, "SELECT * FROM house_furniture");

    static const updateQuery[] = "\
        UPDATE \
            house_furniture \
        SET \
            x = ? \
            y = ? \
            z = ? \
            rx = ?, \
            ry = ?, \
            rz = ? \
        WHERE \
            furniture_id = ? \
        AND \
        house_id = ?\
    ";
    stmt_updateFurniture = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);

    static const insertQuery[] = "\
        INSERT INTO \
        house_furniture (house_id, object_id, x, y, z, rx, ry, rz, intid, vworld) \
        VALUES \
        (?, ?, ?, ?, ?, ?, ?, ?, ?, ?) \
    ";
    stmt_insertFurniture = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);
}


hook OnPlayerEditDynObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    if(Player_IsOnFurnitureMode(playerid)) {
        switch(Furniture_GetEditingState(playerid)) {
            case TYPE_BUYING_FURNITURE: {
                switch(response) {
                    case EDIT_RESPONSE_CANCEL: {
                        Furniture_DeleteTemporary(playerid);
                    }
                    case EDIT_RESPONSE_FINAL: {

                        new
                            index = g_tmpPlayerIndexID[playerid];

                        if (GetPlayerMoney(playerid) < Furniture_GetPrice(index)) {
                            SendErrorMsg(playerid, "You don't have enough money to buy this furniture.");
                            Furniture_DeleteTemporary(playerid);
                            return 1;
                        }

                        inline ReloadFurniture() {
                            // We retrieve the last inserted ID.
                            new furniture_id = cache_insert_id();
                            Furniture_Create(furniture_id, Player_GetInHouseID(playerid), Furniture_GetObjectID(index), x, y, z, rx, ry, rz, Player_GetInHouseVWorld(playerid), Player_GetInHouseInt(playerid));
                        }

                        MySQL_BindInt(stmt_insertFurniture, 0, Player_GetInHouseID(playerid));
                        MySQL_BindInt(stmt_insertFurniture, 1, Furniture_GetObjectID(index));
                        MySQL_BindFloat(stmt_insertFurniture, 2, x);
                        MySQL_BindFloat(stmt_insertFurniture, 3, y);
                        MySQL_BindFloat(stmt_insertFurniture, 4, z);
                        MySQL_BindFloat(stmt_insertFurniture, 5, rx);
                        MySQL_BindFloat(stmt_insertFurniture, 6, ry);
                        MySQL_BindFloat(stmt_insertFurniture, 7, rz);
                        MySQL_BindInt(stmt_insertFurniture, 8, Player_GetInHouseInt(playerid));
                        MySQL_BindInt(stmt_insertFurniture, 9, Player_GetInHouseVWorld(playerid));
                        MySQL_ExecuteThreaded_Inline(stmt_insertFurniture, using inline ReloadFurniture);


                        SendServerMsg(playerid, "Object Saved "C_GREY"[BOUGHT]");
                        GivePlayerMoney(playerid, -Furniture_GetPrice(index));
                        Furniture_DeleteTemporary(playerid);
                    }
                }

            }
            case TYPE_EDITING_FURNITURE: {
                new
                    Float: old_x,
                    Float: old_y,
                    Float: old_z,
                    Float: old_rx,
                    Float: old_ry,
                    Float: old_rz;

                GetDynamicObjectPos(objectid, old_x, old_y, old_z);
                GetDynamicObjectRot(objectid, old_rx, old_ry, old_rz);

                switch(response) {
                    case EDIT_RESPONSE_CANCEL: {
                        Furniture_SetEditingState(playerid, INVALID_EDITING_TYPE);
                        Player_SetFurnitureMode(playerid, false);

                        // Set the object to its old position.
                        SetDynamicObjectPos(objectid, old_x, old_y, old_z);
                        SetDynamicObjectRot(objectid, old_rx, old_ry, old_rz);
                    }
                    case EDIT_RESPONSE_FINAL: {
                        // Set the object to its new position.
                        SetDynamicObjectPos(objectid, x, y, z);
                        SetDynamicObjectRot(objectid, rx, ry, rz);

                        SendServerMsg(playerid, "Object Saved "C_GREY"[EDITED]");
                        Furniture_SetEditingState(playerid, INVALID_EDITING_TYPE);
                        Player_SetFurnitureMode(playerid, false);

                        new
                            arr[2];

                        // first cell -> house index ID
                        // second cell -> furniture index ID

                        Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, arr);

                        MySQL_BindFloat(stmt_updateFurniture, 0, x);
                        MySQL_BindFloat(stmt_updateFurniture, 1, y);
                        MySQL_BindFloat(stmt_updateFurniture, 2, z);
                        MySQL_BindFloat(stmt_updateFurniture, 3, rx);
                        MySQL_BindFloat(stmt_updateFurniture, 4, ry);
                        MySQL_BindFloat(stmt_updateFurniture, 5, rz);
                        MySQL_BindInt(stmt_updateFurniture, 6, arr[1]);
                        MySQL_BindInt(stmt_updateFurniture, 7, arr[0]);

                        MySQL_ExecuteThreaded(stmt_updateFurniture);
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerSelectDynObj(playerid, objectid, modelid, Float:x, Float:y, Float:z) {
    if(Player_IsOnFurnitureMode(playerid) && Furniture_GetEditingState(playerid) == TYPE_EDITING_FURNITURE) {
        EditDynamicObject(playerid, objectid);
    }
    else if (Player_IsOnFurnitureMode(playerid) && Furniture_GetEditingState(playerid) == TYPE_DELETING_FURNITURE) {

        inline ConfirmFurnitureDeletion(pid, dialogid, response, listitem, string:inputtext[]) {
            #pragma unused pid, listitem, dialogid, inputtext
            if(!response) {
                return Furniture_ShowDialog(playerid);
            }

            Furniture_SetEditingState(playerid, INVALID_EDITING_TYPE);
            Player_SetFurnitureMode(playerid, false);

            new
                arr[2];

            // first cell -> house index ID
            // second cell -> furniture index ID
            Streamer_GetArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, arr);
            Furniture_Delete(arr[0], arr[1]);
            CancelEdit(playerid);
            DestroyDynamicObject(objectid);
            SendServerMsg(playerid, "Successfuly deleted furniture");
        }

        Dialog_ShowCallback(playerid, using inline ConfirmFurnitureDeletion, DIALOG_STYLE_MSGBOX,
            "Furniture Delete Confirmation",
            ""C_WHITE"Are you sure you want to delete this furniture?\nIt will be "C_RED"PERMANENTLY"C_WHITE" deleted.",
            "Confirm", "Back");
    }
    return 1;
}