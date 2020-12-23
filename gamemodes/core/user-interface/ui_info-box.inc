#include <YSI_Coding\y_hooks>

// Message box types
#define MAX_MSGBOX_TYPES        (2)

#define TYPE_MSGBOX             (0)
#define TYPE_INFORMATION        (1)


static
    PlayerText:caption_TD[MAX_PLAYERS][MAX_MSGBOX_TYPES],
    PlayerText:info_TD[MAX_PLAYERS][MAX_MSGBOX_TYPES],
    msg_BoxTimer[MAX_PLAYERS][MAX_MSGBOX_TYPES],
    bool:msg_BoxClick[MAX_PLAYERS][MAX_MSGBOX_TYPES],
    bool:msg_PlayerHasBox[MAX_PLAYERS][MAX_MSGBOX_TYPES]
;

hook OnPlayerConnect(playerid)
{
    for(new i = 0; i < MAX_MSGBOX_TYPES; i ++)
        msg_BoxTimer[playerid][i] = -1;

    // Middle textdraws
    caption_TD[playerid][TYPE_MSGBOX] = CreatePlayerTextDraw(playerid, 21.000000, 204.000000, "~y~~h~caption");
    PlayerTextDrawBackgroundColor(playerid, caption_TD[playerid][TYPE_MSGBOX], TD_OUTLINE_COLOUR);
    PlayerTextDrawFont(playerid, caption_TD[playerid][TYPE_MSGBOX], 3);
    PlayerTextDrawLetterSize(playerid, caption_TD[playerid][TYPE_MSGBOX], 0.449999, 1.500000);
    PlayerTextDrawColor(playerid, caption_TD[playerid][TYPE_MSGBOX], -1);
    PlayerTextDrawSetOutline(playerid, caption_TD[playerid][TYPE_MSGBOX], 0);
    PlayerTextDrawSetProportional(playerid, caption_TD[playerid][TYPE_MSGBOX], 1);
    PlayerTextDrawSetShadow(playerid, caption_TD[playerid][TYPE_MSGBOX], 1);

    info_TD[playerid][TYPE_MSGBOX] = CreatePlayerTextDraw(playerid, 22.000000, 220.000000, "This is a text. This is another one. The whole paragraph is supposed to be quite long. So, yeah!");
    PlayerTextDrawBackgroundColor(playerid, info_TD[playerid][TYPE_MSGBOX], TD_OUTLINE_COLOUR);
    PlayerTextDrawFont(playerid, info_TD[playerid][TYPE_MSGBOX], 1);
    PlayerTextDrawLetterSize(playerid, info_TD[playerid][TYPE_MSGBOX], 0.159999, 1.100000);
    PlayerTextDrawColor(playerid, info_TD[playerid][TYPE_MSGBOX], -1);
    PlayerTextDrawSetOutline(playerid, info_TD[playerid][TYPE_MSGBOX], 0);
    PlayerTextDrawSetProportional(playerid, info_TD[playerid][TYPE_MSGBOX], 1);
    PlayerTextDrawSetShadow(playerid, info_TD[playerid][TYPE_MSGBOX], 1);
    PlayerTextDrawUseBox(playerid, info_TD[playerid][TYPE_MSGBOX], 1);
    PlayerTextDrawBoxColor(playerid, info_TD[playerid][TYPE_MSGBOX], 68);
    PlayerTextDrawTextSize(playerid, info_TD[playerid][TYPE_MSGBOX], 179.000000, 0.000000);

    // Bottom textdraws
    caption_TD[playerid][TYPE_INFORMATION] = CreatePlayerTextDraw(playerid, 162.000000, 363.000000, "~y~~h~caption");
    PlayerTextDrawBackgroundColor(playerid, caption_TD[playerid][TYPE_INFORMATION], TD_OUTLINE_COLOUR);
    PlayerTextDrawFont(playerid, caption_TD[playerid][TYPE_INFORMATION], 3);
    PlayerTextDrawLetterSize(playerid, caption_TD[playerid][TYPE_INFORMATION], 0.519999, 1.899999);
    PlayerTextDrawColor(playerid, caption_TD[playerid][TYPE_INFORMATION], -1);
    PlayerTextDrawSetOutline(playerid, caption_TD[playerid][TYPE_INFORMATION], 1);
    PlayerTextDrawSetProportional(playerid, caption_TD[playerid][TYPE_INFORMATION], 1);
    PlayerTextDrawSetShadow(playerid, caption_TD[playerid][TYPE_INFORMATION], 1);

    info_TD[playerid][TYPE_INFORMATION] = CreatePlayerTextDraw(playerid, 161.000000, 393.000000, "This is the message. We tell the user what's going on here!");
    PlayerTextDrawBackgroundColor(playerid, info_TD[playerid][TYPE_INFORMATION], TD_OUTLINE_COLOUR);
    PlayerTextDrawFont(playerid, info_TD[playerid][TYPE_INFORMATION], 1);
    PlayerTextDrawLetterSize(playerid, info_TD[playerid][TYPE_INFORMATION], 0.199999, 1.199999);
    PlayerTextDrawColor(playerid, info_TD[playerid][TYPE_INFORMATION], -1);
    PlayerTextDrawSetOutline(playerid, info_TD[playerid][TYPE_INFORMATION], 1);
    PlayerTextDrawSetProportional(playerid, info_TD[playerid][TYPE_INFORMATION], 1);
    PlayerTextDrawSetShadow(playerid, info_TD[playerid][TYPE_INFORMATION], 1);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if ((newkeys & KEY_FIRE) && !(oldkeys & KEY_FIRE))
    {
        if (msg_BoxClick[playerid][TYPE_MSGBOX])
            HideMessageBox(playerid, TYPE_MSGBOX);
    }
}

