#include <vehicle_impl>

#if SETUP_TABLE
    #include <vehicle_setup-table>
#endif


#include <YSI_Coding\y_hooks>
hook OnPlayerDisconnect(playerid, reason) {
    Vehicle_Destroy(playerid);
    return 1;
}

hook OnPlayerLogin(playerid) {
    Vehicle_Load(playerid);
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {

    if(newstate == PLAYER_STATE_DRIVER) {
        if(Vehicle_IsPlayer(playerid)) {
            SendMsgF(playerid, COLOR_SAMPBLUE, "Welcome back to your personal vehicle.");
            return 1;
        }

        foreach_PersonalVehicles(i) {
            if(Vehicle_GetHandler(i) == GetPlayerVehicleID(playerid)) {
                SendMsgF(playerid, COLOR_SAMPBLUE, "This vehicle is owned by "C_GREY"%s", Vehicle_GetOwnerName(i));
            }
        }
    }
    return 1;
}