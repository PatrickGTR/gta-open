enum E_ITEM_SHOP_DATA {
    E_ITEM_NAME[24],
    E_ITEM_VALUE
}

static const itemsTwentyFourSeven[][E_ITEM_SHOP_DATA] = {
    {"Picklock", 1000},
    {"Condom",   1000},
    {"Wallet",   1000},
    {"Rope",     1000},
    {"Scissors", 1000}
};

static
    twentyFourSevenCP,
    gasStationCP;

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
	twentyFourSevenCP = CreateDynamicCP(-28.9200, -184.2601, 1003.5469, 1.50);
    gasStationCP = CreateDynamicCP(-23.4678, -55.2389, 1003.5469, 1.50);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(checkpointid == twentyFourSevenCP || checkpointid == gasStationCP)
    {
        new
            tmp_string[32],
            string[sizeof(tmp_string) * sizeof(itemsTwentyFourSeven)];

        inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
            #pragma unused pid, dialogid, inputtext, listitem

            if(!response)
                return false;
        }

        strcat(string, "Item\tPrice\n");

        for(new i = 0; i < sizeof(itemsTwentyFourSeven); ++i)
        {
            format(tmp_string, sizeof(tmp_string), "%s\t"C_GREEN"%m\n",
                 itemsTwentyFourSeven[i][E_ITEM_NAME], itemsTwentyFourSeven[i][E_ITEM_VALUE]);

            strcat(string, tmp_string, sizeof(string));
        }
        Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_TABLIST_HEADERS, "Shop Items", string, "Select", "Close");
    }
    return 1;
}