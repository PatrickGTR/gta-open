// Credit goes to rootcause for this

#include <YSI_Coding\y_hooks>

#define     TRASH_BAG_VALUE     (125)    	// value of a collected trash bag (default: 125)
#define     REFILL_TIME         (300)   	// trash container refill time - in seconds (default: 300)
#define     ATTACHMENT_INDEX    (4)     	// for setplayerattachedobject (default: 4)
#define     TRASH_LIMIT         (10)    	// trashmaster capacity (default: 10)

enum {
	TYPE_BIN,
	TYPE_DUMPSTER
}

enum E_TRASH_DATA {
	TrashType,
	Float: TrashX,
	Float: TrashY,
	Float: TrashZ,
	Text3D: TrashLabel,
	TrashLevel,
	TrashTimer
}

enum E_FACTORY_DATA {
    FactoryName[32],
	Float: FactoryX,
	Float: FactoryY,
	Float: FactoryZ,
	FactoryCurrent,
	FactoryCP,
	Text3D: FactoryLabel
}

static
	TrashData[][E_TRASH_DATA] = {
		{TYPE_DUMPSTER, -169.9766, 1027.1953, 19.4453},
		{TYPE_DUMPSTER, -160.2656, 1122.5391, 19.5391},
		{TYPE_DUMPSTER, -149.8516, 1133.7656, 19.5391},
		{TYPE_DUMPSTER, -170.1719, 1169.0547, 19.5391},
		{TYPE_DUMPSTER, -218.0312, 1164.9219, 19.5391},
		{TYPE_DUMPSTER, -149.8203, 1164.1094, 19.5391},
		{TYPE_DUMPSTER, -162.0938, 1175.1406, 19.5391},
		{TYPE_DUMPSTER, -155.6953, 1234.4219, 19.4766},
		{TYPE_DUMPSTER, -123.8125, 1079.3984, 19.5000},
		{TYPE_DUMPSTER, -90.6016, 1128.2188, 19.4609},
		{TYPE_DUMPSTER, -88.8594, 1165.3828, 19.4609},
		{TYPE_DUMPSTER, -44.3047, 1179.2734, 19.2422},
		{TYPE_DUMPSTER, -24.8203, 1165.4062, 19.2422},
		{TYPE_DUMPSTER, 776.8281, 1866.1562, 3.8906},
		{TYPE_DUMPSTER, 338.0547, 39.8438, 6.2656},
		{TYPE_DUMPSTER, 339.7188, 52.9844, 3.2656},
		{TYPE_DUMPSTER, 341.4219, 55.0078, 3.2656},
		{TYPE_DUMPSTER, 1353.1016, 201.7578, 19.2656},
		{TYPE_DUMPSTER, 1353.5781, 204.2266, 19.2656},
		{TYPE_DUMPSTER, 244.1250, -313.1250, 1.2734},
		{TYPE_DUMPSTER, 251.4453, -262.5469, 1.2734},
		{TYPE_DUMPSTER, 254.0000, -263.2578, 1.2734},
		{TYPE_DUMPSTER, 306.0625, -255.1016, 1.2578},
		{TYPE_DUMPSTER, 308.6719, -255.0938, 1.2578},
		{TYPE_BIN, 2317.1562, 29.2031, 26.2188},
		{TYPE_DUMPSTER, 2321.1172, 14.3359, 26.1953},
		{TYPE_BIN, 2317.5938, 30.4766, 26.2188},
		{TYPE_DUMPSTER, 196.7109, -121.4062, 1.2734},
		{TYPE_DUMPSTER, 255.1172, -161.2891, 1.3047},
		{TYPE_DUMPSTER, 255.3125, -132.6250, 1.2734},
		{TYPE_DUMPSTER, 259.5547, -132.7891, 1.2734},
		{TYPE_DUMPSTER, 165.9219, -107.6328, 1.2734},
		{TYPE_DUMPSTER, 182.9922, -93.6172, 1.2734},
		{TYPE_DUMPSTER, 171.4453, -93.4453, 1.2734},
		{TYPE_DUMPSTER, 657.8516, -650.0703, 16.0625},
		{TYPE_DUMPSTER, 665.2266, -624.3750, 16.0625},
		{TYPE_DUMPSTER, 668.2109, -624.4453, 16.0625},
		{TYPE_DUMPSTER, 652.7422, -496.5156, 16.0469},
		{TYPE_DUMPSTER, 652.8125, -499.3203, 16.0469},
		{TYPE_DUMPSTER, 725.8750, -465.7422, 15.9375},
		{TYPE_DUMPSTER, 656.0000, -439.2734, 16.2812},
		{TYPE_DUMPSTER, 693.2891, -456.0156, 16.0078},
		{TYPE_DUMPSTER, 830.4766, -754.6016, 84.9375},
		{TYPE_BIN, 842.5156, -756.1719, 84.3047},
		{TYPE_DUMPSTER, 1300.4531, 221.5078, 19.2656},
		{TYPE_DUMPSTER, 1320.6328, 211.4688, 19.2656},
		{TYPE_DUMPSTER, 1328.8672, 207.3438, 19.2656},
		{TYPE_DUMPSTER, 1362.0391, 232.6094, 19.2656},
		{TYPE_DUMPSTER, 1364.2891, 231.4844, 19.2656},
		{TYPE_DUMPSTER, 1307.6875, 349.7578, 19.2812},
		{TYPE_DUMPSTER, 1315.2500, 349.5625, 19.2578},
		{TYPE_DUMPSTER, 1413.4141, 451.1172, 19.7344},
		{TYPE_DUMPSTER, 1368.6250, 484.1406, 19.7344},
		{TYPE_DUMPSTER, -2146.7344, -2462.4844, 30.5547},
		{TYPE_DUMPSTER, -2105.9375, -2458.1562, 30.5547},
		{TYPE_DUMPSTER, -2108.4922, -2456.1719, 30.5547},
		{TYPE_DUMPSTER, -2103.7734, -2479.7344, 30.5547},
		{TYPE_DUMPSTER, -2218.8828, -2336.2109, 30.4844},
		{TYPE_DUMPSTER, -2213.9609, -2339.3047, 30.4844},
		{TYPE_DUMPSTER, -2136.5547, -2450.5938, 30.5547},
		{TYPE_DUMPSTER, -2176.3438, -2424.5781, 30.5547},
		{TYPE_DUMPSTER, -2174.8594, -2365.2734, 30.7969},
		{TYPE_DUMPSTER, -2136.5000, -2263.8984, 30.7266},
		{TYPE_DUMPSTER, -2138.6641, -2262.1953, 30.7266},
		{TYPE_DUMPSTER, -2087.9922, -2440.9453, 30.6953},
		{TYPE_DUMPSTER, -2107.2109, -2423.8906, 30.7969},
		{TYPE_DUMPSTER, -2085.3203, -2414.5078, 30.6406},
		{TYPE_DUMPSTER, -2087.2031, -2343.1016, 30.7969},
		{TYPE_DUMPSTER, -77.2188, -1188.3672, 0.8359},
		{TYPE_DUMPSTER, -68.3516, -1104.9922, 0.2188},
		{TYPE_DUMPSTER, -63.8125, -1106.4219, 0.2188},
		{TYPE_DUMPSTER, -541.4297, -561.2266, 24.5859},
		{TYPE_DUMPSTER, -513.7578, -561.0078, 24.5859},
		{TYPE_DUMPSTER, -502.6094, -528.6484, 24.5859},
		{TYPE_DUMPSTER, -620.4141, -490.5078, 24.5859},
		{TYPE_DUMPSTER, -619.6250, -473.4531, 24.5859},
		{TYPE_BIN, 788.3438, -863.3828, 59.7031},
		{TYPE_BIN, 787.9766, -862.3750, 59.7109},
		{TYPE_BIN, 787.9766, -862.3750, 59.7109},
		{TYPE_BIN, 787.9844, -841.5234, 59.7031},
		{TYPE_DUMPSTER, 792.6250, -838.8906, 60.6406},
		{TYPE_BIN, 911.7031, -836.2031, 91.3594},
		{TYPE_BIN, 910.8750, -836.6953, 91.1250},
		{TYPE_BIN, 960.2422, -822.8594, 95.5391},
		{TYPE_BIN, 974.9219, -815.5156, 96.7266},
		{TYPE_BIN, 948.4922, -699.7422, 121.2969},
		{TYPE_BIN, 948.0078, -698.7891, 121.3203},
		{TYPE_BIN, 914.3125, -670.3594, 116.2891},
		{TYPE_BIN, 1072.1406, -778.3828, 106.4453},
		{TYPE_BIN, 1072.1406, -778.3828, 106.4453},
		{TYPE_BIN, 1071.0547, -778.4766, 106.2891},
		{TYPE_BIN, 2380.0312, -1038.0703, 52.8281},
		{TYPE_BIN, 2380.8516, -1039.0547, 52.7891},
		{TYPE_BIN, 2426.7266, -1016.7500, 53.4453},
		{TYPE_BIN, 2436.7109, -1052.2500, 53.4297},
		{TYPE_BIN, 2459.4531, -1051.6094, 58.8438},
		{TYPE_BIN, 2457.3984, -1023.1719, 58.7891},
		{TYPE_BIN, 2484.0859, -1053.1406, 66.6406},
		{TYPE_BIN, 2489.6172, -1022.6094, 64.5156},
		{TYPE_BIN, 2505.0781, -1061.0781, 69.3125},
		{TYPE_BIN, 2527.9219, -1058.1406, 68.6875},
		{TYPE_BIN, 2510.2891, -1029.5859, 69.1797},
		{TYPE_BIN, 2528.6719, -1034.9219, 68.6719},
		{TYPE_BIN, 2538.6484, -1058.6016, 68.6719},
		{TYPE_BIN, 2545.1562, -1034.8984, 68.6641},
		{TYPE_BIN, 2567.8203, -1035.2812, 68.6719},
		{TYPE_DUMPSTER, 1420.1172, -1356.8438, 13.3828},
		{TYPE_DUMPSTER, 1425.5312, -1320.5781, 13.3672},
		{TYPE_DUMPSTER, 1415.6016, -1299.1875, 13.3672},
		{TYPE_DUMPSTER, 1425.5703, -1317.9688, 13.3672},
		{TYPE_DUMPSTER, 1439.8594, -1323.7031, 13.3828},
		{TYPE_DUMPSTER, 1593.0781, -1200.3750, 19.6875},
		{TYPE_DUMPSTER, 1616.5547, -1200.3750, 19.6875},
		{TYPE_DUMPSTER, 1660.4688, -1200.3750, 19.6875},
		{TYPE_DUMPSTER, 1435.5859, -1095.7969, 17.4141},
		{TYPE_DUMPSTER, 1438.1953, -1095.8438, 17.4141},
		{TYPE_DUMPSTER, 1424.5234, -1084.3047, 17.4141},
		{TYPE_DUMPSTER, 1424.5781, -1080.3828, 17.4141},
		{TYPE_DUMPSTER, 1520.1562, -1018.5547, 23.8438},
		{TYPE_DUMPSTER, 1520.2109, -1014.6328, 23.8438},
		{TYPE_DUMPSTER, 1611.6875, -993.9062, 23.8438},
		{TYPE_DUMPSTER, 1659.9141, -1065.1172, 23.7969},
		{TYPE_DUMPSTER, 1631.9219, -987.8281, 23.8438},
		{TYPE_DUMPSTER, 1633.9375, -990.5547, 23.8438},
		{TYPE_DUMPSTER, 1660.2500, -1000.4141, 23.7891},
		{TYPE_DUMPSTER, 1666.3984, -997.7031, 23.7891},
		{TYPE_DUMPSTER, 1786.2109, -1148.2969, 23.6797},
		{TYPE_DUMPSTER, 1800.4531, -1148.2969, 23.6797},
		{TYPE_DUMPSTER, 1830.5703, -1147.3828, 23.6797},
		{TYPE_DUMPSTER, 1830.6172, -1143.8203, 23.6797},
		{TYPE_DUMPSTER, 1789.7734, -1116.0625, 23.8906},
		{TYPE_DUMPSTER, 1789.9062, -1112.6406, 23.8906},
		{TYPE_DUMPSTER, 1830.5703, -1113.9297, 23.6797},
		{TYPE_DUMPSTER, 1830.5703, -1097.3047, 23.6797},
		{TYPE_DUMPSTER, 1830.5703, -1084.2891, 23.6797},
		{TYPE_DUMPSTER, 1336.3359, -1842.8516, 12.6641},
		{TYPE_DUMPSTER, 1336.7891, -1816.3047, 12.6641},
		{TYPE_DUMPSTER, 1466.9453, -1847.8438, 12.6641},
		{TYPE_DUMPSTER, 1419.7344, -1846.5469, 12.6641},
		{TYPE_DUMPSTER, 1419.6953, -1844.2031, 12.6641},
		{TYPE_DUMPSTER, 1486.2109, -1848.1250, 12.6641},
		{TYPE_DUMPSTER, 1468.0625, -1847.7891, 12.6641},
		{TYPE_DUMPSTER, 1516.6875, -1850.0547, 12.6641},
		{TYPE_DUMPSTER, 1337.6953, -1774.7344, 12.6641},
		{TYPE_DUMPSTER, 1461.4297, -1489.2188, 12.6797},
		{TYPE_DUMPSTER, 1538.9453, -1849.2734, 12.6641},
		{TYPE_DUMPSTER, 1534.9297, -1480.9922, 8.6094},
		{TYPE_DUMPSTER, 1537.9297, -1480.6094, 8.6094},
		{TYPE_DUMPSTER, 2382.0234, -1941.0391, 12.6641},
		{TYPE_DUMPSTER, 1920.0547, -2122.4141, 12.6875},
		{TYPE_DUMPSTER, 1920.4844, -2088.1719, 12.6875},
		{TYPE_DUMPSTER, 1092.0078, -1881.2812, 13.3047},
		{TYPE_DUMPSTER, 1175.3828, -1877.5625, 13.3047},
		{TYPE_DUMPSTER, 1091.9844, -1876.8281, 13.3047},
		{TYPE_DUMPSTER, 1101.9922, -1874.9766, 13.3047},
		{TYPE_DUMPSTER, 1117.4688, -1874.9766, 13.3047},
		{TYPE_DUMPSTER, 432.2422, -1747.8828, 8.3281},
		{TYPE_DUMPSTER, 477.7734, -1746.4531, 8.5000},
		{TYPE_DUMPSTER, 569.5078, -1765.0312, 13.5312},
		{TYPE_DUMPSTER, 732.8516, -1332.8984, 12.6875},
		{TYPE_DUMPSTER, 732.7266, -1341.7734, 12.6328},
		{TYPE_DUMPSTER, 387.1484, -1751.5078, 7.9453},
		{TYPE_DUMPSTER, 387.2266, -1747.7266, 8.3594},
		{TYPE_DUMPSTER, 1322.1875, -1235.8828, 13.4375},
		{TYPE_DUMPSTER, -826.2812, 495.1172, 1357.8594},
		{TYPE_DUMPSTER, -827.2656, 498.1953, 1357.7656},
		{TYPE_DUMPSTER, -829.0312, 498.1953, 1357.5938},
		{TYPE_BIN, -800.9453, 500.8984, 1360.0312},
		{TYPE_BIN, -800.9453, 501.7422, 1360.0312},
		{TYPE_DUMPSTER, -2531.9062, 2295.0312, 4.7578},
		{TYPE_DUMPSTER, -2526.9453, 2295.0312, 4.7578},
		{TYPE_DUMPSTER, -2527.2422, 2353.1250, 4.7578},
		{TYPE_DUMPSTER, -2520.7188, 2353.1250, 4.7578},
		{TYPE_DUMPSTER, -2524.0625, 2353.1250, 4.7578},
		{TYPE_DUMPSTER, -2480.8828, 2295.0312, 4.7578},
		{TYPE_DUMPSTER, -2503.0703, 2364.2188, 4.7578},
		{TYPE_DUMPSTER, -2503.0469, 2368.0469, 4.7578},
		{TYPE_DUMPSTER, -2253.5391, 2372.5469, 4.7578},
		{TYPE_DUMPSTER, -2455.3750, -143.8750, 26.0156},
		{TYPE_DUMPSTER, -2455.3516, -138.0156, 26.0156},
		{TYPE_DUMPSTER, -2753.9453, -178.3281, 6.8359},
		{TYPE_DUMPSTER, -2658.9766, -168.8984, 3.9844},
		{TYPE_DUMPSTER, -2657.9297, -189.0703, 3.9844},
		{TYPE_DUMPSTER, -2652.7891, -188.2891, 3.9844},
		{TYPE_DUMPSTER, -2653.3828, -167.3984, 3.9844},
		{TYPE_DUMPSTER, -2759.2578, -136.2031, 6.8359},
		{TYPE_DUMPSTER, -2753.3125, -149.8516, 6.8359},
		{TYPE_DUMPSTER, -2659.2734, -125.2031, 3.9844},
		{TYPE_DUMPSTER, -2753.2734, -121.6016, 6.8359},
		{TYPE_DUMPSTER, -2759.2031, -120.8203, 6.8359},
		{TYPE_DUMPSTER, -2653.6797, -124.7422, 3.9844},
		{TYPE_DUMPSTER, -2759.9453, -96.8203, 6.8359},
		{TYPE_DUMPSTER, -2763.7031, -13.7344, 6.8359},
		{TYPE_DUMPSTER, -2766.0312, 25.0156, 6.8359},
		{TYPE_DUMPSTER, -2760.7188, -54.3438, 6.8359},
		{TYPE_DUMPSTER, -2759.4766, 7.8906, 6.8359},
		{TYPE_DUMPSTER, -2754.4219, -85.3906, 6.8359},
		{TYPE_DUMPSTER, -2754.8516, -56.6016, 6.8359},
		{TYPE_DUMPSTER, -2755.9141, -36.3828, 6.8359},
		{TYPE_DUMPSTER, -2747.3594, -8.6641, 6.0938},
		{TYPE_DUMPSTER, -2766.4297, 52.0781, 6.9297},
		{TYPE_DUMPSTER, -2766.2109, 86.5781, 6.9297},
		{TYPE_DUMPSTER, -2760.3672, 63.8594, 6.9375},
		{TYPE_DUMPSTER, -2757.9688, 95.9844, 6.9297},
		{TYPE_DUMPSTER, -2756.2656, 90.3594, 6.9297},
		{TYPE_DUMPSTER, -2756.4844, 93.1875, 6.9297},
		{TYPE_DUMPSTER, -2763.1328, 115.3828, 6.8906},
		{TYPE_DUMPSTER, -2760.3672, 144.3516, 6.8828},
		{TYPE_DUMPSTER, -2658.3125, -89.6172, 3.9844},
		{TYPE_DUMPSTER, -2716.9844, 74.3594, 4.0781},
		{TYPE_DUMPSTER, -2717.9219, 77.9219, 4.0781},
		{TYPE_DUMPSTER, -2656.5938, 71.5625, 3.9844},
		{TYPE_DUMPSTER, -2651.2500, 92.4375, 3.9844},
		{TYPE_DUMPSTER, -2649.8125, 52.7500, 3.9844},
		{TYPE_DUMPSTER, -2651.9062, 133.3438, 3.9844},
		{TYPE_DUMPSTER, -2656.7109, 115.3828, 3.9844},
		{TYPE_DUMPSTER, -2657.7734, 135.6016, 3.9844},
		{TYPE_DUMPSTER, 2535.3906, 1942.2500, 10.6094},
		{TYPE_DUMPSTER, 2676.4531, 1665.6875, 10.6094},
		{TYPE_DUMPSTER, 2676.4531, 1705.5703, 10.6094},
		{TYPE_DUMPSTER, 2657.1250, 1942.2500, 10.6094},
		{TYPE_DUMPSTER, 2676.4531, 1825.4062, 10.6094},
		{TYPE_DUMPSTER, 2178.2188, 1418.8438, 10.6250},
		{TYPE_DUMPSTER, 2181.5625, 1418.8438, 10.6250},
		{TYPE_BIN, 2065.7344, 637.5781, 11.2031},
		{TYPE_BIN, 2011.1328, 638.1172, 11.2031},
		{TYPE_DUMPSTER, 1878.6484, 683.7734, 10.6250},
		{TYPE_DUMPSTER, 1881.3828, 683.7734, 10.6250},
		{TYPE_BIN, 1885.4844, 683.7500, 10.5625},
		{TYPE_DUMPSTER, 1969.9453, 693.7422, 10.6250},
		{TYPE_BIN, 1976.6797, 693.7109, 10.5625},
		{TYPE_BIN, 1969.2109, 712.7344, 10.5625},
		{TYPE_DUMPSTER, 1975.6953, 712.7031, 10.6250},
		{TYPE_DUMPSTER, 2006.1953, 706.4531, 11.2500},
		{TYPE_BIN, 2043.4531, 708.3672, 11.1953},
		{TYPE_DUMPSTER, 1884.8359, 722.7031, 10.6250},
		{TYPE_DUMPSTER, 1882.1016, 722.7031, 10.6250},
		{TYPE_BIN, 1877.8828, 722.7344, 10.5625},
		{TYPE_BIN, 2010.3125, 718.0391, 11.1953},
		{TYPE_DUMPSTER, 2009.2812, 786.4297, 11.2500},
		{TYPE_BIN, 2046.0547, 788.3906, 11.1953},
		{TYPE_BIN, 2065.2812, 717.4688, 11.1953},
		{TYPE_BIN, 2071.4609, 788.9609, 11.1953},
		{TYPE_BIN, 2128.2500, 640.0781, 11.2031},
		{TYPE_BIN, 2090.1562, 638.1016, 11.2031},
		{TYPE_DUMPSTER, 2224.1328, 666.4062, 11.2500},
		{TYPE_DUMPSTER, 2086.3672, 706.4531, 11.2500},
		{TYPE_BIN, 2123.2734, 708.4297, 11.1953},
		{TYPE_BIN, 2174.5703, 678.0625, 11.1953},
		{TYPE_BIN, 2180.9531, 668.4141, 11.2031},
		{TYPE_BIN, 2206.4688, 669.0078, 11.2031},
		{TYPE_DUMPSTER, 2210.4766, 679.9453, 11.2500},
		{TYPE_BIN, 2219.0312, 677.5234, 11.1953},
		{TYPE_BIN, 2254.0859, 677.9844, 11.1953},
		{TYPE_BIN, 2261.4688, 668.3828, 11.1953},
		{TYPE_BIN, 2088.5156, 718.0469, 11.1953},
		{TYPE_DUMPSTER, 2087.4219, 786.4297, 11.2500},
		{TYPE_BIN, 2126.7969, 719.9062, 11.1953},
		{TYPE_BIN, 2126.6797, 788.4062, 11.1953},
		{TYPE_BIN, 2180.2188, 748.3828, 11.1953},
		{TYPE_DUMPSTER, 2180.6016, 778.2266, 11.2500},
		{TYPE_BIN, 2186.9219, 748.3828, 11.1953},
		{TYPE_BIN, 2205.6641, 748.9141, 11.1953},
		{TYPE_DUMPSTER, 2222.5234, 746.4219, 11.2500},
		{TYPE_BIN, 2260.3438, 748.4219, 11.1953},
		{TYPE_DUMPSTER, 2364.0781, 666.5703, 11.2500},
		{TYPE_BIN, 2359.7109, 677.4844, 11.1953},
		{TYPE_BIN, 2394.3906, 678.0312, 11.1953},
		{TYPE_DUMPSTER, 2460.6172, 696.5859, 11.2500},
		{TYPE_BIN, 2463.1250, 706.3438, 11.1953},
		{TYPE_BIN, 2463.1250, 707.8203, 11.1953},
		{TYPE_DUMPSTER, 2538.3125, 716.4219, 10.6172},
		{TYPE_DUMPSTER, 2364.0781, 746.4219, 11.2500},
		{TYPE_BIN, 2462.5859, 739.7500, 11.1953},
		{TYPE_DUMPSTER, 2578.8906, 723.9531, 10.6172},
		{TYPE_DUMPSTER, 2615.2578, 716.3984, 10.6172},
		{TYPE_DUMPSTER, 2658.3438, 716.3984, 10.6172},
		{TYPE_BIN, 2821.8750, 858.1875, 10.4844},
		{TYPE_BIN, 2836.9531, 858.1953, 10.4844},
		{TYPE_DUMPSTER, 2879.0859, 858.1562, 10.5391},
		{TYPE_BIN, 2863.4688, 946.0156, 10.4844},
		{TYPE_DUMPSTER, 2879.6484, 945.9688, 10.5391},
		{TYPE_DUMPSTER, 2764.9766, 1437.9766, 10.5547},
		{TYPE_DUMPSTER, 2763.0469, 1443.0781, 10.5547},
		{TYPE_DUMPSTER, 2108.6562, 2650.0625, 10.5938},
		{TYPE_DUMPSTER, 2120.5156, 2667.0859, 10.6172},
		{TYPE_DUMPSTER, 2120.3359, 2669.8984, 10.6172},
		{TYPE_DUMPSTER, 2180.9766, 2747.1484, 10.6172},
		{TYPE_DUMPSTER, 2190.2500, 2792.6016, 10.6172},
		{TYPE_DUMPSTER, 2203.6406, 2808.6719, 10.6172},
		{TYPE_DUMPSTER, 2229.1641, 2812.1562, 10.5938},
		{TYPE_DUMPSTER, 2256.7500, 2527.4922, 10.6172},
		{TYPE_DUMPSTER, 2260.3516, 2563.2500, 10.6172},
		{TYPE_DUMPSTER, 2264.1719, 2563.2500, 10.6172},
		{TYPE_DUMPSTER, 2273.8438, 2784.4531, 10.5703},
		{TYPE_DUMPSTER, 2287.7891, 2784.2891, 10.5703},
		{TYPE_DUMPSTER, 2361.7969, 2793.0156, 10.6172},
		{TYPE_DUMPSTER, 2361.1016, 2783.2188, 10.6172},
		{TYPE_DUMPSTER, 2361.2422, 2781.7656, 10.6250},
		{TYPE_DUMPSTER, 2374.3516, 2759.8750, 10.6328},
		{TYPE_DUMPSTER, 2377.2109, 2759.4453, 10.6172},
		{TYPE_DUMPSTER, 2379.2578, 2759.4062, 10.6328},
		{TYPE_DUMPSTER, 2596.2500, 2045.4141, 10.6172},
		{TYPE_DUMPSTER, 2579.4141, 2081.3516, 10.6172},
		{TYPE_DUMPSTER, 2596.3203, 2053.7578, 10.6172},
		{TYPE_DUMPSTER, 2596.3203, 2072.0000, 10.6172},
		{TYPE_DUMPSTER, 2596.2500, 2077.6953, 10.6172},
		{TYPE_DUMPSTER, 2514.1875, 2316.5938, 10.6250},
		{TYPE_DUMPSTER, 2550.1094, 2245.0234, 10.6172},
		{TYPE_DUMPSTER, 2542.9141, 2317.9609, 10.6328},
		{TYPE_DUMPSTER, 2545.7031, 2317.8594, 10.6250},
		{TYPE_DUMPSTER, 2257.9375, 2298.6797, 10.6250},
		{TYPE_DUMPSTER, 2781.6250, 2544.4375, 10.6172},
		{TYPE_DUMPSTER, 2809.6094, 2581.0000, 10.6172},
		{TYPE_DUMPSTER, 2818.9297, 2590.2969, 10.6250},
		{TYPE_DUMPSTER, 2820.3594, 2592.9375, 10.6172},
		{TYPE_DUMPSTER, 2253.9062, 2336.5156, 10.6172},
		{TYPE_DUMPSTER, 1004.8125, 1068.0703, 10.6250},
		{TYPE_DUMPSTER, 1002.5625, 1068.0703, 10.6250},
		{TYPE_DUMPSTER, 1346.2734, 1064.0781, 10.9297},
		{TYPE_DUMPSTER, 1341.3516, 1064.0781, 10.9297},
		{TYPE_DUMPSTER, 1339.0781, 1064.0781, 10.6250},
		{TYPE_DUMPSTER, 1303.2188, 1102.7188, 10.6250},
		{TYPE_DUMPSTER, 1338.8047, 1164.1562, 10.9297},
		{TYPE_DUMPSTER, 1584.9297, 663.9844, 10.9297},
		{TYPE_DUMPSTER, 1632.0156, 663.9844, 10.9297},
		{TYPE_DUMPSTER, 1634.6797, 663.9844, 10.9297},
		{TYPE_DUMPSTER, 1635.9844, 892.2109, 10.9297},
		{TYPE_DUMPSTER, 1756.5781, 691.1641, 10.9297},
		{TYPE_DUMPSTER, 1756.5781, 688.6250, 10.9297},
		{TYPE_DUMPSTER, 1478.1250, 963.5625, 10.6250},
		{TYPE_DUMPSTER, 1478.1250, 967.0703, 10.6250},
		{TYPE_DUMPSTER, 1518.2500, 971.4609, 10.9297},
		{TYPE_DUMPSTER, 1518.2500, 979.7656, 10.9297},
		{TYPE_DUMPSTER, 1557.6562, 970.5625, 10.6250},
		{TYPE_DUMPSTER, 1557.7422, 968.3125, 10.9297},
		{TYPE_DUMPSTER, 1464.2188, 1081.7422, 10.6250},
		{TYPE_DUMPSTER, 1598.6250, 1060.6562, 10.9297},
		{TYPE_DUMPSTER, 1603.0078, 1060.6562, 10.9297},
		{TYPE_DUMPSTER, 1668.0547, 911.7969, 10.9297},
		{TYPE_DUMPSTER, 1732.7422, 967.8359, 10.9297},
		{TYPE_DUMPSTER, 1745.3594, 1049.3906, 10.9297},
		{TYPE_DUMPSTER, 1680.0547, 1168.2734, 10.9297},
		{TYPE_DUMPSTER, 1680.0547, 1164.1562, 10.9297},
		{TYPE_DUMPSTER, 1694.4141, 1160.8594, 9.8125},
		{TYPE_DUMPSTER, 1680.2734, 1251.8594, 9.9062},
		{TYPE_DUMPSTER, 1734.2578, 1249.0547, 10.9297},
		{TYPE_DUMPSTER, 1947.6875, 2331.5469, 10.5625},
		{TYPE_DUMPSTER, 1980.8438, 2331.5156, 10.5625},
		{TYPE_DUMPSTER, 1427.1797, 1905.2578, 9.9453},
		{TYPE_BIN, 1427.2422, 1891.8828, 9.9219},
		{TYPE_BIN, 1427.2422, 1893.1094, 9.9219},
		{TYPE_BIN, 1427.2422, 1911.9297, 9.9219},
		{TYPE_BIN, 1427.2422, 1910.7031, 9.9219},
		{TYPE_BIN, 1427.2422, 1915.1328, 9.9219},
		{TYPE_BIN, 1430.2031, 1932.2812, 9.9219},
		{TYPE_BIN, 1431.4297, 1932.2812, 9.9219},
		{TYPE_BIN, 1434.6328, 1932.2812, 9.9219},
		{TYPE_BIN, 1446.2656, 1884.8438, 9.9219},
		{TYPE_BIN, 1446.2656, 1888.0547, 9.9219},
		{TYPE_BIN, 1446.2656, 1910.7031, 9.9219},
		{TYPE_BIN, 1446.2656, 1911.9297, 9.9219},
		{TYPE_BIN, 1446.2656, 1915.1328, 9.9219},
		{TYPE_DUMPSTER, 1446.1016, 1917.5938, 9.9453},
		{TYPE_BIN, 1666.5469, 2042.2109, 9.9219},
		{TYPE_BIN, 1666.5469, 2039.0078, 9.9219},
		{TYPE_BIN, 1666.5469, 2037.7812, 9.9219},
		{TYPE_DUMPSTER, 1666.5781, 2034.5312, 9.9453},
		{TYPE_BIN, 1659.1406, 2050.9062, 9.9219},
		{TYPE_BIN, 1659.1406, 2049.1406, 9.9219},
		{TYPE_BIN, 1659.1406, 2046.4688, 9.9219},
		{TYPE_DUMPSTER, 1666.5781, 2056.0000, 9.9453},
		{TYPE_BIN, 1659.1406, 2068.9688, 9.9219},
		{TYPE_BIN, 1659.1406, 2070.7344, 9.9219},
		{TYPE_BIN, 1659.2109, 2086.6094, 9.9219},
		{TYPE_BIN, 1659.2109, 2092.3047, 9.9219},
		{TYPE_DUMPSTER, 1659.1016, 2084.4844, 9.9453},
		{TYPE_BIN, 1666.6562, 2062.5312, 9.9219},
		{TYPE_BIN, 1666.6562, 2064.2969, 9.9219},
		{TYPE_BIN, 1666.6562, 2098.8438, 9.9219},
		{TYPE_BIN, 1666.6562, 2100.6094, 9.9219},
		{TYPE_BIN, 1659.2109, 2116.0156, 9.9219},
		{TYPE_DUMPSTER, 1666.5781, 2109.2188, 9.9453},
		{TYPE_BIN, 1659.2109, 2121.7031, 9.9219},
		{TYPE_DUMPSTER, 1659.1016, 2124.2266, 9.9453},
		{TYPE_BIN, 1666.9609, 2128.7344, 9.9219},
		{TYPE_BIN, 1666.9609, 2134.4219, 9.9219},
		{TYPE_BIN, 1659.0078, 2144.4297, 9.9219},
		{TYPE_BIN, 1659.0078, 2142.6641, 9.9219},
		{TYPE_DUMPSTER, 1659.1016, 2159.1094, 9.9453},
		{TYPE_DUMPSTER, 1659.1016, 2161.6016, 9.9453},
		{TYPE_BIN, 1047.7969, 1991.3906, 9.9531},
		{TYPE_BIN, 1047.7969, 1990.1641, 9.9531},
		{TYPE_BIN, 1047.7969, 1994.5938, 9.9531},
		{TYPE_BIN, 1066.8203, 1991.3906, 9.9531},
		{TYPE_BIN, 1066.8203, 1994.5938, 9.9531},
		{TYPE_BIN, 1066.8203, 1990.1641, 9.9531},
		{TYPE_DUMPSTER, 1066.6562, 1997.0547, 9.9453},
		{TYPE_BIN, 1066.4766, 2017.5078, 9.9531},
		{TYPE_BIN, 1048.5000, 2012.0391, 9.9531},
		{TYPE_BIN, 1066.4766, 2018.7344, 9.9531},
		{TYPE_BIN, 1066.4766, 2021.9375, 9.9531},
		{TYPE_DUMPSTER, 1048.3359, 2017.7031, 9.9453},
		{TYPE_BIN, 1567.8203, 2096.8047, 9.9219},
		{TYPE_BIN, 1567.8203, 2095.5781, 9.9219},
		{TYPE_BIN, 1567.8203, 2133.4844, 9.9219},
		{TYPE_BIN, 1567.8203, 2134.7109, 9.9219},
		{TYPE_BIN, 1567.8203, 2157.5469, 9.9219},
		{TYPE_BIN, 1567.8203, 2156.3203, 9.9219},
		{TYPE_BIN, 1567.8203, 2160.7500, 9.9219},
		{TYPE_DUMPSTER, 1577.5859, 2161.1484, 10.2109},
		{TYPE_DUMPSTER, 1577.5859, 2119.1016, 10.2109},
		{TYPE_DUMPSTER, 1577.5859, 2091.5391, 10.2109},
		{TYPE_BIN, 1577.7578, 2158.6875, 9.9219},
		{TYPE_BIN, 1577.7578, 2155.4844, 9.9219},
		{TYPE_BIN, 1577.7578, 2154.2578, 9.9219},
		{TYPE_BIN, 1577.7578, 2113.4375, 9.9219},
		{TYPE_BIN, 1577.7578, 2112.2109, 9.9219}
	};

