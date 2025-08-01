#include <server_entrances>
#include <server_wanted-level>
#include <server_time>
#include <server_shop-items>
#include <server_msgs>
#include <server_motd>
#include <server_tax>

#include <server_atm-impl>
#include <server_atm-menu>

#include <dealership>

#include <YSI_Coding\y_hooks>
enum E_ENTRANCE_DATA {
    bool:E_FREEZE_PLAYER,
    E_INTERIOR_ID,
    E_MAP_ICON,
    E_STORE_NAME[MAX_STORE_NAME],
    Float:E_ENTRANCE_POS[3],
    Float:E_EXIT_POS[3],
}

static
    const storeData[][E_ENTRANCE_DATA] =
{
    {false, 5, 54, 		"GYM", 				    	{2229.9028, -1721.258, 13.5612},        {772.3065, -5.51570, 1000.7285}},
    {false, 11, 49, 	"TEN GREEN BOTTLES",	    {2309.987548, -1643.436279, 14.827047}, {501.9013, -67.5635, 998.7578}},
    {false, 9, 14, 		"CLUCKING BELL", 	    	{2397.816650, -1899.185058, 13.546875}, {364.9896, -11.8441, 1001.8516}},
    {false, 9, 14, 		"CLUCKING BELL", 	    	{928.915588, -1353.043823, 13.343750},  {364.9896, -11.8441, 1001.8516}},
    {false, 9, 14, 		"CLUCKING BELL", 	    	{2419.702636, -1509.045654, 24.000000}, {364.9896, -11.8441, 1001.8516}},
    {false, 15, 45, 	"BINCO", 			    	{2244.381347, -1665.566650, 15.476562}, {207.6674, -111.2659, 1005.1328}},
    {false, 4, 6, 		"AMMU-NATION", 		    	{2400.493408, -1981.995605, 13.546875}, {285.8562, -86.7820, 1001.5229}},
    {false, 6, 6, 		"AMMU-NATION", 		    	{1369.000122, -1279.712646, 13.546875}, {316.3490, -170.2974, 999.5938}},
    {false, 3, 21, 		"SEX SHOP", 			    {1940.006225, -2115.978027, 13.695312}, {-100.3562, -25.0387, 1000.7188}},
    {false, 3, 21, 		"SEX SHOP", 			    {1087.683471, -922.481994, 43.390625},  {-100.3562, -25.0387, 1000.7188}},
    {false, 6, 55, 		"GAS STATION", 		    	{1928.580932, -1776.264892, 13.546875}, {-27.2923, -58.0535, 1003.5469}},
    {false, 6, 55, 		"GAS STATION", 		    	{-78.360862, -1169.870605, 2.135507},   {-27.2923, -58.0535, 1003.5469}},
    {false, 10, 10, 	"BURGER SHOT", 		    	{810.484741, -1616.128906, 13.546875},  {362.8823, -75.1634, 1001.5078}},
    {false, 10, 10, 	"BURGER SHOT", 		    	{1199.256347, -918.142150, 43.123218},  {362.8823, -75.1634, 1001.5078}},
    {false, 12, 7, 		"BARBER", 			    	{824.059570, -1588.316894, 13.543567},  {411.8917,-54.4434,1001.8984}},
    {false, 12, 7, 		"BARBER", 			    	{2070.632568, -1793.837036, 13.546875}, {411.8917,-54.4434,1001.8984}},
    {false, 6, 30, 		"POLICE DEPT.", 		    {1555.501220, -1675.639038, 16.195312}, {246.8373,62.3343,1003.6406}},
    {false, 5, 29, 		"PIZZA", 			    	{2105.488281, -1806.570434, 13.554687}, {372.2738, -133.5248, 1001.4922}},
    {false, 2, 36, 		"STRIP CLUB", 		    	{2421.597900, -1219.242675, 25.561447}, {1204.7625,-13.8523,1000.9219}},
    {false, 17, 48, 	"DISCO", 			    	{1837.038696, -1682.395996, 13.322851}, {493.4810, -24.9531, 1000.6719}},
    {false, 17, 61, 	"24/7", 				    {1833.777343, -1842.623657, 13.578125}, {-25.9472, -188.2597, 1003.5469}},
    {false, 17, 61, 	"24/7", 				    {1000.593017, -919.916809, 42.328125},  {-25.9472, -188.2597, 1003.5469}},
    {false, 16, 39, 	"TATTOO", 			    	{2068.582763, -1779.853881, 13.559624}, {-204.417, -27.3470, 1002.2734}},
    {false, 1, 45, 		"SUBURBAN", 			    {2112.8643, -1211.4548, 23.9629},       {203.8414, -50.6566, 1001.8047}},
    {false, 5, 45, 		"VICTIM", 			    	{461.707031, -1500.845092, 31.044902},  {227.3678, -8.3722, 1002.2109}},
    {false, 17, 17, 	"JIM'S STICKY DONUTS",   	{1038.096191, -1340.726074, 13.745031}, {377.1306, -193.3048, 1000.6328}},
    {false, 3, 12, 		"CITY HALL", 				{1481.037719, -1772.312622, 18.795755}, {390.7462, 173.7627, 1008.3828}},
    {false, 15, 59, 	"JEFFERSON MOTEL", 	    	{2233.292968, -1159.849243, 25.890625}, {2214.3845, -1150.4780, 1025.7969}},
    {false, 3, 45,	 	"PROLAPS", 			    	{499.5353000, -1360.6348, 16.3690},     {207.0255, -140.3765, 1003.5078}},
    {false, 18, 45,		"ZIP", 				    	{1457.0670, -1137.1027, 23.9441},       {161.2982, -97.1033, 1001.8047}},
    {false, 0, 52,     	"BANK",                   	{595.6651, -1250.7883, 18.2999},        {2306.1572, -16.2888, 26.7496}},
    {false, 12, 25,    	"CASINO",                 	{1022.6512, -1121.8951, 23.8719},       {1133.2094, -15.3630, 1000.6797}},
    {false, 5, 26,     	"XomoX's Mansion",        	{1298.3035, -798.7736, 84.1406},        {1299.0386,-796.7242,1084.0078}},
    {true, 1, 55,		"GROTTI",					{541.9629, -1293.5179, 17.2414},        {849.4232, -973.6054, 1090.1021}},
    {true, 1, 24, 		"DRUG HOUSE", 				{2166.4160,-1671.7675,15.0742},         {742.9769, 207.1607, 11558.7939}}
};

