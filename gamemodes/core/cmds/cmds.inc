#include <cmds_info>
#include <cmds_arrest>
#include <cmds_cuff>
#include <cmds_bail>
#include <cmds_v> // vehicle
#include <cmds_pm> // private message
#include <cmds_gang>
#include <cmds_perks>

#include <cmds_rob>

#include <cmds_breakcuff>
#include <cmds_breakout>
#include <cmds_ghosthunt>
#include <cmds_gps>

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

    if (!success) {
        return SendErrorMsgF(playerid, "Command ~r~'/%s' ~w~does not exist. Try ~y~'/help'~w~ to see the list of commands.", cmd);
    }

    //get time data everytime a command is performed.
    cmd_Cooldown[playerid] = gettime() + 3;
    return 1;
}


// =============================================================================
// HELP / COMMANDS MENU
// =============================================================================

ALTCMD:help(commands);
ALTCMD:cmds(commands);
CMD:commands(playerid, params[]) {

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext
        if (!response) {
            return 0;
        }

        switch(listitem) {
            case 0: _HelpMenu_General(pid);
            case 1: _HelpMenu_LawEnforcement(pid);
            case 2: _HelpMenu_Jobs(pid);
            case 3: _HelpMenu_Criminal(pid);
            case 4: _HelpMenu_SideJobs(pid);
            case 5: _HelpMenu_House(pid);
            case 6: _HelpMenu_Gang(pid);
            case 7: _HelpMenu_Attachment(pid);
            case 8: _HelpMenu_Animations(pid);
        }
    }
    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        ""C_ORANGE"Server Help & Commands",
        ""C_WHITE"General & Communication\n\
        "C_WHITE"Law Enforcement (Police / Army)\n\
        "C_WHITE"Job Skills\n\
        "C_WHITE"Criminal Activities\n\
        "C_WHITE"Side Jobs & Activities\n\
        "C_WHITE"House\n\
        "C_WHITE"Gang\n\
        "C_WHITE"Attachments & Furniture\n\
        "C_WHITE"Animations",
        "Select",
        "Close"
    );
    return 1;
}

// ---------------------------------------------------------------------------
// GENERAL & COMMUNICATION
// ---------------------------------------------------------------------------

static _HelpMenu_General(playerid) {
    new string[768];

    strcat(string, ""C_ORANGE"Communication\n\
        "C_GREY"/pm <id> <message> "C_WHITE"- Send a private message.\n\
        "C_GREY"/r <message> "C_WHITE"- Reply to the last PM you received.\n\
        "C_GREY"/dnd "C_WHITE"- Toggle Do-Not-Disturb (block PMs).\n\n");

    strcat(string, ""C_ORANGE"Information & Stats\n\
        "C_GREY"/info "C_WHITE"- View your player stats and info.\n\
        "C_GREY"/shots [id] "C_WHITE"- View shot accuracy statistics.\n\
        "C_GREY"/getlevel "C_WHITE"- Check your current level and XP.\n\n");

    strcat(string, ""C_ORANGE"Vehicle\n\
        "C_GREY"/v park "C_WHITE"- Park your personal vehicle.\n\
        "C_GREY"/v lock "C_WHITE"- Lock/unlock your vehicle.\n\n");

    strcat(string, ""C_ORANGE"Other\n\
        "C_GREY"/lotto <amount> "C_WHITE"- Enter the lottery.\n\
        "C_GREY"/animlist "C_WHITE"- List all available animations.\n\
        "C_GREY"/surrender "C_WHITE"- Put your hands up.\n");

    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX, ""C_ORANGE"General & Communication", string, "Back", "");
    return 1;
}

// ---------------------------------------------------------------------------
// LAW ENFORCEMENT (POLICE / ARMY)
// ---------------------------------------------------------------------------

