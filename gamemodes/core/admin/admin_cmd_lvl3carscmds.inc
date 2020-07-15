#include <YSI_Coding\y_hooks>
#define MIN_VEHI_ID		400
#define MAX_VEHI_ID		611

#define MAX_SPAWNED_VEHICLES 100
#define MAX_ADMINS_VEHICLES 100

static 
    SpawnedVehicles[MAX_SPAWNED_VEHICLES],
    SpawnedVehicleCount
;

static
    AdminVehicles[MAX_ADMINS_VEHICLES],
    AdminVehicleCount
;

new aVehicleNames[212][] = {	// Vehicle Names - Betamaster
	{"Landstalker"},
	{"Bravura"},
	{"Buffalo"},
	{"Linerunner"},
	{"Perrenial"},
	{"Sentinel"},
	{"Dumper"},
	{"Firetruck"},
	{"Trashmaster"},
	{"Stretch"},
	{"Manana"},
	{"Infernus"},
	{"Voodoo"},
	{"Pony"},
	{"Mule"},
	{"Cheetah"},
	{"Ambulance"},
	{"Leviathan"},
	{"Moonbeam"},
	{"Esperanto"},
	{"Taxi"},
	{"Washington"},
	{"Bobcat"},
	{"Mr Whoopee"},
	{"BF Injection"},
	{"Hunter"},
	{"Premier"},
	{"Enforcer"},
	{"Securicar"},
	{"Banshee"},
	{"Predator"},
	{"Bus"},
	{"Rhino"},
	{"Barracks"},
	{"Hotknife"},
	{"Trailer 1"}, //artict1
	{"Previon"},
	{"Coach"},
	{"Cabbie"},
	{"Stallion"},
	{"Rumpo"},
	{"RC Bandit"},
	{"Romero"},
	{"Packer"},
	{"Monster"},
	{"Admiral"},
	{"Squalo"},
	{"Seasparrow"},
	{"Pizzaboy"},
	{"Tram"},
	{"Trailer 2"}, //artict2
	{"Turismo"},
	{"Speeder"},
	{"Reefer"},
	{"Tropic"},
	{"Flatbed"},
	{"Yankee"},
	{"Caddy"},
	{"Solair"},
	{"Berkley's RC Van"},
	{"Skimmer"},
	{"PCJ-600"},
	{"Faggio"},
	{"Freeway"},
	{"RC Baron"},
	{"RC Raider"},
	{"Glendale"},
	{"Oceanic"},
	{"Sanchez"},
	{"Sparrow"},
	{"Patriot"},
	{"Quad"},
	{"Coastguard"},
	{"Dinghy"},
	{"Hermes"},
	{"Sabre"},
	{"Rustler"},
	{"ZR-350"},
	{"Walton"},
	{"Regina"},
	{"Comet"},
	{"BMX"},
	{"Burrito"},
	{"Camper"},
	{"Marquis"},
	{"Baggage"},
	{"Dozer"},
	{"Maverick"},
	{"News Chopper"},
	{"Rancher"},
	{"FBI Rancher"},
	{"Virgo"},
	{"Greenwood"},
	{"Jetmax"},
	{"Hotring"},
	{"Sandking"},
	{"Blista Compact"},
	{"Police Maverick"},
	{"Boxville"},
	{"Benson"},
	{"Mesa"},
	{"RC Goblin"},
	{"Hotring Racer A"}, //hotrina
	{"Hotring Racer B"}, //hotrinb
	{"Bloodring Banger"},
	{"Rancher"},
	{"Super GT"},
	{"Elegant"},
	{"Journey"},
	{"Bike"},
	{"Mountain Bike"},
	{"Beagle"},
	{"Cropdust"},
	{"Stunt"},
	{"Tanker"}, //petro
	{"Roadtrain"},
	{"Nebula"},
	{"Majestic"},
	{"Buccaneer"},
	{"Shamal"},
	{"Hydra"},
	{"FCR-900"},
	{"NRG-500"},
	{"HPV1000"},
	{"Cement Truck"},
	{"Tow Truck"},
	{"Fortune"},
	{"Cadrona"},
	{"FBI Truck"},
	{"Willard"},
	{"Forklift"},
	{"Tractor"},
	{"Combine"},
	{"Feltzer"},
	{"Remington"},
	{"Slamvan"},
	{"Blade"},
	{"Freight"},
	{"Streak"},
	{"Vortex"},
	{"Vincent"},
	{"Bullet"},
	{"Clover"},
	{"Sadler"},
	{"Firetruck LA"}, //firela
	{"Hustler"},
	{"Intruder"},
	{"Primo"},
	{"Cargobob"},
	{"Tampa"},
	{"Sunrise"},
	{"Merit"},
	{"Utility"},
	{"Nevada"},
	{"Yosemite"},
	{"Windsor"},
	{"Monster A"}, //monstera
	{"Monster B"}, //monsterb
	{"Uranus"},
	{"Jester"},
	{"Sultan"},
	{"Stratum"},
	{"Elegy"},
	{"Raindance"},
	{"RC Tiger"},
	{"Flash"},
	{"Tahoma"},
	{"Savanna"},
	{"Bandito"},
	{"Freight Flat"}, //freiflat
	{"Streak Carriage"}, //streakc
	{"Kart"},
	{"Mower"},
	{"Duneride"},
	{"Sweeper"},
	{"Broadway"},
	{"Tornado"},
	{"AT-400"},
	{"DFT-30"},
	{"Huntley"},
	{"Stafford"},
	{"BF-400"},
	{"Newsvan"},
	{"Tug"},
	{"Trailer 3"}, //petrotr
	{"Emperor"},
	{"Wayfarer"},
	{"Euros"},
	{"Hotdog"},
	{"Club"},
	{"Freight Carriage"}, //freibox
	{"Trailer 3"}, //artict3
	{"Andromada"},
	{"Dodo"},
	{"RC Cam"},
	{"Launch"},
	{"Police Car (LSPD)"},
	{"Police Car (SFPD)"},
	{"Police Car (LVPD)"},
	{"Police Ranger"},
	{"Picador"},
	{"S.W.A.T. Van"},
	{"Alpha"},
	{"Phoenix"},
	{"Glendale"},
	{"Sadler"},
	{"Luggage Trailer A"}, //bagboxa
	{"Luggage Trailer B"}, //bagboxb
	{"Stair Trailer"}, //tugstair
	{"Boxville"},
	{"Farm Plow"}, //farmtr1
	{"Utility Trailer"} //utiltr1
};

