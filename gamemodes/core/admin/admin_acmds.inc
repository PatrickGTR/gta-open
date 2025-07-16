#define MAX_COMMANDS_PER_LEVEL  (13)

static
    aCommands[MAX_ADMIN_LEVELS][MAX_COMMANDS_PER_LEVEL][2048],
    Iterator:gAdminCommands[MAX_ADMIN_LEVELS]<MAX_COMMANDS_PER_LEVEL>
;

stock Admin_GetRankNameFromLevel(alevel)
{
    new admin_RankNames[6][24] =
    {
        "None",          // 0
        "Junior Admin",  // 1
        "General Admin", // 2
        "Senior Admin",  // 3
        "Head Admin",    // 4
        "Developer"      // 5
    };

    return admin_RankNames[alevel];
}

stock Admin_AddCommandToList(alevel, const string[])
{
    if (!(ADM_LVL_1 <= alevel <= ADM_LVL_5))
    {
        printf("ERROR: Cannot register admin command for level %d", alevel);
        return 0;
    }

    new tmpString[152];
    new freeid = Iter_Alloc(gAdminCommands[alevel - 1]);

    if(freeid == ITER_NONE) {
        Logger_Err("MAX ADMIN COMMANDS PER LEVEL REACHED",
            Logger_S("Command", string),
            Logger_I("Level", alevel));
        return ITER_NONE;
    }
    format(tmpString, sizeof tmpString, "%s\n", string);
    strcat(aCommands[alevel - 1][freeid], tmpString);
    return 1;
}

ACMD:[1]acmds(playerid, params[])
{
    new tmpString[152], ranks[256];
    new alevel = Admin_GetPlayerLevel(playerid);

    inline const _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response) return 1;
        Player_ShowAdminCmdsOfLevel(playerid, listitem);
    }


    for(new i; i < alevel; i++) {
        new newlevel = i + 1;
        format(tmpString, sizeof tmpString, "%s\n", Admin_GetRankNameFromLevel(newlevel));
        strcat(ranks, tmpString);
    }
    Dialog_ShowCallback(playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        "Admin Commands",
        ranks,
        "Select",
        "Close");
    return 1;
}

static Player_ShowAdminCmdsOfLevel(playerid, alevel) {
    new acmds[2048], tmpString[50];

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, response, listitem, inputtext
        return 1;
    }

    foreach(new i : gAdminCommands[alevel])
    {
        strcat(acmds, aCommands[alevel][i]);
    }

    format(tmpString, sizeof tmpString, "%s", Admin_GetRankNameFromLevel(alevel));
    Dialog_ShowCallback(playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        tmpString,
        acmds,
        "Select",
        "Close");
    return 1;
}