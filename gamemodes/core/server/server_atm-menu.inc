#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    // don't run code below if player is not near
    // any ATM machine.
    if(!Player_IsNearATM(playerid)) {
        return 1;
    }

    // disable access if ATM is disabled
    new
        atmID = ATM_GetClosest(playerid),
        idx = ATM_FindIndexIDBySQLID(atmID);

    if(ATM_GetState(idx)) {
        return 1;
    }

    if(newkeys == KEY_YES) {
        ATM_MainMenu(playerid);
    }
    return 1;
}

void:ATM_MainMenu(playerid)
{
    inline const _response(response, listitem, string:inputtext[]) {
        #pragma unused inputtext
        if(!response) {
            return;
        }

        switch(listitem) {
            case 0: {
                ATM_DepositMenu(playerid);
            }
            case 1: {
                ATM_WithdrawMenu(playerid);
            }
        }
    }

    new
        title[32];
    format(title, sizeof(title), "ATM - Balance: "C_GREEN"%m", Player_GetBankMoney(playerid));

    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        title,
        "Deposit\nWithdraw",
        "Choose",
        "Close"
    );
}

void:ATM_DepositMenu(playerid)
{
    inline const _response(response, listitem, string:inputtext[]) {
        #pragma unused listitem
        if(!response) {
            ATM_MainMenu(playerid);
            return ;
        }

        new
            amount = strval(inputtext);

        if(amount <= 0) {
            SendErrorMsg(playerid, "Invalid input");
            ATM_DepositMenu(playerid);
            return;
        }

        if(GetPlayerMoney(playerid) < amount) {
            SendErrorMsg(playerid, "Input is higher than your money");
            ATM_DepositMenu(playerid);
            return;
        }

        // Deduct money from player, add money to player's bank.
        Player_GiveBankMoney(playerid, amount, true);
        GivePlayerMoney(playerid, -amount);

        // Notify Player
        SendServerMsgF(playerid, "You have deposited %m to your bank account", amount);
        SendServerMsgF(playerid, "Current Balance: %m", Player_GetBankMoney(playerid));
    }

    new
        content[64 + 24];
    format(
        content,
        sizeof(content),
        "\
        "C_WHITE"Balance: "C_GREEN"%m\n\n\
        "C_WHITE"Insert amount you want to deposit\
        ",
        Player_GetBankMoney(playerid)
    );

    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_INPUT,
        "ATM Deposit",
        content,
        "Choose",
        "Back To Main"
    );
}

void:ATM_WithdrawMenu(playerid)
{
    inline const _response(response, listitem, string:inputtext[]) {
        #pragma unused listitem
        if(!response) {
            ATM_MainMenu(playerid);
            return;
        }

        new
            amount = strval(inputtext);

        if(amount <= 0) {
            SendErrorMsg(playerid, "Invalid input");
            ATM_WithdrawMenu(playerid);
            return;
        }

        if(GetPlayerMoney(playerid) < amount) {
            SendErrorMsg(playerid, "Input is higher than your money");
            ATM_WithdrawMenu(playerid);
            return;
        }

        // Deduct money from bank, add money to player.
        Player_RemoveBankMoney(playerid, amount);
        GivePlayerMoney(playerid, amount);

        // Notify Player
        SendServerMsgF(playerid, "You withdrew %m from your bank account", amount);
        SendServerMsgF(playerid, "Current Balance: %m", Player_GetBankMoney(playerid));
    }

    new
        content[64 + 24];
    format(
        content,
        sizeof(content),
        "\
        "C_WHITE"Balance: "C_GREEN"%m\n\n\
        "C_WHITE"Insert amount you want to withdraw\
        ",
        Player_GetBankMoney(playerid)
    );

    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_INPUT,
        "ATM Withdraw",
        content,
        "Choose",
        "Back to Main"
    );
}