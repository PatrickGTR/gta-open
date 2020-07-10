#include <discord-connector>
#include <discord_channels>
#include <dcc>

DCCMD:admins(DCC_Channel:channel, DCC_User:user, const params[])
{
    new
        string[128],
        onlineadmins = 0;
    if(channel != tester_Discord_Chat) {
        return 0;
    }
    foreach(new i : Player)
    {
        if(i != INVALID_PLAYER_ID)
        {
            if(Admin_GetPlayerLevel(i) > 0)
            {
                format(string, sizeof(string), "Admin:%p (%d) AdminLevel:%s", i, i, Admin_GetRankName(i));
                DCC_SendChannelMessage(tester_Discord_Chat, string);
                onlineadmins++;
            }
        }
    }
    if(onlineadmins == 0)
    {
        DCC_SendChannelMessage(tester_Discord_Chat, "No Admins online");
    }
    return 1;
}