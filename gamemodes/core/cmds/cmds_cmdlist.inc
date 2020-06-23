forward TextMenuCommands(playerid, listitem);
public TextMenuCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1: ShowGeneralCommands(playerid);
        case 2: ShowTeamCommands(playerid);
        case 3: ShowClassCommands(playerid);
        case 4: ShowHouseCommands(playerid);
        case 5: ShowAttachmentCommands(playerid);
    }
    return 1;
}

stock ShowCommandList(playerid)
{
    TextMenu_Create(playerid, "TextMenuCommands", "Commands");
    TextMenu_Add(playerid, "General Commands");
    TextMenu_Add(playerid, "Team Commads");
    TextMenu_Add(playerid, "Class Commands");
    TextMenu_Add(playerid, "House Commands");
    TextMenu_Add(playerid, "Attachment Commands");
    TextMenu_Show(playerid);
    return 1;
}

//general commands
forward TextMenuGeneralCommandMain(playerid, listitem);
public TextMenuGeneralCommandMain(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/breakcuff");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Escape from cuffs using a picklock.");
        }
        case 2:
        {
            SendSyntaxMsg(playerid, "/breakout");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Escape from jail using a picklock.");
        }
        case 3:
        {
            SendSyntaxMsg(playerid, "/tie");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Tie a player using a rope.");
        }
        case 4:
        {
            SendSyntaxMsg(playerid, "/breaktie");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Escape from being tied.");
        }
        case 5:
        {
            SendSyntaxMsg(playerid, "/payticket");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Pay your ticket.");
        }
        case 6:
        {
            SendSyntaxMsg(playerid, "/rob");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Rob the nearest player.");
        }
        case 7:
        {
            SendSyntaxMsg(playerid, "/placehit <playerid> <Amount> <Reason>");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Place a hit on a player.");
        }
        case 8:
        {
            SendSyntaxMsg(playerid, "/eject");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Eject a player from your vehicle.");
        }
        case 9:
        {
            SendSyntaxMsg(playerid, "/smokeweed");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Smoke weed that you bought.");
        }
        case 10:
        {
            SendSyntaxMsg(playerid, "/smokecrack");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Smoke crack that you bought.");
        }
        case 11:
        {
            ShowGeneralCommands(playerid, true);
        }
        case 12:
        {
            ShowCommandList(playerid);
        }
    }
    return 1;
}

forward TextMenuGeneralCommandNext(playerid, listitem);
public TextMenuGeneralCommandNext(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/buyweed");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Buy weed from a drug dealer that offered you.");
        }
        case 2:
        {
            SendSyntaxMsg(playerid, "/buycrack");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Buy crack from a drug dealer that offered you.");
        }
        case 3:
        {
            SendSyntaxMsg(playerid, "/pm");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Private message a player");
        }
        case 4:
        {
            SendSyntaxMsg(playerid, "/r");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Reply message to a player");
        }
        case 5:
        {
            SendSyntaxMsg(playerid, "/dnd");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" disable/enable players private messing you.");
        }
        case 6:
        {
            SendSyntaxMsg(playerid, "/lock");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" To lock your last vehicle that u drove.");
        }
        case 7:
        {
            SendSyntaxMsg(playerid, "/unlock");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" To unlock your vehicle");
        }
        case 8:
        {
            SendSyntaxMsg(playerid, "/givekeys <playerid>");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" To give the vehicle keys to someone");
        }
        case 9:
        {
            ShowGeneralCommands(playerid);
        }
    }
}

stock ShowGeneralCommands(playerid, bool:next = false)
{
    if(!next) {
        TextMenu_Create(playerid, "TextMenuGeneralCommandMain", "General Commands");
        TextMenu_Add(playerid, "~r~/breakcuff");
        TextMenu_Add(playerid, "~r~/breakout");
        TextMenu_Add(playerid, "~r~/tie");
        TextMenu_Add(playerid, "~r~/breaktie");
        TextMenu_Add(playerid, "~r~/payticket");
        TextMenu_Add(playerid, "~r~/rob");
        TextMenu_Add(playerid, "~r~/placehit");
        TextMenu_Add(playerid, "~r~/eject");
        TextMenu_Add(playerid, "~r~/smokeweed");
        TextMenu_Add(playerid, "~r~/smokecrack");
        TextMenu_Add(playerid, "Next page");
        TextMenu_Add(playerid, "Command List");
    }
    if(next) {
        TextMenu_Create(playerid, "TextMenuGeneralCommandNext", "General Commands");
        TextMenu_Add(playerid, "~r~/buyweed");
        TextMenu_Add(playerid, "~r~/buycrack");
        TextMenu_Add(playerid, "~r~/pm");
        TextMenu_Add(playerid, "~r~/r");
        TextMenu_Add(playerid, "~r~/dnd");
        TextMenu_Add(playerid, "~r~/lock");
        TextMenu_Add(playerid, "~r~/unlock");
        TextMenu_Add(playerid, "~r~/givekeys");
        TextMenu_Add(playerid, "Prev page");
    }
    TextMenu_Show(playerid);
    return 1;
}

