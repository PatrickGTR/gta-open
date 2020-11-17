
TCMD:tchat(playerid, params[])
{
    new msg[128];
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
    return 1;
}