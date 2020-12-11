# GTA Open
##### A Cops and robbers mode based in Los Santos with features including...
- Robbing stores and players
- Attachments (a.k.a clothing system)
- Houses with different interiors that can be customised with an array of furnitures.
- Be a drug dealer, get the skill to plant cannabis and make cocaine.
- Casino where you can play on slot machine and gamble.
- Become a good citizen, do legal missions such as pizza delivery, trucking and so much more!
- Per player vehicle system, customize your car, cutomize your plate and everything will be saved.
- Gangs, competitive gang system that competes with other gangs kills, deaths and zone captures.

## Discord server
Join our discord server discord.gg/fhN3q4J6Qr


# Running & Compiling
Run this gamemode in three line!
```bash
sampctl package ensure
sampctl package build
sampctl package run
```

# How to contribute.

#### Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. 

Any contributions you make are **greatly appreciated**.

- 1. Fork the Project
- 2. Create your Feature Branch (`git checkout -b feature/`)
- 3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
- 4. Push to the Branch (`git push origin feature/AmazingFeature`)
- 5. Open a Pull Request

#### Style Guide
```c
// Constants and macros in "UPPER_CASE", with underscores separating words.
#define MAX_PASSWORD    (16)

const INVALID_ARENA_ID = -1;

// 'static' Globals as much as possible to avoid conflict
// with other module that may have the same variable name
static
    // Globals `g` prefixed and camel case.
    gPlayerPassword[MAX_PASSWORD],
    gArenaID[MAX_PLAYERS] = INVALID_ARENA_ID;

// ------------------------------------------------------------------------
// Brace style
// ------------------------------------------------------------------------
// Both style are acceptable but please NOTE!
// make the indentation style consistent depending on the 
// module you are working on.

// K & R
if(condition == true)
    condition == false;

// Allman 
if(condition == true) 
{
    condition == false;
}

// ------------------------------------------------------------------------
// Function Name
// ------------------------------------------------------------------------
// Functions in PascalCase - all words start with an upper-case letter.
// Each Function must be prefixed with the name of the module

// For example we have a module called 'level.inc'
// the module will be an API so we don't have to access the variables anywhere other than the module.
// Functional Programming!!

Level_Get(playerid) {
    if(!IsPlayerConnected(playerid)) {
        return -1; // notice how we used -1, because 0 is a valid level.
    }

    return gPlayerLevel[playerid];
}

Level_GivePlayer(playerid, level) {
    // Braces even for single statements.
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }
    
    // Single declaration for multiple variables, with each on a new indented line.
    new 
        // Variables/parameters in "lowerCamelCase" - as above, except the first word.
        playerLevel = Level_Get(playerid);

    // Module names come first before an underscore.
    Level_Set(playerid, playerLevel + level);
    return 1;
}

Level_Set(playerid, level, bool:save = false) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    gPlayerLevel[playerid] = level;
    
    if(save) {
        // mock update the database.
        // UPDATE player_statistics SET level = level + ?
        // ? = level
        // execute statement.
    }
    return 1;
}

// ------------------------------------------------------------------------
// Credentials
// ------------------------------------------------------------------------
// Delicate information such as discord_token & mysql credentials
// must be stored in environment variables to avoid rouge scripter who will tamper with the database
// NOTE: 
// USE https://github.com/dakyskye/pawn-env

public OnGameModeInit() {
     new 
        MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true); // it automatically reconnects when loosing connection to mysql server 

    new 
        username[24],
        host[24],
        password[24],
        database[24];

    // it's important to add a fallback if first statement fails.
    // like shown below.
    if(Env_Has("MYSQL_USERNAME")) {
        Env_Get("MYSQL_USERNAME", username);
    } 
    else {
        print("Could not find environment variable for MYSQL_USERNAME");
    }
    
    if(Env_Has("MYSQL_PASSWORD")) {
        Env_Get("MYSQL_PASSWORD", password);
    }
    else {
        print("Could not find env ironment variable for MYSQL_PASSWORD");
    }

    if(Env_Has("MYSQL_HOST")) {
        Env_Get("MYSQL_HOST", host);
    } 
    else {
        print("Could not find environment variable for MYSQL_HOST");
    }
    
    if(Env_Has("MYSQL_DATABASE")) {
        Env_Get("MYSQL_DATABASE", database);
    }
    else {
        print("Could not find environment variable for MYSQL_DATABASE");
    }
    
    MySQL_ConHandle = mysql_connect(host, username, password, database);

    if(MySQL_ConHandle == MYSQL_INVALID_HANDLE || mysql_errno(MySQL_ConHandle) != 0) {
        print("MySQL failed to connect. Server shutting down...");
        exit();
        return 1;
    }

    print("MySQL connection is successful.");
    return 1;
}


// ------------------------------------------------------------------------
// MySQL Prepared Statements
// ------------------------------------------------------------------------
// Each statement declaration must have stmt_ prefix.
// after the prefix, naming must be CamelCase.
static 
    stmt_CamelCase;

// long queries must be seperated into different lines 
// for better readability.
// it also should be stored in an array with no fixed size 
// declared as 'static const'
static const query_LoadAttachments[] = "\
    SELECT \
        slot, \
        model, \
        bone, \
        offset_x, \
        offset_y, \
        offset_z, \
        rotation_x,\
        rotation_y, \
        rotation_z, \
        scale_x, \
        scale_y, \
        scale_z \
    FROM \
        attachments \
    WHERE \
        u_id = ?"
; // this is only acceptable for queries.
```

# Thanks to
Name | Message
--- | --- |
[Southclaws] | Includes, snippets from Scavenge Survive, sampctl.
[maddinat0r] | MySQL
[Y_Less]     | for YSI Library, used a lot throughout the code.
[Zeex]       | amx_assembly, crashdetect, indirection
[Slice]      | formatex
[Lorenc]     | SFCNR, snippets & data from sfcnr
 
Very special thanks to
**SA:MP Team past, present and future - SA:MP.**

