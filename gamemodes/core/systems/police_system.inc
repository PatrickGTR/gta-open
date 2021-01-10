#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_LOOK_BEHIND)) {

        if(Player_GetClass(playerid) != TEAM_POLICE) {
            return 1;
        }

        new
            targetid = Player_GetClosestWanted(playerid, 5.0);

        if(targetid == INVALID_PLAYER_ID) {
            SendErrorMsg(playerid, "No players nearby");
            return 1;
        }

        new
            errorMessage[45];
        if(!Player_IsCuffed(targetid)) {

            if(!Player_CuffPlayer(playerid, targetid, errorMessage, sizeof(errorMessage))) {
                return SendErrorMsg(playerid, errorMessage);
            }

        }
        else {
            if(!Player_Arrest(playerid, targetid, errorMessage, sizeof(errorMessage))) {
                return SendErrorMsg(playerid, errorMessage);
            }
        }
    }
    return 1;
}