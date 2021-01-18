#include <YSI_Coding\y_hooks>

static
    bool:gPlayerLoginStatus[MAX_PLAYERS],
    PlayerAttempts[MAX_PLAYERS];

#define MAX_PASSWORD_ATTEMPT (5)

// Initialise
hook OnPlayerConnect(playerid) {
    gPlayerLoginStatus[playerid] = false;
    return 1;
}

// Global
void:Account_PromptLogin(playerid, const password[], len = sizeof(password)) {
    new
        playerHash[62];
    // copy to local stack
    // fix with y_inline scopes.
    strcpy(playerHash, password, len);

    inline const PromptLoginResponse(response, listitem, string:inputtext[]) {
         #pragma unused listitem

        // User clicked the 'leave' buton or pressed 'ESC' .
        if(!response) {
            Kick(playerid);
            return;
        }

        inline const OnPasswordVerify(bool: success) {
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

                Account_PromptLogin(playerid, playerHash);
                SendErrorMsg(playerid, "Oops something went wrong, try again.");

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
        }
        BCrypt_CheckInline(inputtext, playerHash, using inline OnPasswordVerify);
    }

    new
        string[128];

    static const LoginMessage[] = "\
        "C_WHITE"Hello "C_GREY"%p. "C_WHITE"Welcome back \
        \n\n\
        "C_WHITE"Enter credentials to proceed. \
    ";

    format(
        string,
        sizeof(string),
        LoginMessage,
        playerid,
        SERVER_NAME
    );

    Dialog_ShowCallback(
        playerid,
        using inline PromptLoginResponse,   // Handler
        DIALOG_STYLE_PASSWORD,              // Style
        SERVER_NAME,                        // Title
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


hook OnPlayerLogin(playerid) {
    new
        Statement: stmt_updatePlayerLastLogin;

    stmt_updatePlayerLastLogin = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE players SET last_login = CURRENT_TIMESTAMP() WHERE u_id = ?");
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
