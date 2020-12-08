/*
    Extended vehicle functions by Emmet_

	Thanks to:

	- [uL]Pottus -> GetVehicleTopSpeed idea
	- kvann -> SetVehicleInterior idea
	- Hanger -> Top speed data
*/

#if !defined INVALID_SEAT_ID
	#define INVALID_SEAT_ID 		-1
#endif

#if !defined INVALID_PAINTJOB_ID
	#define INVALID_PAINTJOB_ID     -1
#endif

#define GetVehicleSeats(%0) \
	(GetVehicleModelSeats(GetVehicleModel(%0)))

#define SetVehicleInterior(%0) \
	(LinkVehicleToInterior(%0))

#define GetVehicleBoot(%0,%1,%2,%3) \
	(GetVehicleOffset((%0), VEHICLE_OFFSET_BOOT, %1, %2, %3))

#define GetVehicleHood(%0,%1,%2,%3) \
	(GetVehicleOffset((%0), VEHICLE_OFFSET_HOOD, %1, %2, %3))

#define GetVehicleRoof(%0,%1,%2,%3) \
	(GetVehicleOffset((%0), VEHICLE_OFFSET_ROOF, %1, %2, %3))

enum e_VehicleProperties {
	e_VEHICLE_INTERIOR,
	e_VEHICLE_PAINTJOB,
	e_VEHICLE_COLOR_1,
	e_VEHICLE_COLOR_2
};

static s_VehicleTrailerID[MAX_VEHICLES];

// Called when a vehicle is created.
forward OnVehicleCreated(vehicleid);
// Called when a vehicle is deleted.
forward OnVehicleDestroyed(vehicleid);
// Called when a trailer is hooked.
forward OnTrailerHooked(playerid, vehicleid, trailerid);
// Called when a trailer is unhooked.
forward OnTrailerUnhooked(playerid, vehicleid, trailerid);
// Called when a player shoots at a vehicle.
forward OnPlayerShootVehicle(playerid, vehicleid, weaponid);

enum e_ParamTypes {
	VEHICLE_TYPE_ENGINE,
	VEHICLE_TYPE_LIGHTS,
 	VEHICLE_TYPE_ALARM,
	VEHICLE_TYPE_DOORS,
	VEHICLE_TYPE_BONNET,
	VEHICLE_TYPE_BOOT,
	VEHICLE_TYPE_OBJECTIVE
};

enum e_OffsetTypes {
	VEHICLE_OFFSET_BOOT,
	VEHICLE_OFFSET_HOOD,
	VEHICLE_OFFSET_ROOF
};

#if !defined IsValidVehicle
	native IsValidVehicle(vehicleid);
#endif

static const s_TopSpeed[212] = {
	157, 147, 186, 110, 133, 164, 110, 148, 100, 158, 129, 221, 168, 110, 105, 192, 154, 270,
	115, 149, 145, 154, 140, 99, 135, 270, 173, 165, 157, 201, 190, 130, 94, 110, 167, 0, 149,
	158, 142, 168, 136, 145, 139, 126, 110, 164, 270, 270, 111, 0, 0, 193, 270, 60, 135, 157,
	106, 95, 157, 136, 270, 160, 111, 142, 145, 145, 147, 140, 144, 270, 157, 110, 190, 190,
	149, 173, 270, 186, 117, 140, 184, 73, 156, 122, 190, 99, 64, 270, 270, 139, 157, 149, 140,
	270, 214, 176, 162, 270, 108, 123, 140, 145, 216, 216, 173, 140, 179, 166, 108, 79, 101, 270,
    270, 270, 120, 142, 157, 157, 164, 270, 270, 160, 176, 151, 130, 160, 158, 149, 176, 149, 60,
    70, 110, 167, 168, 158, 173, 0, 0, 270, 149, 203, 164, 151, 150, 147, 149, 142, 270, 153, 145,
    157, 121, 270, 144, 158, 113, 113, 156, 178, 169, 154, 178, 270, 145, 165, 160, 173, 146, 0, 0,
    93, 60, 110, 60, 158, 158, 270, 130, 158, 153, 151, 136, 85, 0, 153, 142, 165, 108, 162, 0, 0,
    270, 270, 130, 190, 175, 175, 175, 158, 151, 110, 169, 171, 148, 152, 0, 0, 0, 108, 0, 0
};

