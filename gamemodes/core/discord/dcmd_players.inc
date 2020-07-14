#include <discord-connector>
#include <discord_channels>
#include <dcc>

DCCMD:players(DCC_Channel:channel, DCC_User:user, const params[])
{
    new onlineplayers = 0,
    string[251];
    if(channel != serverecho_Discord_Chat) {
        return DCC_SendChannelMessage(channel, "[ERROR]: You can only use this in #server-echo");
    }
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            format(string, sizeof(string), "%p (%d)", i, i);
            DCC_SendChannelMessage(channel, string);
            onlineplayers++;
        }
    }
    if(onlineplayers == 0) {
        DCC_SendChannelMessage(channel, "There is no online Players");
    }
    else if(onlineplayers != 0) {
        format(string, sizeof(string), "There are %d online Players", onlineplayers);
        DCC_SendChannelMessage(channel, string);
    }
    return 1;
}