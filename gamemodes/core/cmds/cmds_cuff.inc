// cuff closest player
CMD:cuffcw(playerid) {
    new
        targetid = Player_GetClosestWanted(playerid),
        errorMessage[32],
        ret;

    ret = Player_CuffPlayer(playerid, targetid, errorMessage, sizeof(errorMessage));

    if(!ret) {
        SendErrorMsg(playerid, errorMessage);
    }
    return 1;
}

// cuff player by id
CMD:cuff(playerid, params[]) {
    new
        targetid;

    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/cuff (name/id)");
    }

    new
        errorMessage[32],
        ret;

    ret = Player_CuffPlayer(playerid, targetid, errorMessage, sizeof(errorMessage));

    if(!ret) {
        SendErrorMsg(playerid, errorMessage);
    }
    return 1;
}

// returns
// 0 -> fail
// -> playerid is not police.
// -> targetid == INVALID_PLAYER_ID.
// -> targetid is not in range.
// -> targetid is aleady cuffed.
// 1 -> success, if it passes all the checks above.
Player_CuffPlayer(playerid, targetid, errorMsg[], len = sizeof(errorMsg)) {
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        strcat(errorMsg, "Only cops can use this command!", len);
        return 0;
    }

    if(targetid == INVALID_PLAYER_ID)  {
        strcat(errorMsg, "There's no warrant near you", len);
        return 0;
    }

    // do nothing, can't cuff players with wanted level below 3
    if(GetPlayerWantedLevel(playerid) <= 3) {
        return 1;
    }

    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(playerid, x, y, z);
    if(!IsPlayerInRangeOfPoint(targetid, 5.0, x, y, z)) {
        strcat(errorMsg, "There's no warrant near you", len);
        return 0;
    }

    if(Player_IsCuffed(targetid)) {
        strcat(errorMsg, "The player is already cuffed", len);
        return 0;
    }

    if(targetid == playerid) {
        strcat(errorMsg, "You can't cuff yourself, dummy!", len);
        return 0;
    }


    SendServerMsgF(targetid, "You have been cuffed by officer "C_GREY"%p(%d)", playerid, playerid);
    SendServerMsgF(playerid, "You're now cuffing "C_GREY"%p(%d)", targetid, targetid);
    Player_Cuff(targetid, true);
    return 1;
}