static const s_CarColors[][] = {
    {16, 004, 001, 123, 001, 113, 001, 101, 001, 075, 001, 062, 001, 040, 001, 036, 001},
    {16, 041, 041, 047, 047, 052, 052, 066, 066, 074, 074, 087, 087, 091, 091, 113, 113},
    {16, 010, 010, 013, 013, 022, 022, 030, 030, 039, 039, 090, 090, 098, 098, 110, 110},
    {16, 036, 001, 037, 001, 030, 001, 028, 001, 025, 001, 040, 001, 101, 001, 113, 001},
    {16, 113, 039, 119, 050, 123, 092, 109, 100, 101, 101, 095, 105, 083, 110, 066, 025},
    {16, 011, 001, 024, 001, 036, 001, 040, 001, 075, 001, 091, 001, 123, 001, 004, 001},
    {2,  001, 001},
    {2,  003, 001},
    {2,  026, 026},
    {2,  001, 001},
    {16, 004, 001, 009, 001, 010, 001, 025, 001, 036, 001, 040, 001, 045, 001, 084, 001},
    {16, 012, 001, 064, 001, 123, 001, 116, 001, 112, 001, 106, 001, 080, 001, 075, 001},
    {16, 009, 001, 010, 008, 011, 001, 025, 008, 027, 001, 029, 008, 030, 001, 037, 008},
    {16, 087, 001, 088, 001, 091, 001, 105, 001, 109, 001, 119, 001, 004, 001, 025, 001},
    {16, 025, 001, 028, 001, 043, 001, 067, 001, 072, 001, 009, 001, 095, 001, 024, 001},
    {16, 020, 001, 025, 001, 036, 001, 040, 001, 062, 001, 075, 001, 092, 001, 000, 001},
    {2,  001, 003},
    {0,  000, 000},
    {16, 119, 119, 117, 227, 114, 114, 108, 108, 095, 095, 081, 081, 061, 061, 041, 041},
    {16, 045, 075, 047, 076, 033, 075, 013, 076, 054, 075, 069, 076, 059, 075, 087, 076},
    {2,  006, 001},
    {16, 004, 001, 013, 001, 025, 001, 030, 001, 036, 001, 040, 001, 075, 001, 095, 001},
    {14, 096, 025, 097, 025, 101, 025, 111, 031, 113, 036, 083, 057, 067, 059},
    {12, 001, 016, 001, 056, 001, 017, 001, 053, 001, 005, 001, 035},
    {16, 001, 000, 002, 002, 003, 002, 003, 006, 006, 016, 015, 030, 024, 053, 035, 061},
    {2,  043, 000},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {2,  000, 001},
    {2,  004, 075},
    {16, 012, 012, 013, 013, 014, 014, 001, 002, 002, 001, 001, 003, 003, 001, 010, 010},
    {2,  046, 026},
    {16, 071, 059, 075, 059, 092, 072, 047, 074, 055, 083, 059, 083, 071, 087, 082, 087},
    {2,  043, 000},
    {2,  043, 000},
    {14, 001, 001, 012, 012, 002, 002, 006, 006, 004, 004, 046, 046, 053, 053},
    {2,  001, 001},
    {14, 083, 001, 087, 001, 092, 001, 095, 001, 109, 001, 119, 045, 011, 001},
    {16, 054, 007, 079, 007, 087, 007, 095, 016, 098, 020, 105, 020, 123, 020, 125, 021},
    {2,  006, 076},
    {16, 057, 008, 008, 017, 043, 021, 054, 038, 067, 008, 037, 078, 065, 079, 025, 078},
    {16, 034, 034, 032, 032, 020, 020, 110, 110, 066, 066, 084, 084, 118, 118, 121, 121},
    {16, 002, 096, 079, 042, 082, 054, 067, 086, 126, 096, 070, 096, 110, 054, 067, 098},
    {16, 000, 000, 011, 105, 025, 109, 036, 000, 040, 036, 075, 036, 000, 036, 000, 109},
    {16, 004, 001, 020, 001, 024, 001, 025, 001, 036, 001, 040, 001, 054, 001, 084, 001},
    {12, 032, 036, 032, 042, 032, 053, 032, 066, 032, 014, 032, 032},
    {16, 034, 034, 035, 035, 037, 037, 039, 039, 041, 041, 043, 043, 045, 045, 047, 047},
    {32, 000, 000, 000, 001, 001, 005, 001, 001, 003, 003, 000, 001, 001, 022, 001, 001, 001, 035, 001, 001, 001, 044, 001, 001, 001, 053, 001, 001, 001, 057, 001, 001},
    {2,  075, 002},
    {2,  001, 003},
    {2,  001, 074},
    {2,  001, 001},
    {16, 123, 123, 125, 125, 036, 036, 016, 016, 018, 018, 046, 046, 061, 061, 075, 075},
    {16, 001, 003, 001, 005, 001, 016, 001, 022, 001, 035, 001, 044, 001, 053, 001, 057},
    {2,  056, 056},
    {2,  026, 026},
    {16, 084, 015, 084, 058, 084, 031, 032, 074, 043, 031, 001, 031, 077, 031, 032, 074},
    {16, 084, 063, 091, 063, 102, 065, 105, 072, 110, 093, 121, 093, 012, 095, 023, 001},
    {16, 058, 001, 002, 001, 063, 001, 018, 001, 032, 001, 045, 001, 013, 001, 034, 001},
    {16, 091, 001, 101, 001, 109, 001, 113, 001, 004, 001, 025, 001, 030, 001, 036, 001},
    {16, 026, 026, 028, 028, 044, 044, 051, 051, 057, 057, 072, 072, 106, 106, 112, 112},
    {16, 001, 003, 001, 009, 001, 018, 001, 030, 017, 023, 046, 023, 046, 032, 057, 034},
    {16, 036, 001, 037, 001, 043, 001, 053, 001, 061, 001, 075, 001, 079, 001, 088, 001},
    {16, 012, 012, 013, 013, 014, 014, 001, 002, 002, 001, 001, 003, 003, 001, 010, 010},
    {16, 079, 079, 084, 084, 007, 007, 011, 011, 019, 019, 022, 022, 036, 036, 053, 053},
    {2,  014, 075},
    {2,  014, 075},
    {16, 067, 076, 068, 076, 078, 076, 002, 076, 016, 076, 018, 076, 025, 076, 045, 088},
    {16, 051, 001, 058, 008, 060, 001, 068, 008, 002, 001, 013, 008, 022, 001, 036, 008},
    {8,  006, 006, 046, 046, 053, 053, 003, 003},
    {0,  000, 000},
    {2,  043, 000},
    {16, 120, 117, 103, 111, 120, 114, 074, 091, 120, 112, 074, 083, 120, 113, 066, 071},
    {4,  056, 015, 056, 053},
    {4,  056, 015, 056, 053},
    {16, 097, 001, 081, 001, 105, 001, 110, 001, 091, 001, 074, 001, 084, 001, 083, 001},
    {16, 002, 039, 009, 039, 017, 001, 021, 001, 033, 000, 037, 000, 041, 029, 056, 029},
    {16, 006, 007, 007, 006, 001, 006, 089, 091, 119, 117, 103, 102, 077, 087, 071, 077},
    {16, 092, 001, 094, 001, 101, 001, 121, 001, 000, 001, 022, 001, 036, 001, 075, 001},
    {16, 072, 001, 066, 001, 059, 001, 045, 001, 040, 001, 039, 001, 035, 001, 020, 001},
    {16, 027, 036, 059, 036, 060, 035, 055, 041, 054, 031, 049, 023, 045, 032, 040, 029},
    {14, 073, 045, 012, 012, 002, 002, 006, 006, 004, 004, 046, 046, 053, 053},
    {16, 001, 001, 003, 003, 006, 006, 046, 046, 065, 009, 014, 001, 012, 009, 026, 001},
    {16, 041, 041, 048, 048, 052, 052, 064, 064, 071, 071, 085, 085, 010, 010, 062, 062},
    {32, 001, 031, 001, 000, 001, 031, 001, 000, 001, 020, 003, 000, 001, 005, 000, 000, 000, 006, 003, 000, 003, 006, 003, 000, 016, 000, 008, 000, 017, 000, 120, 000},
    {8,  012, 035, 050, 032, 040, 026, 066, 036},
    {14, 001, 073, 001, 074, 001, 075, 001, 076, 001, 077, 001, 078, 001, 079},
    {2,  001, 001},
    {16, 026, 014, 029, 042, 026, 057, 054, 029, 026, 003, 003, 029, 012, 039, 074, 035},
    {4,  002, 026, 002, 029},
    {12, 013, 118, 014, 123, 120, 123, 112, 120, 084, 110, 076, 102},
    {2,  000, 000},
    {12, 040, 065, 071, 072, 052, 066, 064, 072, 030, 072, 060, 072},
    {16, 030, 026, 077, 026, 081, 027, 024, 055, 028, 056, 049, 059, 052, 069, 071, 107},
    {2,  036, 013},
    {16, 007, 094, 036, 088, 051, 075, 053, 075, 058, 067, 075, 067, 075, 061, 079, 062},
    {16, 123, 124, 119, 122, 118, 117, 116, 115, 114, 108, 101, 106, 088, 099, 005, 006},
    {16, 074, 072, 066, 072, 053, 056, 037, 019, 022, 022, 020, 020, 009, 014, 000, 000},
    {2,  000, 001},
    {16, 011, 123, 013, 120, 020, 117, 024, 112, 027, 107, 036, 105, 037, 107, 043, 093},
    {16, 109, 025, 109, 032, 112, 032, 010, 032, 030, 044, 032, 052, 084, 066, 084, 069},
    {16, 075, 084, 040, 084, 040, 110, 028, 119, 025, 119, 021, 119, 013, 119, 004, 119},
    {2,  014, 075},
    {16, 083, 066, 087, 074, 087, 075, 098, 083, 101, 100, 103, 101, 117, 116, 123, 036},
    {16, 036, 117, 036, 013, 042, 030, 042, 033, 054, 036, 075, 079, 092, 101, 098, 109},
    {16, 051, 039, 057, 038, 045, 029, 034, 009, 065, 009, 014, 001, 012, 009, 026, 001},
    {12, 013, 118, 014, 123, 120, 123, 112, 120, 084, 110, 076, 102},
    {10, 003, 003, 006, 006, 007, 007, 052, 052, 076, 076},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {2,  001, 001},
    {16, 007, 001, 074, 001, 061, 001, 016, 001, 025, 001, 030, 001, 036, 001, 053, 001},
    {16, 043, 043, 046, 046, 039, 039, 028, 028, 016, 016, 006, 006, 005, 005, 002, 002},
    {16, 003, 090, 004, 090, 007, 068, 008, 066, 012, 060, 027, 097, 034, 051, 037, 051},
    {16, 017, 039, 015, 123, 032, 112, 045, 088, 052, 071, 057, 067, 061, 096, 096, 096},
    {16, 038, 051, 021, 036, 021, 034, 030, 034, 054, 034, 055, 020, 048, 018, 051, 006},
    {16, 010, 001, 025, 001, 028, 001, 036, 001, 040, 001, 054, 001, 075, 001, 113, 001},
    {16, 013, 076, 024, 077, 063, 078, 042, 076, 054, 077, 039, 078, 011, 076, 062, 077},
    {16, 116, 001, 119, 001, 122, 001, 004, 001, 009, 001, 024, 001, 027, 001, 036, 001},
    {16, 037, 036, 036, 036, 040, 036, 043, 041, 047, 041, 051, 072, 054, 075, 055, 084},
    {16, 002, 039, 009, 039, 017, 001, 021, 001, 033, 000, 037, 000, 041, 029, 056, 029},
    {2,  001, 001},
    {0,  000, 000},
    {16, 074, 074, 075, 013, 087, 118, 092, 003, 115, 118, 025, 118, 036, 000, 118, 118},
    {16, 003, 003, 003, 008, 006, 025, 007, 079, 008, 082, 036, 105, 039, 106, 051, 118},
    {0,  000, 000},
    {32, 060, 024, 023, 000, 061, 027, 123, 000, 065, 031, 031, 000, 061, 061, 030, 000, 081, 035, 023, 000, 062, 061, 062, 000, 083, 066, 064, 000, 083, 064, 064, 000},
    {14, 001, 001, 017, 020, 018, 020, 022, 030, 036, 043, 044, 051, 052, 054},
    {16, 002, 039, 009, 039, 017, 001, 021, 001, 033, 000, 037, 000, 041, 029, 056, 029},
    {16, 052, 001, 053, 001, 066, 001, 075, 001, 076, 001, 081, 001, 095, 001, 109, 001},
    {0,  000, 000},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {16, 110, 001, 111, 001, 112, 001, 114, 001, 119, 001, 122, 001, 004, 001, 013, 001},
    {12, 002, 035, 036, 002, 051, 053, 091, 002, 011, 022, 040, 035},
    {0,  000, 000},
    {16, 073, 001, 074, 001, 075, 001, 077, 001, 079, 001, 083, 001, 084, 001, 091, 001},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {16, 003, 001, 028, 001, 031, 001, 055, 001, 066, 001, 097, 001, 123, 001, 118, 001},
    {16, 009, 001, 012, 001, 026, 096, 030, 096, 032, 001, 037, 001, 057, 096, 071, 096},
    {2,  001, 001},
    {2,  001, 001},
    {14, 096, 067, 086, 070, 079, 074, 070, 086, 061, 098, 075, 075, 075, 091},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {16, 051, 001, 058, 008, 060, 001, 068, 008, 002, 001, 013, 008, 022, 001, 036, 008},
    {16, 013, 118, 024, 118, 031, 093, 032, 092, 045, 092, 113, 092, 119, 113, 122, 113},
    {16, 076, 008, 032, 008, 043, 008, 067, 008, 011, 011, 008, 090, 002, 002, 083, 013},
    {2,  003, 001},
    {16, 050, 001, 047, 001, 044, 096, 040, 096, 039, 001, 030, 001, 028, 096, 009, 096},
    {16, 062, 037, 078, 038, 002, 062, 003, 087, 002, 078, 113, 078, 119, 062, 007, 078},
    {16, 122, 001, 123, 001, 125, 001, 010, 001, 024, 001, 037, 001, 055, 001, 066, 001},
    {2,  001, 001},
    {16, 074, 039, 072, 039, 075, 039, 079, 039, 083, 036, 084, 036, 089, 035, 091, 035},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {16, 067, 001, 072, 001, 075, 001, 083, 001, 091, 001, 101, 001, 109, 001, 020, 001},
    {6,  056, 056, 049, 049, 026, 124},
    {16, 038, 009, 055, 023, 061, 074, 071, 087, 091, 087, 098, 114, 102, 119, 111, 003},
    {16, 053, 032, 015, 032, 045, 032, 034, 030, 065, 032, 014, 032, 012, 032, 043, 032},
    {16, 051, 001, 058, 001, 060, 001, 068, 001, 002, 001, 013, 001, 022, 001, 036, 001},
    {2,  001, 001},
    {2,  001, 001},
    {16, 112, 001, 116, 001, 117, 001, 024, 001, 030, 001, 035, 001, 036, 001, 040, 001},
    {16, 051, 001, 058, 008, 060, 001, 068, 008, 002, 001, 013, 008, 022, 001, 036, 008},
    {16, 052, 039, 009, 039, 017, 001, 021, 001, 033, 000, 037, 000, 041, 029, 056, 029},
    {16, 057, 008, 008, 017, 043, 021, 054, 038, 067, 008, 037, 078, 065, 079, 025, 078},
    {16, 036, 001, 035, 001, 017, 001, 011, 001, 116, 001, 113, 001, 101, 001, 092, 001},
    {2,  001, 006},
    {0,  000, 000},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {16, 109, 001, 030, 008, 095, 001, 084, 008, 083, 001, 072, 008, 071, 001, 052, 008},
    {16, 097, 096, 088, 064, 090, 096, 093, 064, 097, 096, 099, 081, 102, 114, 114, 001},
    {16, 002, 039, 009, 039, 017, 001, 021, 001, 033, 000, 037, 000, 041, 029, 056, 029},
    {0,  000, 000},
    {2,  001, 001},
    {12, 002, 035, 036, 002, 051, 053, 091, 002, 011, 022, 040, 035},
    {16, 094, 001, 101, 001, 116, 001, 117, 001, 004, 001, 025, 001, 030, 001, 037, 001},
    {16, 091, 038, 115, 043, 085, 006, 079, 007, 078, 008, 077, 018, 079, 018, 086, 024},
    {2,  026, 026},
    {16, 012, 001, 019, 096, 031, 064, 025, 096, 038, 001, 051, 096, 057, 001, 066, 096},
    {16, 067, 001, 068, 096, 072, 001, 074, 008, 075, 096, 076, 008, 079, 001, 084, 096},
    {12, 001, 003, 008, 007, 008, 010, 008, 016, 023, 031, 040, 044},
    {2,  001, 001},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {18, 092, 092, 081, 081, 067, 067, 066, 066, 061, 061, 053, 053, 051, 051, 047, 047, 043, 043},
    {16, 054, 001, 058, 001, 066, 001, 072, 001, 075, 001, 087, 001, 101, 001, 036, 001},
    {16, 041, 010, 041, 020, 049, 011, 056, 123, 110, 113, 112, 116, 114, 118, 119, 101},
    {2,  001, 001},
    {2,  001, 001},
    {16, 037, 037, 042, 042, 053, 053, 062, 062, 007, 007, 010, 010, 011, 011, 015, 015},
    {16, 119, 001, 122, 001, 008, 001, 010, 001, 013, 001, 025, 001, 027, 001, 032, 001},
    {16, 036, 001, 040, 001, 043, 001, 053, 001, 072, 001, 075, 001, 095, 001, 101, 001},
    {2,  001, 001},
    {16, 037, 037, 031, 031, 023, 023, 022, 022, 007, 007, 124, 124, 114, 114, 112, 112},
    {0,  000, 000},
    {2,  001, 001},
    {2,  001, 001},
    {16, 051, 001, 058, 008, 060, 001, 068, 008, 002, 001, 013, 008, 022, 001, 036, 008},
    {0,  000, 000},
    {2,  112, 020},
    {2,  000, 001},
    {2,  000, 001},
    {2,  000, 001},
    {2,  000, 001},
    {16, 081, 008, 032, 008, 043, 008, 067, 008, 011, 011, 008, 090, 002, 002, 083, 013},
    {2,  001, 001},
    {16, 058, 001, 069, 001, 075, 077, 018, 001, 032, 001, 045, 045, 013, 001, 034, 001},
    {16, 058, 001, 069, 001, 075, 077, 018, 001, 032, 001, 045, 045, 013, 001, 034, 001},
    {16, 067, 076, 068, 076, 078, 076, 002, 076, 016, 076, 018, 076, 025, 076, 045, 088},
    {16, 061, 008, 032, 008, 043, 008, 067, 008, 011, 011, 008, 090, 002, 002, 083, 013},
    {0,  000, 000},
    {0,  000, 000},
    {2,  001, 001},
    {2,  036, 036},
    {0,  000, 000},
    {0,  000, 000}
};

