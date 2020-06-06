#include <vehicle_impl>

#if SETUP_TABLE
    #include <vehicle_setup-table>
#endif


#include <YSI_Coding\y_hooks>
hook OnPlayerDisconnect(playerid, reason) {
    Vehicle_Destroy(playerid);
    return 1;
}