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

CMD:rfc(playerid, params[]) {
    AddVehicleComponent(559, 1109);
    AddVehicleComponent(559, 1116);
    AddVehicleComponent(559, 1117);
    AddVehicleComponent(559, 1083);
    AddVehicleComponent(559, 1113);
    AddVehicleComponent(559, 1010);
    AddVehicleComponent(559, 1119);
    return 1;
}