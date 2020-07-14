#include <discord-connector>

#include <dcmd_admins>
#include <dcmd_kick>
#include <dcmd_discordann>
#include <dcmd_players>

#include <discord_channels>
#include <YSI_Coding\y_hooks>

hook DCC_OnMessageCreate(DCC_Message:message)
{
    new realMsg[100];
    DCC_GetMessageContent(message, realMsg, 100);
    new bool:IsBot;
    new DCC_Channel:channel;
    DCC_GetMessageChannel(message, channel);
    new DCC_User:author;
    DCC_GetMessageAuthor(message, author);
    DCC_IsUserBot(author, IsBot);
    if(channel == tester_Discord_Chat && !IsBot)
    {
        new user_name[32 + 1];
        DCC_GetUserName(author, user_name, 32);
        foreach(new i : Player)
        {
            if(i != INVALID_PLAYER_ID)
            {
                if(GetPlayerTester(i) || Admin_GetPlayerLevel(i) > 0)
                {
                    SendMsgF(i, COLOR_GREEN, "[#tester-chat-logs] %s: "C_WHITE"%s", user_name, realMsg);
                }
            }
        }
    }
    if(channel == admin_Discord_Chat && !IsBot)
    {
        new user_name[32 + 1];
        DCC_GetUserName(author, user_name, 32);
        foreach(new i : Player)
        {
            if(i != INVALID_PLAYER_ID)
            {
                if(Admin_GetPlayerLevel(i) > 0)
                {
                    SendMsgF(i, COLOR_GREEN, "[#admin-chat-logs] %s: "C_WHITE"%s", user_name, realMsg);
                }
            }
        }
    }
    if(channel == serverecho_Discord_Chat && !IsBot)
    {
        new user_name[32 + 1];
        DCC_GetUserName(author, user_name, 32);
        foreach(new i : Player)
        {
            if(i != INVALID_PLAYER_ID)
            {
                SendMsgF(i, COLOR_GREEN, "[#server-echo] %s: "C_WHITE"%s", user_name, realMsg);
            }
        }
    }
    return 1;
}

hook OnPlayerText(playerid, text[])
{
    new msg[128];
    format(msg, sizeof(msg), "```%p (%d): %s```", playerid, playerid, text);
    DCC_SendChannelMessage(serverecho_Discord_Chat, msg);
    return 1;
}

ACMD:[1]a(playerid, params[])
{
	new msg[128], msg2[128];
	if(sscanf(params, "s[128]", msg)) return SendSyntaxMsg(playerid, "/a [message]");
	foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID)
        {
            if(Admin_GetPlayerLevel(i) > 0)
            {    
                SendMsgF(i, COLOR_BLUE, "[ADMIN] %p (%d) "C_WHITE": %s", playerid, playerid, msg);
            }
        }
    }
	format(msg2, sizeof(msg2), "```%p (%d): %s```", playerid, playerid, msg);
    DCC_SendChannelMessage(admin_Discord_Chat, msg2);
	return 1;
}

stock SendAdminCmdUsage(playerid, const cmd[], const cmdparam[])
{
    new msg2[250];
    if(Admin_GetPlayerLevel(playerid) == 5) {
        return 0;
    }
    foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID && Admin_GetPlayerLevel(i) > 0)
        {
            SendMsgF(i, COLOR_LIGHTGREEN, "[ADMINCMD]: %p (%d) used %s %s", playerid, playerid, cmd, cmdparam);
        }
    }
    format(msg2, sizeof(msg2), "[ADMINCOMMAND]:%p (%d) used %s %s", playerid, playerid, cmd, cmdparam);
    DCC_SendChannelMessage(cmdlogs_Discord_Chat, msg2);
    return 1;
}
