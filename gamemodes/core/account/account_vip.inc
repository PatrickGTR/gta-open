#include <YSI_Coding\y_hooks>

static
    Player_VIPLevel[MAX_PLAYERS]
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
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerVIPLoad()
    {
        if (cache_num_rows())
        {
            new
                expire,
                expiry_date[20];

            cache_get_value_name_int(0, "vip_level", Player_VIPLevel[playerid]);
            cache_get_value_name_int(0, "expire", expire);
            cache_get_value_name(0, "expiry", expiry_date, 20);

            if (expire <= 0)
            {
                VIP_RemovePlayer(playerid);
                SendServerMsgF(playerid, "Your VIP expired on "C_GREY"%s", expiry_date);
                Player_VIPLevel[playerid] = 0;
                return;
            }

            SendServerMsgF(playerid, "You have logged in as VIP level %i", VIP_GetPlayerLevel(playerid));
        }
    }

    static const query[] = "\
        SELECT *, \
            DATE_FORMAT(vip_expire_date, '"SQL_DATETIME_FORMAT"') as expiry, \
            TIMESTAMPDIFF(SECOND, CURRENT_TIMESTAMP(), vip_expire_date) as expire \
        FROM vips \
        WHERE \
            u_id = %i LIMIT 1"
    ;
	MySQL_TQueryInline(MySQL_GetHandle(), using inline OnPlayerVIPLoad, query, GetPlayerAccountID(playerid));
}

stock VIP_GivePlayer(playerid, level, interval_type, duration) {
	new 
		query[256],
        interval[6]
    ;
	interval = interval_type == 0 ? ("MONTH") : ("YEAR");

	mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO vips \
	(u_id, vip_level, vip_expire_date) \
	VALUES(%i, %i, DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL %i %s))", GetPlayerAccountID(playerid), level, duration, interval);
    mysql_tquery(MySQL_GetHandle(), query, "", "");
    Player_VIPLevel[playerid] = level;
}

stock VIP_RemovePlayer(playerid) {
	new 
		query[45 + MAX_PLAYER_NAME];

	mysql_format(MySQL_GetHandle(), query, sizeof(query), "DELETE FROM vips WHERE u_id = %i", GetPlayerAccountID(playerid));
	mysql_tquery(MySQL_GetHandle(), query);
}

stock VIP_GetPlayerLevel(playerid) {
    return Player_VIPLevel[playerid];
}