/*
    native GetVehicleParams(vehicleid, type);
	native SetVehicleParams(vehicleid, type, status, delay = 0);
	native GetVehicleBoot(vehicleid, &Float:x, &Float:y, &Float:z);
	native GetVehicleHood(vehicleid, &Float:x, &Float:y, &Float:z);
	native GetVehicleRoof(vehicleid, &Float:x, &Float:y, &Float:z);
	native GetVehicleRandomColors(modelid, &color1, &color2);
	native GetVehicleColor(vehicleid, &color1, &color2);
	native GetNearestVehicle(vehicleid);
	native GetVehiclePaintjob(vehicleid);
	native GetVehicleDriver(vehicleid);
	native GetVehicleTopSpeed(vehicleid);
	native GetVehicleInterior(vehicleid);
	native GetVehicleSeats(vehicleid);
	native GetVehicleModelSeats(modelid);
	native ResetVehiclePaintjob(vehicleid);
	native IsVehicleSeatOccupied(vehicleid, seatid);
	native IsValidVehicle(vehicleid);
*/

forward EVF_SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
public EVF_SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
{
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
}

stock static ResetVehicleProperties(vehicleid)
{
    s_VehicleTrailerID[vehicleid] = INVALID_VEHICLE_ID;

	for (new i = 0; i < _:e_VehicleProperties; i ++)
	{
	    deleteproperty(4, !"", (vehicleid << 2) + i);
	}
}

