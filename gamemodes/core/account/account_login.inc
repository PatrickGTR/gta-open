#include <YSI_Coding\y_hooks>

static
    gPlayerHash[MAX_PLAYERS][62],
    bool:gPlayerLoginStatus[MAX_PLAYERS],
    PlayerAttempts[MAX_PLAYERS];

#define MAX_PASSWORD_ATTEMPT (5)

// Initialise
hook OnPlayerConnect(playerid) {
    gPlayerHash[playerid][0] = EOS;
    gPlayerLoginStatus[playerid] = false;
    return 1;
}

// Global
void:Account_PromptLogin(playerid, const password[], len = sizeof(password)) {
    if(isnull(gPlayerHash[playerid])) {
        strcat(gPlayerHash[playerid], password, len);
    }

    inline const PromptLoginResponse(pid, dialogid, response, listitem, string:inputtext[]) {
         #pragma unused pid, dialogid, listitem

        // User clicked the 'leave' buton or pressed 'ESC' .
        if(!response) {
            Kick(playerid);
            return;
        }

        inline const OnPasswordVerify(bool: success)
        {
            if(!success) {
                PlayerAttempts[playerid] ++;
                if(PlayerAttempts[playerid] >= MAX_PASSWORD_ATTEMPT) {
                    SendErrorMsg(playerid, "You have been kicked from the server for attempting to login numerous times.");
                    Kick(playerid);

                    Logger_Dbg(PLAYER_DEBUG_HANDLER, "player has been kicked for too many login attempts",
                        Logger_P(playerid),
                        Logger_I("uid", Player_GetAccountID(playerid))
                    );
                    return;
                }

                Account_PromptLogin(playerid, gPlayerHash[playerid]);
                SendErrorMsgF(playerid, "Wrong password, try again! - Attempts: [%i/%i]", PlayerAttempts[playerid], MAX_PASSWORD_ATTEMPT);

                Logger_Dbg(PLAYER_DEBUG_HANDLER, "player failed to login",
                    Logger_I("attemps", PlayerAttempts[playerid]),
                    Logger_P(playerid),
                    Logger_I("uid", Player_GetAccountID(playerid))
                );
                return;
            }

            Logger_Dbg(PLAYER_DEBUG_HANDLER, "player successfully logged in",
                Logger_P(playerid),
                Logger_I("uid", Player_GetAccountID(playerid))
            );

            PlayerAttempts[playerid] = 0;
            Account_NotifySuccess(playerid);
            CallLocalFunction("OnPlayerLogin", "i", playerid); // Used in other modules to load other data.

            // Force Spawn Player
            defer ForceSpawnPlayer(playerid);
        }
        BCrypt_CheckInline(inputtext, gPlayerHash[playerid], using inline OnPasswordVerify);
    }

    new
        string[48 + MAX_PLAYER_NAME + 16];

    static const
        LoginMessage[] = ""C_WHITE"Hello "C_GREY"%p. "C_WHITE"Welcome back to "C_YELLOW"%s";

    format(string, sizeof(string), LoginMessage, playerid, SERVER_NAME);

    Dialog_ShowCallback(
        playerid,
        using inline PromptLoginResponse,   // Handler
        DIALOG_STYLE_PASSWORD,              // Style
        "Please Login...",                  // Title
        string,                             // Content
        "Login",                            // Button Left
        "Leave"                             // Button Right
    );
}

// Local
static void:Account_NotifySuccess(playerid) {
    static const
        msg_title[] = "~g~Welcome back!",
        msg_content[] = "Hello ~p~%p, ~w~Welcome back to ~p~%s. ~n~~n~~y~Enjoy your stay!";
    MessageBox_ShowF(playerid, TYPE_MSGBOX, msg_title, msg_content, 8000, playerid, SERVER_NAME);
}

static
    Statement: stmt_updatePlayerLastLogin;

hook OnMySQLConnected() {
    stmt_updatePlayerLastLogin = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE players SET last_login = CURRENT_TIMESTAMP() WHERE u_id = ?");
    return 1;
}

hook OnPlayerLogin(playerid) {

    MySQL_BindInt(stmt_updatePlayerLastLogin, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_updatePlayerLastLogin);

    gPlayerLoginStatus[playerid] = true;
    return 1;
}


 // API
Player_IsLoggedIn(playerid) {
    return gPlayerLoginStatus[playerid];
}

Player_SetLoginStatus(playerid, bool:status) {
    return gPlayerLoginStatus[playerid] = status;
}
