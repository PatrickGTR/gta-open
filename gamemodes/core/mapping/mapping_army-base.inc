#include <YSI_Coding\y_hooks>

static 
    ArmyGateFront,
    bool:GateOpenFront,
    ArmyGateBack,
    bool:GateOpenBack
;

hook OnGameModeInit()
{
    CreateDynamicObject(8210,1238.5430,-2069.7080,58.7460,-1.5000,0.0000,89.4000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1238.3669,-2005.0470,59.0070,1.1000,0.0000,90.9000, 0, 0, -1,200.0,200.0);
    ArmyGateFront = CreateDynamicObject(19912,1239.2260,-2030.2720,61.5380,0.0000,0.0000,88.9000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1211.3690,-2097.0911,58.5630,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1205.4290,-2097.0911,65.6230,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1162.3280,-2097.0911,65.6230,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1156.3571,-2097.0911,72.6430,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1125.4890,-2097.0911,72.6730,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1125.4890,-2097.0911,65.5130,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    ArmyGateBack = CreateDynamicObject(19912,1097.9821,-2097.4470,66.2130,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1058.4900,-2097.0911,65.5130,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1058.4900,-2097.0911,58.5330,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1058.4900,-2097.0911,51.4930,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1058.4900,-2097.0911,44.5430,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1058.4900,-2097.0911,37.4830,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1066.3220,-2069.5100,57.9930,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1066.3220,-2069.5100,51.0730,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1066.3220,-2069.5100,44.0930,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1071.6000,-2026.5330,57.9930,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1071.6000,-2026.5330,50.8930,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1071.6000,-2026.5330,43.9530,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1210.5229,-1977.5930,58.9430,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1204.5530,-1977.6350,66.0530,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1158.5250,-1977.9550,58.9130,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1158.5250,-1977.9550,65.9930,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1106.9760,-1978.3140,58.9130,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1106.9760,-1978.3140,65.9730,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1104.0950,-1978.3340,51.8930,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1103.9050,-1978.3361,44.9530,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1074.2780,-2004.6970,50.8930,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1074.2780,-2004.6970,57.8730,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1074.2780,-2004.6970,43.8530,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1103.9050,-1978.3361,37.9830,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1074.2780,-2004.6970,43.8530,0.0000,0.0000,-97.0000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1104.0950,-1978.3340,58.9630,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1238.4950,-2005.0470,65.6950,1.1000,0.0000,90.9000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1238.3580,-2069.7080,65.8040,-1.5000,0.0000,89.4000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1238.5470,-2051.6780,65.8040,-1.5000,0.0000,89.4000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1210.5081,-1977.5870,66.0530,0.0000,0.0000,-179.6000, 0, 0, -1,200.0,200.0);
    CreateDynamicObject(8210,1108.1639,-2097.0220,72.6730,0.0000,0.0000,0.0000, 0, 0, -1,200.0,200.0);
    CreateObject(16093, 1195.86780, -2054.47852, 72.20000,   0.00000, 0.00000, 0.00000);
    CreateObject(19909, 1153.17407, -2052.48218, 68.11590,   0.00000, 0.00000, 0.00000);
    CreateObject(14877, 1189.51563, -2057.21143, 70.40280,   0.00000, 1.00000, 89.70803);
    CreateObject(14877, 1202.56885, -2051.46240, 70.40280,   0.00000, 1.00000, 269.58899);
    CreateObject(19909, 1197.30457, -2019.84021, 68.41891,   0.00000, 0.00000, 0.00000);
    CreateObject(18850, 1154.47510, -2018.90112, 64.17500,   0.00000, 0.00000, 0.00000);
    CreateObject(5820, 1161.84717, -2001.30713, 72.56483,   0.00000, 0.00000, 178.78679);
    CreateObject(18850, 1154.77258, -2051.72559, 64.06355,   0.00000, 0.00000, 0.00000);
    CreateObject(5820, 1162.37366, -2069.41357, 72.52350,   0.00000, 0.00000, 357.13467);
    CreateObject(19909, 1153.12512, -2019.07092, 68.11590,   0.00000, 0.00000, 0.00000);
    CreateObject(2208, 1155.78650, -2048.90942, 68.11138,   0.00000, 0.00000, 90.09866);
    CreateObject(2208, 1155.79773, -2051.68335, 68.11138,   0.00000, 0.00000, 90.09866);
    CreateObject(2208, 1155.79773, -2051.68335, 68.11138,   0.00000, 0.00000, 90.09866);
    CreateObject(2208, 1155.83167, -2054.45142, 68.11138,   0.00000, 0.00000, 90.09866);
    CreateObject(2208, 1155.81653, -2057.25146, 68.11138,   0.00000, 0.00000, 90.09866);
    CreateObject(2208, 1155.81531, -2058.18384, 68.11138,   0.00000, 0.00000, 90.09866);
    CreateObject(16782, 1159.17615, -2052.83521, 70.56110,   0.00000, 0.00000, 179.74933);
    CreateObject(2357, 1155.82922, -2015.99780, 68.56161,   0.00000, 0.00000, 89.12450);
    CreateObject(2357, 1155.75598, -2021.86218, 68.56161,   0.00000, 0.00000, 89.12450);
    CreateObject(11736, 1155.81409, -2017.67993, 69.00550,   0.00000, 0.00000, 0.00000);
    CreateObject(11736, 1155.88928, -2014.13794, 69.00550,   0.00000, 0.00000, 0.00000);
    CreateObject(11738, 1155.82983, -2017.26721, 69.00550,   0.00000, 0.00000, 0.00000);
    CreateObject(11738, 1155.91931, -2014.54529, 69.00550,   0.00000, 0.00000, 0.00000);
    CreateObject(19816, 1155.79285, -2015.13770, 69.10550,   0.00000, -89.00000, 1.78533);
    CreateObject(19816, 1155.76648, -2016.92981, 69.10550,   0.00000, -89.00000, 358.47086);
    CreateObject(11747, 1155.86621, -2016.02649, 69.00550,   0.00000, 0.00000, 0.00000);
    CreateObject(11745, 1155.77063, -2020.39880, 69.10550,   0.00000, 0.00000, 0.00000);
    CreateObject(11745, 1155.79236, -2021.42407, 69.10550,   0.00000, 0.00000, 0.00000);
    CreateObject(11745, 1155.75415, -2022.58606, 69.10550,   0.00000, 0.00000, 0.00000);
    CreateObject(11745, 1155.81409, -2023.51416, 69.10550,   0.00000, 0.00000, 0.00000);
    CreateObject(2977, 1202.88416, -2014.11292, 68.25899,   0.00000, 0.00000, 0.00000);
    CreateObject(2977, 1201.43030, -2014.13489, 68.25899,   0.00000, 0.00000, 0.00000);
    CreateObject(2977, 1200.05078, -2014.07117, 68.25899,   0.00000, 0.00000, 0.00000);
    CreateObject(964, 1202.70447, -2024.93359, 68.41618,   0.00000, 0.00000, 0.00000);
    CreateObject(964, 1201.09851, -2024.94922, 68.41618,   0.00000, 0.00000, 0.00000);
    CreateObject(964, 1199.65955, -2025.02942, 68.41618,   0.00000, 0.00000, 0.00000);
    CreateObject(2035, 1199.53186, -2024.82971, 69.53270,   0.00000, 0.00000, -164.00000);
    CreateObject(2036, 1201.09033, -2024.96509, 69.41390,   0.00000, 0.00000, -120.00000);
    CreateObject(2040, 1203.07825, -2024.85181, 69.46830,   0.00000, 0.00000, 0.00000);
    CreateObject(2040, 1202.69800, -2024.86511, 69.46830,   0.00000, 0.00000, 0.00000);
    CreateObject(2040, 1202.27625, -2024.86182, 69.46830,   0.00000, 0.00000, 0.00000);
    CreateObject(11729, 1203.34290, -2016.42053, 68.37388,   0.00000, 0.00000, 269.88568);
    CreateObject(11729, 1203.40906, -2018.35315, 68.37388,   0.00000, 0.00000, 269.98465);
    CreateObject(11729, 1203.44604, -2020.05127, 68.37388,   0.00000, 0.00000, 269.98465);
    CreateObject(11729, 1203.41626, -2022.01208, 68.37388,   0.00000, 0.00000, 269.17252);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    RemoveBuildingForPlayer(playerid, 661, 1159.9766, -2075.1563, 67.1484, 0.25);
    RemoveBuildingForPlayer(playerid, 618, 1155.3672, -2072.5547, 67.8594, 0.25);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_NO))
    {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 1240.9739, -2035.3715, 59.9941) && Player_GetClass(playerid) == TEAM_ARMY)
        {
            if(GateOpenFront == false)
            {
                MoveDynamicObject(ArmyGateFront, 1239.43347, -2021.10034, 61.53800, 3.0, 0.00000, 0.00000, 88.90000);
                GateOpenFront = true;
            }
            else if(GateOpenFront == true)
            {
                MoveDynamicObject(ArmyGateFront, 1239.2260, -2030.2720, 61.5380, 3.0, 0.0000,0.0000,88.9000);
                GateOpenFront = false;
            }
        }
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 1086.5114, -2098.7629, 64.5963) && Player_GetClass(playerid) == TEAM_ARMY)
        {
            if(GateOpenBack == false)
            {
                MoveDynamicObject(ArmyGateBack, 1109.16309, -2097.43262, 66.21300, 3.0, 0.00000, 0.00000, 0.00000);
                GateOpenBack = true;
            }
            else if(GateOpenBack == true)
            {
                MoveDynamicObject(ArmyGateBack, 1097.9821, -2097.4470, 66.2130, 3.0, 0.0000, 0.0000, 0.0000);
                GateOpenBack = false;
            }
        }
    }
    return 1;
}