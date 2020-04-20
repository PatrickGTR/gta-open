# Account Module

## accounts.inc (main module)
- The main tree of the module, all the files with **account_** prefix will be included here.

#### hooked callbacks
- ``hook OnMySQLConnected()`` - Initialise the prepared statement for this module.
- ``hook OnPlayerConnect(playerid)`` - Initialise player data, checks if player is banned if not ban then proceed to check whether player is registered otherwise prompt register dialog.
#### Functions
- ``SetPlayerKills(playerid, value)``
- ``GetPlayerKills(playerid)``
- ``SetPlayerDeaths(playerid, value)``
- ``GetPlayerDeaths(playerid)``
- ``SetPlayerAccountID(playerid, value) ``
- ``GetPlayerAccountID(playerid)``
  
## account_create.inc 
#### hooked callback
- ``hook OnMySQLConnected`` - Initialise the prepared statement for this module.

#### Functions
- ``stock Account_PromptRegister(playerid)`` - Shows the login dialog.
- ``static Account_Create(playerid, const password[])`` - Internal function, validations, if all check has passed then call **OnPasswordHash**
- ``static Account_InsertToDatabase(playerid, const hash)`` - Internal function, creates a new entry on the database, also notifies player when registered successfully.

## account_login.inc
#### constants
``#define MAX_PASSWORD_ATTEMPT (5)``
#### hooked callbacks
- ``hook OnMySQLConnected(playerid)`` - Initialise the prepared statement for this module.
- ``hook OnPlayerConnect(playerid)`` - Initialise the variables to **none** when player connects.
#### Functions
- ``OnPasswordVerify(playerid, bool:success)`` - bcrypt callback that does all the hash comparing, in this callback we also limit on how many failed attempts before we kick, the limit depends on **MAX_PASSWORD_ATTEMPT**
- ``Account_PromptLogin(playerid, const password[], len = sizeof(password))`` - Shows the login dialog for player.
- ``Account_LoadData(playerid)`` - Loads the user's data when successfully logged in.
- ``Player_IsLoggedIn(playerid)`` - returns whether player is logged in or not.

## account_setup-table.inc
#### hooked callback
- ``hook OnMySQLConnected()`` - initialise the table setup for accounts.

## NOTE:
-  This module is only included if ``#define SETUP_TABLE`` is set to **TRUE**

## account_vip.inc
#### hooked callbacks
- ``hook OnMySQLConnected()`` - initialise table setup.
- ``hook OnPlayerLogin(playerid)`` - Run a query check if the user who logged in has an account in vips then log him in with vip level.
#### functions
- ``VIP_GivePlayer(playerid, level, interval_type, duration)`` - sets player vip level and inserts a new entry for player in the database.
- ``VIP_RemovePlayer(playerid)`` - removes player vip level and deletes the entry of player in the database.
- ``VIP_GetPlayerLevel(playerid)`` - returns the player's vip level.