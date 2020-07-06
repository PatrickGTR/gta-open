CMD:inventory(playerid) {
    ShowInvMenu(playerid);
    return 1;
}

CMD:inv(playerid) {
    return cmd_inventory(playerid);
}

ShowInvMenu(playerid)
{
    new string[128];
    TextInfo_Create(playerid, "INV", "INVENTORY");
    format(string, sizeof(string), "~r~Name:~w~ %p (%d)~n~", playerid, playerid);
    TextInfo_Add(playerid, string);
    format(string, sizeof(string), "~r~Instafixes:~w~ %d", Player_GetInstaFix(playerid));
    TextInfo_Add(playerid, string);
    TextInfo_Show(playerid);
    return 1;
}