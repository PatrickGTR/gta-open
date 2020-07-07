#include <YSI_Coding\y_hooks>

static
    Statement:stmt_loadPlayerStats,
    Statement:stmt_insertPlayerStats,
    Statement:stmt_savePlayerScore,
    Statement:stmt_savePlayerKills,
    Statement:stmt_savePlayerDeaths;

static 
    PlayerScore[MAX_PLAYERS],
    PlayerKills[MAX_PLAYERS],
    PlayerDeaths[MAX_PLAYERS]
;


hook OnMySQLConnected() {

    static const loadQuery[] ="\
    SELECT \
        kills, \
        deaths, \
        job_id, \
        class_id, \
        wanted_level, \
        money, \
        score \
    FROM \
        player_stats \
    WHERE \
        u_id = ?";


    stmt_loadPlayerStats = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    stmt_insertPlayerStats = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO player_stats (u_id) VALUES (?)");

    static const updateQuery[] = "\
    UPDATE \
        player_stats \
    SET \
        score = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_savePlayerScore = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);

    static const updateKills[] = "\
    UPDATE \
        player_stats \
    SET \
        kills = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_savePlayerKills = MySQL_PrepareStatement(MySQL_GetHandle(), updateKills);

    static const updateDeaths[] = "\
    UPDATE \
        player_stats \
    SET \
        deaths = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_savePlayerDeaths = MySQL_PrepareStatement(MySQL_GetHandle(), updateDeaths);
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
            playerClass,
            playerScore;
        MySQL_BindResultInt(stmt_loadPlayerStats, 0, kills);
        MySQL_BindResultInt(stmt_loadPlayerStats, 1, deaths);
        MySQL_BindResultInt(stmt_loadPlayerStats, 2, jobID);
        MySQL_BindResultInt(stmt_loadPlayerStats, 3, playerClass);
        MySQL_BindResultInt(stmt_loadPlayerStats, 4, wantedLevel);
        MySQL_BindResultInt(stmt_loadPlayerStats, 5, playerMoney);
        MySQL_BindResultInt(stmt_loadPlayerStats, 6, playerScore);

        if(MySQL_Statement_FetchRow(stmt_loadPlayerStats)) {
            Player_GiveKill(playerid, kills);
            Player_SetDeaths(playerid, deaths);
            Player_SetJob(playerid, jobID);
            SetPlayerWantedLevel(playerid, wantedLevel);
            GivePlayerMoney(playerid, playerMoney);
            Player_SetClass(playerid, playerClass);
            Player_GiveScore(playerid, playerScore);
        }
    }

    MySQL_BindInt(stmt_loadPlayerStats, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerStats, using inline OnDataLoad);
}

stock Player_GiveScore(playerid, score, bool:save = false)
{
    new
        currentScore = Player_GetScore(playerid),
        newScore = currentScore + score;
    SetPlayerScore(playerid, newScore);
    if(save) {
        MySQL_BindInt(stmt_savePlayerScore, 0, newScore);
        MySQL_BindInt(stmt_savePlayerScore, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerScore);
    }
}

stock Player_RemoveScore(playerid, score) {
    new 
        currentScore = Player_GetScore(playerid),
        newScore = currentScore - score;
    SetPlayerScore(playerid, newScore);
    MySQL_BindInt(stmt_savePlayerScore, 0, newScore);
    MySQL_BindInt(stmt_savePlayerScore, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_savePlayerScore);
}

stock Player_GetScore(playerid)
    return PlayerScore[playerid];

stock Player_GetKills(playerid) 
    return PlayerKills[playerid];

stock Player_GiveKill(playerid, kills, bool:save = false) {
    new 
        currentKills = Player_GetKills(playerid),
        newKills = currentKills + kills;
    PlayerKills[playerid] = newKills;
    if(save) {
        MySQL_BindInt(stmt_savePlayerKills, 0, newKills);
        MySQL_BindInt(stmt_savePlayerKills, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerKills);
    }
}

stock Player_GetDeaths(playerid)
    return PlayerDeaths[playerid];

stock Player_SetDeaths(playerid, deaths, bool:save = false) {
    new 
        currentDeaths = Player_GetDeaths(playerid),
        newDeaths = currentDeaths + deaths;
    PlayerDeaths[playerid] = newDeaths;
    if(save) {
        MySQL_BindInt(stmt_savePlayerDeaths, 0, newDeaths);
        MySQL_BindInt(stmt_savePlayerDeaths, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerDeaths);
    }
}