stock static SetVehiclePropertyValue(vehicleid, type, value)
{
	new
	    string[12];

	format(string, sizeof(string), "%d", value);

	setproperty(4, !"", ((vehicleid << 2) + type), string);
}

stock static GetVehiclePropertyValue(vehicleid, type)
{
	new
	    string[12];

	getproperty(4, !"", ((vehicleid << 2) + type), string);

	return strval(string);
}

stock static IsVehiclePropertySet(vehicleid, type)
{
    return existproperty(4, !"", (vehicleid << 2) + type);
}

stock GetVehicleRandomColors(modelid, &color1, &color2)
{
	new
		index = 0;

	color1 = 0;
	color2 = 0;

	if (!(400 <= modelid <= 611))
	{
	    return 0;
	}
	else
	{
		modelid -= 400;

		if (!s_CarColors[modelid][0])
		{
		    return 0;
		}
		else if (s_CarColors[modelid][0] == 2)
		{
		    color1 = s_CarColors[modelid][1];
		    color2 = s_CarColors[modelid][2];
		}
		else
		{
			index = random(s_CarColors[modelid][0]) & -2;

			color1 = s_CarColors[modelid][++index];
			color2 = s_CarColors[modelid][++index];
		}
	}
	return 1;
}

stock GetVehicleParams(vehicleid, type)
{
	new
		params[7]
	;
	GetVehicleParamsEx(vehicleid, params[0], params[1], params[2], params[3], params[4], params[5], params[6]);

	return (!(params[type] <= 0));
}

