#include <cmds_ifix>
#include <cmds_inv>
#include <cmds_info>
#include <cmds_arrest>
#include <cmds_cuff>
#include <cmds_bail>
#include <cmds_v> // vehicle
#include <cmds_pm> // private message

#include <cmds_rob>

#include <cmds_breakcuff>
#include <cmds_breakout>

static
	cmd_Cooldown[MAX_PLAYERS],
	cmd_Count[MAX_PLAYERS];

public OnPlayerCommandReceived(playerid, cmd[])
{
	// if player is not spawned, do not allow him to use commands.
	if(!Player_IsSpawned(playerid))
		return 0;

	// anti command spam
	if(gettime() < cmd_Cooldown[playerid]) {
		cmd_Count[playerid] ++;

		if(cmd_Count[playerid] >= 3) {
	 		SendServerMsgF(playerid, "Do not spam the command "C_GREY"'/%s' - count: %i", cmd, cmd_Count[playerid]);
	 		return 0;
		}
	}
	else {
		if(cmd_Count[playerid] > 0) {
			cmd_Count[playerid] --;
		}
	}

	//get time data everytime a command is recieved.
	cmd_Cooldown[playerid] = gettime() + 3;
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], success) {

    if (!success)
    	return SendErrorMsgF(playerid, "The command "C_RED"'/%s' "C_WHITE"does not exist, try typing the command once again.", cmd);

    //get time data everytime a command is performed.
    cmd_Cooldown[playerid] = gettime() + 3;
    return 1;
}


// general
ALTCMD:cmds(commands);
CMD:commands(playerid, params[]) {

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, pid, inputtext
        if (!response) {
            return 0;
        }

        switch(listitem) {
            case 0: ShowCommands(playerid, 0);
            case 1: ShowCommands(playerid, 1);
            case 2: ShowCommands(playerid, 2);
            case 3:
            {
                Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "House Commands", "\
                        "C_GREY"/buyhouse "C_WHITE"- Purchase a house.\n\
                        "C_WHITE"Press Key "C_GREY"F"C_WHITE"- To enter/exit a house.\n\
                        "C_GREY"/hdescription "C_WHITE"- Change house description text.\n\
                        "C_GREY"/buyfurniture "C_WHITE"- Choices to buy, edit & delete a furniture.", "Close", "");
            }
            case 4:
            {
                    Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Attachment Commands", "\
                        "C_GREY"/attachment buy "C_WHITE"- Purchase a attachment.\n\
                        "C_GREY"/attachment delete "C_WHITE"- Delete an attachment.\n\
                        "C_GREY"/attachment edit "C_WHITE"- Edit an attachment.\n\
                        "C_GREY"/attachment view "C_WHITE"- List all the attachment you own.\n\
                        "C_GREY"/attachment attach "C_WHITE"- Attach an attachment you own.\n\
                        "C_GREY"/attachment detach "C_WHITE"- Detach an attachment you own.\n", "Close", "");
            }
        }
    }
    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        "Server Commands & Keys",
        "General\nTeam\nClass\nHouse\nAttachment",
        "Select",
        "Close"
    );
    return 1;
}

ShowCommands(playerid, type)
{
    new
        string[1024];
    switch(type)
    {
        case 0:
        {
            strcat(string, ""C_ORANGE"Bought items from 24/7\n\
                "C_GREY"/breakcuff "C_WHITE"- Escape from cuffs using a picklock.\n\
                "C_GREY"/breakout "C_WHITE"- Escape from jail using a picklock.\n\
                "C_GREY"/tie "C_WHITE"- Tie a player using a rope.\n\
                "C_GREY"/breaktie "C_WHITE"- Escape from being tied.\n\n");

            strcat(string, ""C_ORANGE"General Commands\n\
                "C_GREY"/payticket "C_WHITE"- Pay current ticket.\n\
                "C_GREY"/rob "C_WHITE"- Rob the nearest player.\n\
                "C_GREY"/placehit "C_WHITE"- Place a hit on a player you HATE.\n\
                "C_GREY"/eject "C_WHITE"- Eject a player from your vehicle.\n\
                "C_GREY"/smokeweed "C_WHITE"- Smoke weed that you bought.\n\
                "C_GREY"/smokecrack "C_WHITE"- Smoke crack that you bought.\n\
                "C_GREY"/buyweed "C_WHITE"- Buy weed from a drug dealer that offered you.\n\
                "C_GREY"/buycrack "C_WHITE"- Buy crack from a drug dealer that offered you.\n\
                "C_GREY"/pm "C_WHITE"- Private message a player\n\
                "C_GREY"/dnd "C_WHITE"- disable/enable players private messing you.\
                ");
            Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, ""C_ORANGE"General Commands", string, "Close", "");
        }
        case 1:
        {
            strcat(string, ""C_ORANGE"Basic Commands:\n\n\
            "C_GREY"! "C_WHITE"- Radio chat.\n\
            "C_GREY"MMB "C_WHITE"\n- (in vehicle) Request a wanted player in a vehicle to be pulled over\n- (on foot) Cuff and arrest the closest wanted player.\n\n\
            "C_GREY"/ar "C_WHITE"- Arrest a wanted player and send him to jail.\n\
            "C_GREY"/cuff "C_WHITE"- Cuff a player and you can arrest him afterwards.\n\
            "C_GREY"/uncuff "C_WHITE"- Remove a player's cuff and set him free.\n\
            "C_GREY"/ticket "C_WHITE"- Give a low wanted level player a ticket, and lose his/her stars."
            );

            Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, ""C_ORANGE"Law Enforcement Officers Command", string, "Close", "");
        }
        case 2:
        {
            strcat(string, ""C_ORANGE"Hitman\n\
                "C_GREY"/hitlist "C_WHITE"- Check a list of players with hits on them.\n\n");

            strcat(string, ""C_ORANGE"Weapon Dealer\n\
                "C_GREY"/sellgun "C_WHITE"- Sell weapon to a player.\n\
                "C_GREY"/sellarmour "C_WHITE"- Sell armour to a player.\n\n");

            strcat(string, ""C_ORANGE"Rapist\n\
                "C_GREY"/rape "C_WHITE"- Rape a player and infect him with different kinds of infections.\n\n");

            strcat(string, ""C_ORANGE"Terrorist\n\
                "C_GREY"/plantc4 "C_WHITE"- Plant a C4 to.\n\
                "C_GREY"/detonate "C_WHITE"- To detonate the c4 that has been planted.\n\n");

            strcat(string, ""C_ORANGE"Drug Dealer\n\
                "C_GREY"/plantweed "C_WHITE"- Plant a weed seed.\n\
                "C_GREY"/harvestweed "C_WHITE"- Harvest the planted weed.\n\
                "C_GREY"/sellweed "C_WHITE"- Sell weed to player.\n\
                "C_GREY"/sellcrack "C_WHITE"- Sell crack to player.\n\n");

            strcat(string, ""C_ORANGE"Mechanic\n\
                "C_GREY"/mechfix "C_WHITE"- Fix the vehicle you're in.");

            Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, ""C_ORANGE"Job Commands", string, "Close", "");
        }
    }
    return 1;
}