hook OnGameModeInit() {

    // Init Entrances
    new
        entID,
        Float:enX,
        Float:enY,
        Float:enZ,
        Float:exX,
        Float:exY,
        Float:exZ,
        intID,
        vwID;

    for(new i = 0; i < sizeof(storeData); i++) {

        enX = storeData[i][E_ENTRANCE_POS][0];
        enY = storeData[i][E_ENTRANCE_POS][1];
        enZ = storeData[i][E_ENTRANCE_POS][2];
        exX = storeData[i][E_EXIT_POS][0];
        exY = storeData[i][E_EXIT_POS][1];
        exZ = storeData[i][E_EXIT_POS][2];
        intID = storeData[i][E_INTERIOR_ID];
        vwID = i; // unique vw id.


        // create entrance
        entID = Entrance_Create(enX, enY, enZ, 0.0, 0, 0, exX, exY, exZ, 0.0, vwID, intID);

        Entrance_SetIcon(entID, storeData[i][E_MAP_ICON]);
        Entrance_SetName(entID, storeData[i][E_STORE_NAME]);
        Entrance_EnableFreeze(entID, storeData[i][E_FREEZE_PLAYER]);

        // create exit
        entID = Entrance_Create(exX, exY, exZ, 0.0, vwID, intID, enX, enY, enZ, 0.0, 0, 0);
        Entrance_EnableFreeze(entID, storeData[i][E_FREEZE_PLAYER]);

        if(!strcmp("GROTTI", storeData[i][E_STORE_NAME], true)) {
            new
                vehicleid;

            vehicleid = CreateVehicle(411,846.7003,-966.7253,1089.8379,154.6938, 1, 1, (60 * 2), false); // Infernus
            SetVehicleVirtualWorld(vehicleid, vwID);
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);

            vehicleid = CreateVehicle(429,846.8061,-981.0212,1089.7911,31.8394, 1, 1, (60 * 2), false); // Banshee
            SetVehicleVirtualWorld(vehicleid, vwID);
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);

            vehicleid = CreateVehicle(434,836.0557,-981.4208,1090.0729,358.1186, 1, 1, (60 * 2), false); // HotKnife
            SetVehicleVirtualWorld(vehicleid, vwID);
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);

            vehicleid = CreateVehicle(451,836.3260,-966.7363,1089.8171,180.5268, 1, 1, (60 * 2), false); // Turismo
            SetVehicleVirtualWorld(vehicleid, vwID);
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);

            vehicleid = CreateVehicle(522,813.9284,-966.6889,1089.6785,239.2200, 1, 1, (60 * 2), false); // NRG
            SetVehicleVirtualWorld(vehicleid, vwID);
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);

            vehicleid = CreateVehicle(521,813.7883,-981.1411,1089.6801,297.5581, 1, 1, (60 * 2), false); // FCR
            SetVehicleVirtualWorld(vehicleid, vwID);
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);

            vehicleid = CreateVehicle(535,826.3376,-980.8220,1089.8749,4.6079, 1, 1, (60 * 2), false); // Slamvan
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleVirtualWorld(vehicleid, vwID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);

            vehicleid = CreateVehicle(579,826.4156,-966.4870,1090.0450,175.3807, 1, 1, (60 * 2), false); // Huntley
            SetVehicleVirtualWorld(vehicleid, vwID);
            LinkVehicleToInterior(vehicleid, intID);
            SetVehicleParamsEx(vehicleid, 0, 1, 0, 1, 0, 0, 0);


        }
    }
    return 1;
}

static task _ServerSecondTimer[1000]() {
    CallRemoteFunction("OnServerSecondUpdate", "");
}
































