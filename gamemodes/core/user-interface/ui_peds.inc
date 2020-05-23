#include <a_samp>
#include <actor_robbery>

#define MAX_PED_NAME              (60)

enum E_ACTORS_DATA
{
    E_ACTOR_DATA_SKIN,
    E_ACTOR_DATA_UNIQUEVM,
    E_ACTOR_DATA_NAME[MAX_PED_NAME],
    Float:ACTOR_POS[4],
}

static
    const DATA[][E_ACTORS_DATA] = 
{
    {81, 0, "[GYM]", {757.9487,5.4251,1000.7023,268.0144}},
    {11, 1, "[TEN GREEN BOTTLES]", {497.0593,-77.5612,998.7651,358.8423}},
    {167, 2, "[CLUCKING BELL]", {369.7043,-4.4917,1001.8589,178.9015}},
    {167, 3, "[CLUCKING BELL]", {369.7043,-4.4917,1001.8589,178.9015}},
    {167, 4, "[CLUCKING BELL]", {369.7043,-4.4917,1001.8589,178.9015}},
    {172, 5, "[BINCO]", {207.7273,-98.7015,1005.2578,177.6088}},
    {179, 6, "[AMMU]", {295.4240,-82.5273,1001.5156,358.0439}},
    {179, 7, "[AMMU]", {312.8376,-167.7640,999.5938,358.4665}},
    {64, 8, "[SEX SHOP]", {-103.9144,-24.2024,1000.7188,0.7224}},
    {64, 9, "[SEX SHOP]", {-103.9144,-24.2024,1000.7188,0.7224}},
    {50, 10, "[GAS STATION]", {-23.6437,-57.3135,1003.5469,354.8711}},
    {50, 11, "[GAS STATION]", {-23.6437,-57.3135,1003.5469,354.8711}},
    {205, 12, "[BURGER SHOT]", {376.5121,-65.8494,1001.5078,177.2327}},
    {205, 13, "[BURGER SHOT]", {376.5121,-65.8494,1001.5078,177.2327}},
    {156, 14, "[BARBER]", {408.9911,-53.8214,1001.8984,271.7742}},
    {156, 15, "[BARBER]", {408.9911,-53.8214,1001.8984,271.7742}},
    {155, 17, "[PIZZA]", {374.7137,-117.2788,1001.4922,177.7735}},
    {171, 18, "[STRIP CLUB]", {1214.8301,-15.2607,1000.9219,0.5112}},
    {187, 19, "[DISCO]", {501.7273,-19.8817,1000.6797,88.6607}},
    {194, 20, "[24/7]", {-29.1803,-186.8155,1003.5469,0.7225}},
    {194, 21, "[24/7]", {-29.1803,-186.8155,1003.5469,0.7225}},
    {242, 22, "[TATOO]", {-200.9247,-26.2980,1002.2734,88.6606}},
    {217, 23, "[SUBURBAN]", {203.7887,-41.6704,1001.8047,180.9928}},
    {98, 24, "[VICTIM]", {204.8536,-7.9085,1001.2109,269.7297}},
    {209, 25, "[JIM'S STICKY DONUTS]", {380.6587,-186.9554,1000.6328,89.6240}},
    {211, 28, "[PROLAPS]", {206.9888,-127.8065,1003.5078,173.6375}},
    {228, 29, "[ZIP]", {161.2677,-81.1919,1001.8047,183.2488}},
    {11, 31,  "[CASINO]", {1141.1563,-1.6102,1000.6797,90.3758}}
};

hook OnGameModeInit() {
    new 
        Float:pedX,
        Float:pedY,
        Float:pedZ,
        Float:pedAng,
        pedSkin,
        pedVM;

    for(new i = 0; i < sizeof(DATA); i++) {
        pedX = DATA[i][ACTOR_POS][0];
		pedY = DATA[i][ACTOR_POS][1];
		pedZ = DATA[i][ACTOR_POS][2];
        pedAng = DATA[i][ACTOR_POS][3];
        pedSkin = DATA[i][E_ACTOR_DATA_SKIN];
        pedVM = DATA[i][E_ACTOR_DATA_UNIQUEVM];

        Robbery_CreateActor(pedSkin, pedX, pedY, pedZ, pedAng, pedVM, 500, 3000);
    }
}

public OnPlayerStartRobbery(playerid, actorid, robbed_recently)
{
    if(robbed_recently)
    {
        SendServerMsg(playerid, "This store have been robbed recently!");
        return 0;
    }
    return 1;
}

public OnPlayerFinishRobbery(playerid, actorid, robbedmoney, type)
{
    switch(type)
    {
        case TYPE_SUCCESS:
        {
            SendServerMsgF(playerid, "You've robbed this store succesfully %d", robbedmoney);
            GivePlayerMoney(playerid, robbedmoney);
        }
        case TYPE_FAILED:
        {
            SendServerMsg(playerid, "Robbery failed cashier refused to give money!");
        }
        case TYPE_UNFINISHED:
        {
            SendServerMsg(playerid, "You have gone too far away from the actor, he managed to call 911! RUN!");
        }
    }
    GivePlayerWantedLevel(playerid, 2);
    return 1;
}