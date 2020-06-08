enum E_HOUSE_INTERIOR_DATA
{
	E_HOUSE_INTERIOR_NAME[ 19 ], 		
    Float: E_HOUSE_INTERIOR_X, 				
    Float: E_HOUSE_INTERIOR_Y,
	Float: E_HOUSE_INTERIOR_Z, 	
    E_HOUSE_INTERIOR_ID, 				
    E_HOUSE_INTERIOR_PRICE,
    bool:E_HOUSE_FOR_VIP
};

#define H_DEFAULT_X					266.4996
#define H_DEFAULT_Y					304.9577
#define H_DEFAULT_Z					999.1484

static const HouseInteriors[][E_HOUSE_INTERIOR_DATA] =
{
    { "Cattus Interior",   	H_DEFAULT_X, H_DEFAULT_Y, H_DEFAULT_Z, 	2,  0,	false},
    { "Assum Interior",   	243.71980, 304.963500, 999.14840, 	1,  10000,	false},
    { "Fossor Interior", 	2218.4036, -1076.2621, 1050.4844,	1,	15000,	false},
    { "Organum Interior", 	309.37170, 311.674700, 1003.3047,	4,  25000,	false},
    { "Aurora Interior", 	-2170.344, 639.502500, 1052.3750,	1,	30000,	false},
    { "Fragor Interior",   	318.58580, 1114.47920, 1083.8828,	5,	35000,	false},
    { "Artus Interior", 	2237.5259, -1081.6458, 1049.0234,	2,	40000,	false},
    { "Caelum Interior", 	2233.6931, -1115.2620, 1050.8828,	5,	40000,	false},
    { "Rotta Interior",		2495.9663, -1692.0857, 1014.7422,	3,	50000,	false},
    { "Ascensor Interior", 	2317.8369, -1026.7662, 1050.2178,	9,	50000,	false},
    { "Colonel Interior",	2807.5693, -1174.7520, 1025.5703,	8,	60000,	false},
    { "Recens Interior",	2270.4192, -1210.5172, 1047.5625,	10,	70000,	false},
    { "Novus Interior",		2365.2341, -1135.5957, 1050.8826,	8,	72000,	false},
    { "Securuse Interior",	2324.3826, -1149.5442, 1050.7101,	12,	80000,	false}
};

stock House_GetInteriorName(index, name[], len = sizeof(name)) {
    // invalid index.
    if(!(0 <= index < sizof(HouseInteriors))) {
        return 0;
    }
    strcpy(name, HouseInteriors[index][E_HOUSE_INTERIOR_NAME]);
    return 1;
}

stock House_GetInteriorArraySize() {
    return sizeof(HouseInteriors);
}

stock House_GetInteriorData(index, &Float:x, &Float:y, &Float:z, &int, &price, &bool:vip) {

    // invalid index.
    if(!(0 <= index < sizeof(HouseInteriors))) {
        return 0;
    }

    x = HouseInteriors[index][E_HOUSE_INTERIOR_X];
    y = HouseInteriors[index][E_HOUSE_INTERIOR_Y];
    z = HouseInteriors[index][E_HOUSE_INTERIOR_Z];
    int = HouseInteriors[index][E_HOUSE_INTERIOR_ID];
    price = HouseInteriors[index][E_HOUSE_INTERIOR_PRICE];
    vip = HouseInteriors[index][E_HOUSE_FOR_VIP];
    return 1;

}
