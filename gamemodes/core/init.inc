#include <a_mysql>
#include <YSI_Coding\y_hooks>
#include <logger>


main() {
	log("gamemode initialised.");
	logger_debug(PLAYER_DEBUG_HANDLER, true);
	logger_debug("admin", true);
}


static 
    MySQL:MySQL_ConHandle;

// TODO: move to environment var or .ini config.
static const 
    MYSQL_HOST[]    = "localhost",
    MYSQL_PW[]      = "",
    MYSQL_DB[]      = "gta-open",
    MYSQL_USER[]    = "root";

hook OnGameModeInit() {
    new MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true); // it automatically reconnects when loosing connection to mysql server

    MySQL_ConHandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PW, MYSQL_DB, option_id);

    if(MySQL_ConHandle == MYSQL_INVALID_HANDLE || mysql_errno(MySQL_ConHandle) != 0) {
        fatal("MySQL failed to connect. Server shutting down...");
        SendRconCommand("exit");
        return 1;
    }

    CallLocalFunction("OnMySQLConnected", "");
    log("MySQL connection is successful.");
    return 1;
}

hook OnGameModeExit() {
    CallLocalFunction("OnMySQLPreClose", "");
    mysql_close(MySQL_ConHandle);
    log("MySQL connection has been closed.");
}

stock MySQL:MySQL_GetHandle() {
    return MySQL_ConHandle;
}

