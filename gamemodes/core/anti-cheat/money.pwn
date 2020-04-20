/*
 * Irresistible Gaming (c) 2018
 * Developed by Lorenc
 * Module: anticheat\money.pwn
 * Purpose: server-sided money
 */

/* ** Error checking ** */
#if !defined __ac__money
    #define __ac__money
#else
    #endinput
#endif

/* ** Includes ** */
#include                            < YSI\y_hooks >

/* ** Variables ** */
static stock
 	p_Cash              			[ MAX_PLAYERS ];

/* ** Forwards ** */
forward OnPlayerMoneyChanged        ( playerid, amount );

/* ** Hooks ** */
hook OnPlayerUpdate( playerid )
{
    // reset the player's money if it is inaccurate
    if ( p_Cash[ playerid ] != GetPlayerMoney( playerid ) )
    {
        ResetPlayerMoney( playerid );
        GivePlayerMoney( playerid, p_Cash[ playerid ] );
    }
    return 1;
}

hook OnVehicleMod( playerid, vehicleid, componentid )
{
    switch( componentid )
    {
        case 1018: GivePlayerCash( playerid, -350 );
        case 1019: GivePlayerCash( playerid, -300 );
        case 1020: GivePlayerCash( playerid, -250 );
        case 1021: GivePlayerCash( playerid, -200 );
        case 1022: GivePlayerCash( playerid, -150 );
        case 1028: GivePlayerCash( playerid, -770 );
        case 1029: GivePlayerCash( playerid, -680 );
        case 1034: GivePlayerCash( playerid, -790 );
        case 1037: GivePlayerCash( playerid, -690 );
        case 1043: GivePlayerCash( playerid, -500 );
        case 1044: GivePlayerCash( playerid, -500 );
        case 1045: GivePlayerCash( playerid, -510 );
        case 1046: GivePlayerCash( playerid, -710 );
        case 1059: GivePlayerCash( playerid, -720 );
        case 1064: GivePlayerCash( playerid, -830 );
        case 1065: GivePlayerCash( playerid, -850 );
        case 1066: GivePlayerCash( playerid, -750 );
        case 1089: GivePlayerCash( playerid, -650 );
        case 1092: GivePlayerCash( playerid, -750 );
        case 1104: GivePlayerCash( playerid, -1610 );
        case 1105: GivePlayerCash( playerid, -1540 );
        case 1113: GivePlayerCash( playerid, -3340 );
        case 1114: GivePlayerCash( playerid, -3250 );
        case 1126: GivePlayerCash( playerid, -3340 );
        case 1127: GivePlayerCash( playerid, -3250 );
        case 1129: GivePlayerCash( playerid, -1650 );
        case 1132: GivePlayerCash( playerid, -1590 );
        case 1135: GivePlayerCash( playerid, -1500 );
        case 1136: GivePlayerCash( playerid, -1000 );
        case 1004: GivePlayerCash( playerid, -100 );
        case 1005: GivePlayerCash( playerid, -150 );
        case 1011: GivePlayerCash( playerid, -220 );
        case 1012: GivePlayerCash( playerid, -250 );
        case 1117: GivePlayerCash( playerid, -2130 );
        case 1152: GivePlayerCash( playerid, -910 );
        case 1153: GivePlayerCash( playerid, -1200 );
        case 1155: GivePlayerCash( playerid, -1030 );
        case 1157: GivePlayerCash( playerid, -930 );
        case 1160: GivePlayerCash( playerid, -1050 );
        case 1165: GivePlayerCash( playerid, -850 );
        case 1166: GivePlayerCash( playerid, -950 );
        case 1169: GivePlayerCash( playerid, -970 );
        case 1170: GivePlayerCash( playerid, -880 );
        case 1171: GivePlayerCash( playerid, -990 );
        case 1172: GivePlayerCash( playerid, -900 );
        case 1173: GivePlayerCash( playerid, -950 );
        case 1174: GivePlayerCash( playerid, -1000 );
        case 1175: GivePlayerCash( playerid, -900 );
        case 1179: GivePlayerCash( playerid, -2150 );
        case 1181: GivePlayerCash( playerid, -2050 );
        case 1182: GivePlayerCash( playerid, -2130 );
        case 1185: GivePlayerCash( playerid, -2040 );
        case 1188: GivePlayerCash( playerid, -2080 );
        case 1189: GivePlayerCash( playerid, -2200 );
        case 1190: GivePlayerCash( playerid, -1200 );
        case 1191: GivePlayerCash( playerid, -1040 );
        case 1140: GivePlayerCash( playerid, -870 );
        case 1141: GivePlayerCash( playerid, -980 );
        case 1148: GivePlayerCash( playerid, -890 );
        case 1149: GivePlayerCash( playerid, -1000 );
        case 1150: GivePlayerCash( playerid, -1090 );
        case 1151: GivePlayerCash( playerid, -840 );
        case 1154: GivePlayerCash( playerid, -1030 );
        case 1156: GivePlayerCash( playerid, -920 );
        case 1159: GivePlayerCash( playerid, -1050 );
        case 1161: GivePlayerCash( playerid, -950 );
        case 1167: GivePlayerCash( playerid, -850 );
        case 1168: GivePlayerCash( playerid, -950 );
        case 1176: GivePlayerCash( playerid, -1000 );
        case 1177: GivePlayerCash( playerid, -900 );
        case 1178: GivePlayerCash( playerid, -2050 );
        case 1180: GivePlayerCash( playerid, -2130 );
        case 1183: GivePlayerCash( playerid, -2040 );
        case 1184: GivePlayerCash( playerid, -2150 );
        case 1186: GivePlayerCash( playerid, -2095 );
        case 1187: GivePlayerCash( playerid, -2175 );
        case 1192: GivePlayerCash( playerid, -940 );
        case 1193: GivePlayerCash( playerid, -1100 );
        case 1006: GivePlayerCash( playerid, -80 );
        case 1128: GivePlayerCash( playerid, -3340 );
        case 1130: GivePlayerCash( playerid, -3380 );
        case 1131: GivePlayerCash( playerid, -3290 );
        case 1103: GivePlayerCash( playerid, -3250 );
        case 1032: GivePlayerCash( playerid, -170 );
        case 1033: GivePlayerCash( playerid, -120 );
        case 1035: GivePlayerCash( playerid, -150 );
        case 1038: GivePlayerCash( playerid, -190 );
        case 1053: GivePlayerCash( playerid, -130 );
        case 1054: GivePlayerCash( playerid, -210 );
        case 1055: GivePlayerCash( playerid, -230 );
        case 1061: GivePlayerCash( playerid, -180 );
        case 1067: GivePlayerCash( playerid, -250 );
        case 1068: GivePlayerCash( playerid, -200 );
        case 1088: GivePlayerCash( playerid, -150 );
        case 1091: GivePlayerCash( playerid, -100 );
        case 1000: GivePlayerCash( playerid, -400 );
        case 1001: GivePlayerCash( playerid, -550 );
        case 1002: GivePlayerCash( playerid, -200 );
        case 1003: GivePlayerCash( playerid, -250 );
        case 1014: GivePlayerCash( playerid, -400 );
        case 1015: GivePlayerCash( playerid, -500 );
        case 1016: GivePlayerCash( playerid, -200 );
        case 1023: GivePlayerCash( playerid, -350 );
        case 1049: GivePlayerCash( playerid, -810 );
        case 1050: GivePlayerCash( playerid, -620 );
        case 1058: GivePlayerCash( playerid, -620 );
        case 1060: GivePlayerCash( playerid, -530 );
        case 1138: GivePlayerCash( playerid, -580 );
        case 1139: GivePlayerCash( playerid, -470 );
        case 1146: GivePlayerCash( playerid, -490 );
        case 1147: GivePlayerCash( playerid, -600 );
        case 1158: GivePlayerCash( playerid, -550 );
        case 1162: GivePlayerCash( playerid, -650 );
        case 1163: GivePlayerCash( playerid, -550 );
        case 1164: GivePlayerCash( playerid, -450 );
        case 1007: GivePlayerCash( playerid, -500 );
        case 1017: GivePlayerCash( playerid, -500 );
        case 1026: GivePlayerCash( playerid, -480 );
        case 1027: GivePlayerCash( playerid, -480 );
        case 1030: GivePlayerCash( playerid, -37 );
        case 1031: GivePlayerCash( playerid, -370 );
        case 1036: GivePlayerCash( playerid, -500 );
        case 1039: GivePlayerCash( playerid, -390 );
        case 1040: GivePlayerCash( playerid, -500 );
        case 1041: GivePlayerCash( playerid, -390 );
        case 1042: GivePlayerCash( playerid, -1000 );
        case 1047: GivePlayerCash( playerid, -670 );
        case 1048: GivePlayerCash( playerid, -530 );
        case 1051: GivePlayerCash( playerid, -670 );
        case 1052: GivePlayerCash( playerid, -530 );
        case 1056: GivePlayerCash( playerid, -520 );
        case 1057: GivePlayerCash( playerid, -430 );
        case 1062: GivePlayerCash( playerid, -250 );
        case 1063: GivePlayerCash( playerid, -430 );
        case 1069: GivePlayerCash( playerid, -550 );
        case 1070: GivePlayerCash( playerid, -450 );
        case 1071: GivePlayerCash( playerid, -550 );
        case 1072: GivePlayerCash( playerid, -450 );
        case 1090: GivePlayerCash( playerid, -450 );
        case 1093: GivePlayerCash( playerid, -350 );
        case 1094: GivePlayerCash( playerid, -450 );
        case 1095: GivePlayerCash( playerid, -350 );
        case 1099: GivePlayerCash( playerid, -1000 );
        case 1101: GivePlayerCash( playerid, -780 );
        case 1102: GivePlayerCash( playerid, -830 );
        case 1106: GivePlayerCash( playerid, -780 );
        case 1107: GivePlayerCash( playerid, -780 );
        case 1108: GivePlayerCash( playerid, -780 );
        case 1118: GivePlayerCash( playerid, -780 );
        case 1119: GivePlayerCash( playerid, -940 );
        case 1120: GivePlayerCash( playerid, -780 );
        case 1121: GivePlayerCash( playerid, -940 );
        case 1122: GivePlayerCash( playerid, -780 );
        case 1124: GivePlayerCash( playerid, -780 );
        case 1133: GivePlayerCash( playerid, -830 );
        case 1134: GivePlayerCash( playerid, -800 );
        case 1137: GivePlayerCash( playerid, -800 );
        case 1013: GivePlayerCash( playerid, -100 );
        case 1024: GivePlayerCash( playerid, -50 );
        case 1142: GivePlayerCash( playerid, -150 );
        case 1143: GivePlayerCash( playerid, -150 );
        case 1144: GivePlayerCash( playerid, -100 );
        case 1145: GivePlayerCash( playerid, -100 );
        case 1025: GivePlayerCash( playerid, -1000 );
        case 1073: GivePlayerCash( playerid, -1000 );
        case 1074: GivePlayerCash( playerid, -1030 );
        case 1075: GivePlayerCash( playerid, -980 );
        case 1076: GivePlayerCash( playerid, -1560 );
        case 1077: GivePlayerCash( playerid, -1620 );
        case 1078: GivePlayerCash( playerid, -1200 );
        case 1079: GivePlayerCash( playerid, -1030 );
        case 1080: GivePlayerCash( playerid, -1000 );
        case 1081: GivePlayerCash( playerid, -1230 );
        case 1082: GivePlayerCash( playerid, -820 );
        case 1083: GivePlayerCash( playerid, -1560 );
        case 1084: GivePlayerCash( playerid, -1350 );
        case 1085: GivePlayerCash( playerid, -770 );
        case 1096: GivePlayerCash( playerid, -1000 );
        case 1097: GivePlayerCash( playerid, -620 );
        case 1098: GivePlayerCash( playerid, -1140 );
        case 1008: GivePlayerCash( playerid, -200 );
        case 1009: GivePlayerCash( playerid, -500 );
        case 1010: GivePlayerCash( playerid, -1000 );
        case 1086: GivePlayerCash( playerid, -100 );
        case 1087: GivePlayerCash( playerid, -1500 );
        case 1100: GivePlayerCash( playerid, -940 );
        case 1123: GivePlayerCash( playerid, -860 );
        case 1125: GivePlayerCash( playerid, -1120 );
        case 1109: GivePlayerCash( playerid, -1610 );
        case 1110: GivePlayerCash( playerid, -1540 );
        case 1115: GivePlayerCash( playerid, -2130 );
        case 1116: GivePlayerCash( playerid, -2050 );
    }
    return 1;
}

hook OnVehicleRespray( playerid, vehicleid, color1, color2 )
{
    GivePlayerCash( playerid, -100 ); // costs 100 to respray
    return 1;
}

/* ** Functions ** */
stock GivePlayerCash( playerid, money )
{
    p_Cash[ playerid ] += money;
    ResetPlayerMoney( playerid );
    GivePlayerMoney( playerid, p_Cash[ playerid ] );
    CallRemoteFunction( "OnPlayerMoneyChanged", "dd", playerid, money );
}

stock SetPlayerCash( playerid, money )
{
    p_Cash[ playerid ] = money;
    ResetPlayerMoney( playerid );
    GivePlayerMoney( playerid, p_Cash[ playerid ] );
}

stock ResetPlayerCash( playerid )
{
    p_Cash[ playerid ] = 0;
    ResetPlayerMoney( playerid );
    GivePlayerMoney( playerid, p_Cash[ playerid ] );
}

stock GetPlayerCash( playerid )
{
	return p_Cash[ playerid ];
}
