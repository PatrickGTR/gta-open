#include <YSI_Coding\y_hooks>

#if SETUP_TABLE
    #include <admin_setup-bans-table>
    #include <admin_setup-admins-table>
    #include <admin_setup-atm-table>
#endif

#include <admin_account>
#include <admin_ban>

#include <admin_cmd_lvl1>

#include <admin_cmd_lvl2>

#include <admin_cmd_lvl4>

#include <admin_cmd_lvl5>

#include <admin_cmd-atm>
#include <rcon_cmd>
#include <fly_cmd>

hook OnGameModeInit() {
    Admin_AddCommandToList(1, "/acmds - list of admin commands");
    Admin_AddCommandToList(1, "/get - get a player");
    Admin_AddCommandToList(1, "/goto - go to a player");
    Admin_AddCommandToList(1, "/a - admin chat");

    Admin_AddCommandToList(2, "/unjail - unjail a player");

    Admin_AddCommandToList(3, "/ban");
    Admin_AddCommandToList(3, "/unban");

    Admin_AddCommandToList(4, "/setvip");
    Admin_AddCommandToList(4, "/givemoney");
    Admin_AddCommandToList(4, "/fine");
    Admin_AddCommandToList(4, "/getmoney - to get someone's money info");

    Admin_AddCommandToList(5, "/setadmin");
    Admin_AddCommandToList(5, "/settester");
    Admin_AddCommandToList(5, "/setplayerdept - set a player bank's dept");
    Admin_AddCommandToList(5, "/bankrupt - set a player bank and tax bal to 0");
    Admin_AddCommandToList(5, "/createatm");
    Admin_AddCommandToList(5, "/deleteatm");
    Admin_AddCommandToList(5, "/editatm");
    Admin_AddCommandToList(5, "/nearatm");
}
