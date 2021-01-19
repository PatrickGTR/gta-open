CMD:info(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target))
    {
        Player_ShowInfo(playerid, playerid);
        return 1;
    }

    if(!IsPlayerConnected(target)) {
        SendErrorMsg(playerid, "Player is not connected");
        return 1;
    }

    Player_ShowInfo(playerid, target);
    return 1;
}

void:Player_ShowInfo(playerid, targetid) {
    new
        formatContent[64],
        mainContent[512],
        location[MAX_MAP_ZONE_NAME + 12];

    format(formatContent, sizeof(formatContent), "Name\t%p(%i)\n", targetid, targetid);
    strcat(mainContent, formatContent);

    Player_GetLocation(targetid, location);
    format(formatContent, sizeof(formatContent), "Location\t%s\n", location);
    strcat(mainContent, formatContent);

    format(formatContent, sizeof(formatContent), "Class\t%s\n", Player_GetClassName(targetid));
    strcat(mainContent, formatContent);

    if(Player_GetClass(targetid) == TEAM_CIVILIAN) {
        format(formatContent, sizeof(formatContent), "Job\t%s\n", Player_GetJobName(targetid));
	    strcat(mainContent, formatContent);
    }

    format(formatContent, sizeof(formatContent), "Kills\t%d\n", Player_GetKills(targetid));
    strcat(mainContent, formatContent);

    format(formatContent, sizeof(formatContent), "Deaths\t%d\n", Player_GetDeaths(targetid));
    strcat(mainContent, formatContent);

    format(formatContent, sizeof(formatContent), "Ratio\t%.2f", floatdiv(Player_GetKills(targetid), Player_GetDeaths(targetid)));
	strcat(mainContent, formatContent);

    Dialog_Show(
        playerid,
        DIALOG_STYLE_TABLIST,
        "Player Info",
        mainContent,
        "Close"
    );
}