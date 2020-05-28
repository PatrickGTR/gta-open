#include <player_spawn>
#include <player_spawn-protection>
#include <player_class>
#include <player_job>
#include <player_location>

#include <attachment>
#include <job>

#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_bit>

new 
    BitArray:PlayerSpawnState<MAX_PLAYERS>;

hook OnPlayerSpawn(playerid) {
    Bit_Set(PlayerSpawnState, playerid, true);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason, Float: damage, bodypart) {
    Bit_Set(PlayerSpawnState, playerid, false);
    return 1;
}

stock Player_IsSpawned(playerid) {
    return Bit_Get(PlayerSpawnState, playerid);
}

static ptask _PlayerPerSecondTimer[1000](playerid) {
    if(Player_IsSpawned(playerid)) {
        CallLocalFunction("OnPlayerSecondUpdate", "i", playerid);
    }
}