new aWeaponNames[][32] = {
	{"Unarmed (Fist)"}, // 0
	{"Brass Knuckles"}, // 1
	{"Golf Club"}, // 2
	{"Night Stick"}, // 3
	{"Knife"}, // 4
	{"Baseball Bat"}, // 5
	{"Shovel"}, // 6
	{"Pool Cue"}, // 7
	{"Katana"}, // 8
	{"Chainsaw"}, // 9
	{"Purple Dildo"}, // 10
	{"Big White Vibrator"}, // 11
	{"Medium White Vibrator"}, // 12
	{"Small White Vibrator"}, // 13
	{"Flowers"}, // 14
	{"Cane"}, // 15
	{"Grenade"}, // 16
	{"Teargas"}, // 17
	{"Molotov"}, // 18
	{" "}, // 19
	{" "}, // 20
	{" "}, // 21
	{"Colt 45"}, // 22
	{"Colt 45 (Silenced)"}, // 23
	{"Desert Eagle"}, // 24
	{"Normal Shotgun"}, // 25
	{"Sawnoff Shotgun"}, // 26
	{"Combat Shotgun"}, // 27
	{"Micro Uzi (Mac 10)"}, // 28
	{"MP5"}, // 29
	{"AK47"}, // 30
	{"M4"}, // 31
	{"Tec9"}, // 32
	{"Country Rifle"}, // 33
	{"Sniper Rifle"}, // 34
	{"Rocket Launcher"}, // 35
	{"Heat-Seeking Rocket Launcher"}, // 36
	{"Flamethrower"}, // 37
	{"Minigun"}, // 38
	{"Satchel Charge"}, // 39
	{"Detonator"}, // 40
	{"Spray Can"}, // 41
	{"Fire Extinguisher"}, // 42
	{"Camera"}, // 43
	{"Night Vision Goggles"}, // 44
	{"Infrared Vision Goggles"}, // 45
	{"Parachute"}, // 46
	{"Fake Pistol"} // 47
};


forward Float:GetXYInFrontOfPlayer2(playerid, &Float:q, &Float:w, Float:distance);
Float:GetXYInFrontOfPlayer2(playerid, &Float:q, &Float:w, Float:distance)
{
    new Float:a;
    GetPlayerPos(playerid, q, w, a);
    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    else GetPlayerFacingAngle(playerid, a);
    q += (distance * floatsin(-a, degrees));
    w += (distance * floatcos(-a, degrees));
    return a;
}

GetVehicleModelIDFromName(const vname[])
{
	for(new i = 0; i < 211; i++)
	{
		if ( strfind(aVehicleNames[i], vname, true) != -1 )
			return i + MIN_VEHI_ID;
	}
	return -1;
}

GetWeaponModelIDFromName(const wname[])
{
    for(new i = 0; i < 48; i++) {
        if (i == 19 || i == 20 || i == 21) continue;
		if (strfind(aWeaponNames[i], wname, true) != -1) {
			return i;
		}
	}
	return -1;
}

stock SpawnVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2)
{
    new v = AddStaticVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2);
    SpawnedVehicles[SpawnedVehicleCount++] = v;
	return v;
}

stock bool:IsSpawnedVehicle(vehicleid)
{
    for (new i = 0; i < MAX_SPAWNED_VEHICLES; i ++)
    {
        if (SpawnedVehicles[i] == vehicleid)
            return true;
    }
    return false;
}

stock CreateAdminVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2)
{
    new v = AddStaticVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2);
    AdminVehicles[AdminVehicleCount++] = v;
}

