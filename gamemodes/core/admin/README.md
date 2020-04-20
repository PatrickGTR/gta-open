# Admin Module

## admin.inc (main module)
- The main tree of the module, all the files with **admin_** prefix will be included here.
#### hooked callback
- hook OnGameModeInit - appends all the admin command to **adminCommands** variable.

## admin_ban.inc
- ``Ban_AddUser(playerid, byid, reason, interval_type, banduration)`` - Creates a new entry on the database.
- ``Ban_RemoveUser(username[], playerid = INVALID_PLAYER_ID)`` - Removes an entry from the database.
- ``Ban_Check(playerid)`` - Returns true if the player matches one of the entries in the database by IP, GCPI or name.
- ``Ban_GetData(playerid, username[], ip[], reason[], admin[], bandate[], unbandate[])`` - Returns all the ban data, used if **Ban_Check** is true.

check module [admin_ban-cmd.inc](https://github.com/PatrickGTR/gta-open/blob/master/gamemodes/core/admin/admin_ban-cmd.inc) for usage of this API.

## admin_setup-table.inc ##
#### hooked callback
- ``hook OnGameModeInit`` - initialise table setup.

## NOTE: 
- This module is only included if ``#define SETUP_TABLE`` is set to **TRUE**

## admin_account.inc
#### constants
- ``#define MAX_ADMIN_LEVELS (5)``
```chttps://github.com/PatrickGTR/gta-open
enum
{
    ADM_LVL_1 = 1,
    ADM_LVL_2,
    ADM_LVL_3,
    ADM_LVL_4,
    ADM_LVL_5
}
```

#### hooked callback
- ``hook OnGameModeInit`` - Initiliase the prepared statement
- ``hook OnPlayerLogin`` - Run a query check if the user who logged in has an account in admins then log him in with admin level. 
#### Functions
- ``SendAdminMsg(const fmat[])`` - Send message to all admins.
- ``SendAdminMsgF(const fmat[], {Float,_}:...)`` - Same as SendAdminMsg but formatted.
- ``Admin_AddCommandToList(level, const string[])`` - Adds an admin command to spciefied level in **/acmds** 
- ``Admin_SetPlayerLevel(playerid, level)`` - Sets the player with specified level, if player is already an admin, just update the admin_level column with new level.
- ``Admin_GetRankName(playerid)`` - returns the name of the admin level.
- ``Admin_GetPlayerLevel(playerid)`` - returns the admin level of the player.
- ``Admin_SetPlayerDuty(playerid, bool:toggle)`` - change the user onduty state, toggle takes **true** or **false**
- ``Admin_IsOnDuty(playerid)`` - returns true if player is on duty and false if not.
