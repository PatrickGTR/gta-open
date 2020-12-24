#include <YSI_Coding\y_hooks>

#define MAX_DUELS   (MAX_PLAYERS / 2)
#define INVALID_DUEL_ID     -1
static
    bool:g1v1Enabled
;

static
    Iterator:gDuels<MAX_DUELS>,
    // Player 1 side
    gPlayer1[MAX_DUELS],
    gPlayer1Wins[MAX_DUELS],
    gPlayer1Lose[MAX_DUELS],

    // Player 2 side
    gPlayer2[MAX_DUELS],
    gPlayer2Wins[MAX_DUELS],
    gPlayer2Lose[MAX_DUELS],

    // Duel Side
    gRounds[MAX_DUELS],
    gCurrRound[MAX_DUELS],
    gBet[MAX_DUELS],
    gPlayerDuelID[MAX_PLAYERS],
    gPlayerID[MAX_PLAYERS]
;

static
    Timer:gAcceptTimer[MAX_PLAYERS],
    bool:gIsPlayerHasDuelInvite[MAX_PLAYERS]
;

hook OnGameModeInit()
{
    g1v1Enabled = false;
    Admin_AddCommandToList(1, "/tog1v1");
    return 1;
}

hook OnPlayerConnect(playerid)
{
    gPlayerDuelID[playerid] = INVALID_DUEL_ID;
    gIsPlayerHasDuelInvite[playerid] = false;
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(IsPlayerInDuel(playerid) && IsPlayerInDuel(killerid))
    {
        new duelid = gPlayerDuelID[playerid];
        if(gPlayerID[killerid] == 1) // Killer id is the player1
        {
            gPlayer1Wins[duelid]++;
            gPlayer2Lose[duelid]++;
            gCurrRound[duelid]++;
        }
        if(gPlayerID[killerid] == 2) // Killer id is the player2
        {
            gPlayer2Wins[duelid]++;
            gPlayer1Lose[duelid]++;
            gCurrRound[duelid]++;
        }
        CheckDuelPoints(duelid);
    }
    return 1;
}

static CheckDuelPoints(duelid)
{
    new
        player1 = gPlayer1[duelid],
        player2 = gPlayer2[duelid];
    if(gCurrRound[duelid] > gRounds[duelid])
    {
        if(gPlayer1Wins[duelid] > gPlayer2Wins[duelid])
        {
            SendMsgAllF(COLOR_ORANGE, "** DUEL ** "C_WHITE"%p (%d) won a duel against %p (%d) with the score of %d:%d", player1, player1, player2, player2, gPlayer1Wins[duelid], gPlayer2Wins[duelid]);
            GivePlayerMoney(player1, gBet[duelid]);
            GivePlayerMoney(player2, -gBet[duelid]);
        }
        else if(gPlayer1Wins[duelid] < gPlayer2Wins[duelid])
        {
            SendMsgAllF(COLOR_ORANGE, "** DUEL ** "C_WHITE"%p (%d) won a duel against %p (%d) with the score of %d:%d", player2, player2, player1, player1, gPlayer2Wins[duelid], gPlayer1Wins[duelid]);
            GivePlayerMoney(player2, gBet[duelid]);
            GivePlayerMoney(player1, -gBet[duelid]);
        }
        else if(gPlayer1Wins[duelid] == gPlayer2Wins[duelid])
        {
            SendMsgAllF(COLOR_ORANGE, "** DUEL ** "C_WHITE"%p (%d) and %p (%d) has tied in a duel");
        } 
        DeleteDuel(player1, player2, duelid);
    }
    else StartDuel(duelid);
}

static ClearDuel(duelid)
{
    gPlayer1[duelid] = INVALID_PLAYER_ID;
    gPlayer1Wins[duelid] = 
    gPlayer1Lose[duelid] = 0;

    gPlayer2[duelid] = INVALID_PLAYER_ID;
    gPlayer2Wins[duelid] = 
    gPlayer2Lose[duelid] = 0;

    gRounds[duelid] = 
    gCurrRound[duelid] = 
    gBet[duelid] = 0;
    Iter_Remove(gDuels, duelid);
}

static SendDuelRequest(playerid)
{
    gIsPlayerHasDuelInvite[playerid] = true;
    gAcceptTimer[playerid] = defer AcceptTimer(playerid);
}

IsPlayerInDuel(playerid) {
    if(gPlayerDuelID[playerid] != INVALID_DUEL_ID) return 1;
    return 0;
}

static CreateDuel(player1, player2, rounds, bet)
{
    new duelid = Iter_Alloc(gDuels);
    if(duelid == ITER_NONE) return 0;
    gPlayerDuelID[player1] = duelid;
    gPlayerID[player1] = 1;
    gPlayerDuelID[player2] = duelid;
    gPlayerID[player2] = 2;

    gPlayer1[duelid] = player1;
    gPlayer2[duelid] = player2;
    gRounds[duelid] = rounds;
    gBet[duelid] = bet;
    SendDuelRequest(player2);
    return 1;
}

