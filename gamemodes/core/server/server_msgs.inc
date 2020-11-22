
#define DEFAULT_MESSAGE_TIME (1000 * 60) * 3
#define MAX_MESSAGES (20)

static
    MessageCount = 0,
    MessageTime = DEFAULT_MESSAGE_TIME, // 3 minutes by default.
    Messages[MAX_MESSAGES][128];

Message_SetTime(minutes) {
    MessageTime = (1000 * 60) * minutes;
}

Message_Add(const message[]) {

    if(MessageCount > MAX_MESSAGES) {
        Logger_Log("[Message_Add / server_msgs.inc] Could not add message, limit reached.");
        return 0;
    }

    if(strlen(Messages[MessageCount]) > 128) {
        Logger_Log("[Message_Add / server_msgs.inc] Could not add message, more than 128 characters.");
        return 0;
    }


    Logger_Dbg(SERVER_DEBUG_HANDLER, "[Message_Add / server_msgs.inc] Message added",
        Logger_S("message", message),
        Logger_I("id", MessageCount)
    );

    strcpy(Messages[MessageCount], message, 128);

    MessageCount ++;
    return 1;
}

static
    lastIndex = -1;
task AutoSendMessage[MessageTime]() {

    new
        idx = random(MessageCount);

    // regenerate new id.
    if(idx == lastIndex) {
        idx = random(MessageCount);
    }

    SendMsgAllF(COLOR_RED, "%s", Messages[clamp(idx, 0, MessageCount)]);

    lastIndex = idx;
}

CMD:forcemsg(playerid, params[]) {
    AutoSendMessage();
    return 1;
}