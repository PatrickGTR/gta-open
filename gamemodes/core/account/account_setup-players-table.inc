#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{   
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS players \
        (\
            u_id int(11) NOT NULL AUTO_INCREMENT,\
            username varchar(24) NOT NULL,\
            password char(250) NOT NULL,\
            kills mediumint(8) NOT NULL DEFAULT '0',\
            deaths mediumint(8) NOT NULL DEFAULT '0',\
            job_id tinyint(4) NOT NULL DEFAULT '0',\
            wanted_level mediumint(6) NOT NULL DEFAULT '0',\
            PRIMARY KEY (u_id), \
            UNIQUE KEY username (username)\
        )";
    mysql_tquery(MySQL_GetHandle(), query);

    log("setting up 'players' table...");
    return 1;
}
