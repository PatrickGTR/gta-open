#include <YSI_Coding\y_hooks>

static
    PlayerText:ClassName[MAX_PLAYERS],
    PlayerText:ClassInfo[MAX_PLAYERS],
    bool:ClassTDShown[MAX_PLAYERS];

hook OnPlayerSpawn(playerid) {
    if(ClassTDShown[playerid]) {
        UI_ClassSelectioTDHide(playerid);
    }
}

stock UI_ClassSelectionTDShow(playerid) {
    PlayerTextDrawShow(playerid, ClassName[playerid]);
    PlayerTextDrawShow(playerid, ClassInfo[playerid]);
    ClassTDShown[playerid] = true;
    return 1;
}

stock UI_ClassSelectioTDHide(playerid)
{
    PlayerTextDrawHide(playerid, ClassName[playerid]);
    PlayerTextDrawHide(playerid, ClassInfo[playerid]);
    ClassTDShown[playerid] = false;
    return 1;
}

stock UI_ClassSelectionTDUpdate(playerid, color, const title[], const info[])
{
    if(ClassTDShown[playerid])
    {
        PlayerTextDrawSetString(playerid, ClassName[playerid], title);
        PlayerTextDrawSetString(playerid, ClassInfo[playerid], info);
        PlayerTextDrawColor(playerid, ClassName[playerid], color);
        UI_ClassSelectioTDHide(playerid);
        UI_ClassSelectionTDShow(playerid);
        return 1;
    }
    return 0;
}

hook OnPlayerConnect(playerid)
{
    ClassName[playerid] = CreatePlayerTextDraw(playerid, 110.000000, 145.000000, "_");
    PlayerTextDrawAlignment(playerid, ClassName[playerid], TEXT_DRAW_ALIGN_CENTRE);
    PlayerTextDrawBackgroundColor(playerid, ClassName[playerid], 255);
    PlayerTextDrawFont(playerid, ClassName[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, ClassName[playerid], 0.400000, 2.000000);
    PlayerTextDrawColor(playerid, ClassName[playerid], -1);
    PlayerTextDrawSetOutline(playerid, ClassName[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ClassName[playerid], true);
    PlayerTextDrawSetSelectable(playerid, ClassName[playerid], false);

    ClassInfo[playerid] = CreatePlayerTextDraw(playerid, 10.000000, 170.500000, "_");
    PlayerTextDrawBackgroundColor(playerid, ClassInfo[playerid], 255);
    PlayerTextDrawFont(playerid, ClassInfo[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, ClassInfo[playerid], 0.200000, 1.000000);
    PlayerTextDrawColor(playerid, ClassInfo[playerid], -1);
    PlayerTextDrawSetOutline(playerid, ClassInfo[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ClassInfo[playerid], true);
    PlayerTextDrawUseBox(playerid, ClassInfo[playerid], true);
    PlayerTextDrawBoxColour(playerid, ClassInfo[playerid], 128);
    PlayerTextDrawTextSize(playerid, ClassInfo[playerid], 210.000000, 0.000000);
    PlayerTextDrawSetSelectable(playerid, ClassInfo[playerid], false);

    ClassTDShown[playerid] = false;
    return 1;
}