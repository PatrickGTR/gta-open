#include <YSI_Coding\y_hooks>

static enum E_COMPONENT_DATA {
    E_COMPONENT_ID,
    E_COMPONENT_PRICE
}

static ComponentData[][E_COMPONENT_DATA] = {
    1018, 350,
    1019, 300,
    1020, 250,
    1021, 200,
    1022, 150,
    1028, 770,
    1029, 680,
    1034, 790,
    1037, 690,
    1043, 500,
    1044, 500,
    1045, 510,
    1046, 710,
    1059, 720,
    1064, 830,
    1065, 850,
    1066, 750,
    1089, 650,
    1092, 750,
    1104, 1610,
    1105, 1540,
    1113, 3340,
    1114, 3250,
    1126, 3340,
    1127, 3250,
    1129, 1650,
    1132, 1590,
    1135, 1500,
    1136, 1000,
    1004, 100,
    1005, 150,
    1011, 220,
    1012, 250,
    1117, 2130,
    1152, 910,
    1153, 1200,
    1155, 1030,
    1157, 930,
    1160, 1050,
    1165, 850,
    1166, 950,
    1169, 970,
    1170, 880,
    1171, 990,
    1172, 900,
    1173, 950,
    1174, 1000,
    1175, 900,
    1179, 2150,
    1181, 2050,
    1182, 2130,
    1185, 2040,
    1188, 2080,
    1189, 2200,
    1190, 1200,
    1191, 1040,
    1140, 870,
    1141, 980,
    1148, 890,
    1149, 1000,
    1150, 1090,
    1151, 840,
    1154, 1030,
    1156, 920,
    1159, 1050,
    1161, 950,
    1167, 850,
    1168, 950,
    1176, 1000,
    1177, 900,
    1178, 2050,
    1180, 2130,
    1183, 2040,
    1184, 2150,
    1186, 2095,
    1187, 2175,
    1192, 940,
    1193, 1100,
    1006, 80,
    1128, 3340,
    1130, 3380,
    1131, 3290,
    1103, 3250,
    1032, 170,
    1033, 120,
    1035, 150,
    1038, 190,
    1053, 130,
    1054, 210,
    1055, 230,
    1061, 180,
    1067, 250,
    1068, 200,
    1088, 150,
    1091, 100,
    1000, 400,
    1001, 550,
    1002, 200,
    1003, 250,
    1014, 400,
    1015, 500,
    1016, 200,
    1023, 350,
    1049, 810,
    1050, 620,
    1058, 620,
    1060, 530,
    1138, 580,
    1139, 470,
    1146, 490,
    1147, 600,
    1158, 550,
    1162, 650,
    1163, 550,
    1164, 450,
    1007, 500,
    1017, 500,
    1026, 480,
    1027, 480,
    1030, 37,
    1031, 370,
    1036, 500,
    1039, 390,
    1040, 500,
    1041, 390,
    1042, 1000,
    1047, 670,
    1048, 530,
    1051, 670,
    1052, 530,
    1056, 520,
    1057, 430,
    1062, 250,
    1063, 430,
    1069, 550,
    1070, 450,
    1071, 550,
    1072, 450,
    1090, 450,
    1093, 350,
    1094, 450,
    1095, 350,
    1099, 1000,
    1101, 780,
    1102, 830,
    1106, 780,
    1107, 780,
    1108, 780,
    1118, 780,
    1119, 940,
    1120, 780,
    1121, 940,
    1122, 780,
    1124, 780,
    1133, 830,
    1134, 800,
    1137, 800,
    1013, 100,
    1024, 50,
    1142, 150,
    1143, 150,
    1144, 100,
    1145, 100,
    1025, 1000,
    1073, 1000,
    1074, 1030,
    1075, 980,
    1076, 1560,
    1077, 1620,
    1078, 1200,
    1079, 1030,
    1080, 1000,
    1081, 1230,
    1082, 820,
    1083, 1560,
    1084, 1350,
    1085, 770,
    1096, 1000,
    1097, 620,
    1098, 1140,
    1008, 200,
    1009, 500,
    1010, 1000,
    1086, 100,
    1087, 1500,
    1100, 940,
    1123, 860,
    1125, 1120,
    1109, 1610,
    1110, 1540,
    1115, 2130,
    1116, 2050
};

static
 	PlayerCash[MAX_PLAYERS],
    PlayerOldCash[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerCash[playerid] =
    PlayerOldCash[playerid] = 0;
    return 1;
}

hook OnPlayerSecondUpdate(playerid) {

    // if server side money does not match client side money AND client side money is more than server side money.
    if ((GetPlayerMoney(playerid) != PlayerCash[playerid]) && (GetPlayerMoney(playerid) > PlayerCash[playerid])) {
        PlayerOldCash[playerid] = PlayerCash[playerid];
        ResetPlayerMoney(playerid);

        // we're nice enough to return player's old money instead of resetting it back to 0.
        GivePlayerMoney(playerid, PlayerOldCash[playerid]);
    }
    return 1;
}

hook native GivePlayerMoney(playerid, money)
{
    PlayerCash[playerid] += money;
    if(GetPlayerMoney(playerid) != PlayerCash[playerid]) {
        CallLocalFunction("OnPlayerMoneyChange", "iii", playerid, GetPlayerMoney(playerid), PlayerCash[playerid]);
    }
    return continue(playerid, money);
}

hook native ResetPlayerMoney(playerid)
{
    PlayerCash[playerid] = 0;
    return continue(playerid);
}

hook OnVehicleMod(playerid, vehicleid, componentid)
{
    for(new i = 0; i < sizeof(ComponentData); i ++) {
        if(componentid == ComponentData[i][E_COMPONENT_ID]) {
            GivePlayerMoney(playerid, -ComponentData[i][E_COMPONENT_PRICE]);
            break;
        }
    }
    return 1;
}

hook OnVehicleRespray(playerid, vehicleid, color1, color2)
{
    GivePlayerMoney(playerid, -100); // costs 100 to respray
    return 1;
}

forward OnPlayerMoneyChange(playerid, previous, current);