# Admin Module

## admin_account.inc
#### constants
- ``#define MAX_ADMIN_LEVELS (5)``
```c
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