stock SetVehicleParams(vehicleid, type, status, delay = 0)
{
	new
		params[7];

    if (GetVehicleParamsEx(vehicleid, params[0], params[1], params[2], params[3], params[4], params[5], params[6]))
	{
		params[type] = status;

		if (delay > 0)
		{
			SetTimerEx("EVF_SetVehicleParamsEx", delay, false, "iiiiiiii", vehicleid, params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
		}
		else
		{
			SetVehicleParamsEx(vehicleid, params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
		}
		return 1;
	}
	return 0;
}

stock GetVehicleOffset(vehicleid, type, &Float:x, &Float:y, &Float:z)
{
    new Float:fPos[4], Float:fSize[3];

	if (!IsValidVehicle(vehicleid))
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;

		return 0;
	}
	else
	{
		GetVehiclePos(vehicleid, fPos[0], fPos[1], fPos[2]);
		GetVehicleZAngle(vehicleid, fPos[3]);
		GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, fSize[0], fSize[1], fSize[2]);

		switch (type)
		{
		    case VEHICLE_OFFSET_BOOT:
		    {
				x = fPos[0] - (floatsqroot(fSize[1] + fSize[1]) * floatsin(-fPos[3], degrees));
				y = fPos[1] - (floatsqroot(fSize[1] + fSize[1]) * floatcos(-fPos[3], degrees));
 				z = fPos[2];
			}
			case VEHICLE_OFFSET_HOOD:
			{
			    x = fPos[0] + (floatsqroot(fSize[1] + fSize[1]) * floatsin(-fPos[3], degrees));
				y = fPos[1] + (floatsqroot(fSize[1] + fSize[1]) * floatcos(-fPos[3], degrees));
	 			z = fPos[2];
			}
			case VEHICLE_OFFSET_ROOF:
			{
			    x = fPos[0];
			    y = fPos[1];
			    z = fPos[2] + floatsqroot(fSize[2]);
			}
		}
	}
	return 1;
}

