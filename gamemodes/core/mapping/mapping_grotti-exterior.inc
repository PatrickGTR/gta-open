#include <YSI_Coding\y_hooks>

// credits to Gooner
// https://forum.sa-mp.com/showthread.php?t=594061
hook OnGameModeInit() {
    new tmpobjid;
    tmpobjid = CreateDynamicObject(6337,536.131,-1291.679,23.468,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "ws_runwaytarmac", 0);
    SetDynamicObjectMaterial(tmpobjid, 1, 1675, "wshxrefhse", "duskyblue_128", 0);
    SetDynamicObjectMaterial(tmpobjid, 2, 7555, "bballcpark1", "ws_carparknew2", 0);
    SetDynamicObjectMaterial(tmpobjid, 3, 10765, "airportgnd_sfse", "white", 0);
    SetDynamicObjectMaterial(tmpobjid, 4, 10765, "airportgnd_sfse", "white", 0);
    SetDynamicObjectMaterial(tmpobjid, 6, 7555, "bballcpark1", "ws_carparknew2", 0);
    SetDynamicObjectMaterial(tmpobjid, 7, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(6357,505.054,-1269.937,28.687,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 5, 6922, "vgnretail6", "marinawindow2_256", 0);
    tmpobjid = CreateDynamicObject(1557,540.584,-1294.385,16.233,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 0, 4600, "theatrelan2", "wolf1 copy", 0);
    tmpobjid = CreateDynamicObject(1557,543.607,-1294.369,16.233,0.000,0.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 0, 4600, "theatrelan2", "wolf1 copy", 0);
    tmpobjid = CreateDynamicObject(3498,521.804,-1294.024,25.799,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,517.481,-1300.263,25.799,0.000,90.000,270.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,517.481,-1298.360,24.993,0.000,90.000,270.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,517.481,-1309.284,25.799,0.000,90.000,270.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,517.481,-1307.378,24.993,0.000,90.000,270.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,530.813,-1294.024,25.799,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(11313,552.736,-1294.367,18.089,0.000,0.000,-90.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,521.804,-1294.024,24.993,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,530.813,-1294.024,24.993,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,562.747,-1294.024,25.799,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,553.743,-1294.024,25.799,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,553.743,-1294.024,24.999,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,562.747,-1294.024,24.999,0.000,90.000,180.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    SetDynamicObjectMaterial(tmpobjid, 2, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,567.090,-1298.352,25.799,0.000,90.000,90.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,567.090,-1307.372,25.799,0.000,90.000,90.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,567.090,-1300.292,24.999,0.000,90.000,90.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(3498,567.090,-1309.292,24.999,0.000,90.000,90.000,-1,-1,-1,300.000,300.000);
    SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0);
    tmpobjid = CreateDynamicObject(11313,561.131,-1294.352,18.089,0.000,0.000,-90.000,-1,-1,-1,300.000,300.000);
    return 1;
}

hook OnPlayerConnect(playerid) {
    RemoveBuildingForPlayer(playerid, 6482, 536.132, -1291.679, 23.468, 0.250);
    RemoveBuildingForPlayer(playerid, 6357, 505.054, -1269.937, 28.687, 0.250);
    RemoveBuildingForPlayer(playerid, 6337, 536.132, -1291.679, 23.468, 0.250);
    return 1;
}