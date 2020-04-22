#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_hooks>
#include <formatex>
#include <logger>
#include <mysql_prepared>

static
    Statement:stmt_loadPlayerData,
    gPlayerHash[MAX_PLAYERS][250],
    bool:gPlayerLoginStatus[MAX_PLAYERS];


// Initialise
hook OnMySQLConnected(playerid) {
    stmt_loadPlayerData = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT kills, deaths FROM players WHERE u_id = ?");
}

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
static Account_LoadData(playerid) {
    inline OnDataLoad() {
        new 
            kills, deaths;
        MySQL_BindResultInt(stmt_loadPlayerData, 0, kills);
        MySQL_BindResultInt(stmt_loadPlayerData, 1, deaths);


        if(MySQL_Statement_FetchRow(stmt_loadPlayerData)) {
            
            Player_SetKills(playerid, kills);
            Player_SetDeaths(playerid, deaths);

    
            static const 
                msg_title[] = "~g~Welcome back!",
                msg_content[] = "Hello ~p~%p, ~w~Welcome back to ~p~%s. ~n~~n~~y~Enjoy your stay!";
            MessageBox_ShowF(playerid, TYPE_MSGBOX, msg_title, msg_content, 8000, playerid, SERVER_NAME);

            CallLocalFunction("OnPlayerLogin", "i", playerid); // Used in other modules to load other data.

            gPlayerLoginStatus[playerid] = true;

            dbg("player", "player successfully logged in", 
                _p("username", playerid), 
                _i("uid", Account_GetID(playerid)));
        }
    }

    MySQL_BindInt(stmt_loadPlayerData, 0, Account_GetID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerData, using inline OnDataLoad);
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
                _i("uid", Account_GetID(playerid)) 
            );
            return;
        }

        dbg("player", "player failed to login",
            _i("attemps", Player_Attempts[playerid]),
            _p("username", playerid),
            _i("uid", Account_GetID(playerid))
		);

        Player_Attempts[playerid] ++;
        return;
    }

    Account_LoadData(playerid);
    Player_Attempts[playerid] = 0;
 }

 // API
Player_IsLoggedIn(playerid) {
    return gPlayerLoginStatus[playerid];
}