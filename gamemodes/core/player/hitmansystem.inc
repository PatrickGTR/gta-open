#include <YSI_Coding\y_hooks>
static 
    PlayerBounty[MAX_PLAYERS],
    Statement:stmt_savePlayerBounty
;

enum {
    hitlist
};

hook OnMySQLConnected() {
    stmt_savePlayerBounty = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE players SET player_bounty = ? WHERE u_id = ?");
    return 1;
}

Player_SetBounty(playerid, bounty, bool:save = false) {


    if(save) {
        MySQL_BindInt(stmt_savePlayerBounty, 0, bounty);
        MySQL_BindInt(stmt_savePlayerBounty, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerBounty);
    }

    PlayerBounty[playerid] = bounty;
    return 1;
}

Player_GetBounty(playerid) {
    return PlayerBounty[playerid];
}

CMD:hit(playerid, params[])
{
    new target, hitm;
    if(sscanf(params, "ui", target, hitm)) return SendSyntaxMsg(playerid, "/hit [player] [bounty]");
    if(target == INVALID_PLAYER_ID) return SendErrorMsg(playerid, "The player is not connected");
    if(target == playerid) return SendErrorMsg(playerid, "You can't place a hit on yourself");
    Player_SetBounty(playerid, hitm, true);
    SendServerMsgF(playerid, "You have placed a bounty on %p (%d) for %d", target, target, hitm);
    SendServerMsgF(target, "%p (%d) has placed a bounty on you for %d", playerid, playerid, hitm);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(Player_GetJob(i) == TYPE_HITMAN)
        {
            SendServerMsgF(i, "%p (%d) has placed a bounty on %p (%d) for %d", playerid, playerid, target, target, hitm);
        }
    }
    return 1;
}

CMD:hits(playerid)
{
    if(Player_GetJob(playerid) == TYPE_HITMAN)
    {
        for(new i=0; i < MAX_PLAYERS; i++)
        {
            if(Player_GetBounty(i) >= 1)
            {
                new string[128];
                format(string, sizeof(string), "%p (%d) has %d", i, i, Player_GetBounty(i));
                ShowPlayerDialog(playerid, hitlist, DIALOG_STYLE_MSGBOX, "HITS", string, "Done", "");
            }
        }
    }
    else return SendErrorMsg(playerid, "You're not a hitman!");
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    if(Player_GetBounty(playerid) >= 1)
    {
        new hitmoney = Player_GetBounty(playerid);
        GivePlayerMoney(killerid, hitmoney);
        SendMsgAllF(-1, "%p (%d) killed %p (%d) for %d", killerid, killerid, playerid, playerid, Player_GetBounty(playerid));
        Player_SetBounty(playerid, 0, true);
    }
    return 1;
}