static _HelpMenu_LawEnforcement(playerid) {
    new string[768];

    strcat(string, ""C_ORANGE"Arrest & Detain\n\
        "C_GREY"/ar <id> "C_WHITE"- Arrest a wanted player (send to jail).\n\
        "C_GREY"/cuff <id> "C_WHITE"- Handcuff a nearby player.\n\
        "C_GREY"/uncuff <id> "C_WHITE"- Remove a player's handcuffs.\n\
        "C_GREY"/cuffcw "C_WHITE"- Cuff closest wanted player.\n\
        "C_GREY"/arcw "C_WHITE"- Arrest closest wanted player.\n\n");

    strcat(string, ""C_ORANGE"Communication & Controls\n\
        "C_GREY"! <message> "C_WHITE"- Team radio chat.\n\
        "C_GREY"MMB (in vehicle) "C_WHITE"- Request a suspect to pull over.\n\
        "C_GREY"MMB (on foot) "C_WHITE"- Cuff & arrest nearest wanted player.\n\n");

    strcat(string, ""C_ORANGE"Police Mission\n\
        "C_GREY"/mission "C_WHITE"- Start a police patrol mission (at LSPD).\n");

    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX, ""C_ORANGE"Law Enforcement Commands", string, "Back", "");
    return 1;
}

// ---------------------------------------------------------------------------
// JOBS
// ---------------------------------------------------------------------------

static _HelpMenu_Jobs(playerid) {

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, inputtext
        if (!response) {
            // Go back to main help menu
            CommandExecute(pid, "commands");
            return 0;
        }
        switch(listitem) {
            case 0: _HelpMenu_Job_DrugDealer(pid);
            case 1: _HelpMenu_Job_WeaponDealer(pid);
            case 2: _HelpMenu_Job_Hitman(pid);
            case 3: _HelpMenu_Job_Terrorist(pid);
            case 4: _HelpMenu_Job_Rapist(pid);
            case 5: _HelpMenu_Job_Mechanic(pid);
        }
    }

    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        ""C_ORANGE"Job Skills",
        ""C_WHITE"Drug Dealer\n\
        "C_WHITE"Weapon Dealer\n\
        "C_WHITE"Hitman\n\
        "C_WHITE"Terrorist\n\
        "C_WHITE"Rapist\n\
        "C_WHITE"Mechanic",
        "Select",
        "Back"
    );
    return 1;
}

static _HelpMenu_Job_DrugDealer(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        _HelpMenu_Jobs(pid);
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Drug Dealer Commands",
        ""C_GREY"/plantweed "C_WHITE"- Plant a weed seed.\n\
        "C_GREY"/harvestweed "C_WHITE"- Harvest your planted weed.\n\
        "C_GREY"/sellweed <id> "C_WHITE"- Offer weed to a player.\n\
        "C_GREY"/sellcrack <id> "C_WHITE"- Offer crack to a player.\n\n\
        "C_ORANGE"Note: "C_WHITE"Change job at City Hall ($7,500).",
        "Back", ""
    );
    return 1;
}

static _HelpMenu_Job_WeaponDealer(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        _HelpMenu_Jobs(pid);
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Weapon Dealer Commands",
        ""C_GREY"/sellgun <id> <weaponid> <price> <ammo> "C_WHITE"- Offer a weapon.\n\
        "C_GREY"/acceptgun "C_WHITE"- Accept a weapon offer.\n\
        "C_GREY"/sellarmour <id> <price> <amount> "C_WHITE"- Offer armour.\n\
        "C_GREY"/acceptarmour "C_WHITE"- Accept an armour offer.\n\
        "C_GREY"/weapons "C_WHITE"- Buy weapons from dealer menu.\n\
        "C_GREY"/weaponinventory "C_WHITE"- View/edit your weapon inventory.\n\
        "C_GREY"/nosell "C_WHITE"- Toggle selling mode on/off.\n\n\
        "C_ORANGE"Note: "C_WHITE"Change job at City Hall ($7,500).",
        "Back", ""
    );
    return 1;
}

static _HelpMenu_Job_Hitman(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        _HelpMenu_Jobs(pid);
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Hitman Commands",
        ""C_GREY"/hitlist "C_WHITE"- View players with active bounties.\n\
        "C_GREY"/placehit <id> <amount> "C_WHITE"- Place a hit on a player.\n\n\
        "C_ORANGE"Note: "C_WHITE"Change job at City Hall ($7,500).",
        "Back", ""
    );
    return 1;
}

