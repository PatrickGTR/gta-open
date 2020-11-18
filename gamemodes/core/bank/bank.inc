// #include <bankatm>
#include <bank_taxes>

#if SETUP_TABLE
    #include <bank_setup-bankacc-table>
#endif
#include <YSI_Coding\y_hooks>

static
    Statement:stmt_insertBank,
    Statement:stmt_loadBank,
    Statement:stmt_saveBank
;

static 
    PlayerBankMoney[MAX_PLAYERS],
    PlayerBankDept[MAX_PLAYERS],
    PlayerBankTax[MAX_PLAYERS]
;

hook OnMySQLConnected()
{
    static const insertQuery[] = "\
    INSERT INTO \
        player_bank(u_id) \
    VALUES \
        (?) \
    ";
    stmt_insertBank = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = "\
    SELECT \
        bank_money, \
        player_tax, \
        player_dept \
    FROM \
        player_bank \
    WHERE \
        u_id = ? \
    ";
    stmt_loadBank = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const updateQuery[] = "\
    UPDATE \
        player_bank \
    SET \
        bank_money = ?, \
        player_tax = ?, \
        player_dept = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_saveBank = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);
    return 1;
}

hook OnPlayerRegister(playerid)
{
    MySQL_BindInt(stmt_insertBank, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_insertBank);
}

hook OnPlayerLogin(playerid)
{
    Bank_Load(playerid);
    MySQL_BindInt(stmt_insertBank, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_insertBank);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    PlayerBankMoney[playerid] = 0;
    PlayerBankTax[playerid] = 0;
    PlayerBankDept[playerid] = 0;
    return 1;
}

Bank_Load(playerid) {
    inline BankLoad()
    {
        new
            BMoney,
            PDept,
            PTax;
        MySQL_BindResultInt(stmt_loadBank, 0, BMoney);
        MySQL_BindResultInt(stmt_loadBank, 1, PTax);
        MySQL_BindResultInt(stmt_loadBank, 2, PDept);

        if(MySQL_Statement_FetchRow(stmt_loadBank)) {
            Player_GiveBankMoney(playerid, BMoney);
            Player_AddBankDept(playerid, PDept);
            Player_AddBankTax(playerid, PTax);
        }
    }
    MySQL_BindInt(stmt_loadBank, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadBank, using inline BankLoad);
}

stock Player_GetBankMoney(playerid)
    return PlayerBankMoney[playerid];

stock Player_GiveBankMoney(playerid, bankmoney, bool:save = false)
{
    new
        currentBMoney = Player_GetBankMoney(playerid),
        newBMoney = currentBMoney + bankmoney;
    PlayerBankMoney[playerid] = newBMoney;
    if(save) {
        MySQL_BindInt(stmt_saveBank, 0, newBMoney);
        MySQL_BindInt(stmt_saveBank, 1, Player_GetBankTax(playerid));
        MySQL_BindInt(stmt_saveBank, 2, Player_GetBankDept(playerid));
        MySQL_BindInt(stmt_saveBank, 3, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_saveBank);
    }
}

stock Player_RemoveBankMoney(playerid, bankmoney)
{
    new 
        currentBMoney = Player_GetBankMoney(playerid),
        newBMoney = currentBMoney - bankmoney;
    PlayerBankMoney[playerid] = newBMoney;
    MySQL_BindInt(stmt_saveBank, 0, newBMoney);
    MySQL_BindInt(stmt_saveBank, 1, Player_GetBankTax(playerid));
    MySQL_BindInt(stmt_saveBank, 2, Player_GetBankDept(playerid));
    MySQL_BindInt(stmt_saveBank, 3, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveBank);
}

stock Player_GetBankDept(playerid)
    return PlayerBankDept[playerid];

stock Player_GetBankTax(playerid)
    return PlayerBankTax[playerid];

stock Player_AddBankDept(playerid, bankdept, bool:save = false)
{
    new
        currentPDept = Player_GetBankDept(playerid),
        newPDept = currentPDept + bankdept;
    PlayerBankDept[playerid] = newPDept;
    if(save) {
        MySQL_BindInt(stmt_saveBank, 0, Player_GetBankMoney(playerid));
        MySQL_BindInt(stmt_saveBank, 1, Player_GetBankTax(playerid));
        MySQL_BindInt(stmt_saveBank, 2, newPDept);
        MySQL_BindInt(stmt_saveBank, 3, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_saveBank);
    }
}

stock Player_RemoveBankDept(playerid, bankdept)
{
    new 
        currentPDept = Player_GetBankDept(playerid),
        newPDept = currentPDept - bankdept;
    PlayerBankDept[playerid] = newPDept;
    if(PlayerBankDept[playerid] < 0) {
        PlayerBankDept[playerid] = 0;
    }
    MySQL_BindInt(stmt_saveBank, 0, Player_GetBankMoney(playerid));
    MySQL_BindInt(stmt_saveBank, 1, Player_GetBankTax(playerid));
    MySQL_BindInt(stmt_saveBank, 2, newPDept);
    MySQL_BindInt(stmt_saveBank, 3, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveBank);
}

stock Player_AddBankTax(playerid, banktax, bool:save = false)
{
    new
        currentPTax = Player_GetBankTax(playerid),
        newPTax = currentPTax + banktax;
    PlayerBankTax[playerid] = newPTax;
    if(save) {
        MySQL_BindInt(stmt_saveBank, 0, Player_GetBankMoney(playerid));
        MySQL_BindInt(stmt_saveBank, 1, newPTax);
        MySQL_BindInt(stmt_saveBank, 2, Player_GetBankDept(playerid));
        MySQL_BindInt(stmt_saveBank, 3, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_saveBank);
    }
}

stock Player_RemoveBankTax(playerid, banktax)
{
    new
        currentPTax = Player_GetBankTax(playerid),
        newPTax = currentPTax - banktax;
    PlayerBankTax[playerid] = newPTax;
    if(PlayerBankTax[playerid] < 0) {
        PlayerBankTax[playerid] = 0;
    }
    MySQL_BindInt(stmt_saveBank, 0, Player_GetBankMoney(playerid));
    MySQL_BindInt(stmt_saveBank, 1, newPTax);
    MySQL_BindInt(stmt_saveBank, 2, Player_GetBankDept(playerid));
    MySQL_BindInt(stmt_saveBank, 3, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_saveBank);
}