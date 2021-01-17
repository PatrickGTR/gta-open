// Gang Module
// Written by PatrickGTR

#include <YSI_Coding\y_hooks>

#define INVALID_GANG_ID (-1)

static
// Player Data
    bool:PlayerIsLeader[MAX_PLAYERS] = false,
    bool:PlayerInGang[MAX_PLAYERS] = false,
    PlayerInGangID[MAX_PLAYERS] = INVALID_GANG_ID,
// Invite Data
    PlayerInviterID[MAX_PLAYERS],
    bool:PlayerIsInvited[MAX_PLAYERS] = false;

static
    Iterator: GangIndex<MAX_GANGS>,
    GangName[MAX_GANGS][MAX_GANG_NAME],
    GangID[MAX_GANGS],
    GangColour[MAX_GANGS],
    GangLeader[MAX_GANGS],
    GangLeaderName[MAX_GANGS][MAX_PLAYER_NAME];

static
    Statement: stmt_CreateGang,
    Statement: stmt_InsertMember,
    Statement: stmt_DeleteMember,
    Statement: stmt_DeleteGang,
    Statement: stmt_LoadGang,
    Statement: stmt_IsGangMember;

hook OnMySQLConnected() {

    stmt_CreateGang = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO gangs (leader_uid, name) VALUES (?, ?)");
    stmt_InsertMember = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT into gang_members (gang_id, user_id) VALUES (?,?)");
    stmt_DeleteMember = MySQL_PrepareStatement(MySQL_GetHandle(), "DELETE FROM gang_members WHERE user_id = ?");
    stmt_DeleteGang = MySQL_PrepareStatement(MySQL_GetHandle(), "DELETE FROM gangs WHERE leader_uid = ? AND id = ?");

    static const loadGangs_Query[] =
    "SELECT \
        g.id, \
        g.leader_uid, \
        g.name, \
        g.colour, \
        g.kills, \
        g.deaths, \
        p.username \
    FROM  \
        gangs as g \
    LEFT JOIN  \
        players as p \
    ON  \
        p.u_id = g.leader_uid \
    ";

    stmt_LoadGang = MySQL_PrepareStatement(MySQL_GetHandle(), loadGangs_Query);

    static const checkMember_Query[] =
    "SELECT \
        gm.gang_id, \
        gm.gang_rank, \
        g.leader_uid \
    FROM \
        gang_members AS gm \
    LEFT JOIN \
        gangs AS g \
    ON \
        gm.gang_id = g.id \
    WHERE \
        gm.user_id = ?";
    stmt_IsGangMember = MySQL_PrepareStatement(MySQL_GetHandle(), checkMember_Query);

    // Load Gang
    inline const OnLoadGang() {
        new
            gangID,
            gangLeader,
            gangName[MAX_GANG_NAME],
            gangColour,
            gangKills,
            gangDeaths,
            gangLeaderName[MAX_PLAYER_NAME];

        MySQL_BindResultInt(stmt_LoadGang, 0, gangID);
        MySQL_BindResultInt(stmt_LoadGang, 1, gangLeader);
        MySQL_BindResult(stmt_LoadGang, 2, gangName, sizeof(gangName));
        MySQL_BindResultInt(stmt_LoadGang, 3, gangColour);
        MySQL_BindResultInt(stmt_LoadGang, 4, gangKills);
        MySQL_BindResultInt(stmt_LoadGang, 5, gangDeaths);
        MySQL_BindResult(stmt_LoadGang, 6, gangLeaderName, sizeof(gangLeaderName));

        new
            freeID = 0,
            startTick;

        startTick = GetTickCount();
        new
            count = 0;
        while(MySQL_Statement_FetchRow(stmt_LoadGang)) {
            freeID = Iter_Alloc(GangIndex);

            GangID[freeID] = gangID;
            GangLeader[freeID] = gangLeader;
            GangName[freeID] = gangName;
            GangColour[freeID] = gangColour;
            GangLeaderName[freeID] = gangLeaderName;

            Gang_AddKills(freeID, gangKills);
            Gang_AddDeaths(freeID, gangDeaths);

            count ++;
        }

        Logger_Log("Gang Loaded",
            Logger_I("total", count),
            Logger_I("load time (ms)", GetTickCount() - startTick)
        );
    }
    MySQL_ExecuteThreaded_Inline(stmt_LoadGang, using inline OnLoadGang);
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerInGang[playerid] = false;
    PlayerIsLeader[playerid] = false;
    PlayerInGangID[playerid] = INVALID_GANG_ID;
    PlayerInviterID[playerid] = INVALID_PLAYER_ID;
    PlayerIsInvited[playerid] = false;
    return 1;
}

