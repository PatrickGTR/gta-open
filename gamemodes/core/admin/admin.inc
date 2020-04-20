#include <YSI_Coding\y_hooks>

#include <admin_account>
#include <admin_ban>

#include <admin_cmd_lvl1>

#include <admin_cmd_lvl4>


hook OnGameModeInit() {

    Admin_AddCommandToList(1, "/acmds - list of admin commands");

    Admin_AddCommandToList(3, "/ban");
    Admin_AddCommandToList(3, "/unban");

    Admin_AddCommandToList(4, "/setvip");
}
