#include <YSI_Coding\y_hooks>

static
    Statement:stmt_insertBank,
    Statement:stmt_loadBank,
    PlayerBankMoney[MAX_PLAYERS];

hook OnMySQLConnected() {
    static const insertQuery[] = "\
    INSERT INTO \
        player_bank(u_id) \
    VALUES \
        (?) \
    ON DUPLICATE KEY UPDATE \
        money = ? \
    ";
    stmt_insertBank = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = "\
    SELECT \
        money \
    FROM \
        player_bank \
    WHERE \
        u_id = ? \
    ";
    stmt_loadBank = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

hook OnPlayerLogin(playerid) {
    Bank_Load(playerid);
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerBankMoney[playerid] = 0;
    return 1;
}

Bank_Load(playerid) {
    inline OnBankLoad() {
        new
            bankBalance;
        MySQL_BindResultInt(stmt_loadBank, 0, bankBalance);

        if(MySQL_Statement_FetchRow(stmt_loadBank)) {
            Player_GiveBankMoney(playerid, bankBalance);
        }
    }
    MySQL_BindInt(stmt_loadBank, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadBank, using inline OnBankLoad);
}

stock Player_GetBankMoney(playerid)
    return PlayerBankMoney[playerid];

stock Player_GiveBankMoney(playerid, amount, bool:save = false) {
    PlayerBankMoney[playerid] = (Player_GetBankMoney(playerid) + amount);

    if(save) {
        MySQL_BindInt(stmt_insertBank, 0, Player_GetAccountID(playerid));
        MySQL_BindInt(stmt_insertBank, 1, Player_GetBankMoney(playerid));
        MySQL_ExecuteThreaded(stmt_insertBank);
    }
}

stock Player_RemoveBankMoney(playerid, amount) {
    PlayerBankMoney[playerid] = (Player_GetBankMoney(playerid) - amount);

    MySQL_BindInt(stmt_insertBank, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_insertBank, 1, Player_GetBankMoney(playerid));
    MySQL_ExecuteThreaded(stmt_insertBank);
}