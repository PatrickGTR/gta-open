#include <YSI_Coding\y_hooks>

static
    gMOTD[128];

hook OnGameModeInit() {

    ini_open("config.ini");
    ini_getString("motd", gMOTD);
    ini_close();
    return 1;
}

hook OnPlayerPassedBanCheck(playerid) {
    // Clear chat
    for(new i = 0; i < 100; i++) {
        SendClientMessage(playerid, -1, " ");
    }

    SendMsgF(playerid, COLOR_YELLOW, "(MOTD)"C_BLUE" %s", gMOTD);

    return 1;
}

void:MOTD_UpdateConfig(const motd[]) {

    ini_open("config.ini");

    ini_setString("motd", motd);

    ini_commit();
}

void:MOTD_Set(const motd[], bool:save = false) {
    if(strlen(motd) > 128) {
        return;
    }
    if(isnull(motd)) {
        return;
    }
    strcpy(gMOTD, motd, sizeof(gMOTD));

    if(save) {
        MOTD_UpdateConfig(motd);
    }
}

stock void:MOTD_Get(motd[], len = sizeof(motd)) {
    strcpy(motd, gMOTD, len);
}