hook OnPlayerLogin(playerid) {
    inline const OnMemberCheck() {
        new
            gangID = INVALID_GANG_ID,
            gangRank = 0,
            gangLeaderUID = -1;

        MySQL_BindResultInt(stmt_IsGangMember, 0, gangID);
        MySQL_BindResultInt(stmt_IsGangMember, 1, gangRank);
        MySQL_BindResultInt(stmt_IsGangMember, 2, gangLeaderUID);

        if(MySQL_Statement_FetchRow(stmt_IsGangMember)) {
            PlayerInGang[playerid] = true;
            PlayerIsLeader[playerid] = (Player_GetAccountID(playerid) == gangLeaderUID) ? (true) : (false);
            PlayerInGangID[playerid] = gangID;
        }
    }

    MySQL_BindInt(stmt_IsGangMember, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_IsGangMember, using inline OnMemberCheck);
    return 1;
}

// PLAYER
Player_GetGangID(playerid) {
    return PlayerInGangID[playerid];
}

// GANG
Gang_GetName(gangid, name[], len = sizeof(name)) {

    if(gangid == INVALID_GANG_ID) {
        return;
    }

    new
        idx = INVALID_GANG_ID;

    foreach(idx : GangIndex) {
        if(gangid == GangID[idx]) {
            break;
        }
    }

    strcpy(name, GangName[idx], len);
}

// returns
// 0 -> gang name already exists
// 1 -> success
// -1 -> gang limit exceed
Gang_Create(playerid, const string:gangName[]) {

    new
        bool:found = false;
    foreach(new i : GangIndex) {
        if(!strcmp(gangName, GangName[i])) {
            found = true;
        }
    }

    if(found) {
        return 0;
    }

    if(Iter_Count(GangIndex) > MAX_GANGS) {
        return -1;
    }

    new
        fix_inline[MAX_GANG_NAME];
    strcpy(fix_inline, gangName);

    inline const CreateGang() {
        // Assign Data
        new
            idx = Iter_Free(GangIndex),
            gangID = cache_insert_id();


        GangName[idx] = fix_inline;
        GangID[idx] = gangID;
        GangColour[idx] = -1;
        GangLeader[idx] = Player_GetAccountID(playerid);
        GangLeaderName[idx] = ReturnPlayerName(playerid);

        Iter_Add(GangIndex, idx);

        // Add player to the gang.
        Gang_Join(playerid, gangID);

        // Make player gang leader.
        PlayerIsLeader[playerid] = true;
    }


    // Insert Data to database.
    MySQL_BindInt(stmt_CreateGang, 0, Player_GetAccountID(playerid)); // leader uid
    MySQL_Bind(stmt_CreateGang, 1, gangName); // gang name
    MySQL_ExecuteThreaded_Inline(stmt_CreateGang, using inline CreateGang);
    return 1;
}

// returns
// 1 -> success
// 0 -> invalid gang id
// -1 -> playerid not leader.
Gang_Disband(playerid, id) {
    if(id == INVALID_GANG_ID) {
        return 0;
    }

    if(!PlayerIsLeader[playerid]) {
        return -1;
    }

    // remove data from databases.
    MySQL_BindInt(stmt_DeleteGang, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_DeleteGang, 1, PlayerInGangID[playerid]);
    MySQL_ExecuteThreaded(stmt_DeleteGang);

    // reset player data.
    foreach(new i : Player) {
        if(PlayerInGangID[playerid] != PlayerInGangID[i]) {
            // skip player who are not in the same gang.
            continue;
        }

        PlayerIsLeader[i] = false;
        PlayerInGang[i] = false;
        PlayerInGangID[i] = INVALID_GANG_ID;
    }

    // reset gang data.
    new
        idx = INVALID_GANG_ID;
    foreach(idx : GangIndex) {
        if(id == GangID[idx]) {
            break;
        }
    }

    GangName[idx][0] = EOS;
    GangID[idx] = INVALID_GANG_ID;
    GangColour[idx] = -1;
    GangLeader[idx] = -1;
    GangLeaderName[idx][0] = EOS;

    Iter_Remove(GangIndex, idx);
    return 1;
}