static
	FactoryData[][E_FACTORY_DATA] = {
	// location, x, y, z
	    {"Los Santos", 2432.553710, -2115.611328, 13.546875},
		{"Las Venturas", 981.711303, 2168.738769, 10.820312},
		{"San Fierro", -1044.592895, -606.348876, 32.007812}
	};


static
    PlayerHasTrash[MAX_PLAYERS],
    TrashCheckpoint[MAX_PLAYERS],
    PlayerText: CapacityText[MAX_PLAYERS],
    FactoryIcons[MAX_PLAYERS][sizeof(FactoryData)],
    PlayerBar: CapacityBar[MAX_PLAYERS];

static
    LoadedTrash[MAX_VEHICLES];

// Initialise Trash Data
hook OnGameModeInit() {
    new
		label[128];
    for(new i; i < sizeof(TrashData); i++)
    {
        format(label, sizeof(label), "%s\n{FFFFFF}\n/pickup to collect.", (TrashData[i][TrashType] == TYPE_BIN) ? ("Trash Bin") : ("Dumpster"));
        TrashData[i][TrashLabel] = CreateDynamic3DTextLabel(label, 0x2ECC71FF, TrashData[i][TrashX], TrashData[i][TrashY], TrashData[i][TrashZ ]+ 1.25, 15.0, .testlos = 1);
        TrashData[i][TrashLevel] = (TrashData[i][TrashType] == TYPE_BIN) ? 1 : 2;
    }

    for(new i; i < sizeof(FactoryData); i++)
    {
        format(label, sizeof(label), "Recycling Factory - %s\n\n{FFFFFF}Current Trash Bags: {F39C12}0\n{FFFFFF}Bring trash here to earn money!", FactoryData[i][FactoryName]);
        FactoryData[i][FactoryLabel] = CreateDynamic3DTextLabel(label, 0x2ECC71FF, FactoryData[i][FactoryX], FactoryData[i][FactoryY], FactoryData[i][FactoryZ] + 0.5, 15.0, .testlos = 1);
        FactoryData[i][FactoryCP] = CreateDynamicCP(FactoryData[i][FactoryX], FactoryData[i][FactoryY], FactoryData[i][FactoryZ], 6.0);
    }
}