stock GetNearestVehicle(playerid)
{
 	new
	 	Float:fX,
	 	Float:fY,
	 	Float:fZ,
	 	Float:fSX,
	    Float:fSY,
		Float:fSZ,
		Float:fRadius;

	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i ++)
	{
	    if (!IsVehicleStreamedIn(i, playerid))
		{
			continue;
	    }
	    else
	    {
			GetVehiclePos(i, fX, fY, fZ);

			GetVehicleModelInfo(GetVehicleModel(i), VEHICLE_MODEL_INFO_SIZE, fSX, fSY, fSZ);

			fRadius = floatsqroot((fSX + fSX) + (fSY + fSY));

			if (IsPlayerInRangeOfPoint(playerid, fRadius, fX, fY, fZ) && GetPlayerInterior(playerid) == GetVehicleInterior(i) && GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(i))
			{
				return i;
			}
		}
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleDriver(vehicleid)
{
	for (new i = 0; i < MAX_PLAYERS; i ++)
	{
	    if (GetPlayerState(i) == PLAYER_STATE_DRIVER && IsPlayerInVehicle(i, vehicleid))
		{
			return i;
		}
	}
	return INVALID_PLAYER_ID;
}

stock IsVehicleSeatOccupied(vehicleid, seatid)
{
	if (!GetVehicleModel(vehicleid))
	{
		return 0;
	}
	else
	{
		for (new i = 0; i < MAX_PLAYERS; i ++)
		{
	    	if (IsPlayerInVehicle(i, vehicleid) && GetPlayerVehicleSeat(i) == seatid)
			{
				return 1;
			}
		}
	}
	return 0;
}

stock GetVehicleNextSeat(vehicleid, passenger = 1)
{
	new
	    seats = GetVehicleSeats(vehicleid);

	if (seats > 1)
	{
	    for (new i = passenger; i < seats; i ++)
		{
		    if (!IsVehicleSeatOccupied(vehicleid, i))
			{
				return i;
			}
		}
	}
	return INVALID_SEAT_ID;
}

stock GetVehicleModelSeats(modelid)
{
    static const s_VehicleSeats[] =
	{
		4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2, 1, 4, 4, 4, 2,
		1, 7, 1, 2, 2, 0, 2, 7, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 0, 0, 2, 1, 1, 1, 2, 2, 2, 4,
		4, 2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2, 2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2,
		2, 4, 2, 4, 1, 2, 2, 2, 4, 4, 2, 2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2,
		1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 7, 7, 1, 4, 2, 2, 2, 2, 2, 4, 4,
		2, 2, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2,
		4, 4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 7, 2, 2, 1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 2, 0, 0, 0,
		4, 0, 0
	};
	return (modelid < 400 || modelid > 611) ? (0) : (s_VehicleSeats[(modelid - 400)]);
}

stock Float:GetVehicleTopSpeed(vehicleid)
{
	new model = GetVehicleModel(vehicleid);

	if (model)
 	{
  		return float(s_TopSpeed[(model - 400)]);
    }
   	return 0.0;
}

stock GetVehicleInterior(vehicleid)
{
	if (IsValidVehicle(vehicleid))
	{
	    return GetVehiclePropertyValue(vehicleid, e_VEHICLE_INTERIOR);
	}
	return 0;
}

stock GetVehicleColor(vehicleid, &color1, &color2)
{
	if (IsValidVehicle(vehicleid))
	{
	    color1 = GetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_1);
	    color2 = GetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_2);
	    return 1;
	}
	return 0;
}