// returns
// 1 -> success
// 0 -> player was not invited.
// -1 -> inviter is not connected anymore.
Gang_AcceptInvite(playerid, &gangID, &gangColour, &inviterid, gangName[MAX_GANG_NAME]) {
    if(!PlayerIsInvited[playerid]) {
        return 0;
    }

    // 			   NOTE! [To avoid confusion]
    // inviterID    == the player who initiated the invite.
    // playerid     == the player who got invited.
    // inviterid    == pass on argument of player who initiated the invite.
    new
        inviterID = PlayerInviterID[playerid];

    if(!IsPlayerConnected(inviterID)) {
        return -1;
    }

    new
        idx = INVALID_GANG_ID;
    foreach(idx : GangIndex) {
        if(PlayerInGangID[inviterID] == GangID[idx]) {
            break;
        }
    }

    inviterid = PlayerInviterID[playerid];
    gangID = PlayerInGangID[inviterID];
    gangColour = GangColour[idx];
    strcpy(gangName, GangName[idx]);

    Gang_Join(playerid, PlayerInGangID[inviterID]);

    // Clear data
    GangInviteTimerExpire(playerid);
    return 1;
}

// returns
// 0 -> targetid not connected.
// 1 -> success
// -1 -> targetid is already in gang.
// -2 -> playerid is not a gang leader.
Gang_InvitePlayer(playerid, targetid) {
    if(!IsPlayerConnected((targetid))) {
        return 0;
    }

    if(PlayerInGangID[targetid] != INVALID_GANG_ID) {
        return -1;
    }

    if(!PlayerIsLeader[playerid]) {
        return -2;
    }

    PlayerInviterID[targetid] = playerid;
    PlayerIsInvited[targetid] = true;

    // start expire count.
    defer GangInviteTimerExpire(targetid);
    return 1;
}

timer GangInviteTimerExpire[1000 * 60](playerid)  {
    PlayerInviterID[playerid] = INVALID_PLAYER_ID;
    PlayerIsInvited[playerid] = false;
}

Gang_Join(playerid, id) {
    if(id == INVALID_GANG_ID) {
        return 0;
    }

    PlayerInGang[playerid] = true;
    PlayerInGangID[playerid] = id;

    // Insert Data to database.
    MySQL_BindInt(stmt_InsertMember, 0, id);
    MySQL_BindInt(stmt_InsertMember, 1, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_InsertMember);
    return 1;
}


// returns
// 0 -> player not in gang
// 1 -> success
Gang_Leave(playerid) {
    if(!PlayerInGang[playerid]) {
        return 0;
    }

    PlayerInGang[playerid] = false;
    PlayerInGangID[playerid] = INVALID_GANG_ID;

    // Delete Data to database.
    MySQL_BindInt(stmt_DeleteMember, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_DeleteMember);
    return 1;
}

Gang_ShowMembers(playerid, bool:online = true) {
    new
        count = 0;
    if(online) {
        TextInfo_Create(playerid, "GANGMEM", "Online Members");
        foreach(new i : Player) {
            // skip self
            if(playerid == i) {
                continue;
            }
            if(Player_GetGangID(playerid) == Player_GetGangID(i)) {
                TextInfo_Add(playerid, ReturnPlayerName(i));
                count ++;
            }
        }

        if(count == 0) {
            TextInfo_Add(playerid, "No Online Members");
        }

        TextInfo_Show(playerid);
    }
    else {
        // TODO: show offline members
    }

    return 1;
}

Gang_ShowGangs(playerid) {
    TextInfo_Create(playerid, "GANGS", "Gangs");
    new
        string[64];
    foreach(new i : GangIndex) {
        format(string, sizeof(string),
            "~y~%s ~w~- ~y~%s",
            GangID[i], GangName[i], GangLeaderName[i]
        );
        TextInfo_Add(playerid, string);
    }

    TextInfo_Show(playerid);
    return 1;
}

#include <gang_stats>