// Clean up
hook OnPlayerConnect(playerid) {
    PlayerHasTrash[playerid] = false;
    TrashCheckpoint[playerid] = -1;

    CapacityText[playerid] = CreatePlayerTextDraw(playerid, 32.000000, 290.000000, "Vehicle Capacity (0/10)");
    PlayerTextDrawBackgroundColor(playerid, CapacityText[playerid], 255);
    PlayerTextDrawFont(playerid, CapacityText[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, CapacityText[playerid], 0.200000, 1.000000);
    PlayerTextDrawColor(playerid, CapacityText[playerid], -1);
    PlayerTextDrawSetOutline(playerid, CapacityText[playerid], 1);
    PlayerTextDrawSetProportional(playerid, CapacityText[playerid], true);
    PlayerTextDrawSetSelectable(playerid, CapacityText[playerid], false);

    CapacityBar[playerid] = CreatePlayerProgressBar(playerid, 30.000000, 304.000000, 118.500000, 6.199999, -1429936641, TRASH_LIMIT, 0);
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate){
	if(newstate == PLAYER_STATE_DRIVER) {
	    new
			vehicleid = GetPlayerVehicleID(playerid);
	    if(GetVehicleModel(vehicleid) == 408) {
		    if(LoadedTrash[vehicleid] > 0) {
				SendMsgF(
					playerid,
					COLOR_SAMPBLUE,
					"(trash master) "C_WHITE"This vehicle has "C_ORANGE"%d "C_WHITE"trash bags which is worth "C_GREEN"%m.",
					LoadedTrash[vehicleid],
					LoadedTrash[vehicleid] * TRASH_BAG_VALUE
				);
				SendClientMessage(
					playerid,
					COLOR_SAMPBLUE,
					"(trash master)"C_WHITE" You can sell your trash bags to recycling factories marked by a truck icon."
				);

				for(new i; i < sizeof(FactoryData); i++)
				{
				    FactoryIcons[playerid][i] = CreateDynamicMapIcon(
						FactoryData[i][FactoryX],
						FactoryData[i][FactoryY],
						FactoryData[i][FactoryZ],
						51, 0, _, _, playerid, 8000.0, MAPICON_GLOBAL
					);
					TogglePlayerDynamicCP(playerid, FactoryData[i][FactoryCP], 1);
				}
		    }
			else {
		        SendClientMessage(playerid, COLOR_SAMPBLUE, "(trash master) "C_WHITE"You can collect trash and sell them at recycling factories.");
		        SendClientMessage(playerid, COLOR_SAMPBLUE, "(trash master) "C_WHITE"Find trash cans/dumpsters and use /pickup.");
			}
			ShowCapacity(playerid);
			SetPVarInt(playerid, "LastVehicleID", vehicleid);
		}
	}

	if(oldstate == PLAYER_STATE_DRIVER) {
		for(new i; i < sizeof(FactoryData); i++) {
		    if(IsValidDynamicMapIcon(FactoryIcons[playerid][i])) {
		        DestroyDynamicMapIcon(FactoryIcons[playerid][i]);
		        FactoryIcons[playerid][i] = -1;
		    }
			TogglePlayerDynamicCP(playerid, FactoryData[i][FactoryCP], 0);
		}
		PlayerTextDrawHide(playerid, CapacityText[playerid]);
		HidePlayerProgressBar(playerid, CapacityBar[playerid]);
	}

	InitPlayerTrash(playerid);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if((newkeys & KEY_NO) && PlayerHasTrash[playerid]) {
		InitPlayerTrash(playerid);
		SendClientMessage(playerid, COLOR_SAMPBLUE, "(trash master) "C_WHITE"Trash bag removed.");
	}
	return 1;
}

public OnVehicleSpawn(vehicleid) {
	LoadedTrash[vehicleid] = 0;
	return 1;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid) {
	if(checkpointid == TrashCheckpoint[playerid]) {
	    if(!PlayerHasTrash[playerid]) {
			return SendErrorMsg(playerid, "You're not carrying a trash bag.");
		}
		new
			vehicleid = GetPVarInt(playerid, "LastVehicleID");

	    if(LoadedTrash[vehicleid] >= TRASH_LIMIT) {
			return SendErrorMsg(playerid, "This vehicle is full, you can't load any more trash.");
		}

		LoadedTrash[vehicleid]++;

		ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, false, false, false, false, 0);

		SendClientMessage(playerid, 0x2ECC71FF, "TRASHMASTER JOB: {FFFFFF}You've collected a trash bag.");

		new
			amountLeft = (TRASH_LIMIT - LoadedTrash[vehicleid]);
		if(amountLeft > 0) {
			SendMsgF(
				playerid,
				COLOR_SAMPBLUE,
				"(trash master) "C_WHITE"You can load "C_ORANGE"%d "C_WHITE"more trash bags to this vehicle.",
				amountLeft
			);
		}

		new
			driverid = GetVehicleDriver(vehicleid);

		if(IsPlayerConnected(driverid)) {
			ShowCapacity(driverid);
		}
		InitPlayerTrash(playerid);
		return 1;
	}

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		for(new i; i < sizeof(FactoryData); i++) {
		    if(checkpointid == FactoryData[i][FactoryCP]) {
		        new
					vehicleid = GetPlayerVehicleID(playerid),
					reward = LoadedTrash[vehicleid] * TRASH_BAG_VALUE;

				SendMsgF(
					playerid,
					COLOR_SAMPBLUE,
					"(trash master) "C_WHITE"Sold "C_ORANGE"%d "C_WHITE"bags of trash and earned "C_GREEN"%m.",
					LoadedTrash[vehicleid], reward
				);
		        GivePlayerMoney(playerid, reward);

		        FactoryData[i][FactoryCurrent] += LoadedTrash[vehicleid];
		        LoadedTrash[vehicleid] = 0;

				ShowCapacity(playerid);
				new
					string[128];
                format(string, sizeof(string), "Recycling Factory - %s\n\n{FFFFFF}Current Trash Bags: {F39C12}%d\n{FFFFFF}Bring trash here to earn money!", FactoryData[i][FactoryName], FactoryData[i][FactoryCurrent]);
                UpdateDynamic3DTextLabelText(FactoryData[i][FactoryLabel], 0x2ECC71FF, string);

		        for(new x; x < sizeof(FactoryData); x++) {
				    if(IsValidDynamicMapIcon(FactoryIcons[playerid][x])) {
				        DestroyDynamicMapIcon(FactoryIcons[playerid][x]);
				        FactoryIcons[playerid][x] = -1;
				    }
					TogglePlayerDynamicCP(playerid, FactoryData[x][FactoryCP], 0);
				}
		        break;
		    }
		}
	}
	return 1;
}

