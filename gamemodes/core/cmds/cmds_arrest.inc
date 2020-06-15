CMD:arrestcw(playerid)
{
    new
        targetid = Player_GetClosestWanted(playerid),
        ret = Player_Arrest(playerid, targetid);

    if(ret == -1) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(ret == INVALID_PLAYER_ID) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }

    if(targetid == -1)  {
        return SendErrorMsg(playerid, "There's no warrant near you");
    }
    return 1;
}

CMD:arcw(playerid)
{
    return cmd_arrestcw(playerid);
}

CMD:arrest(playerid, params[])
{
    new targetid;
    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/arrest (name/id)");
    }

    new
        ret = Player_Arrest(playerid, targetid);

    if(ret == -1) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(ret == INVALID_PLAYER_ID) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(ret == -3) {
        return SendErrorMsg(playerid, "Player is not wanted!");
    }
    if(targetid == playerid) {
        return SendErrorMsg(playerid, "You can't arrest yourself!");
    }
    return 1;
}

CMD:ar(playerid, params[])
{
    return cmd_arrest(playerid, params);
}