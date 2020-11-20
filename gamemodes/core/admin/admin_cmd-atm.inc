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
	return 1;
}

timer DelayEdit[1500](playerid, ret) {
    // Send user to editing state once ATM has been created.
    ATM_Edit(playerid, ret);
}

ACMD:[5]deleteatm(playerid, params[]) {
    if(isnull(params)) {
        return SendErrorMsg(playerid, "/deleteatm <atm id>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Invalid input.");
    }

    new
        atmID = strval(params),
        ret = ATM_Delete(atmID);

    if(!ret) {
        return SendErrorMsg(playerid, "Invalid ATM ID, try again.");
    }
    return 1;
}