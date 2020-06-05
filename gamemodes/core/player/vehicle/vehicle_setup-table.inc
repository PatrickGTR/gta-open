#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    mysql_tquery(MySQL_GetHandle(),
  		"CREATE TABLE IF NOT EXISTS player_vehicles ( \
  		vehicle_id int(11) NOT NULL AUTO_INCREMENT, \
  		u_id int(11) DEFAULT NULL, \
  		model_id smallint(4) NOT NULL, \
  		x float DEFAULT NULL, \
  		y float NOT NULL, \
  		z float NOT NULL, \
  		rot float NOT NULL, \
  		color_1 tinyint(4) NOT NULL, \
  		color_2 tinyint(4) NOT NULL, \
  		intid tinyint(4) NOT NULL, \
  		vworld smallint(6) NOT NULL, \
  		PRIMARY KEY (vehicle_id), \
  		FOREIGN KEY (u_id) REFERENCES players(u_id) ON DELETE CASCADE ON UPDATE CASCADE)");

  	mysql_tquery(MySQL_GetHandle(), "\
    CREATE TABLE IF NOT EXISTS \
        vehicle_components (\
  		vehicle_id int(11) DEFAULT NULL, \
  		component_id smallint(6) NOT NULL, \
  		slot smallint(2) NOT NULL, \
  		PRIMARY KEY (vehicle_id, slot), \
  		FOREIGN KEY (vehicle_id) REFERENCES player_vehicles(vehicle_id) ON DELETE CASCADE ON UPDATE CASCADE)");
    return 1;
}