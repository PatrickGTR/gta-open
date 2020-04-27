#include <YSI_Coding\y_hooks>

static
    Player_VIPLevel[MAX_PLAYERS],
    Statement: stmt_deleteVIP,
    Statement: stmt_insertVIP,
    Statement: stmt_selectVIP
;

hook OnMySQLConnected()
{
    mysql_tquery(MySQL_GetHandle(), "CREATE TABLE IF NOT EXISTS vips(\
        u_id INT(11) AUTO_INCREMENT, \
        vip_level TINYINT(2) NOT NULL DEFAULT 0, \
        vip_expire_date datetime NULL, \
        PRIMARY KEY (u_id), \
        FOREIGN KEY (u_id) REFERENCES players(u_id) ON DELETE CASCADE ON UPDATE RESTRICT)"
    );

    static const delete_Query[] = "\
        DELETE FROM \
            vips \
        WHERE \
            u_id = ?"
    ;
    stmt_deleteVIP = MySQL_PrepareStatement(MySQL_GetHandle(), delete_Query);

    static const insert_Query[] = "\
        INSERT INTO \
            vips (u_id, vip_level, vip_expire_date) \
        VALUES \
            (?, ?, DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL ? ?))"
    ;
    stmt_insertVIP = MySQL_PrepareStatement(MySQL_GetHandle(), insert_Query);

    static const select_Query[] = "\
        SELECT \
            vip_level, \
            DATE_FORMAT(vip_expire_date, '"SQL_DATETIME_FORMAT"') as expiry, \
            TIMESTAMPDIFF(SECOND, CURRENT_TIMESTAMP(), vip_expire_date) as expire \
        FROM vips \
        WHERE \
            u_id = ? LIMIT 1"
    ;
    stmt_selectVIP = MySQL_PrepareStatement(MySQL_GetHandle(), select_Query);
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerVIPLoad()
    {
        new 
            expire, 
            expiry_date[30];

        MySQL_BindResultInt(stmt_selectVIP, 0, Player_VIPLevel[playerid]);
        MySQL_BindResult(stmt_selectVIP, 1, expiry_date, sizeof(expiry_date));
        MySQL_BindResultInt(stmt_selectVIP, 2, expire);

        
        if(MySQL_Statement_FetchRow(stmt_selectVIP)) {
            if (expire <= 0) {
                VIP_RemovePlayer(playerid);
                SendServerMsgF(playerid, "Your VIP expired on "C_GREY"%s", expiry_date);
                Player_VIPLevel[playerid] = 0;
                return;
            }
            SendServerMsgF(playerid, "You have logged in as VIP level %i", VIP_GetPlayerLevel(playerid));
        }
    }

    MySQL_BindInt(stmt_selectVIP, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_selectVIP, using inline OnPlayerVIPLoad);
}

stock VIP_GivePlayer(playerid, level, interval_type, duration) {
    new interval[6];

	interval = interval_type == 0 ? ("MONTH") : ("YEAR");

    MySQL_BindInt(stmt_insertVIP, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_insertVIP, 1, level);
    MySQL_BindInt(stmt_insertVIP, 2, duration);
    MySQL_Bind(stmt_insertVIP, 3, interval);

    MySQL_ExecuteThreaded(stmt_insertVIP);
    Player_VIPLevel[playerid] = level;
}

stock VIP_RemovePlayer(playerid) {
    MySQL_BindInt(stmt_deleteVIP, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_deleteVIP);
}

stock VIP_GetPlayerLevel(playerid) {
    return Player_VIPLevel[playerid];
}