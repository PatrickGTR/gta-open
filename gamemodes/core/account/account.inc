
#include <account_create>
#include <account_login>
#include <account_vip>
#include <account_wanted-level>

#if SETUP_TABLE
    #include <account_setup-players-table>
    #include <account_setup-vip-table>
#endif

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_inline>
#include <mysql_prepared>


static 
    Player_UID[MAX_PLAYERS],
    Player_Kills[MAX_PLAYERS],
    Player_Deaths[MAX_PLAYERS],
    Statement: stmt_checkPlayer;

hook OnMySQLConnected() {
    stmt_checkPlayer = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT u_id, password FROM players WHERE username=?");
}

hook OnPlayerConnect(playerid) {

    new res = Ban_Check(playerid);
    if(res) {

        new 
            banName[MAX_PLAYER_NAME],
            banIP[20], 
            currIP[20],
            banAdmin[MAX_PLAYER_NAME],
            banReason[MAX_BAN_REASON],
            banDate[40],
            unbanDate[40]
        ;

        GetPlayerIp(playerid, currIP, sizeof(currIP));

        new expired = Ban_GetData(playerid, banName, banIP, banReason, banAdmin, banDate, unbanDate);
        if(!expired) {
            
            new banInfo[512];
            format(
                banInfo, sizeof(banInfo), "\
                "C_WHITE"Username: "C_GREY"%s\n\
                "C_WHITE"Banned IP: "C_GREY"%s\n\
                "C_WHITE"Current IP: "C_GREY"%s\n\
                "C_WHITE"Banned By: "C_GREY"%s\n\
                "C_WHITE"Reason of Ban: "C_GREY"%s\n\
                "C_WHITE"Date of Ban: "C_GREY"%s\n\
                "C_WHITE"Date of Unban: "C_GREY"%s", 
                banName,
                banIP, 
                currIP, 
                banAdmin, 
                banReason, 
                banDate, 
                unbanDate
            );
            Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Ban Information", banInfo, "Close", "");
            
            Kick(playerid);
            return;
        }
        SendMsgF(playerid, COLOR_WHITE, "Your ban expired on "C_GREY"%s "C_WHITE"\nWelcome back %p(%i), don't break any rules again", 
        unbanDate, playerid, playerid);
        
        Ban_RemoveUser(banName, INVALID_PLAYER_ID);
    }


    inline OnDataLoad() {
        new 
            playerUID, 
            playerHash[250];

        // retrieve u_id and password data and store them to local variable.
        MySQL_BindResultInt(stmt_checkPlayer, 0, playerUID); 
        MySQL_BindResult(stmt_checkPlayer, 1, playerHash, sizeof(playerHash));

        if(MySQL_Statement_FetchRow(stmt_checkPlayer)) {
            Player_SetAccountID(playerid, playerUID);

            Account_PromptLogin(playerid, playerHash);
        } else {
            Account_PromptRegister(playerid);
        }
    }
    
    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

    MySQL_Bind(stmt_checkPlayer, 0, playerName);
    MySQL_ExecuteParallel_Inline(stmt_checkPlayer, using inline OnDataLoad);
}

stock Player_SetKills(playerid, value) {
    return Player_Kills[playerid] = value;
}

stock Player_GetKills(playerid) {
    return Player_Kills[playerid];
}

stock Player_SetDeaths(playerid, value) {
    return Player_Deaths[playerid] = value;
}

stock Player_GetDeaths(playerid) {
    return Player_Deaths[playerid];
}

stock Player_SetAccountID(playerid, value) {
    return Player_UID[playerid] = value;
}

stock Player_GetAccountID(playerid) {
    return Player_UID[playerid];
}
