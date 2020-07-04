#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS atms \
    ( \
    	atm_id INT(11) NOT NULL, \
    	atm_x  FLOAT NOT NULL, \
        atm_y  FLOAT NOT NULL, \
        atm_z  FLOAT NOT NULL, \
        atm_a  FLOAT NOT NULL, \
        wid TINYINT(6) NOT NULL, \
        interior TINYINT(6) NOT NULL, \
    	PRIMARY KEY (atm_id) \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("setting up 'atms' table...");
    return 1;
}