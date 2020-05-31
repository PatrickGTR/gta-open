#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <formatex>
#include <logger>
#include <mysql_prepared>

static
    skin[MAX_PLAYERS]
;

new PlayerIsRegistered[MAX_PLAYERS];

static
    Statement:stmt_loadPlayerStats,
    gPlayerHash[MAX_PLAYERS][250],
    bool:gPlayerLoginStatus[MAX_PLAYERS];


// Initialise
hook OnMySQLConnected(playerid) {
    stmt_loadPlayerStats = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT kills, deaths, job_id, wanted_level, money, skin FROM player_stats WHERE u_id = ?");
}

hook OnPlayerConnect(playerid) {
    gPlayerHash[playerid][0] = EOS;
    gPlayerLoginStatus[playerid] = false;
}

// Global 
Account_PromptLogin(playerid, const password[], len = sizeof(password)) {

    PlayerIsRegistered[playerid] = 1;
    if(isnull(gPlayerHash[playerid])) {
        strcat(gPlayerHash[playerid], password, len);
    }

    inline PromptLoginResponse(pid, dialogid, response, listitem, string:inputtext[]) {
         #pragma unused pid, dialogid, listitem

        // User clicked the 'leave' buton or pressed 'ESC' .
        if(!response) {
            Kick(playerid);
            return;
        }

        bcrypt_verify(playerid, "OnPasswordVerify", inputtext, gPlayerHash[playerid]);
    }

    new string[MAX_PLAYER_NAME + 35];
    format(string, sizeof(string), "Hello %p! Welcome back to %s", playerid, SERVER_NAME);

    Dialog_ShowCallback(playerid, 
        using inline PromptLoginResponse,   // Handler
        DIALOG_STYLE_PASSWORD,              // Style  
        "Please Login...",                  // Title
        string,                             // Content
        "Login",                            // Button Left
        "Leave");                           // Button Right
}

// Local
static Account_LoadData(playerid) {
    inline OnDataLoad() {
        new 
            kills, 
            deaths,
            jobID, 
            wantedLevel,
            player_money,
            player_skin;
        MySQL_BindResultInt(stmt_loadPlayerStats, 0, kills);
        MySQL_BindResultInt(stmt_loadPlayerStats, 1, deaths);
        MySQL_BindResultInt(stmt_loadPlayerStats, 2, jobID);
        MySQL_BindResultInt(stmt_loadPlayerStats, 3, wantedLevel);
        MySQL_BindResultInt(stmt_loadPlayerStats, 4, player_money);
        MySQL_BindResultInt(stmt_loadPlayerStats, 5, player_skin);


        if(MySQL_Statement_FetchRow(stmt_loadPlayerStats)) {
            
            Player_SetKills(playerid, kills);
            Player_SetDeaths(playerid, deaths);
            Player_SetJob(playerid, jobID);
            SetPlayerWantedLevel(playerid, wantedLevel);
            GivePlayerMoney(playerid, player_money);
            SetPlayerSkin(playerid, player_skin);
            skin[playerid] = player_skin;
    
            static const 
                msg_title[] = "~g~Welcome back!",
                msg_content[] = "Hello ~p~%p, ~w~Welcome back to ~p~%s. ~n~~n~~y~Enjoy your stay!";
            MessageBox_ShowF(playerid, TYPE_MSGBOX, msg_title, msg_content, 8000, playerid, SERVER_NAME);

            CallLocalFunction("OnPlayerLogin", "i", playerid); // Used in other modules to load other data.

            gPlayerLoginStatus[playerid] = true;

            dbg("player", "player successfully logged in", 
                _p("username", playerid), 
                _i("uid", Player_GetAccountID(playerid)));
        }
    }

    MySQL_BindInt(stmt_loadPlayerStats, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerStats, using inline OnDataLoad);
}

// Bcrypt Callback

#define MAX_PASSWORD_ATTEMPT (5)

static 
    Player_Attempts[MAX_PLAYERS];

forward OnPasswordVerify(playerid, bool:success);
public OnPasswordVerify(playerid, bool:success) {
    if(!success) {
        SendErrorMsgF(playerid, "Wrong password, try again! - Attempts: [%i/%i]", Player_Attempts, MAX_PASSWORD_ATTEMPT);
        Account_PromptLogin(playerid, gPlayerHash[playerid]);

        if(Player_Attempts[playerid] >= MAX_PASSWORD_ATTEMPT) {
            SendErrorMsg(playerid, "You have been kicked from the server for attempting to login numerous times.");
            Kick(playerid);

            dbg("player", "player has been kicked for too many login attempts", 
                _p("username", playerid), 
                _i("uid", Player_GetAccountID(playerid)) 
            );
            return;
        }

        dbg("player", "player failed to login",
            _i("attemps", Player_Attempts[playerid]),
            _p("username", playerid),
            _i("uid", Player_GetAccountID(playerid))
        );

        Player_Attempts[playerid] ++;
        return;
    }

    Account_LoadData(playerid);
    Player_Attempts[playerid] = 0;
    SpawnPlayer(playerid);
}

hook OnPlayerSpawn(playerid)
{
    if(PlayerIsRegistered[playerid] == 0) {
        new string[256];

        static const query[] = "\
        INSERT INTO \
            player_stats(u_id, skin) \
        VALUES \
            (%i, %i) \
        ON DUPLICATE KEY UPDATE \
            skin = %i \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), GetPlayerSkin(playerid), GetPlayerSkin(playerid));
        mysql_tquery(MySQL_GetHandle(), string);
    }
    SetPlayerSkin(playerid, skin[playerid]);
    return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
    if(Player_IsLoggedIn(playerid)) {
        defer SpawningPlayer(playerid);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    new string[256], string2[256];

    static const query[] = "\
    INSERT INTO \
        player_stats(u_id, money) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        money = %i \
    ";
    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, Player_GetAccountID(playerid), GetPlayerMoney(playerid), GetPlayerMoney(playerid));
    mysql_tquery(MySQL_GetHandle(), string);

    static const query2[] = "\
    INSERT INTO \
        player_stats(u_id, skin) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        skin = %i \
    ";
    mysql_format(MySQL_GetHandle(), string2, sizeof(string2), query2, Player_GetAccountID(playerid), GetPlayerSkin(playerid), GetPlayerSkin(playerid));
    mysql_tquery(MySQL_GetHandle(), string2);
    return 1;
}

timer SpawningPlayer[1000](playerid)
{
    SpawnPlayer(playerid);
}

CMD:kill(playerid) {
    SetPlayerHealth(playerid, 0);
    return 1;
}

 // API
Player_IsLoggedIn(playerid) {
    return gPlayerLoginStatus[playerid];
}
