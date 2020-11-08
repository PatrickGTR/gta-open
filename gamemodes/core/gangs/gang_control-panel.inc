#include <YSI_Coding\y_hooks>

static
    Timer:ganginvitationtimer[MAX_PLAYERS]
;

static 
    Statement: stmt_insertPGang,
    Statement: stmt_deletePGang,
    Statement: stmt_updatePRank;

static
    bool:PlayerGangInvited[MAX_PLAYERS],
    GangOwner[MAX_PLAYERS];

hook OnMySQLConnected()
{
    static const insertQuery[] = "\
    INSERT INTO \
        player_gang(g_id, u_id) \
    VALUES \
        (?,?) \
    ";
    stmt_insertPGang = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const deleteQuery[] = "\
    DELETE FROM \
        player_gang \
    WHERE \
        u_id = ?\
    ";
    stmt_deletePGang = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);

    static const updateQuery[] = "\
    UPDATE \
        player_gang \
    SET \
        gRank = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_updatePRank = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);
    return 1;
}

CMD:gangkick(playerid, params[])
{
    new target;
    if(Player_GetGangRank(playerid) < 7) return SendErrorMsg(playerid, "Your not Level 7 Up");
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/gangkick (name/id)");
    if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
    MySQL_BindInt(stmt_deletePGang, 0, Player_GetAccountID(target));
    MySQL_ExecuteThreaded(stmt_deletePGang);
    SendMsgF(playerid, COLOR_RED, "[GANG KICK]:"C_WHITE" You have kicked %p (%d) from the gang", target, target);
    SendMsgF(target, COLOR_RED, "[GANG KICK]:"C_WHITE" You have been kicked out from your gang");
    Player_SetGangRank(target, 0);
    Player_SetGangID(target, 0);
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(Player_GetGangID(i) == Player_GetGangID(playerid))
            {
                SendMsgF(i, COLOR_RED, "[GANG KICK]:"C_WHITE" %p (%d) has been kicked out from the gang", target, target);
            }
        }
    }
    return 1;
}

CMD:ganginvite(playerid, params[])
{
    new target;
    if(Player_GetGangRank(playerid) < 7) return SendErrorMsg(playerid, "Your not Level 7 Up");
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/ganginvite (name/id)");
    if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
    if(Player_GetGangID(target) != 0) return SendErrorMsg(playerid, "Player is already in a gang");
    SendMsgF(target, COLOR_RED, "[GANG INVITATION]:"C_WHITE" You have been invited to %s by %p (%d)",GetGangName(Player_GetGangID(playerid)), playerid, playerid);
    SendMsgF(playerid, COLOR_RED, "[GANG]:"C_WHITE" You have invited %p (%d) to the gang", target, target);
    PlayerGangInvited[target] = true;
    GangOwner[target] = playerid;
    ganginvitationtimer[target] = defer ACGI(target);
    return 1;
}

CMD:acceptganginvite(playerid)
{
    new target = GangOwner[playerid];
    if(!PlayerGangInvited[playerid]) {
        return SendErrorMsg(playerid, "You're not invited to any gangs");
    }
    MySQL_BindInt(stmt_insertPGang, 0, Player_GetGangID(target));
    MySQL_BindInt(stmt_insertPGang, 1, Player_GetAccountID(playerid));        
    MySQL_ExecuteThreaded(stmt_insertPGang);
    Player_SetGangID(playerid, Player_GetGangID(target));
    Player_SetGangRank(playerid, 1);
    GangOwner[playerid] = -1;
    PlayerGangInvited[playerid] = false;
    stop ganginvitationtimer[playerid];
    return 1;
}

CMD:setrank(playerid, params[])
{
    new target, rank;
    if(Player_GetGangRank(playerid) < 8) return SendErrorMsg(playerid, "Your not Level 8 Up");
    if(sscanf(params, "ui", target, rank)) return SendSyntaxMsg(playerid, "/setrank (name/id) (rank)");
    if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
    if(Player_GetGangID(target) != Player_GetGangID(playerid)) return SendSyntaxMsg(playerid, "Player is not in your gang :/");
    if(Player_GetGangRank(playerid) <= Player_GetGangRank(playerid)) return SendErrorMsgF(playerid, "Player is Equal or has Higher level than you");
    if(rank < 0 || rank > 10) return SendErrorMsg(playerid, "Player Rank max is 10");
    MySQL_BindInt(stmt_updatePRank, 0, rank);
    MySQL_BindInt(stmt_updatePRank, 1, Player_GetAccountID(playerid));        
    MySQL_ExecuteThreaded(stmt_updatePRank);
    Player_SetGangRank(target, rank);
    SendMsgF(playerid, COLOR_RED, "[GANG]:"C_WHITE" You have set the rank of %p (%d) to rank %i", target, target, rank);
    SendMsgF(target, COLOR_RED, "[GANG]:"C_WHITE" Your rank has been set to %i", rank);
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(Player_GetGangID(i) == Player_GetGangID(playerid))
            {
                SendMsgF(i, COLOR_RED, "[GANG]:"C_WHITE" %p (%d)'s rank has been set to %i", target, target, rank);
            }
        }
    }
    return 1;
}

CMD:gm(playerid, params[])
{
    new msg[128];
    if(sscanf(params, "s[128]", msg)) return SendSyntaxMsg(playerid, "/gm (message)");
    if(Player_GetGangID(playerid) == INVALID_GANG_ID) return SendErrorMsg(playerid, "You're not in a gang");
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(Player_GetGangID(i) == Player_GetGangID(playerid))
            {
                SendMsgF(i, COLOR_RED, "[GANG MESSAGE] %s %p (%d) "C_WHITE"%s", GetGangRankName(Player_GetGangID(playerid), Player_GetGangRank(playerid)), playerid, playerid, msg);
            }
        }
    }
    return 1;
}

timer ACGI[60000](playerid)
{
    PlayerGangInvited[playerid] = false;
    GangOwner[playerid] = -1;
    return 1;
}