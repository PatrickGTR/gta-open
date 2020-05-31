#include <YSI_Coding\y_hooks>

static 
    Statement:stmt_loadPlayerStats,
    Statement:stmt_insertPlayerStats;

hook OnMySQLConnected() {

    static const loadQuery[] ="\
    SELECT \
        kills, \
        deaths, \
        job_id, \
        wanted_level, \
        money, \
        skin, \
        class_id \
    FROM \
        player_stats \
    WHERE \
        u_id = ?";

   
    stmt_loadPlayerStats = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    
    stmt_insertPlayerStats = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO player_stats (u_id) VALUES (?)");
}

hook OnPlayerLogin(playerid) {
    Account_LoadStats(playerid);
    return 1;
}

hook OnPlayerRegister(playerid) {
     // insert stats default data.
    MySQL_BindInt(stmt_insertPlayerStats, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_insertPlayerStats);
}

static Account_LoadStats(playerid) {
    inline OnDataLoad() {
        new 
            kills, 
            deaths,
            jobID, 
            wantedLevel,
            playerMoney,
            playerSkin,
            playerClass;
        MySQL_BindResultInt(stmt_loadPlayerStats, 0, kills);
        MySQL_BindResultInt(stmt_loadPlayerStats, 1, deaths);
        MySQL_BindResultInt(stmt_loadPlayerStats, 2, jobID);
        MySQL_BindResultInt(stmt_loadPlayerStats, 3, wantedLevel);
        MySQL_BindResultInt(stmt_loadPlayerStats, 4, playerMoney);
        MySQL_BindResultInt(stmt_loadPlayerStats, 5, playerSkin);
        MySQL_BindResultInt(stmt_loadPlayerStats, 6, playerClass);

        if(MySQL_Statement_FetchRow(stmt_loadPlayerStats)) {

            printf("kills %i, deaths %i, job id: %i", kills, deaths, jobID);
            printf("wanted: %i, money: %i, skin: %i", wantedLevel, playerMoney, playerSkin);
            printf("class: %i", playerClass);
            

            Player_SetKills(playerid, kills);
            Player_SetDeaths(playerid, deaths);
            Player_SetJob(playerid, jobID);
            SetPlayerWantedLevel(playerid, wantedLevel);
            GivePlayerMoney(playerid, playerMoney);
            SetPlayerSkin(playerid, playerSkin);
            Player_SetClass(playerid, playerClass);
        }
    }

    MySQL_BindInt(stmt_loadPlayerStats, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerStats, using inline OnDataLoad);
}