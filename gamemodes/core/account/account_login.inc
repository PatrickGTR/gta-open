#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <formatex>
#include <logger>
#include <mysql_prepared>

static
    gPlayerHash[MAX_PLAYERS][250],
    bool:gPlayerLoginStatus[MAX_PLAYERS];


// Initialise
hook OnPlayerConnect(playerid) {
    gPlayerHash[playerid][0] = EOS;
    gPlayerLoginStatus[playerid] = false;
}

// Global 
Account_PromptLogin(playerid, const password[], len = sizeof(password)) {
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
static Account_NotifySuccess(playerid) {
    static const 
        msg_title[] = "~g~Welcome back!",
        msg_content[] = "Hello ~p~%p, ~w~Welcome back to ~p~%s. ~n~~n~~y~Enjoy your stay!";
    MessageBox_ShowF(playerid, TYPE_MSGBOX, msg_title, msg_content, 8000, playerid, SERVER_NAME);
}

// Bcrypt Callback

#define MAX_PASSWORD_ATTEMPT (5)

static 
    PlayerAttempts[MAX_PLAYERS];

forward OnPasswordVerify(playerid, bool:success);
public OnPasswordVerify(playerid, bool:success) {
    if(!success) {
        PlayerAttempts[playerid] ++;
        if(PlayerAttempts[playerid] >= MAX_PASSWORD_ATTEMPT) {
            SendErrorMsg(playerid, "You have been kicked from the server for attempting to login numerous times.");
            Kick(playerid);

            dbg("player", "player has been kicked for too many login attempts", 
                _p("username", playerid), 
                _i("uid", Player_GetAccountID(playerid)) 
            );
            return;
        }

        Account_PromptLogin(playerid, gPlayerHash[playerid]);
        SendErrorMsgF(playerid, "Wrong password, try again! - Attempts: [%i/%i]", PlayerAttempts[playerid], MAX_PASSWORD_ATTEMPT);
        
        dbg("player", "player failed to login",
            _i("attemps", PlayerAttempts[playerid]),
            _p("username", playerid),
            _i("uid", Player_GetAccountID(playerid))
        );
        return;
    }

    dbg("player", "player successfully logged in", 
        _p("username", playerid), 
        _i("uid", Player_GetAccountID(playerid))
    );

    PlayerAttempts[playerid] = 0;
    Account_NotifySuccess(playerid);
    CallLocalFunction("OnPlayerLogin", "i", playerid); // Used in other modules to load other data.
    
    // Force Spawn Player
    SetSpawnInfo(playerid, NO_TEAM, GetPlayerSkin(playerid), 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
}

static 
    Statement: stmt_updatePlayerSkin;

hook OnMySQLConnected() {
    stmt_updatePlayerSkin = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE player_stats SET skin = ? WHERE u_id = ?");
    return 1;
}

hook OnPlayeLogin(playerid) {
    gPlayerLoginStatus[playerid] = true;
    return 1;
}

hook OnPlayerSpawn(playerid) {
    if(Player_NewComer(playerid)) {
        MySQL_BindInt(stmt_updatePlayerSkin, 0, GetPlayerSkin(playerid));
        MySQL_BindInt(stmt_updatePlayerSkin, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_updatePlayerSkin);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    // save money
    // save skin (if changed)
    return 1;
}

CMD:kill(playerid) {
    SetPlayerHealth(playerid, 0);
    return 1;
}

 // API
Player_IsLoggedIn(playerid) {
    return gPlayerLoginStatus[playerid];
}

Player_SetLoginStatus(playerid, bool:status) {
    return gPlayerLoginStatus[playerid] = status;
}