forward FillTrash(id);
public FillTrash(id) {
	TrashData[id][TrashLevel]++;
	if(TrashData[id][TrashType] == TYPE_BIN && TrashData[id][TrashLevel] > 1) TrashData[id][TrashLevel] = 1;

	if(TrashData[id][TrashType] == TYPE_DUMPSTER) {
		if(TrashData[id][TrashLevel] == 1) TrashData[id][TrashTimer] = SetTimerEx("FillTrash", REFILL_TIME * 1000, false, "i", id);
		if(TrashData[id][TrashLevel] >= 2) {
			TrashData[id][TrashLevel] = 2;
			KillTimer(TrashData[id][TrashTimer]);
			TrashData[id][TrashTimer] = -1;
		}

		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TrashData[id][TrashLabel], E_STREAMER_COLOR, (TrashData[id][TrashLevel] == 1) ? 0xF39C12FF : 0x2ECC71FF);
		return 1;
	}

	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TrashData[id][TrashLabel], E_STREAMER_COLOR, 0x2ECC71FF);
	return 1;
}

CMD:pickup(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid))  {
		return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}You can't use this command in a vehicle.");
	}

	new
		vehicleid = GetPVarInt(playerid, "LastVehicleID");

	if(GetVehicleModel(vehicleid) != 408) {
		return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}Your last vehicle has to be a Trashmaster.");
	}

	if(PlayerHasTrash[playerid]) {
		return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}You're already carrying a trash bag.");
	}

	new
		id = ClosestTrash(playerid);
	if(id == -1) {
		return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}You're not near any trash.");
	}
	if(TrashData[id][TrashLevel] < 1) {
		return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}There's nothing here.");
	}
	new
		Float: x,
		Float: y,
		Float: z;
    GetVehicleBoot(vehicleid, x, y, z);

    if(GetPlayerDistanceFromPoint(playerid, x, y, z) >= 30.0) {
		return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}You're not near your Trashmaster.");
	}

	TrashData[id][TrashLevel]--;

	KillTimer(TrashData[id][TrashTimer]);

    TrashData[id][TrashTimer] = SetTimerEx("FillTrash", REFILL_TIME * 1000, false, "i", id);
	TrashCheckpoint[playerid] = CreateDynamicCP(x, y, z, 3.0, .playerid = playerid);
	PlayerHasTrash[playerid] = true;

	ApplyAnimation(playerid, "CARRY", "liftup105", 4.1, false, false, false, false, 0);
	SetPlayerAttachedObject(playerid, ATTACHMENT_INDEX, 1264, 6, 0.222, 0.024, 0.128, 1.90, -90.0, 0.0, 0.5,0.5, 0.5);

	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TrashData[id][TrashLabel], E_STREAMER_COLOR, (TrashData[id][TrashLevel] == 0) ? 0xE74C3CFF : 0xF39C12FF);
	SendClientMessage(playerid, 0x2ECC71FF, "TRASHMASTER JOB: {FFFFFF}You can press {F39C12}~k~~CONVERSATION_NO~ {FFFFFF}to remove the trash bag.");
	return 1;
}


