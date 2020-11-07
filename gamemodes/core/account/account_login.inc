#include <YSI_Coding\y_hooks>

static
	bool:PlayerFromSelection[MAX_PLAYERS];

static
    gPlayerHash[MAX_PLAYERS][250],
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

    inline PromptLoginResponse(pid, dialogid, response, listitem, string:inputtext[]) {
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
static void:Account_NotifySuccess(playerid) {
    static const
        msg_title[] = "~g~Welcome back!",
        msg_content[] = "Hello ~p~%p, ~w~Welcome back to ~p~%s. ~n~~n~~y~Enjoy your stay!";
    MessageBox_ShowF(playerid, TYPE_MSGBOX, msg_title, msg_content, 8000, playerid, SERVER_NAME);
}

static
    Statement: stmt_updatePlayerSkin,
    Statement: stmt_updatePlayerLastLogin;

hook OnMySQLConnected() {
    stmt_updatePlayerSkin = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE player_stats SET skin = ? WHERE u_id = ?");
    stmt_updatePlayerLastLogin = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE players SET last_login = CURRENT_TIMESTAMP() WHERE u_id = ?");
    return 1;
}

hook OnPlayerLogin(playerid) {

    MySQL_BindInt(stmt_updatePlayerLastLogin, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_updatePlayerLastLogin);

    gPlayerLoginStatus[playerid] = true;
    return 1;
}

hook OnPlayerRequestSpawn(playerid)
{
	PlayerFromSelection[playerid] = true;
	return 1;
}

stock bool:IsPlayerFromSelection(playerid)
	return PlayerFromSelection[playerid];

stock SetPlayerSelectionStats(playerid, bool:stats) {
	PlayerFromSelection[playerid] = stats;
}

hook OnPlayerSpawn(playerid) {
    if(!IsPlayerFromSelection(playerid)) {
		SetPlayerSkin(playerid, Player_GetSkin(playerid));
	}
	if(IsPlayerFromSelection(playerid)) {
		if(Player_New(playerid)) {
            MySQL_BindInt(stmt_updatePlayerSkin, 0, GetPlayerSkin(playerid));
            MySQL_BindInt(stmt_updatePlayerSkin, 1, Player_GetAccountID(playerid));
            MySQL_ExecuteThreaded(stmt_updatePlayerSkin);
            Class_SelectionState(playerid, false);
            Player_SetNew(playerid, false);
        }
        if(Player_BoughtSkin(playerid)) {
            MySQL_BindInt(stmt_updatePlayerSkin, 0, GetPlayerSkin(playerid));
            MySQL_BindInt(stmt_updatePlayerSkin, 1, Player_GetAccountID(playerid));
            MySQL_ExecuteThreaded(stmt_updatePlayerSkin);
            Class_SelectionState(playerid, false);
		    Player_SetSkin(playerid, GetPlayerSkin(playerid));
		    Player_SetBoughtSkin(playerid, false);
        }
		SetPlayerSelectionStats(playerid, false);
	}
    printf("Player Skin ID: %d", Player_GetSkin(playerid));
    printf("Player %p Spawned with skin ID: %d", playerid, GetPlayerSkin(playerid));
    return 1;
}

 // API
Player_IsLoggedIn(playerid) {
    return gPlayerLoginStatus[playerid];
}

Player_SetLoginStatus(playerid, bool:status) {
    return gPlayerLoginStatus[playerid] = status;
}
