#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_SUBMISSION)) {
        if(Player_GetClass(playerid) != TEAM_POLICE) {
            return 0;
        }
        new
            id = Player_GetClosestWanted(playerid);

        if(id == INVALID_PLAYER_ID) {
            return 1;
        }

        new
            Float: x,
            Float: y,
            Float: z;
        GetPlayerPos(id, x, y, z);

        if(GetPlayerDistanceFromPoint(playerid, x, y, z) >= 3.5) {
            SendErrorMsg(playerid, "No players nearby");
            return 1;
        }

        new
            errorMessage[45];
        if(!Player_IsCuffed(id)) {

            if(!Player_CuffPlayer(playerid, id, errorMessage, sizeof(errorMessage))) {
                return SendErrorMsg(playerid, errorMessage);
            }

        }
        else {
            if(!Player_Arrest(playerid, id, errorMessage, sizeof(errorMessage))) {
                return SendErrorMsg(playerid, errorMessage);
            }
        }
    }
    return 1;
}