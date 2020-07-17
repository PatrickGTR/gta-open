#include <YSI_Coding\y_hooks>

hook OnServerSecondUpdate()
{
    new players = 0, string[128];
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            players++;
        }
    }
    format(string, sizeof(string), "GTO (%d/50 Players)", players);
    DCC_SetBotActivity(string);
    return 1;
}