static _HelpMenu_Job_Terrorist(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        _HelpMenu_Jobs(pid);
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Terrorist Commands",
        ""C_GREY"/plantc4 "C_WHITE"- Plant a C4 explosive.\n\
        "C_GREY"/detonate "C_WHITE"- Detonate your planted C4.\n\n\
        "C_ORANGE"Buy C4: "C_WHITE"Visit the Bomb Dealer (map icon).\n\
        "C_ORANGE"Note: "C_WHITE"Change job at City Hall ($7,500).",
        "Back", ""
    );
    return 1;
}

static _HelpMenu_Job_Rapist(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        _HelpMenu_Jobs(pid);
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Rapist Commands",
        ""C_GREY"/rape <id> "C_WHITE"- Infect a nearby player.\n\n\
        "C_ORANGE"Note: "C_WHITE"Change job at City Hall ($7,500).",
        "Back", ""
    );
    return 1;
}

static _HelpMenu_Job_Mechanic(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        _HelpMenu_Jobs(pid);
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Mechanic Commands",
        ""C_GREY"/mechfix "C_WHITE"- Fix the vehicle you are currently in.\n\n\
        "C_ORANGE"Note: "C_WHITE"Change job at City Hall ($7,500).",
        "Back", ""
    );
    return 1;
}

// ---------------------------------------------------------------------------
// CRIMINAL ACTIVITIES
// ---------------------------------------------------------------------------

static _HelpMenu_Criminal(playerid) {
    new string[768];

    strcat(string, ""C_ORANGE"Robbery\n\
        "C_GREY"/rob <id> "C_WHITE"- Rob a nearby player.\n\
        "C_GREY"/robbery "C_WHITE"- Rob stores around the city.\n\
        "C_GREY"/towerrobbery "C_WHITE"- Attempt to rob the tower.\n\n");

    strcat(string, ""C_ORANGE"Escape & Jailbreak\n\
        "C_GREY"/breakcuff "C_WHITE"- Escape from handcuffs (requires picklock).\n\
        "C_GREY"/breakout "C_WHITE"- Escape from jail (requires picklock).\n\
        "C_GREY"/bail "C_WHITE"- Pay bail to get out of jail.\n\n");

    strcat(string, ""C_ORANGE"Tips\n\
        "C_WHITE"- Buy picklocks from 24/7 stores.\n\
        "C_WHITE"- C4 can be used to breach jail cells.\n\
        "C_WHITE"- Car Crusher in Willowfield pays for wanted vehicles.\n");

    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX, ""C_ORANGE"Criminal Activities", string, "Back", "");
    return 1;
}

// ---------------------------------------------------------------------------
// SIDE JOBS & ACTIVITIES
// ---------------------------------------------------------------------------

static _HelpMenu_SideJobs(playerid) {
    new string[768];

    strcat(string, ""C_ORANGE"Trucker (Civilian)\n\
        "C_GREY"/trucker "C_WHITE"- Start a trucking mission (enter a Mule).\n\n");

    strcat(string, ""C_ORANGE"Pizza Delivery (Civilian)\n\
        "C_GREY"/pdelivery "C_WHITE"- Start pizza delivery (enter a Pizzaboy bike).\n\n");

    strcat(string, ""C_ORANGE"Garbage Collector\n\
        "C_GREY"/pickup "C_WHITE"- Pick up trash near dumpsters (Trashmaster).\n\n");

    strcat(string, ""C_ORANGE"Ghost Hunting\n\
        "C_GREY"/starthunt "C_WHITE"- Start a ghost hunting session.\n\
        "C_GREY"/leavehunt "C_WHITE"- Leave the ghost hunt.\n\n");

    strcat(string, ""C_ORANGE"Farming\n\
        "C_GREY"/buyfarm "C_WHITE"- Buy farm supplies (near Farm Supplier NPC).\n\
        "C_GREY"/sellfarm "C_WHITE"- Sell harvest (near Harvest Master NPC).\n\n");

    strcat(string, ""C_ORANGE"Other\n\
        "C_WHITE"- Dumpster Diving: search dumpsters around the map.\n\
        "C_WHITE"- Car Crusher: sell wanted vehicles in Willowfield.\n");

    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX, ""C_ORANGE"Side Jobs & Activities", string, "Back", "");
    return 1;
}

// ---------------------------------------------------------------------------
// HOUSE
// ---------------------------------------------------------------------------

