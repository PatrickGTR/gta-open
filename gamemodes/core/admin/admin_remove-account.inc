void:Acc_Remove(username[], playerid = INVALID_PLAYER_ID)
{
    new 
        string[45 + MAX_PLAYER_NAME],
        name[MAX_PLAYER_NAME];
    strcpy(name, username, MAX_PLAYER_NAME);

    inline OnPlayerRemoveAcc() {
        if (!cache_num_rows()) {
            if (playerid != INVALID_PLAYER_ID) {
                SendServerMsgF(playerid, "The Account (%s) does not exist in the database", name);
                dbg(PLAYER_DEBUG_HANDLER, "Attempted to remove Account", _s("username", name));
                return;
            }
        }

        mysql_format(MySQL_GetHandle(), string, sizeof(string), "DELETE FROM players WHERE username = '%e'", name);
        mysql_tquery(MySQL_GetHandle(), string, "", "");
        if (playerid != INVALID_PLAYER_ID) {
            SendServerMsgF(playerid, "You successfully Removed "C_GREY"%s's "C_WHITE"account.", name);
            dbg(PLAYER_DEBUG_HANDLER, "Account has been successfully removed the Account", _s("username", name));
        }
    }

    static const query[] = "\
        SELECT \
            username \
        FROM \
            players \
        WHERE \
            username = '%e'"
    ;
    MySQL_TQueryInline(MySQL_GetHandle(), using inline OnPlayerRemoveAcc, query, username, playerid);
}

ACMD:[5]deleteacc(playerid, params[])
{
    if (isnull(params) || strval(params)) {
        return SendSyntaxMsg(playerid, "/deleteacc <playername>");
    }
    if (strlen(params) > MAX_PLAYER_NAME) {
        return SendErrorMsg(playerid, "MAX_PLAYER_NAME = 24, type the name again!");
    }

    Acc_Remove(params, playerid);
    return 1;
}