#include <YSI_Coding\y_hooks>

ACMD:[5]createentrance(playerid, params[]) {

    new
        Float:to_x,
        Float:to_y,
        Float:to_z,
        Float:to_ang,
        to_world,
        to_interior,
        bool:freeze;

    if(sscanf(params, "p<,>ffffiil", to_x, to_y, to_z, to_ang, to_world, to_interior, freeze)) {
        return SendSyntaxMsg(playerid, "/createentrance x, y, z, world angle interior freeze(0/1)");
    }

    new
        Float: x,
        Float: y,
        Float: z,
        Float: ang,
        interior = GetPlayerInterior(playerid),
        world = GetPlayerVirtualWorld(playerid);

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, ang);

    // Entrance
    Entrance_Create(
        x,
        y,
        z,
        ang,
        world,
        interior,
        to_x,
        to_y,
        to_z,
        to_ang,
        to_world,
        to_interior
    );

    // Exit
    Entrance_Create(
        to_x,
        to_y,
        to_z,
        to_ang,
        to_world,
        to_interior,
        x,
        y,
        z,
        ang,
        world,
        interior
    );
    return 1;
}