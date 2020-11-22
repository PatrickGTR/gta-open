#include <YSI_Coding\y_hooks>

static
    PlayerRobTick[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerRobTick[playerid] = 0;
    return 1;
}

CMD:rob(playerid, params[])
{
    new
        targetid = Player_GetClosestPlayer(playerid, 5.0);

    if (!IsPlayerConnected(targetid) || !Player_IsSpawned(targetid)) {
        return SendErrorMsg(playerid, "There are no players nearby to rob.");
    }

    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        return SendErrorMsg(playerid, "The player your trying to rob is not on foot");
    }

    if (gettime() - PlayerRobTick[playerid] < 30) {
        return SendErrorMsg(playerid, "You just robbed someone recently, please try again later");
    }

    if (Player_GetWallet(targetid) > 0)
    {
        SendMsgF(playerid, COLOR_ORANGE, "(player robbery) "C_WHITE"You failed to rob "C_GREY"%p (%i) "C_WHITE"because he had wallet, run away!", targetid, targetid);
        SendMsgF(targetid, COLOR_ORANGE, "(player robbery) "C_GREY"%p (%i) "C_WHITE"attempted to rob you but failed, chase him! - Wallets Left: %i", playerid, playerid, Player_GetWallet(playerid));
        return 1;
    }

    new
        bool:success_rate = RandomChance(65);

    if (!success_rate) {
        SendMsgF(playerid, COLOR_ORANGE, "(player robbery) "C_WHITE"You failed to rob "C_GREY"%p (%i) "C_WHITE"run away!", targetid, targetid);
        SendMsgF(targetid, COLOR_ORANGE, "(player robbery) "C_GREY"%p (%i) "C_WHITE"attempted to rob you but failed, chase him!", playerid, playerid);
        return 1;
    }
    new
        robbedcash = random( (GetPlayerMoney(targetid) / 100) * 5 ) + 500; //5% + 500 min of player's money.

    CallLocalFunction("OnPlayerRobPlayer", "iii", playerid, targetid, robbedcash);

    PlayerRobTick[playerid] = gettime();
    return true;
}