#include <discord-connector>
#include <discord_channels>

#define CMD_PREFIX "!"
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

DC_CMD:m(DCC_User:user, const args[])
{
    if(isnull(args)) {
        return SendDC(CHANNEL_ID, "```!m [message]```");
    }
    if(strlen(args) > 145) {
        return SendDC(CHANNEL_ID, "```Error: message too long```");
    } 

    new user_name[32 + 1];
    DCC_GetUserName(user, user_name, 32);
    SendDC(CHANNEL_ID, "```%s : %s```", user_name, args);
    return 1;
}