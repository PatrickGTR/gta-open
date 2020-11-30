#include <YSI_Coding\y_hooks>

#include <admin_account>
#include <admin_ban>

#include <admin_cmd_lvl1>
#include <admin_cmd_lvl2>

// #include <admin_cmd_lvl3carscmds>
#include <admin_cmd_lvl3>
#include <admin_cmd_lvl4>
#include <admin_remove-account>
#include <admin_cmd_lvl5>

#include <admin_cmd-atm>
#include <rcon_cmd>
#include <fly_cmd>
#include <admin_player-accuracy>
#include <admin_spec-cmd>

hook OnGameModeInit() {
    Admin_AddCommandToList(1, "/freeze");
    Admin_AddCommandToList(1, "/akill");
    Admin_AddCommandToList(1, "/afix");
    Admin_AddCommandToList(1, "/get");
    Admin_AddCommandToList(1, "/kick");
    Admin_AddCommandToList(1, "/goto");

    Admin_AddCommandToList(2, "/jail");
    Admin_AddCommandToList(2, "/unjail");
    Admin_AddCommandToList(2, "/tempban");

    Admin_AddCommandToList(3, "/getallciv");
    Admin_AddCommandToList(3, "/unban");
    Admin_AddCommandToList(3, "/disarm");
    Admin_AddCommandToList(3, "/sethealth");
    Admin_AddCommandToList(3, "/eventint - event interiors");
    Admin_AddCommandToList(3, "/setarmour");
    Admin_AddCommandToList(3, "/giveweaps");
    Admin_AddCommandToList(3, "/veh");
    Admin_AddCommandToList(3, "/offban");
    Admin_AddCommandToList(3, "/aveh - admin vehicle");
    Admin_AddCommandToList(3, "/dav - destroy all admin vehicle");
    Admin_AddCommandToList(3, "/rscars - destroy all vehicle");
    Admin_AddCommandToList(3, "/setname - change a player's name");

    Admin_AddCommandToList(4, "/setvip");
    Admin_AddCommandToList(4, "/givemoney");
    Admin_AddCommandToList(4, "/givearmy - Allow a player to access Army skins");
    Admin_AddCommandToList(4, "/fine");
    Admin_AddCommandToList(4, "/hcreate");
    Admin_AddCommandToList(4, "/hdelete");
    Admin_AddCommandToList(4, "/getmoney - to get someone's money info");

    Admin_AddCommandToList(5, "/setadmin");
    Admin_AddCommandToList(5, "/settester");
    Admin_AddCommandToList(5, "/setplayerdept - set a player bank's dept");
    Admin_AddCommandToList(5, "/bankrupt - set a player bank and tax bal to 0");
    Admin_AddCommandToList(5, "/skick - silent kick");
    Admin_AddCommandToList(5, "/setarmy - set army even score is not 30k");
    Admin_AddCommandToList(5, "/blacklist - blacklist a player from the army");
    Admin_AddCommandToList(5, "/unblacklist");
    Admin_AddCommandToList(5, "/deleteacc - delete an acc from the database");
    Admin_AddCommandToList(5, "/createatm");
    Admin_AddCommandToList(5, "/deleteatm");
    Admin_AddCommandToList(5, "/editatm");
}
