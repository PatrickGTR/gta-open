#include <a_mysql>
#include <YSI_Coding\y_hooks>
#include <logger>

// Damage
DEFINE_HOOK_REPLACEMENT__(Damage, Dmg);

static
    MySQL:MySQL_ConHandle;

main() { }

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid) {
		case 1136: printf("[MySQL] Error 1136 | Column count does not match value count => \"%s\"", query);
		case 1054: printf("[MySQL] Error 1054 | Invalid field name => \"%s\"", query);
		case 1065: printf("[MySQL] Error 1065 | Query was empty (variable's size too small?) => \"%s\" from \"%s\"", query, callback);
		case 1058: printf("[MySQL] Error 1058 | Column count doesn't match value count => \"%s\" from \"%s\"", query, callback);
		case 1203: printf("[MySQL] Error 1203 | User already has more than 'max_user_connections' active connections => \"%s\" from \"%s\"", query, callback);
		case 1045: printf("[MySQL] Error 1045 | Access denied");
		case ER_SYNTAX_ERROR: printf("[MySQL] Syntax Error => \"%s\"",query);

		default : printf("[MySQL] Error %d | Callback: %s | \"%s\"", errorid, callback, query);
	}
	return 1;
}

hook OnGameModeInit() {

    print("[first call OnGameModeInit] setting up...");

    Logger_ToggleDebug(PLAYER_DEBUG_HANDLER, true);
	Logger_ToggleDebug(ADMIN_DEBUG_HANDLER, true);
	Logger_ToggleDebug(SERVER_DEBUG_HANDLER, true);

    new
        MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true); // it automatically reconnects when loosing connection to mysql server

    MySQL_ConHandle = mysql_connect_file("mysql.ini");

    if(MySQL_ConHandle == MYSQL_INVALID_HANDLE || mysql_errno(MySQL_ConHandle) != 0) {
        Logger_Fatal("MySQL failed to connect. Server shutting down...");
        return 1;
    }

    #if defined SETUP_TABLE
        CallLocalFunction("OnMySQLSetupTable", "");
    #endif

    CallLocalFunction("OnMySQLConnected", "");
    Logger_Log("MySQL connection is successful.");
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