//team commands
forward TextMenuTeamCommands(playerid, listitem);
public TextMenuTeamCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "! <text>");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Radio chat.");
        }
        case 2:
        {
            SendSyntaxMsg(playerid, "/ar <playerid>");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Arrest a wanted player and send him to jail.");
        }
        case 3:
        {
            SendSyntaxMsg(playerid, "/cuff <playerid>");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Cuff a player and you can arrest him afterwards.");
        }
        case 4:
        {
            SendSyntaxMsg(playerid, "/uncuff <playerid>");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Remove a player's cuff and set him free.");
        }
        case 5:
        {
            SendSyntaxMsg(playerid, "/ticket <playerid>");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Give a low wanted level player a ticket, and lose his/her stars.");
        }
        case 6:
        {
            ShowCommandList(playerid);
        }
    }
}

stock ShowTeamCommands(playerid)
{
    TextMenu_Create(playerid, "TextMenuTeamCommands", "Team Commands");
    TextMenu_Add(playerid, "~r~!");
    TextMenu_Add(playerid, "~r~/ar");
    TextMenu_Add(playerid, "~r~/cuff");
    TextMenu_Add(playerid, "~r~/uncuff");
    TextMenu_Add(playerid, "~r~/ticket");
    TextMenu_Add(playerid, "Command List");
    TextMenu_Show(playerid);
    return 1;
}

//Class Commands
forward TextMenuClassCommands(playerid, listitem);
public TextMenuClassCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1: ShowClassHitman(playerid);
        case 2: ShowClassWeaponDealer(playerid);
        case 3: ShowRapist(playerid);
        case 4: ShowTerrorist(playerid);
        case 5: ShowDrugDealer(playerid);
        case 6: ShowCommandList(playerid);
    }
    return 1;
}

stock ShowClassCommands(playerid)
{
    TextMenu_Create(playerid, "TextMenuClassCommands", "Team Commands");
    TextMenu_Add(playerid, "Hitman");
    TextMenu_Add(playerid, "Weapon Dealer");
    TextMenu_Add(playerid, "Rapist");
    TextMenu_Add(playerid, "Terrorist");
    TextMenu_Add(playerid, "Drug Dealer");
    TextMenu_Add(playerid, "Command List");
    TextMenu_Show(playerid);
    return 1;
}

forward TextMenuHitmanTeamCommands(playerid, listitem);
public TextMenuHitmanTeamCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/hitlist");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Check a list of players with hits on them.");
        }
        case 2:
        {
            ShowClassCommands(playerid);
        }
    }
    return 1;
}

stock ShowClassHitman(playerid)
{
    TextMenu_Create(playerid, "TextMenuHitmanTeamCommands", "Hitman Commands");
    TextMenu_Add(playerid, "~r~/hitlist");
    TextMenu_Add(playerid, "Back");
    TextMenu_Show(playerid);
    return 1;
}

forward WeaponDealerTeamCommands(playerid, listitem);
public WeaponDealerTeamCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/sellgun");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Sell weapon to a player.");
        }
        case 2:
        {
            SendSyntaxMsg(playerid, "/sellarmour");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Sell armour to a player.");
        }
        case 3:
        {
            ShowClassCommands(playerid);
        }
    }
    return 1;
}

stock ShowClassWeaponDealer(playerid)
{
    TextMenu_Create(playerid, "WeaponDealerTeamCommands", "Weapon Dealer Commands");
    TextMenu_Add(playerid, "~r~/sellgun");
    TextMenu_Add(playerid, "~r~/sellarmour");
    TextMenu_Add(playerid, "Back");
    TextMenu_Show(playerid);
    return 1;
}

forward TextMenuRapistTeamCommands(playerid, listitem);
public TextMenuRapistTeamCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/rape");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Rape a player and infect him with different kinds of infections.");
        }
        case 2:
        {
            ShowClassCommands(playerid);
        }
    }
    return 1;
}

stock ShowRapist(playerid)
{
    TextMenu_Create(playerid, "TextMenuRapistTeamCommands", "Rapist Commands");
    TextMenu_Add(playerid, "~r~/rape");
    TextMenu_Add(playerid, "Back");
    TextMenu_Show(playerid);
    return 1;
}

