#include <YSI_Coding\y_hooks>

new
    ServerTime = 0,
    ServerDay = 0;

CMD:forcerace(playerid, params[]) {
    ServerTime = 1440 - 65;
    return 1;
}

stock Server_GetInGameTime() {
    return ServerTime;
}

stock Server_GetInGameDay() {
    return ServerDay;
}

hook OnServerSecondUpdate() {

    new
        timestring[24],
        daystring[11];

	new
        seconds = ServerTime % 60,
	    minutes = (ServerTime - seconds) / 60;

	ServerTime ++;

	if(ServerDay == 6 && ServerTime == 1440) { // New Week
		ServerDay = 0;
		ServerTime = 0;

        CallLocalFunction("OnServerWeekReset", "");
	}
	if(ServerTime == 1440) {
		ServerDay ++;
		ServerTime = 0;

        new dayName[][] = {
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday"
        };
        format(daystring, sizeof (daystring), "%s", dayName[clamp(ServerDay, 0, sizeof(dayName) - 1)]);
        UI_SetDay(daystring);

        CallLocalFunction("OnServerDayReset", "");
	}

	foreach(new i : Player) {
		SetPlayerTime(i, minutes, seconds);
	}



    format(timestring, sizeof (timestring), "%02d:%02d", minutes, seconds);
    UI_SetTime(timestring);
}