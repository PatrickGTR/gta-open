#include <discord-connector>
#include <discord_channels>
#include <dcc>

DCCMD:ingamekick(DCC_Channel:channel, DCC_User:user, const params[])
{
    new 
        target,
        string[128],
        reason[128];
    if(channel != cmdexecute_Discord_Chat) {
        return 0;
    }
    if(sscanf(params, "us[128]", target, reason)) return DCC_SendChannelMessage(cmdexecute_Discord_Chat, "```/ingamekick (name/id) (reason)```");
    if(!IsPlayerConnected(target)) return DCC_SendChannelMessage(cmdexecute_Discord_Chat, "```Player is not connected```");
    SendMsgAllF(COLOR_MODERATION, "[ProHelper]: %p (%d) has been kicked for %s", target, target, reason);
    format(string, sizeof(string), "You have kicked %p (%d)", target, target);
    DCC_SendChannelMessage(cmdexecute_Discord_Chat, string);
    defer KickTimer(target);
    return 1;
}