forward TextMenuTerroristTeamCommands(playerid, listitem);
public TextMenuTerroristTeamCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/plantc4");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Plant a C4 to.");
        }
        case 2:
        {
            SendSyntaxMsg(playerid, "/detonate");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" To detonate the c4 that has been planted.");
        }
        case 3:
        {
            ShowClassCommands(playerid);
        }
    }
    return 1;
}

stock ShowTerrorist(playerid)
{
    TextMenu_Create(playerid, "TextMenuTerroristTeamCommands", "Terrorist Commands");
    TextMenu_Add(playerid, "~r~/plantc4");
    TextMenu_Add(playerid, "~r~/detonate");
    TextMenu_Add(playerid, "Back");
    TextMenu_Show(playerid);
    return 1;
}

forward TextMenuDrugDealerCommands(playerid, listitem);
public TextMenuDrugDealerCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/plantweed");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Plant a weed seed.");
        }
        case 2:
        {
            SendSyntaxMsg(playerid, "/harvestweed");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Harvest the planted weed.");
        }
        case 3:
        {
            SendSyntaxMsg(playerid, "/sellweed");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Sell weed to player.");
        }
        case 4:
        {
            SendSyntaxMsg(playerid, "/detonate");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Sell crack to player.");
        }
        case 5:
        {
            ShowClassCommands(playerid);
        }
    }
    return 1;
}

stock ShowDrugDealer(playerid)
{
    TextMenu_Create(playerid, "TextMenuDrugDealerCommands", "Drug Dealer Commands");
    TextMenu_Add(playerid, "~r~/plantweed");
    TextMenu_Add(playerid, "~r~/harvestweed");
    TextMenu_Add(playerid, "~r~/sellweed");
    TextMenu_Add(playerid, "~r~/sellcrack");
    TextMenu_Add(playerid, "Back");
    TextMenu_Show(playerid);
    return 1;
}

//House Commands
forward TextMenuHouseCommands(playerid, listitem);
public TextMenuHouseCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/buyhouse");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Purchase a house.");
        }
        case 2:
        {
            ShowHouseCommands(playerid);
        }
        case 3:
        {
            SendSyntaxMsg(playerid, "/hdescription");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Change house description text");
        }
        case 4:
        {
            SendSyntaxMsg(playerid, "/buyfurniture");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Choices to buy, edit & delete a furniture.");
        }
        case 5:
        {
            ShowCommandList(playerid);
        }
    }
    return 1;
}

stock ShowHouseCommands(playerid)
{
    TextMenu_Create(playerid, "TextMenuHouseCommands", "House Commands");
    TextMenu_Add(playerid, "~r~/buyhouse");
    TextMenu_Add(playerid, "Press Key ~r~F~w~ To enter/exit a house.");
    TextMenu_Add(playerid, "~r~/hdescription");
    TextMenu_Add(playerid, "~r~/buyfurniture");
    TextMenu_Add(playerid, "Command List");
    TextMenu_Show(playerid);
    return 1;
}

forward TextMenuAttachmentCommands(playerid, listitem);
public TextMenuAttachmentCommands(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SendSyntaxMsg(playerid, "/attachment buy");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Purchase a attachment.");
        }
        case 2:
        {
            SendSyntaxMsg(playerid, "/attachment delete");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Delete an attachment.");
        }
        case 3:
        {
            SendSyntaxMsg(playerid, "/attachment edit");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Edit an attachment.");
        }
        case 4:
        {
            SendSyntaxMsg(playerid, "/attachment view");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" List all the attachment you own.");
        }
        case 5:
        {
            SendSyntaxMsg(playerid, "/attachment attach");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Attach an attachment you own.");
        }
        case 6:
        {
            SendSyntaxMsg(playerid, "/attachment detach");
            SendClientMessage(playerid, COLOR_GREEN, "[FUNCTION]:"C_WHITE" Detach an attachment you own.");
        }
        case 7:
        {
            ShowCommandList(playerid);
        }
    }
    return 1;
}

stock ShowAttachmentCommands(playerid)
{
    TextMenu_Create(playerid, "TextMenuAttachmentCommands", "Attachment Commands");
    TextMenu_Add(playerid, "~r~/attachment buy");
    TextMenu_Add(playerid, "~r~/attachment delete");
    TextMenu_Add(playerid, "~r~/attachment edit");
    TextMenu_Add(playerid, "~r~/attachment view");
    TextMenu_Add(playerid, "~r~/attachment attach");
    TextMenu_Add(playerid, "~r~/attachment detach");
    TextMenu_Add(playerid, "Command List");
    TextMenu_Show(playerid);
    return 1;
}