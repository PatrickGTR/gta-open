#include <a_mysql>
#include <YSI_Coding\y_hooks>
#include <logger>


main() {
	print("[main] gamemode initialised.");
}


static
    MySQL:MySQL_ConHandle;

hook OnGameModeInit() {

    print("[first call OnGameModeInit] setting up...");

    Logger_ToggleDebug(PLAYER_DEBUG_HANDLER, true);
	Logger_ToggleDebug(ADMIN_DEBUG_HANDLER, true);
	Logger_ToggleDebug(SERVER_DEBUG_HANDLER, true);

    new 
        MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true); // it automatically reconnects when loosing connection to mysql server 

    new 
        username[24],
        host[24],
        password[24],
        database[24];

    if(Env_Has("MYSQL_USERNAME")) {
        Env_Get("MYSQL_USERNAME", username);
    } 
    else {
        Logger_Log("Could not find environment variable for MYSQL_USERNAME");
    }
    
    if(Env_Has("MYSQL_PASSWORD")) {
        Env_Get("MYSQL_PASSWORD", password);
    }
    else {
        Logger_Log("Could not find environment variable for MYSQL_PASSWORD");
    }

    if(Env_Has("MYSQL_HOST")) {
        Env_Get("MYSQL_HOST", host);
    } 
    else {
        Logger_Log("Could not find environment variable for MYSQL_HOST");
    }
    
    if(Env_Has("MYSQL_DATABASE")) {
        Env_Get("MYSQL_DATABASE", database);
    }
    else {
        Logger_Log("Could not find environment variable for MYSQL_DATABASE");
    }
    
    MySQL_ConHandle = mysql_connect(host, username, password, database);

    if(MySQL_ConHandle == MYSQL_INVALID_HANDLE || mysql_errno(MySQL_ConHandle) != 0) {
        Logger_Fatal("MySQL failed to connect. Server shutting down...");
        return 1;
    }

    Logger_Log("MySQL connection is successful.");
    CallLocalFunction("OnMySQLConnected", "");
    return 1;
}

hook OnGameModeExit() {
    CallLocalFunction("OnMySQLPreClose", "");
    Logger_Log("MySQL connection has been closed.");
    mysql_close(MySQL_ConHandle);
}

stock MySQL:MySQL_GetHandle() {
    return MySQL_ConHandle;
}

