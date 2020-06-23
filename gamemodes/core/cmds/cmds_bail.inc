CMD:bail(playerid) {
    if(!Player_HasFinishedJailSentence(playerid)) {
        return SendErrorMsg(playerid, "You need to finish your sentence in order to bail.");
    }

    if(!Player_IsInJail(playerid)) {
        return SendErrorMsg(playerid, "You are not in jail!");
    }


    if(GetPlayerMoney(playerid) < Player_GetBailAmount(playerid)) {
        return SendErrorMsgF(playerid, "You don't have "C_GREEN"$%i "C_WHITE"to pay for your bail.", Player_GetBailAmount(playerid));
    }
    Player_ReleaseFromJail(playerid);
    GivePlayerMoney(playerid, Player_GetBailAmount(playerid));
    Player_SetBailAmount(playerid, 0);
    return 1;
}