stock bool:IsAdminVehicle(vehicleid)
{
    for (new i = 0; i < MAX_ADMINS_VEHICLES; i ++)
    {
        if (AdminVehicles[i] == vehicleid)
            return true;
    }
    return false;
}

hook OnVehicleDeath(vehicleid, killerid)
{
    if(IsSpawnedVehicle(vehicleid))
    {
        DestroyVehicle(vehicleid);
    }
    if(IsAdminVehicle(vehicleid))
    {
        DestroyVehicle(vehicleid);
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        new vid = GetPlayerVehicleID(playerid);
        if(IsAdminVehicle(vid) && Admin_GetPlayerLevel(playerid) == 0)
        {
            GameTextForPlayer(playerid, "~r~Admin Vehicle!", 5000, 3);
            RemovePlayerFromVehicle(playerid);
        }
    }
    return 1;
}

static stock VehicleHasAPlayer(vehicleid)
{
    for(new i; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerInAnyVehicle(i))
        {
            if(GetPlayerVehicleID(i) == vehicleid)
            {
                if(GetPlayerState(i) == PLAYER_STATE_PASSENGER || GetPlayerState(i) == PLAYER_STATE_PASSENGER)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

ACMD:[3]giveweaps(playerid, params[])
{
    new target, wname[60], wid, ammo, wname2[60];
    if(sscanf(params, "us[32]i", target, wname, ammo)) return SendSyntaxMsg(playerid, "/giveweaps (name/id) (weaponname) (ammo)");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player not connected");
    }
    wid = GetWeaponModelIDFromName(wname);
    if(wid == -1) {
        wid = strval(wname);
        if(wid < 0 || wid > 47) {
            return SendErrorMsg(playerid, "Invalid Weapon Name");
        }
    }
    strcpy(wname2, aWeaponNames[wid], sizeof(wname2));
    GivePlayerWeapon(target, wid, ammo);
    SendMsgF(target, COLOR_MODERATION, "[ADMIN WEAPON]: Admin gave %s [%i ammo] to you", wname2, ammo);
    SendAdminCmdUsage(playerid, "/giveweaps", params);
	return 1;
}

ACMD:[3]veh(playerid, params[])
{
    new vname[32], color1, color2;
    new Float:x, Float:y, Float:z;
    new Float:a;
    new veh;
    if(sscanf(params, "s[32]D(1)D(color1)", vname, color1, color2)) return SendSyntaxMsg(playerid, "/veh (vehiclename) (optional:color 1) (optional:color2)");
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);
    GetXYInFrontOfPlayer2(playerid, x, y, 5.0);
    veh = GetVehicleModelIDFromName( vname );
    if(veh == -1)
    {
        veh = strval(vname);
        if(veh < 400 || veh > 611) {
            return SendErrorMsg(playerid, "Invalid Veh name");
        }
    }
    new vehid = SpawnVehicle(veh, x, y, z, a, color1, color2);
	LinkVehicleToInterior(vehid, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(vehid, GetPlayerVirtualWorld(playerid));
    SendAdminCmdUsage(playerid, "/veh", params);
    return 1;
}

ACMD:[3]aveh(playerid, params[])
{
    new vname[32], color1, color2;
    new Float:x, Float:y, Float:z;
    new Float:a;
    new vehid;
    if(sscanf(params, "s[32]D(1)D(1)", vname, color1, color2)) return SendSyntaxMsg(playerid, "/veh (vehiclename) (optional:color 1) (optional:color2)");
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);
    GetXYInFrontOfPlayer2(playerid, x, y, 5.0);
    vehid = GetVehicleModelIDFromName( vname );
    if(vehid == -1)
    {
        vehid = strval(vname);
        if(vehid < 400 || vehid > 611) {
            return SendErrorMsg(playerid, "Invalid Veh name");
        }
    }
    CreateAdminVehicle(vehid, x, y, z, a, color1, color2);
    SendAdminCmdUsage(playerid, "/aveh", params);
    return 1;
}

ACMD:[3]dav(playerid, params[])
{
    for(new i = 0; i < MAX_VEHICLES; i++)
    {
        if(IsAdminVehicle(i) && !VehicleHasAPlayer(i))
        {
            DestroyVehicle(i);
        }
    }
    SendAdminCmdUsage(playerid, "/dav", params);
    return 1;
}

ACMD:[3]rscars(playerid, params[])
{
    for(new i = GetVehiclePoolSize(); i > 0; i--)
    {
        if(IsSpawnedVehicle(i) && !VehicleHasAPlayer(i) || IsAdminVehicle(i) && !VehicleHasAPlayer(i))
        {
            DestroyVehicle(i);
        }
        else if(!IsSpawnedVehicle(i) && !VehicleHasAPlayer(i))
        {
            SetVehicleToRespawn(i);
        }
    }
    SendMsgAllF(COLOR_MODERATION, "[ADMIN RESTARTCARS]: Admin Respawned all vehicles");
    SendAdminCmdUsage(playerid, "/rscars", params);
    return 1;
}