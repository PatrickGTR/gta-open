#include <YSI_Coding\y_hooks>

static
    BitArray:PlayerPMDisabled<MAX_PLAYERS>,
    PlayerLastPM[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    Bit_Set(PlayerPMDisabled, playerid, false);
    PlayerLastPM[playerid] = INVALID_PLAYER_ID;
    return 1;
}

CMD:dnd(playerid, params[]) {

    if(!Bit_Get(PlayerPMDisabled, playerid)) {
        SendServerMsg(playerid, "You have blocked your private messages.");
        Bit_Let(PlayerPMDisabled, playerid);
    } else {
        SendServerMsg(playerid, "You have unblocked your private messages.");
        Bit_Vet (PlayerPMDisabled, playerid);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerLastPM[playerid] == INVALID_PLAYER_ID) return 1;

    new target = PlayerLastPM[PlayerLastPM[playerid]];
    if(IsPlayerConnected(target)) {
        PlayerLastPM[target] = INVALID_PLAYER_ID;
    }
    PlayerLastPM[playerid] = INVALID_PLAYER_ID;
    return 1;
}

CMD:pm(playerid, params[]) {
    new
        targetid, msg[128];
    if (sscanf(params, "us[128]", targetid, msg)) {
        return SendSyntaxMsg(playerid, "/pm <playerid> <message>");
    }

    if (!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "The player you are trying to PM is invalid");
    }

    if (targetid == playerid) {
        return SendErrorMsg(playerid, "You can not PM yourself.");
    }

    if (Bit_Get(PlayerPMDisabled, playerid)) {
        return SendErrorMsg(playerid, "This player has his PM disabled.");
    }

    SendMsgF(playerid, COLOR_YELLOW, "** PM TO "C_GREY"%p (%i) ** "C_WHITE"%s", targetid, targetid, msg);
    SendMsgF(targetid, COLOR_YELLOW, "** PM FROM "C_GREY"%p (%i) ** "C_WHITE"%s", playerid, playerid, msg);
    PlayerPlaySound(targetid, 17802, 0.0, 0.0, 0.0);
    GameTextForPlayer(targetid, "~n~~n~~n~~y~Message Recieved", 1500, 5);
    PlayerLastPM[targetid] = playerid;
    return 1;
}

CMD:r(playerid, params[])
{
    new msg[128];
    new targetid = PlayerLastPM[playerid];
    if(sscanf(params, "s[128]", msg)) {
        return SendSyntaxMsg(playerid, "/r <message>");
    }
    if(targetid == -1) {
        return SendErrorMsg(playerid, "The player you are trying to PM has Disconnected");
    }
    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "The player you are trying to PM is invalid");
    }
    SendMsgF(playerid, COLOR_YELLOW, "** PM TO "C_GREY"%p (%i) ** "C_WHITE"%s", targetid, targetid, msg);
    SendMsgF(targetid, COLOR_YELLOW, "** PM FROM "C_GREY"%p (%i) ** "C_WHITE"%s", playerid, playerid, msg);
    PlayerPlaySound(targetid, 17802, 0.0, 0.0, 0.0);
    GameTextForPlayer(targetid, "~n~~n~~n~~y~Message Recieved", 1500, 5);
    PlayerLastPM[targetid] = playerid;
    return 1;
}