static StartDuel(duelid)
{
    // start the duel here
    // TODO: spawn in a interior, create a count down
    new
        player1 = gPlayer1[duelid],
        player2 = gPlayer2[duelid];
    // Player 1
    GivePlayerWeapon(player1, WEAPON_CHAINSAW, 5000);
    GivePlayerWeapon(player1, WEAPON_DEAGLE, 5000);
    GivePlayerWeapon(player1, WEAPON_SAWEDOFF, 5000);
    GivePlayerWeapon(player1, WEAPON_UZI, 5000);
    GivePlayerWeapon(player1, WEAPON_M4, 5000);
    GivePlayerWeapon(player1, WEAPON_SNIPER, 5000);
    SetPlayerHealth(player1, 100.0);
    SetPlayerArmour(player1, 100.0);

    // Player 2
    GivePlayerWeapon(player2, WEAPON_CHAINSAW, 5000);
    GivePlayerWeapon(player2, WEAPON_DEAGLE, 5000);
    GivePlayerWeapon(player2, WEAPON_SAWEDOFF, 5000);
    GivePlayerWeapon(player2, WEAPON_UZI, 5000);
    GivePlayerWeapon(player2, WEAPON_M4, 5000);
    GivePlayerWeapon(player2, WEAPON_SNIPER, 5000);
    SetPlayerHealth(player2, 100.0);
    SetPlayerArmour(player2, 100.0);
}

static DeleteDuel(player1, player2, duelid)
{
    gPlayerDuelID[player1] = INVALID_DUEL_ID;
    gPlayerDuelID[player2] = INVALID_DUEL_ID;
    ClearDuel(duelid);
    return 1;
}

CMD:duel(playerid, params[])
{
    new targetid, cash, rounds;
    if(!g1v1Enabled) return SendErrorMsg(playerid, "1v1 duel system is not available");
    if(sscanf(params, "udD(0)", targetid, rounds, cash)) return SendSyntaxMsg(playerid, "/duel (name/id) (rounds) (option:cash)");
    if(targetid == playerid) return SendErrorMsg(playerid, "You can't duel yourself");
    if(!IsPlayerConnected(targetid)) return SendErrorMsg(playerid, "Player is not connected");
    if(rounds > 10 || 1 > rounds) return SendErrorMsg(playerid, "Max rounds is 10 min is 1");
    if(GetPlayerMoney(playerid) < cash) return SendErrorMsg(playerid, "You don't have enough money.");
    if(GetPlayerMoney(targetid) < cash) return SendErrorMsgF(playerid, "%p (%d) doesn't have enough money", targetid, targetid);
    if(gPlayerDuelID[playerid] != INVALID_DUEL_ID) {
        if(gIsPlayerHasDuelInvite[playerid]) return SendErrorMsgF(playerid, "You already have a request from %p (%d)", gPlayer1[gPlayerDuelID[playerid]], gPlayer1[gPlayerDuelID[playerid]]);
        else if(!gIsPlayerHasDuelInvite[playerid]) return SendErrorMsg(playerid, "You already invited someone / in a duel");
    }
    if(Player_GetWantedLevel(playerid) != 0) return SendErrorMsg(playerid, "You can't duel someone while having wanted level");
    if(Player_GetWantedLevel(targetid) != 0) return SendErrorMsg(playerid, "Player has wanted level");
    CreateDuel(playerid, targetid, rounds, cash); // create the duel
    return 1;
}

CMD:acceptduel(playerid, params[])
{
    if(!g1v1Enabled) return SendErrorMsg(playerid, "1v1 duel system is not available");
    if(!gIsPlayerHasDuelInvite[playerid]) return SendErrorMsg(playerid, "You don't have any request");
    gIsPlayerHasDuelInvite[playerid] = false;
    stop gAcceptTimer[playerid];
    StartDuel(gPlayerDuelID[playerid]);
    return 1;
}

ACMD:[1]tog1v1(playerid, params[])
{
    if(!g1v1Enabled)
    {
        SendAdminMsgF("%p (%d) turned on the 1v1 system", playerid, playerid);
        g1v1Enabled = true;
    } else if(g1v1Enabled) {
        SendAdminMsgF("%p (%d) turned off the 1v1 system", playerid, playerid);
        g1v1Enabled = false;
    }
    return 1;
}

timer AcceptTimer[30000](playerid)
{
    new duelid = gPlayerDuelID[playerid];
    gIsPlayerHasDuelInvite[playerid] = false;
    SendServerMsgF(gPlayer1[duelid], "%p (%d) refuses to duel with you", gPlayer2[duelid], gPlayer2[duelid]);
    DeleteDuel(gPlayer1[duelid], gPlayer2[duelid], duelid);
}