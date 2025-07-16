ACMD:[5]createatm(playerid, params[]) {
	new
        Float:x,
        Float:y,
        Float:z,
        Float:a,
        world = GetPlayerVirtualWorld(playerid),
        interior = GetPlayerInterior(playerid);

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new
        ret = ATM_Create(x, y, z, a, world, interior);

    if(ret == -1) {
        return SendErrorMsg(playerid, "ATM Limit reached, increase the size of MAX_ATMS.");
    }

    defer DelayEdit(playerid, ret);

    SendServerMsg(playerid, "ATM Created.");
	return 1;
}

timer DelayEdit[1500](playerid, ret) {
    // Send user to editing state once ATM has been created.
    ATM_Edit(playerid, ret);
}

ACMD:[5]editatm(playerid, params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/editatm <atm id>");
    }

    if(!IsNumeric(params)) {
        return SendErrorMsg(playerid, "Invalid input.");
    }

    new
        atmID = strval(params);

    if(!ATM_Edit(playerid, ATM_FindIndexIDBySQLID(atmID))) {
        return SendErrorMsg(playerid, "Invalid ATM ID.");
    }

    SendServerMsgF(playerid, "ATM "C_GREY"ID %i "C_WHITE"Edited.");
    return 1;
}

ACMD:[5]deleteatm(playerid, params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/deleteatm <atm id>");
    }

    if(!IsNumeric(params)) {
        return SendErrorMsg(playerid, "Invalid input.");
    }

    new
        atmID = strval(params),
        ret = ATM_Delete(atmID);

    if(!ret) {
        return SendErrorMsg(playerid, "Invalid ATM ID, try again.");
    }

    SendServerMsgF(playerid, "ATM "C_GREY"ID %i "C_WHITE"Deleted.", atmID);
    return 1;
}