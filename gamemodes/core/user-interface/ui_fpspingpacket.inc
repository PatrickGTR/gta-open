#include <YSI_Coding\y_hooks>

static
    PlayerText:FPSPingPacket[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    FPSPingPacket[playerid] = CreatePlayerTextDraw(playerid,502.0, 1.4, "_");
	PlayerTextDrawBackgroundColor(playerid, FPSPingPacket[playerid], COLOR_BLACK);
	PlayerTextDrawFont(playerid, FPSPingPacket[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, FPSPingPacket[playerid], 0.19, 0.19 * 4);
	PlayerTextDrawColor(playerid, FPSPingPacket[playerid], 16711935);
	PlayerTextDrawSetOutline(playerid, FPSPingPacket[playerid], 1);
	PlayerTextDrawSetProportional(playerid, FPSPingPacket[playerid], true);
	PlayerTextDrawAlignment(playerid, FPSPingPacket[playerid], TEXT_DRAW_ALIGN_LEFT);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    PlayerTextDrawShow(playerid, FPSPingPacket[playerid]);
    return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason) {
    PlayerTextDrawHide(playerid, FPSPingPacket[playerid]);
    return 1;
}

hook OnPlayerSecondUpdate(playerid) {
    new
        string[64];
    format(string, sizeof(string), "~w~FPS ~r~%d ~w~Ping ~r~%d ~w~PacketLoss ~r~%.2f%%", GetPlayerFPS(playerid), GetPlayerPing(playerid), NetStats_PacketLossPercent(playerid));
    PlayerTextDrawSetString(playerid, FPSPingPacket[playerid], string);
    return 1;
}