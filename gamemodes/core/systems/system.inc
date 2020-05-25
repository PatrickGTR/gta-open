#include <burglary_system>
#include <tower_system>
#include <trucker_system>
#include <stores_system>
#include <police_system>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_YES)) {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 295.4240, -82.5273, 1001.5156) || IsPlayerInRangeOfPoint(playerid, 5.0, 312.8376, -167.7640, 999.5938)) {
            Ammunation_ShowMenu(playerid);
        }
    }
    if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 5.0, 1015.4679, -930.1953, 42.1797)) {
        ShowMechServices(playerid);
    }
    if(PRESSED(KEY_SUBMISSION))
    {
        if(PlayerCuffed[Player_GetClosestWanted(playerid)] == 0) {
            return cmd_cuffcw(playerid);
        }
        else if(PlayerCuffed[Player_GetClosestWanted(playerid)] == 1) {
            return cmd_arrestcw(playerid);
        }
    }
    return 1;
}