forward TextMenuTCMDS(playerid, listitem);
public TextMenuTCMDS(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendServerMsg(playerid, "To see available Commands for Beta Testers");
        }
        case 2:
        {
            SendServerMsg(playerid, "Chat for Beta Testers.");
            SendSyntaxMsg(playerid, "/tchat <message>");
        }
        case 3:
        {
            SendServerMsg(playerid, "To see available interior teleports");
        }
    }
    return 1;
}

stock ShowTcmds(playerid)
{
    TextMenu_Create(playerid, "TextMenuTCMDS", "Tester Commands");
    TextMenu_Add(playerid, "~w~/tcmds");
    TextMenu_Add(playerid, "~w~/tchat");
    TextMenu_Add(playerid, "~w~/interiors");
    TextMenu_Show(playerid);
    return 1;
}

TCMD:tcmds(playerid, params[])
{
    ShowTcmds(playerid);
    return 1;
}