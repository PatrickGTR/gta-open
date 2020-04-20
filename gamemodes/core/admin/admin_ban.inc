#include <YSI_Coding\y_hooks>

#if defined SETUP_TABLE
    #include <admin_setup-table>
#endif

#include <admin_ban-cmd>

// Create a new entry on the database.
// allows you to ban player from day, month upto a year.
// returns whether the query was sent successfully.
Ban_AddUser(playerid, byid = INVALID_PLAYER_ID, reason[], interval_type, banduration) {
    new
        playerIP[16 + 1],
        bannerName[MAX_PLAYER_NAME],
        string[512],
        playerGCPI[60],
        playerName[MAX_PLAYER_NAME]
    ;

    GetPlayerName(playerid, playerName, sizeof(playerName));
    GetPlayerIp(playerid, playerIP, sizeof(playerIP));
    gpci(playerid, playerGCPI, sizeof(playerGCPI));

    strcpy(bannerName, (byid == INVALID_PLAYER_ID ? "SERVER" : playerName) , MAX_PLAYER_NAME);

    new
        interval[6]
    ;
    switch(interval_type) {
        case 0: strcpy(interval, "DAY", sizeof(interval));
        case 1: strcpy(interval, "MONTH", sizeof(interval));
        case 2: strcpy(interval, "YEAR", sizeof(interval));
    }

    static const query[] = "\
        INSERT INTO bans \
            (username, ip, gcpi, reason, admin, ban_date, unban_date) \
        VALUES \
            ('%e', '%e', '%e', '%e', '%e',  CURRENT_TIMESTAMP(), DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL %i %s))"
    ;
    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, playerName, playerIP, playerGCPI, reason, bannerName, banduration, interval);

    dbg("admin", "admin has banned", _p("user", playerid), _p("admin", byid));
    return mysql_tquery(MySQL_GetHandle(), string);
}

// removes the user entry from the table by username.
// returns whether the query was sent successfully.
Ban_RemoveUser(username[], playerid = INVALID_PLAYER_ID) {
    new
        string[45 + MAX_PLAYER_NAME],
        name[MAX_PLAYER_NAME];

    strcpy(name, username, MAX_PLAYER_NAME);

    inline OnPlayerRemoveBan() {
        if (!cache_num_rows()) {
            if (playerid != INVALID_PLAYER_ID) {
                SendServerMsgF(playerid, "The account "C_GREY"(%s) "C_WHITE"you are trying to unban is not in the database.", name);
                dbg("admin", "admin attempted to unban", _p("admin", playerid), _s("username", name));
                return 1;
            }
        }
    
        mysql_format(MySQL_GetHandle(), string, sizeof(string), "DELETE FROM bans WHERE username = '%e'", name);
        mysql_tquery(MySQL_GetHandle(), string, "", "");
        if (playerid != INVALID_PLAYER_ID) {
            SendServerMsgF(playerid, "You successfully unbanned "C_GREY"%s's "C_WHITE"account.", name);
            dbg("admin", "admin has successfully unbanned", _p("admin", playerid), _s("username", name));
        }
    }

    static const query[] = "\
        SELECT \
            username \
        FROM \
            bans \
        WHERE \
            username = '%e'"
    ;
    return MySQL_TQueryInline(MySQL_GetHandle(), using inline OnPlayerRemoveBan, query, username, playerid);
}

// check if player is banned by username, ip or gcpi.
// returns whether the query count(*) returns a row.
Ban_Check(playerid) {

    new
        playerIP[20],
        playerGCPI[60],
        playerName[MAX_PLAYER_NAME]
    ;
    GetPlayerIp(playerid, playerIP, sizeof(playerIP));
    gpci(playerid, playerGCPI, sizeof(playerGCPI));
    GetPlayerName(playerid, playerName, sizeof(playerName));

    static const query[] = "\
        SELECT \
            COUNT(*) \
        FROM \
            bans \
        WHERE \
            username = '%e' OR gcpi = '%e' OR ip = '%e' LIMIT 1"
    ;

    new string[128 + MAX_PLAYER_NAME + 20];
    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, playerName, playerGCPI, playerIP);
    new Cache:res = mysql_query(MySQL_GetHandle(), string);
    new bool:ret = false;
    cache_get_value_index_int(0, 0, ret);
    cache_delete(res);
    return ret;
}


// retrieves the player's ban details.
// username, ip, admin who banned the user, reason, unban date, ban date.
// this callback returns whether the ban has expired or not.
Ban_GetData(playerid, username[], ip[], reason[], admin[], bandate[], unbandate[]) {

    static const query[] = "\
        SELECT \
        *,  DATE_FORMAT(ban_date,'"SQL_DATETIME_FORMAT"') AS date_ban, \
            DATE_FORMAT(unban_date,'"SQL_DATETIME_FORMAT"') AS date_unban, \
            TIMESTAMPDIFF(SECOND, CURRENT_TIMESTAMP(), unban_date) AS expired \
        FROM \
            bans \
        WHERE \
            username = '%e' OR gcpi = '%e' OR ip = '%e' LIMIT 1"
    ;

    new
        playerIP[20],
        playerGCPI[60],
        playerName[MAX_PLAYER_NAME];
    GetPlayerIp(playerid, playerIP, sizeof(playerIP));
    gpci(playerid, playerGCPI, sizeof(playerGCPI));
    GetPlayerName(playerid, playerName, sizeof(playerName));


    new
        expired,
        string[512];

    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, playerName, playerGCPI, playerIP);
    new Cache:res = mysql_query(MySQL_GetHandle(), string);

    if (cache_num_rows()) {
        cache_get_value_name(0, "username", username, MAX_PLAYER_NAME);
        cache_get_value_name(0, "ip",  ip, 20);
        cache_get_value_name(0, "admin", admin, MAX_PLAYER_NAME);
        cache_get_value_name(0, "reason", reason, MAX_BAN_REASON);

        cache_get_value_name(0, "date_ban", bandate, 40);
        cache_get_value_name(0, "date_unban", unbandate, 40);

        cache_get_value_name_int(0, "expired", expired);

    }
    cache_delete(res);
    return (expired <= 0);
}