// Internal Function
static stock ShowCapacity(playerid) {
    new
        vehicleid = GetPlayerVehicleID(playerid),
        capacity_string[32];

    format(capacity_string, sizeof(capacity_string), "Vehicle Capacity (%d/%d)", LoadedTrash[vehicleid], TRASH_LIMIT);
    PlayerTextDrawSetString(playerid, CapacityText[playerid], capacity_string);
    PlayerTextDrawShow(playerid, CapacityText[playerid]);

    SetPlayerProgressBarValue(playerid, CapacityBar[playerid], LoadedTrash[vehicleid]);
    ShowPlayerProgressBar(playerid, CapacityBar[playerid]);
}

static ClosestTrash(playerid) {
    new
		closest_id = -1,
		Float: dist = 3.0,
		Float: tempdist;

    for(new i; i < sizeof(TrashData); i++) {
        tempdist = GetPlayerDistanceFromPoint(playerid, TrashData[i][TrashX], TrashData[i][TrashY], TrashData[i][TrashZ]);
        if(tempdist > 3.0) continue;
        if(tempdist <= dist) {
            dist = tempdist;
            closest_id = i;
        }
    }
    return closest_id;
}


static InitPlayerTrash(playerid, bool:removeUI = false)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, ATTACHMENT_INDEX)) {
		RemovePlayerAttachedObject(playerid, ATTACHMENT_INDEX);
	}
	if(IsValidDynamicCP(TrashCheckpoint[playerid])) {
		DestroyDynamicCP(TrashCheckpoint[playerid]);
	}
	PlayerHasTrash[playerid] = false;
	TrashCheckpoint[playerid] = -1;

	if(removeUI) {
	    PlayerTextDrawDestroy(playerid, CapacityText[playerid]);
	    DestroyPlayerProgressBar(playerid, CapacityBar[playerid]);
	}
	return 1;
}