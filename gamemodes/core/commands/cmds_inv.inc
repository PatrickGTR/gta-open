CMD:inventory(playerid) {
    ShowInvMenu(playerid);
    return 1;
}

CMD:inv(playerid) {
    return cmd_inventory(playerid);
}

stock ShowInvMenu(playerid)
{
    new
        INV[600],
        bool:form = true,
        string[128];
    if(form)
    {
        format(string, sizeof(string), "~r~Name:~w~ %p (%d)~n~", playerid, playerid);
        strcat(INV, string);
        format(string, sizeof(string), "~r~Instafixes:~w~ %d", Player_GetInstaFix(playerid));
        strcat(INV, string);
        form = false;
    }
    TextMenuShowForPlayer(playerid, MENU_INV, "~b~INVENTORY", INV, 0);
    return 1;
}