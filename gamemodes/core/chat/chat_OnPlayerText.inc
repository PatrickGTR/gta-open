static
    chat_Cooldown[MAX_PLAYERS],
    chat_Count[MAX_PLAYERS],
    chat_LastMessage[MAX_PLAYERS][144];

public OnPlayerText(playerid, text[])
{
    if(Mute_PlayerHas(playerid)) {
        SendErrorMsgF(playerid, "You can not speak in global chat, you have been muted for ~r~%i ~w~seconds!", Mute_GetPlayerDuration(playerid));
        return 0;
    }

    if(!Player_IsLoggedIn(playerid)) {
        SendErrorMsg(playerid, "You need to login before you can speak.");
        return 0;
    }

    if(gettime() < chat_Cooldown[playerid]) {
        chat_Count[playerid] ++;

        if(3 <= chat_Count[playerid] < 10) {
            SendServerMsg(playerid, "Do not spam the chat, or you'll be muted!");
            return 0;
        }
        if(chat_Count[playerid] >= 10) {
            chat_Count[playerid] = 0;
            Mute_ToggleForPlayer(playerid, true, 60);
            SendServerMsgF(playerid, "You have been muted for "C_GREY"%i "C_WHITE"seconds for spamming the chat", Mute_GetPlayerDuration(playerid));
            return 0;
        }
    }
    else {
        if(chat_Count[playerid] > 0) {
            chat_Count[playerid] --;
        }
    }


    new
        processedMessage[144];

    ExpandMentions(text, processedMessage, sizeof(processedMessage), -1);

    // User can not send the same message twice.
    if (!isnull(chat_LastMessage[playerid]) && !strcmp(chat_LastMessage[playerid], processedMessage, true, 144)) {
        SendErrorMsg(playerid, "Do not repeat the same message.");
        return 0;
    }

    strcpy(chat_LastMessage[playerid], processedMessage, 144);


    // Police Radio
    if(processedMessage[0] == '!') {
        if(!Player_GetClass(playerid)) {
            return 0;
        }

        foreach(new i : Player) {
            if(Player_GetClass(i) != TEAM_POLICE) {
                continue;
            }

            SendMsgF(i, COLOR_BLUE, "(radio) officer %p: "C_WHITE"%s", playerid, processedMessage[1]);
        }
        return 0;
    }

    // Normal Global Message
    SendMsgAllF(GetPlayerColor(playerid), "[%i] %p "C_WHITE": %s", playerid, playerid, processedMessage);

    chat_Cooldown[playerid] = gettime() + 2;
    return 0;
}