#include <YSI_Coding\y_hooks>

#define MAX_MONEY_PICKUP 15

static
    ATM_RobbedRecently[MAX_ATMS],
    ATM_MoneyPickup[MAX_ATMS][MAX_MONEY_PICKUP];

#define ATM_COOLDOWN_MINUTES 5

#define ATM_COOLDOWN (1000 * 60) * ATM_COOLDOWN_MINUTES

hook OnExplosiveDetonate(playerid, Float: x, Float: y, Float: z) {
    new
        atmID = ATM_GetClosest(playerid),
        objectID = ATM_GetObjectID(atmID),
        Float: atmX,
        Float: atmY,
        Float: atmZ;

    GetDynamicObjectPos(objectID, atmX, atmY, atmZ);

    new
        Float:dist = Distance(atmX, atmY, atmZ, x, y, z);

    // grab the position infront of atm.
    // technically this grabs the x, y, z behind but
    // for some reason so had to reverse it.
    atmX += 1.0 * floatsin(-atmZ + 180, degrees);
    atmY += 1.0 * floatcos(-atmZ + 180, degrees);

    if(dist < 3.5) {
        new
            idx = ATM_FindIndexIDBySQLID(atmID);

        // avoid accessing invalid index.
        if(idx == INVALID_ATM_ID) {
            return 1;
        }

        // atm has not been replinished yet, disallow action.
        if(gettime() - ATM_RobbedRecently[idx] < 60 * ATM_COOLDOWN_MINUTES) {
            return 1;
        }

        // User Interface
        new
            Float: deg,
            arr[2];
        for(new i = 0; i < MAX_MONEY_PICKUP; i++) {
            // spread money around the atm.
            deg += 360.0 / float(random(10)+ 2);
            atmX -= 1.0 * floatsin(deg, degrees);
            atmY -= 1.0 * floatcos(deg, degrees);

            ATM_MoneyPickup[idx][i] = CreateDynamicPickup(
                1212,
                19,
                atmX,
                atmY,
                atmZ
            );

            arr[0] = idx;
            arr[1] = i;
            Streamer_SetArrayData(
                STREAMER_TYPE_PICKUP,
                ATM_MoneyPickup[idx][i],
                E_STREAMER_EXTRA_ID,
                arr,
                sizeof(arr)
            );
        }
        ATM_UpdateLabel(idx, COLOR_RED, "ATM Disabled\nRecently robbed");

        // Settings
        // Change Model ID to broken ATM.
        Streamer_SetIntData(
            STREAMER_TYPE_OBJECT,
            objectID,
            E_STREAMER_MODEL_ID,
            2943
        );
        ATM_State(idx, true);
        ATM_RobbedRecently[idx] = gettime();

        // Replenish ATM in ATM_COOLDOWN_MINUTES.
        defer RestoreATMState(objectID, idx);
    }
    return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid) {
    new
        arr[2];
    Streamer_GetArrayData(
        STREAMER_TYPE_PICKUP,
        pickupid,
        E_STREAMER_EXTRA_ID,
        arr,
        sizeof(arr)
    );

    if(ATM_MoneyPickup[arr[0]][arr[1]]== pickupid) {
        static
            count[MAX_PLAYERS] = 0,
            reward[MAX_PLAYERS] = 0;

        reward[playerid] += random(100) + 500;

        if(++ count[playerid] >= MAX_MONEY_PICKUP) {

            // beautify reward
            SendMsgF(playerid, COLOR_GREEN, "%m", reward[playerid]);
        }


    }
    return 1;
}

// 5 minutes
timer RestoreATMState[ATM_COOLDOWN](objectID, idx) {
    ATM_RobbedRecently[idx] = 0;
    ATM_State(idx, false);
    ATM_UpdateLabel(idx);

    // Change model id back to normal ATM.
    Streamer_SetIntData(
        STREAMER_TYPE_OBJECT,
        objectID,
        E_STREAMER_MODEL_ID,
        19324
    );
}

CMD:givemec4(playerid, params[]) {

    Player_GiveC4(playerid, 10);
    return 1;
}

