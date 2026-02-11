#include <YSI_Coding\y_hooks>

static
    Statement:stmt_insertPlayerAccount;

hook OnMySQLConnected() {
    stmt_insertPlayerAccount = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO players (username, password) VALUES (?, ?)");
    return 1;
}

// Prompts the player the register dialog.
// return n/a
stock Account_PromptRegister(playerid) {
    inline const _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem
        if (!response) {
            Kick(playerid);
            return;
        }
        Account_Create(playerid, inputtext);
    }

    new
        string[256];

    static
        const RegisterMessage[] = "\
        "C_LGREEN"CREATE ACCOUNT\
        \n\n"C_WHITE"Hello "C_GOLD"%p"C_WHITE", welcome to "C_SAMPBLUE"%s"C_WHITE"!\
        \n\n"C_GREY"You're about to create a new account on our server.\
        \n"C_GREY"Please choose a secure password for your account.\
        \n\n"C_GREEN"Enter your desired password below.\
        \n"C_ORANGE"Remember: Keep your password safe and secure!\
    ";

    format(string, sizeof(string), RegisterMessage, playerid, SERVER_NAME);

    Dialog_ShowCallback(playerid,
        using inline _response, // handler
        DIALOG_STYLE_PASSWORD,  // style
        SERVER_NAME,            // title
        string,                 // content
        "Register",             // button left
        "Leave");               // button right
}

// only used internally, it checks for validations before calling OnPasswordHash callback.
// it checks for pass length, must be more than 3 but less than 20.
// password can't be all just numbers.
// return n/a
static Account_Create(playerid, const password[]) {

    if (!(3 <= strlen(password) <= 20)) {
        SendErrorMsg(playerid, "Invalid length on the password. It should be between 3-20 characters" );
        Account_PromptRegister(playerid);
        return;
    }
    if (IsNumeric(password)) {
        SendErrorMsg(playerid, "Your password is invalid. The password should include alphabets.");
        Account_PromptRegister(playerid);
        return;
    }

    bcrypt_hash(playerid, "OnBCryptPasswordHash", password, BCRYPT_COST);
}

forward OnBCryptPasswordHash(playerid, hashid);
public OnBCryptPasswordHash(playerid, hashid) {
    #pragma unused hashid
    new hash[61];
    bcrypt_get_hash(hash);
    Account_InsertToDatabase(playerid, hash);
}

// only used internally, when all checks passed this function will be called.
// it notifies player that they have successfully registered to the server.
// it inserts their data into the database.
// return n/a
static Account_InsertToDatabase(playerid, const hash[]) {
    inline const OnRegister() {
        Player_SetAccountID(playerid, cache_insert_id());

        static const
                msg_title[] = "~g~Welcome!",
                msg_content[] = "Hello ~p~%p, ~w~You have just registered to our server! You have been automatically logged in!~n~~n~~y~Enjoy your stay!";
        MessageBox_ShowF(playerid, TYPE_MSGBOX, msg_title, msg_content, 8000, playerid, SERVER_NAME);

        CallLocalFunction("OnPlayerRegister", "i", playerid);
        TogglePlayerSpectating(playerid, false);
        Player_SetLoginStatus(playerid, true);
        Class_SelectionState(playerid, true);
    }

    new
        username[MAX_PLAYER_NAME];
    GetPlayerName(playerid, username, sizeof(username));

    // insert account data.
    MySQL_Bind(stmt_insertPlayerAccount, 0, username);
    MySQL_Bind(stmt_insertPlayerAccount, 1, hash);
    MySQL_ExecuteThreaded_Inline(stmt_insertPlayerAccount, using inline OnRegister);
}