stock GetVehiclePaintjob(vehicleid)
{
	if (IsValidVehicle(vehicleid))
	{
	    if (IsVehiclePropertySet(vehicleid, e_VEHICLE_PAINTJOB))
	    {
		    return GetVehiclePropertyValue(vehicleid, e_VEHICLE_PAINTJOB);
		}
		else
		{
			return INVALID_PAINTJOB_ID;
		}
	}
	return 0;
}

stock ResetVehiclePaintjob(vehicleid)
{
	if (IsValidVehicle(vehicleid))
	{
	    ChangeVehiclePaintjob(vehicleid, INVALID_PAINTJOB_ID);
	    SetVehiclePropertyValue(vehicleid, e_VEHICLE_PAINTJOB, INVALID_PAINTJOB_ID);
	    return 1;
	}
	return 0;
}

stock EVF_LinkVehicleToInterior(vehicleid, interiorid)
{
	new
	    ret = LinkVehicleToInterior(vehicleid, interiorid);

	if (ret)
	{
		SetVehiclePropertyValue(vehicleid, e_VEHICLE_INTERIOR, interiorid);
	}
	return ret;
}

stock EVF_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:a, color1, color2, respawn_delay, addsiren = 0)
{
	new vehicleid = INVALID_VEHICLE_ID;

	if (400 <= modelid <= 611)
	{
	    new
			randcolor1,
			randcolor2;

	    if (GetVehicleRandomColors(modelid, randcolor1, randcolor2))
	    {
	        if (color1 == -1)
	        {
				color1 = randcolor1;
			}
			if (color2 == -1)
			{
				color2 = randcolor2;
			}
		}
  		vehicleid = CreateVehicle(modelid, x, y, z, a, color1, color2, respawn_delay, addsiren);

	    if (vehicleid != INVALID_VEHICLE_ID)
	    {
			ResetVehicleProperties(vehicleid);

	        SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_1, color1);
	        SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_2, color2);

			CallLocalFunction("OnVehicleCreated", "i", vehicleid);
		}
	}
	return vehicleid;
}

stock EVF_DestroyVehicle(vehicleid)
{
	if (IsValidVehicle(vehicleid))
	{
		if (CallLocalFunction("OnVehicleDestroyed", "i", vehicleid) > 0 || funcidx("OnVehicleDestroyed") == -1)
		{
		    ResetVehicleProperties(vehicleid);

		    return DestroyVehicle(vehicleid);
	    }
	}
	return 0;
}

stock EVF_AddStaticVehicle(modelid, Float:x, Float:y, Float:z, Float:a, color1, color2)
{
	new vehicleid = INVALID_VEHICLE_ID;

	if (400 <= modelid <= 611)
	{
	    new
			randcolor1,
			randcolor2;

	    if (GetVehicleRandomColors(modelid, randcolor1, randcolor2))
	    {
	        if (color1 == -1)
	        {
				color1 = randcolor1;
			}
			if (color2 == -1)
			{
				color2 = randcolor2;
			}
		}
  		vehicleid = AddStaticVehicle(modelid, x, y, z, a, color1, color2);

	    if (vehicleid != INVALID_VEHICLE_ID)
	    {
	        ResetVehicleProperties(vehicleid);

	        SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_1, color1);
	        SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_2, color2);

			CallLocalFunction("OnVehicleCreated", "i", vehicleid);
		}
	}
	return vehicleid;
}

