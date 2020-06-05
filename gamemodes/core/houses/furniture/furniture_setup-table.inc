#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    mysql_tquery(MySQL_GetHandle(),
        "CREATE TABLE IF NOT EXISTS \
            house_furniture \
            (furniture_id INT(11) AUTO_INCREMENT, \
            house_id SMALLINT(6) NOT NULL, \
            object_id INT(11) NOT NULL, \
            x FLOAT(6) NOT NULL, \
            y FLOAT(6) NOT NULL, \
            z FLOAT(6) NOT NULL, \
            rx FLOAT(6) NOT NULL, \
            ry FLOAT(6) NOT NULL, \
            rz FLOAT(6) NOT NULL, \
            intid INT(11) NOT NULL, \
            vworld INT(11) NOT NULL, \
        PRIMARY KEY (furniture_id, house_id), \
        FOREIGN KEY(house_id) REFERENCES player_houses(house_id) \
        ON DELETE CASCADE ON UPDATE CASCADE)");
    return 1;
}