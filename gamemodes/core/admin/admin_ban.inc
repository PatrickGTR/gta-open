#include <YSI_Coding\y_hooks>

#include <admin_ban-cmd>

static 
    Statement: stmt_checkBan;

hook OnMySQLConnected() {

    static const checkQuery[] = "\
        SELECT \
            *,  DATE_FORMAT(ban_date,'"SQL_DATETIME_FORMAT"') AS date_ban, \
            DATE_FORMAT(unban_date,'"SQL_DATETIME_FORMAT"') AS date_unban, \
            TIMESTAMPDIFF(SECOND, CURRENT_TIMESTAMP(), unban_date) AS expired \
        FROM \
            bans \
        WHERE \
            username = ? OR gcpi = ? OR ip = ? LIMIT 1\
    ";
    stmt_checkBan = MySQL_PrepareStatement (MySQL_GetHandle(), checkQuery);
}

hook OnPlayerConnect(playerid) {
    Ban_CheckUser(playerid);
    return 1;
}

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

Ban_CheckUser(playerid) {
    new
        playerIP[20],
        playerGCPI[60],
        playerName[MAX_PLAYER_NAME];
    GetPlayerIp(playerid, playerIP, sizeof(playerIP));
    gpci(playerid, playerGCPI, sizeof(playerGCPI));
    GetPlayerName(playerid, playerName, sizeof(playerName));

    inline OnPlayerBanLoad() {
        new
            banIP[16 + 1],
            banName[MAX_PLAYER_NAME],
            banAdmin[MAX_PLAYER_NAME],
            banReason[MAX_BAN_REASON],
            banDate[40],
            unbanDate[40],
            expired;

        if (cache_num_rows()) {
            cache_get_value_name(0, "username", banName, MAX_PLAYER_NAME);
            cache_get_value_name(0, "ip",  banIP, 20);
            cache_get_value_name(0, "admin", banAdmin, MAX_PLAYER_NAME);
            cache_get_value_name(0, "reason", banReason, MAX_BAN_REASON);

            cache_get_value_name(0, "date_ban", banDate, 40);
            cache_get_value_name(0, "date_unban", unbanDate, 40);

            cache_get_value_name_int(0, "expired", expired);

            if (expired <= 0) {
                SendMsgF(playerid, COLOR_WHITE, "Your ban expired on "C_GREY"%s "C_WHITE"\nWelcome back %p(%i), don't break any rules again", unbanDate, playerid, playerid);
                Ban_RemoveUser(banName, INVALID_PLAYER_ID);
            }
            else {
                new string[512];
                format(string, sizeof(string), "\
                    "C_WHITE"Username: "C_GREY"%s\n\
                    "C_WHITE"Banned IP: "C_GREY"%s\n\
                    "C_WHITE"Current IP: "C_GREY"%s\n\
                    "C_WHITE"Banned By: "C_GREY"%s\n\
                    "C_WHITE"Reason of Ban: "C_GREY"%s\n\
                    "C_WHITE"Date of Ban: "C_GREY"%s\n\
                    "C_WHITE"Date of Unban: "C_GREY"%s", banName, banIP, playerIP, banAdmin, banReason, banDate, unbanDate);
                Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Ban Information", string, "Close", "");
                Kick(playerid);
            }
        } else {
            CallLocalFunction("OnPlayerPassedBanCheck", "i", playerid);
        }
    }

    MySQL_Bind(stmt_checkBan, 0, playerName);
    MySQL_Bind(stmt_checkBan, 1, playerGCPI);
    MySQL_Bind(stmt_checkBan, 2, playerIP);

    MySQL_ExecuteParallel_Inline(stmt_checkBan, using inline OnPlayerBanLoad);
}

