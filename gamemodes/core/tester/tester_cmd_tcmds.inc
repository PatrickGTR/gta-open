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
        case 4:
        {
            SendServerMsg(playerid, "Create an atm machine");
        }
        case 5:
        {
            SendServerMsg(playerid, "delete an atm machine");
            SendSyntaxMsg(playerid, "/deleteatm <atm id>");
        }
        case 6:
        {
            SendServerMsg(playerid, "Edit an atm machine");
            SendSyntaxMsg(playerid, "/editatm <atm id>");
        }
        case 7:
        {
            SendServerMsg(playerid, "To see near atm ids");
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
    TextMenu_Add(playerid, "~w~/createatm");
    TextMenu_Add(playerid, "~w~/deleteatm");
    TextMenu_Add(playerid, "~w~/editatm");
    TextMenu_Add(playerid, "~w~/nearatm");
    TextMenu_Show(playerid);
    return 1;
}

TCMD:tcmds(playerid, params[])
{
    ShowTcmds(playerid);
    return 1;
}