// -1 = all types
forward HideMessageBox(playerid, type);
public HideMessageBox(playerid, type)
{
    switch(type)
    {
        case -1: // all
        {
            for(new i = 0; i < MAX_MSGBOX_TYPES; i ++)
            {
                if (msg_BoxTimer[playerid][i] != -1)
                {
                    KillTimer(msg_BoxTimer[playerid][i]);
                    msg_BoxTimer[playerid][i] = -1;
                }
                PlayerTextDrawHide(playerid, info_TD[playerid][i]);
                PlayerTextDrawHide(playerid, caption_TD[playerid][i]);
                msg_PlayerHasBox[playerid][i] = false;
            }
        }
        default:
        {
            PlayerTextDrawHide(playerid, info_TD[playerid][type]);
            PlayerTextDrawHide(playerid, caption_TD[playerid][type]);
            KillTimer(msg_BoxTimer[playerid][type]);
            msg_BoxTimer[playerid][type] = -1;
            msg_PlayerHasBox[playerid][type] = false;
        }
    }
    return 1;
}

stock MessageBox_Show(playerid, type, const caption[], const info[], interval = 6000)
{
    if (playerid == INVALID_PLAYER_ID)
        return 0;

    if (type < 0 || type == MAX_MSGBOX_TYPES)
        return 0;

    if (strlen(caption) < 1)
        return 0;

    if (strlen(info) < 1)
        return 0;

    switch(type)
    {
        case TYPE_MSGBOX:
        {
            PlayerTextDrawSetString(playerid, caption_TD[playerid][type], caption);
            PlayerTextDrawSetString(playerid, info_TD[playerid][type], info);
            PlayerTextDrawShow(playerid, caption_TD[playerid][type]);
            PlayerTextDrawShow(playerid, info_TD[playerid][type]);
        }
        case TYPE_INFORMATION:
        {
            PlayerTextDrawSetString(playerid, caption_TD[playerid][type], caption);
            PlayerTextDrawSetString(playerid, info_TD[playerid][type], info);
            PlayerTextDrawShow(playerid, caption_TD[playerid][type]);
            PlayerTextDrawShow(playerid, info_TD[playerid][type]);
        }
        default:
            return 0;
    }

    if (interval != -1)
    {
        if(!msg_PlayerHasBox[playerid][type]) {
            msg_BoxTimer[playerid][type] = SetTimerEx("HideMessageBox", interval, false, "ii", playerid, type);
        }

        msg_PlayerHasBox[playerid][type] = true;
    }
    else
    {
        msg_BoxClick[playerid][type] = true;
        msg_PlayerHasBox[playerid][type] = true;
        KillTimer(msg_BoxTimer[playerid][type]);
    }
    return 1;
}

stock void:MessageBox_ShowF(playerid, type, const caption[], const info[], interval = 6000, {Float,_}:...)
{
    new string[256];
    formatex(string, sizeof(string), info, ___(5));
    MessageBox_Show(playerid, type, caption, string, interval);
}

stock void:MessageBox_ShowAllF(type, const caption[], const info[], interval = 6000, {Float,_}:...)
{
    new string[256];
    formatex(string, sizeof(string), info, ___(4));

    foreach(new i : Player) {

        // skip not spawned players
        if(!Player_IsSpawned(i)) {
            continue;
        }

        MessageBox_Show(i, type, caption, string, interval);
    }
}