forward TextMenuInteriorList(playerid, listitem);
public TextMenuInteriorList(playerid, listitem)
{
	switch(listitem)
	{
		case 1:
		{
			SetPlayerPos(playerid, 1369.000122, -1279.712646, 13.546875);
		}
		case 2:
		{
			SetPlayerPos(playerid, 1555.501220, -1675.639038, 16.195312);
		}
		case 3:
		{
			SetPlayerPos(playerid, 1481.037719, -1772.312622, 18.795755);
		}
		case 4:
		{
			SetPlayerPos(playerid, 1022.6512, -1121.8951, 23.8719);
		}
		case 5:
		{
			SetPlayerPos(playerid, 1298.3035, -798.7736, 84.1406);
		}
		case 6:
		{
			SetPlayerPos(playerid, 541.9629, -1293.5179, 17.2414);
		}
		case 7:
		{
			SetPlayerPos(playerid, 2166.4160, -1671.7675, 15.0742);
		}
	}
	return 1;
}


stock ShowInteriorsList(playerid)
{
	TextMenu_Create(playerid, "TextMenuInteriorList", "Interiors");
    TextMenu_Add(playerid, "~w~[AMMU-NATION-PLAZA]");
    TextMenu_Add(playerid, "~w~[POLICE DEPT.]");
    TextMenu_Add(playerid, "~w~[CITY HALL]");
    TextMenu_Add(playerid, "~w~[CASINO]");
    TextMenu_Add(playerid, "~w~[XomoX's Mansion]");
    TextMenu_Add(playerid, "~w~[GROTTI]");
    TextMenu_Add(playerid, "~w~[DRUG HOUSE]");
    TextMenu_Show(playerid);
	return 1;
}

TCMD:interiors(playerid, params[])
{
    ShowInteriorsList(playerid);
    return 1;
}