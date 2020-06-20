#include <discord>

TCMD:tchat(playerid, params[])
{
    new msg[512], msg2[512];
    if(sscanf(params, "s[128]", msg)) return SendSyntaxMsg(playerid, "/tchat <message>");
    foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID)
        {
            if(GetPlayerTester(i) || Admin_GetPlayerLevel(i) > 0)
            {    
                SendMsgF(i, COLOR_PINK, "[TESTER]: "C_WHITE"%p (%d): %s", playerid, playerid, msg);
            }
        }
    }
    format(msg2, sizeof(msg2), "```%p (%d): %s```", playerid, playerid, msg);
    DCC_SendChannelMessage(tester_Discord_Chat, msg2);
    return 1;
}