stock EVF_AddStaticVehicleEx(modelid, Float:x, Float:y, Float:z, Float:a, color1, color2, respawn_delay, addsiren = 0)
{
	new vehicleid = INVALID_VEHICLE_ID;

	if (400 <= modelid <= 611)
	{
	    new
			randcolor1,
			randcolor2;

	    if (GetVehicleRandomColors(modelid, randcolor1, randcolor2))
	    {
	        if (color1 == -1)
	        {
				color1 = randcolor1;
			}
			if (color2 == -1)
			{
				color2 = randcolor2;
			}
		}
  		vehicleid = AddStaticVehicleEx(modelid, x, y, z, a, color1, color2, respawn_delay, addsiren);

	    if (vehicleid != INVALID_VEHICLE_ID)
	    {
	        ResetVehicleProperties(vehicleid);

	        SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_1, color1);
	        SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_2, color2);

			CallLocalFunction("OnVehicleCreated", "i", vehicleid);
		}
	}
	return vehicleid;
}

stock EVF_ChangeVehicleColor(vehicleid, color1, color2)
{
	new
	    ret = ChangeVehicleColor(vehicleid, color1, color2);

	if (ret)
	{
	    SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_1, color1);
	    SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_2, color2);
	}
	return ret;
}

stock EVF_ChangeVehiclePaintjob(vehicleid, paintjobid)
{
	new
	    ret = ChangeVehiclePaintjob(vehicleid, paintjobid);

	if (ret)
	{
		SetVehiclePropertyValue(vehicleid, e_VEHICLE_PAINTJOB, paintjobid);
	}
	return ret;
}

public OnPlayerUpdate(playerid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
	    new
			vehicleid = GetPlayerVehicleID(playerid),
			trailerid = GetVehicleTrailer(vehicleid)
		;

		if (s_VehicleTrailerID[vehicleid] != trailerid)
	    {
	        if (trailerid != 0)
			{
				CallLocalFunction("OnTrailerHooked", "iii", playerid, vehicleid, trailerid);
			}
			else
			{
			    CallLocalFunction("OnTrailerUnhooked", "iii", playerid, vehicleid, s_VehicleTrailerID[vehicleid]);
			}
			s_VehicleTrailerID[vehicleid] = trailerid;
		}
	}
	#if defined EVF_OnPlayerUpdate
	    return EVF_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if ((hittype == BULLET_HIT_TYPE_VEHICLE) && (22 <= weaponid <= 38))
	{
	    CallLocalFunction("OnPlayerShootVehicle", "iii", playerid, hitid, weaponid);
	}
	#if defined EVF_OnPlayerWeaponShot
	    return EVF_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);
	#else
	    return 1;
	#endif
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
    SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_1, color1);
    SetVehiclePropertyValue(vehicleid, e_VEHICLE_COLOR_2, color2);

	#if defined EVF_OnVehicleRespray
	    return EVF_OnVehicleRespray(playerid, vehicleid, color1, color2);
	#else
	    return 1;
	#endif
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	SetVehiclePropertyValue(vehicleid, e_VEHICLE_PAINTJOB, paintjobid);

	#if defined EVF_OnVehiclePaintjob
	    return EVF_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	#else
	    return 1;
	#endif
}

#if defined _ALS_LinkVehicleToInterior
	#define LinkVehicleToInterior
#else
	#define _ALS_LinkVehicleToInterior
#endif

#if defined _ALS_CreateVehicle
	#define CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#if defined _ALS_DestroyVehicle
	#define DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#if defined _ALS_AddStaticVehicle
	#define AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#if defined _ALS_AddStaticVehicleEx
	#define AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#if defined _ALS_ChangeVehicleColor
	#define ChangeVehicleColor
#else
	#define _ALS_ChangeVehicleColor
#endif

#if defined _ALS_ChangeVehiclePaintjob
	#define ChangeVehiclePaintjob
#else
	#define _ALS_ChangeVehiclePaintjob
#endif

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif

#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif

#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif

#define LinkVehicleToInterior 	EVF_LinkVehicleToInterior
#define CreateVehicle 			EVF_CreateVehicle
#define DestroyVehicle          EVF_DestroyVehicle
#define AddStaticVehicle 		EVF_AddStaticVehicle
#define AddStaticVehicleEx 		EVF_AddStaticVehicleEx
#define ChangeVehicleColor      EVF_ChangeVehicleColor
#define ChangeVehiclePaintjob	EVF_ChangeVehiclePaintjob
#define OnPlayerUpdate          EVF_OnPlayerUpdate
#define OnPlayerWeaponShot      EVF_OnPlayerWeaponShot
#define OnVehicleRespray        EVF_OnVehicleRespray
#define OnVehiclePaintjob       EVF_OnVehiclePaintjob

#if defined EVF_OnPlayerUpdate
	forward EVF_OnPlayerUpdate(playerid);
#endif

#if defined EVF_OnPlayerWeaponShot
	forward EVF_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif

#if defined EVF_OnVehicleRespray
	forward EVF_OnVehicleRespray(playerid, vehicleid, color1, color2);
#endif

#if defined EVF_OnVehiclePaintjob
	forward EVF_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
#endif