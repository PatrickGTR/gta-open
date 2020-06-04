CMD:buyfurniture(playerid, params[]) {
    if (!Player_IsInsideHouse(playerid)) {
        return SendErrorMsg(playerid, "You must be inside your house to buy a furniture.");
    }

    inline ShowFurnitureOption(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response)
            return 0;

        switch(listitem) {
            // Main Menu
            case 0: {
                Furniture_ShowDialog(playerid);
            }
            // Edit Menu
            case 1: {
                if (Player_IsOnFurnitureMode(playerid) && Furniture_GetEditingState(playerid) == TYPE_EDITING_FURNITURE) {
                    return SendErrorMsg(playerid, "You are already editing a furniture, close the current one in order to proceed again.");
                }

                Furniture_SetEditingState(playerid, TYPE_EDITING_FURNITURE);
                Player_SetFurnitureMode(playerid, true);

                SelectObject(playerid);
                SendServerMsg(playerid, "Use your mouse cursor to choose the furniture you want to edit.");
                SendServerMsg(playerid, "Press ESC once you're done, to allow your character to move.");
            }
            // Delete Menu
            case 2: {
                Furniture_SetEditingState(playerid, TYPE_DELETING_FURNITURE);
                Player_SetFurnitureMode(playerid, true);

                SelectObject(playerid);
                SendServerMsg(playerid, "Use your mouse cursor to choose the furniture you want to delete.");
                SendServerMsg(playerid, "Press ESC once you're done, to allow your character to move.");
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline ShowFurnitureOption, DIALOG_STYLE_LIST, "Furniture", "Buy Furniture\nEdit Furniture\nDelete Furniture", "Select", "Close");
    return 1;
}