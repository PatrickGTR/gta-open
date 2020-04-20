#include <YSI_Coding\y_hooks>

static PlayerText:FPSPingPacket[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    FPSPingPacket[playerid] = CreatePlayerTextDraw(playerid,502.0, 1.4, "_");
	PlayerTextDrawBackgroundColor(playerid, FPSPingPacket[playerid], COLOR_BLACK);
	PlayerTextDrawFont(playerid, FPSPingPacket[playerid], 1);
    PlayerTextDrawLetterSize(playerid, FPSPingPacket[playerid], 0.190000, 0.93000);
	PlayerTextDrawColor(playerid, FPSPingPacket[playerid], 16711935);
	PlayerTextDrawSetOutline(playerid, FPSPingPacket[playerid], 1);
	PlayerTextDrawSetProportional(playerid, FPSPingPacket[playerid], 1);
	PlayerTextDrawAlignment(playerid, FPSPingPacket[playerid], 1); 
}

hook OnPlayerSpawn(playerid) {
    PlayerTextDrawShow(playerid, FPSPingPacket[playerid]);
}

hook OnPlayerDeath(playerid, killerid, reason) {
    PlayerTextDrawHide(playerid, FPSPingPacket[playerid]);
}

ptask OnFPSPingPacket[1000](playerid) {

    new string[64];

    format(string, sizeof(string), "~w~FPS ~r~%d ~w~Ping ~r~%d ~w~PacketLoss ~r~%.2f%%", GetPlayerFPS(playerid), GetPlayerPing(playerid), NetStats_PacketLossPercent(playerid));
    PlayerTextDrawSetString(playerid, FPSPingPacket[playerid], string);
}