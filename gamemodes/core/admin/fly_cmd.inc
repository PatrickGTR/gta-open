#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

#define green 0x0AFF0AAA
#define red 0xFF0000FF

static bool:fly[MAX_PLAYERS];
static Float:fx, Float:fy, Float:fz, Float:fangle;

forward Float:GetXYInFrontOfPlayer(playerid, &Float:q, &Float:w, Float:distance);
forward Float:GetXYBehindPlayer(playerid, &Float:q, &Float:w, Float:distance);

hook OnPlayerConnect(playerid)
{
    fly[playerid] = false;
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    fly[playerid] = false;
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason)
{
    fly[playerid] = false;
    return 1;
}

ACMD:[5]fly(playerid, params[])
{
    if(fly[playerid] == false)
    {
        fly[playerid] = true;
        SendServerMsg(playerid, "Fly Mode On");
        SendServerMsg(playerid, "Control: W = Move forward");
        SendServerMsg(playerid, "Control: S = Move Backward");
        SendServerMsg(playerid, "Control: D = Face Right");
        SendServerMsg(playerid, "Control: A = Face Left");
        SendServerMsg(playerid, "Control: W = Move forward");
        SendServerMsg(playerid, "Control: Space = Move Low");
        SendServerMsg(playerid, "Control: Shift = Move Up");
        TogglePlayerControllable(playerid, false);
        //SendAdminCmdUsage(playerid, "/fly turn on", params);
    }
    else if(fly[playerid] == true)
    {
        fly[playerid] = false;
        SendServerMsg(playerid, "Fly Mode off");
        //SendAdminCmdUsage(playerid, "/fly turn off", params);
        TogglePlayerControllable(playerid, true);
    }
    return 1;
}

Float:GetXYInFrontOfPlayer(playerid, &Float:q, &Float:w, Float:distance)
{
    new Float:a;
    GetPlayerPos(playerid, q, w, a);
    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    else GetPlayerFacingAngle(playerid, a);
    q += (distance * floatsin(-a, degrees));
    w += (distance * floatcos(-a, degrees));
    return a;
}

Float:GetXYBehindPlayer(playerid, &Float:q, &Float:w, Float:distance)
{
    new Float:a;
    GetPlayerPos(playerid, q, w, a);
    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    else GetPlayerFacingAngle(playerid, a);
    q += (distance * -floatsin(-a, degrees));
    w += (distance * -floatcos(-a, degrees));
    return a;
}

hook OnPlayerUpdate(playerid)
{
    new keys, updown, leftright;
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }
    if(fly[playerid] == true)
    {
        GetPlayerKeys(playerid,keys,updown,leftright);
        if(updown == KEY_UP) {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                GetPlayerPos(playerid, fx, fy, fz);
                GetXYInFrontOfPlayer(playerid, fx, fy, 15.0);
                SetPlayerPos(playerid, fx, fy, fz);
                SetCameraBehindPlayer(playerid);
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
                new playercar = GetPlayerVehicleID(playerid);
                GetVehiclePos(playercar, fx, fy, fz);
                GetXYInFrontOfPlayer(playerid, fx, fy, 15.0);
                SetVehiclePos(playercar, fx, fy, fz);
                SetCameraBehindPlayer(playerid);
            }
        }
        else if(updown == KEY_DOWN) {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                GetPlayerPos(playerid, fx, fy, fz);
                GetXYBehindPlayer(playerid, fx, fy, 15.0);
                SetPlayerPos(playerid, fx, fy, fz);
                SetCameraBehindPlayer(playerid);
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
                new playercar = GetPlayerVehicleID(playerid);
                GetVehiclePos(playercar, fx, fy, fz);
                GetXYBehindPlayer(playerid, fx, fy, 15.0);
                SetVehiclePos(playercar, fx, fy, fz);
                SetCameraBehindPlayer(playerid);
            }
        }
        if(leftright == KEY_LEFT) {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                GetPlayerFacingAngle(playerid, fangle);
                SetPlayerFacingAngle(playerid, fangle+10);
                SetCameraBehindPlayer(playerid);
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
                new playercar = GetPlayerVehicleID(playerid);
                GetVehicleZAngle(playercar, fangle);
                SetVehicleZAngle(playercar, fangle+10);
                SetCameraBehindPlayer(playerid);
            }
        }
        else if(leftright == KEY_RIGHT) {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                GetPlayerFacingAngle(playerid, fangle);
                SetPlayerFacingAngle(playerid, fangle-10);
                SetCameraBehindPlayer(playerid);
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
                new playercar = GetPlayerVehicleID(playerid);
                GetVehicleZAngle(playercar, fangle);
                SetVehicleZAngle(playercar, fangle-10);
                SetCameraBehindPlayer(playerid);
            }
        }
        if(keys == KEY_JUMP) {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                GetPlayerPos(playerid, fx, fy, fz);
                SetPlayerPos(playerid, fx, fy, fz+10);
                SetCameraBehindPlayer(playerid);
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
                new playercar = GetPlayerVehicleID(playerid);
                GetVehiclePos(playercar, fx, fy, fz);
                SetVehiclePos(playercar, fx, fy, fz+10);
                SetCameraBehindPlayer(playerid);
            }
        }
        else if(keys == KEY_SPRINT) {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
                GetPlayerPos(playerid, fx, fy, fz);
                SetPlayerPos(playerid, fx, fy, fz-10);
                SetCameraBehindPlayer(playerid);
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
                new playercar = GetPlayerVehicleID(playerid);
                GetVehiclePos(playercar, fx, fy, fz);
                SetVehiclePos(playercar, fx, fy, fz-10);
                SetCameraBehindPlayer(playerid);
            }
        }
    }
    return 1;
}