static _HelpMenu_House(playerid) {
    new string[512];

    strcat(string, ""C_ORANGE"House Commands\n\
        "C_GREY"/buyhouse "C_WHITE"- Purchase a house.\n\
        "C_GREY"/hlock "C_WHITE"- Lock/unlock your house.\n\
        "C_GREY"/hdescription <text> "C_WHITE"- Change house description.\n\
        "C_GREY"/hgivekey <id> "C_WHITE"- Give a player a key to your house.\n\
        "C_GREY"/hremovekey <id> "C_WHITE"- Remove a player's key.\n\
        "C_GREY"/furniture "C_WHITE"- Open the furniture menu (inside house).\n\n");

    strcat(string, ""C_ORANGE"Controls\n\
        "C_WHITE"~k~~VEHICLE_ENTER_EXIT~ - Enter/exit house.\n\
        "C_WHITE"~k~~CONVERSATION_NO~ - Open furniture menu (inside house).\n");

    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX, ""C_ORANGE"House Commands", string, "Back", "");
    return 1;
}

// ---------------------------------------------------------------------------
// GANG
// ---------------------------------------------------------------------------

static _HelpMenu_Gang(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Gang Commands",
        ""C_GREY"/gangs "C_WHITE"- View all active gangs.\n\
        "C_GREY"/gang create <name> "C_WHITE"- Create a new gang.\n\
        "C_GREY"/gang disband "C_WHITE"- Disband your gang. "C_YELLOW"(Leader)\n\
        "C_GREY"/gang invite <id> "C_WHITE"- Invite a player. "C_YELLOW"(Leader)\n\
        "C_GREY"/gang accept "C_WHITE"- Accept a gang invitation.\n\
        "C_GREY"/gang leave "C_WHITE"- Leave your current gang.\n",
        "Back", ""
    );
    return 1;
}

// ---------------------------------------------------------------------------
// ATTACHMENTS & FURNITURE
// ---------------------------------------------------------------------------

static _HelpMenu_Attachment(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Attachments & Furniture",
        ""C_ORANGE"Attachments\n\
        "C_GREY"/attachment buy "C_WHITE"- Purchase an attachment.\n\
        "C_GREY"/attachment delete "C_WHITE"- Delete an attachment.\n\
        "C_GREY"/attachment edit "C_WHITE"- Edit an attachment position.\n\
        "C_GREY"/attachment view "C_WHITE"- List all your attachments.\n\
        "C_GREY"/attachment attach "C_WHITE"- Equip an attachment.\n\
        "C_GREY"/attachment detach "C_WHITE"- Unequip an attachment.\n\n\
        "C_ORANGE"Furniture\n\
        "C_GREY"/furniture "C_WHITE"- Open the furniture menu (inside your house).\n",
        "Back", ""
    );
    return 1;
}

// ---------------------------------------------------------------------------
// ANIMATIONS
// ---------------------------------------------------------------------------

static _HelpMenu_Animations(playerid) {
    inline _back(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused dialogid, response, listitem, inputtext
        CommandExecute(pid, "commands");
    }
    Dialog_ShowCallback(playerid, using inline _back, DIALOG_STYLE_MSGBOX,
        ""C_ORANGE"Animations",
        ""C_GREY"/animlist "C_WHITE"- View full list of all animation commands.\n\n\
        "C_ORANGE"Quick Reference\n\
        "C_GREY"/dance <1-3> "C_WHITE"- Dance animations.\n\
        "C_GREY"/sit <1-5> "C_WHITE"- Sitting animations.\n\
        "C_GREY"/surrender "C_WHITE"- Put your hands up.\n\
        "C_GREY"/wave "C_WHITE"- Wave at someone.\n\
        "C_GREY"/smoke <1-2> "C_WHITE"- Smoking animation.\n\
        "C_GREY"/sleep <1-2> "C_WHITE"- Sleeping animation.\n\
        "C_GREY"/gesture <1-15> "C_WHITE"- Gesture animations.\n\
        "C_GREY"/rap <1-3> "C_WHITE"- Rapping animations.\n\
        "C_GREY"/cross <1-5> "C_WHITE"- Crossed arms animations.\n\n\
        "C_ORANGE"Tip: "C_WHITE"Press "C_YELLOW"SPRINT "C_WHITE"to stop any animation.\n",
        "Back", ""
    );
    return 1;
}
