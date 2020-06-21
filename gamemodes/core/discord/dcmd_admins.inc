#include <discord-connector>
#include <discord_channels>

#define CMD_PREFIX "/"
#define BOT_CHANNEL "tester-chat-logs"
#define BOT_NAME "ProHelper"
#define CHANNEL_ID "723648604945776721"

#include <dcc>

public OnDCCommandPerformed(const args[], success)
{
    if(!success) {
        return SendDC(CHANNEL_ID, "```css\n'%s' command not found, try again...```", args[1]);
    }
    return 1;
}

DC_CMD:admins(DCC_User:user, const args[])
{
    new onlineadmins = 0;
    foreach(new i : Player)
    {
        if(i != INVALID_PLAYER_ID)
        {
            if(Admin_GetPlayerLevel(i) > 0)
            {
                SendDC(CHANNEL_ID, "Admin:%p (%d) AdminLevel:%s", i, i, Admin_GetRankName(i));
                onlineadmins++;
            }
        }
    }
    if(onlineadmins == 0)
    {
        SendDC(CHANNEL_ID, "No Admins Online!");
    }
    return 1;
}