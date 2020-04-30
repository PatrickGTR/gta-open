# GTA Open
## Cops and robbers mode based in Los Santos.


Run this gamemode in two line!
```bash
sampctl package install
sampctl package run
```

# How to contribute.

## Modules
Each module must have a prefix and should be in the right place.

self explanatory.
```c
// folder tree

account_
admin_
anticheat_ // currently w.i.p
player_
player\attachment_ 
server_
utils_
```

## Variable Declaration
### Global
```c
// Every global variable must have a g prefix.
// Must be camel case.
// e.g
new 
    gServerData;
```

### Local
```c
// I would only accept two ways of declaration.
// like shown below, this way we kep the code style consistent.

// First (PREFERRED!)
new 
    first,
    second,
    third;

// Second
new first, second, third;

// DO NOT 
new 
    first, second, third
;
// OR
new 
    first, 
    second, 
    third
;
```

## Prepared Statement & MySQL
```c
// Each statement declaration must have stmt_ prefix.
// after the prefix, naming must be CamelCase.
// e.g
static stmt_CamelCase;

// long queries must be seperated into different lines 
// for better readability.
// it also should be stored in an array with no fixed size 
// declared as 'static const'
// e.g
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

# MySQL Table Structure 
Table Name | Relationship
--- | --- |
[players] | Parent
[admins] | child of players
[vips] | child of players
[bans] | Parent (standalone)

# Thanks to
Name | Message
--- | --- |
[Southclaws] | Includes, snippets from Scavenge Survive, sampctl.
[maddinat0r] | MySQL
[Y_Less]     | for YSI Library, used a lot throughout the code.
[Zeex]       | amx_assembly, crashdetect, indirection
[Slice]      | formatex
[Lorenc]     | spawn, entrance data etc..
 
Very special thanks to
**SA:MP Team past, present and future - SA:MP.**

