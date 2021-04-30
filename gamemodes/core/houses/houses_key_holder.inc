// Module: Key holder for houses
// Date: 23/03/2021 - 12:44 AM
// Author: PatrickGTR

#include <YSI_Coding\y_hooks>

#define MAX_KEY_HOLDERS 3

static
    KeyHolder[MAX_HOUSES][MAX_KEY_HOLDERS] = {-1, ...};

// re-write, do the toggle of setting on player login instead of
// init.
hook OnMySQLConnected() {

    new
        Statement:stmt_LoadKeyHolders;
    stmt_LoadKeyHolders = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT houseid, uid FROM house_key_holders");

    inline const OnHouseKeyHolderLoad() {
        new
            houseid,
            userid;

        MySQL_BindResultInt(stmt_LoadKeyHolders, 0, houseid);
        MySQL_BindResultInt(stmt_LoadKeyHolders, 1, userid);
        while(MySQL_Statement_FetchRow(stmt_LoadKeyHolders)) {

            new
                freeSlot = GetFreeSlot(houseid);

            // skip, no more space.
            if(freeSlot == -1) {
                continue;
            }

            KeyHolder[houseid][freeSlot] = userid;

            printf("keyholders for house id %i", houseid);
            printf("on slot %i is account id %i", freeSlot, userid);

        }
    }
    MySQL_ExecuteThreaded_Inline(stmt_LoadKeyHolders, using inline OnHouseKeyHolderLoad);
}

static GetFreeSlot(houseid) {
    new
        id = -1;

    for(new i = 0; i < MAX_KEY_HOLDERS; i++) {
        if(KeyHolder[houseid][i] == -1) {
            id = i;
            break;
        }
    }
    return id;
}

House_IsKeyHolder(playerid, houseid) {

    // if player is an owner, he's obviously a key holder.
    // no point of running the code below.
    // terminate here
    if(House_PlayerIsOwner(playerid, houseid)) {
        return 1;
    }

    new
        bool:ret = false;

    for(new i = 0; i < MAX_KEY_HOLDERS; i++) {
        new
            accountid = Player_GetAccountID(playerid);
        if(KeyHolder[houseid][i] == accountid) {
            printf("found accountid %i in houseid %i in slot %i", accountid, houseid, i);
            ret = true;
            break;
        }
    }
    return ret;
}

// return values
// -1 -> playerid already a key holder
// 0 -> invalid player
// 1 -> success
House_SetKeyHolder(playerid, houseid) {
    new
        accountid = Player_GetAccountID(playerid),
        freeSlot = GetFreeSlot(houseid);

    // no more slot left
    if(freeSlot == -1) {
        return 0;
    }

    KeyHolder[houseid][freeSlot] = accountid;
    return 1;
}

House_RevokeKeyHolder(playerid, houseid) {
    new
        accountid = Player_GetAccountID(playerid), index;

    for(new i = 0; i < MAX_KEY_HOLDERS; i++) {
        if(KeyHolder[houseid][i] == accountid) {
            index = i;
            break;
        }
    }

    KeyHolder[houseid][index] = -1;
    return 1;
}