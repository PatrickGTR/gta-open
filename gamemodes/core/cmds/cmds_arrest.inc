CMD:arrestcw(playerid)
{
    new
        targetid = Player_GetClosestWanted(playerid),
        errorMessage[45],
        ret;

    ret = Player_Arrest(playerid, targetid, errorMessage, sizeof(errorMessage));

    if(!ret) {
        return SendErrorMsg(playerid, errorMessage);
    }
    return 1;
}

CMD:arcw(playerid)
{
    return cmd_arrestcw(playerid);
}

CMD:arrest(playerid, params[])
{
    new
        targetid;
    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/arrest (name/id)");
    }

    new
        errorMessage[45],
        ret;
    ret = Player_Arrest(playerid, targetid, errorMessage, sizeof(errorMessage));

    if(!ret) {
        return SendErrorMsg(playerid, errorMessage);
    }
    return 1;
}

CMD:ar(playerid, params[])
{
    return cmd_arrest(playerid, params);
}