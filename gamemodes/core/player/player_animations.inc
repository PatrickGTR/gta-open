#include <YSI_Coding\y_hooks>

static
    bool:PlayerUsingAnimation[MAX_PLAYERS],
    Text:txtAnimHelper;


SetPlayerSpecialAction_UI(playerid, action) {
	PlayerUsingAnimation[playerid] = true;
	SetPlayerSpecialAction(playerid, action);
	TextDrawShowForPlayer(playerid, txtAnimHelper);
}

ApplyAnimation_UI(playerid, const animlib[], const aninamne[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync) {
	PlayerUsingAnimation[playerid] = true;
	ApplyAnimation(playerid, animlib, aninamne, fDelta, loop, lockx, locky, freeze, time, forcesync);
	TextDrawShowForPlayer(playerid, txtAnimHelper);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(!PlayerUsingAnimation[playerid]) {
        return 1;
    }

	if(PRESSED(KEY_SPRINT)) {
	    PlayerUsingAnimation[playerid] = false;
        ApplyAnimation_UI(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        TextDrawHideForPlayer(playerid, txtAnimHelper);
    }
    return 1;
}


hook OnPlayerDeath(playerid, killerid, reason) {
	if(PlayerUsingAnimation[playerid]) {
        PlayerUsingAnimation[playerid] = false;
        TextDrawHideForPlayer(playerid, txtAnimHelper);
	}
 	return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerUsingAnimation[playerid] = false;
	return 1;
}

hook OnGameModeInit() {
	txtAnimHelper = TextDrawCreate(630.0, 420.0,"~r~~k~~PED_SPRINT~ ~w~to stop the animation");
	TextDrawUseBox(txtAnimHelper, 0);
	TextDrawFont(txtAnimHelper, 2);
	TextDrawSetShadow(txtAnimHelper, 0);
    TextDrawSetOutline(txtAnimHelper, 1);
    TextDrawBackgroundColor(txtAnimHelper, 0x000000FF);
    TextDrawColor(txtAnimHelper ,0xFFFFFFFF);
    TextDrawAlignment(txtAnimHelper, 3);
	return 1;
}

CMD:animlist(playerid, params[])
{
    SendClientMessage(playerid, COLOR_YELLOW, "/fall - /fallback - /injured - /akick - /push - /lowbodypush - /handsup - /bomb - /drunk - /getarrested - /laugh - /sup\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/basket - /headbutt - /medic - /spray - /robman - /taichi - /lookout - /kiss - /cellin - /cellout - /crossarms - /lay\n");
	SendClientMessage(playerid, COLOR_YELLOW, "/deal - /crack - /smokeanim - /groundsit - /chat - /chat2 - /dance - /fucku - /strip - /hide - /vomit - /eat - /chairsit - /reload\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/koface - /kostomach - /rollfall - /carjacked - /rcarjack1 - /rcarjack2 - /lcarjack1 - /lcarjack2 - /bat\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/lifejump - /exhaust - /leftslap - /carlock - /hoodfrisked - /lightcig - /tapcig - /box - /lay2 - /chant - /finger\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/shouting - /knife - /cop - /elbow - /kneekick - /airkick - /gkick - /gpunch - /fstance - /lowthrow - /highthrow - /aim\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/pee - /lean - /run - /poli - /surrender - /sit - /breathless - /seat - /rap - /cross - /ped - /jiggy - /gesture\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/sleep - /smoke - /urinate - /chora - /relax - /crabs - /stop - /wash - /mourn - /fuck - /tosteal\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/followme - /greeting - /still - /hitch - /palmbitch - /cpranim - /giftgiving - /slap2 - /pump - /cheer\n");
    SendClientMessage(playerid, COLOR_YELLOW, "/dj - /entrenar - /foodeat - /wave - /slapass - /dealer - /dealstance - /gwalk - /inbedright - /inbedleft\n");
	SendClientMessage(playerid, COLOR_YELLOW, "/wank - /sexy - /bj - /getup - /follow - /stand - /slapped - /slapass - /yes - /celebrate - /win - /checkout\n");
	SendClientMessage(playerid, COLOR_YELLOW, "/thankyou - /invite1 - /scratch - /nod - /cry - /carsmoke - /benddown - /shakehead - /angry\n");
	SendClientMessage(playerid, COLOR_YELLOW, "/cockgun - /bar - /liftup - /putdown - /die - /joint - /bed - /lranim\n");
	return 1;
}

CMD:animhelp(playerid, params[])
{
	return cmd_animlist(playerid, params);
}


CMD:surrender(playerid,params[])
{
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {

        return SendErrorMsg(playerid, "You must be on-foot to use this animation.");
    }
    SetPlayerSpecialAction_UI(playerid, SPECIAL_ACTION_HANDSUP);
    return 1;
}

CMD:sit(playerid,params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/sit <1-5>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: {
            ApplyAnimation_UI(playerid, "BEACH","bather",4.1, 0, 1, 1, 1, 1, 1);
        }
        case 2: {
            ApplyAnimation_UI(playerid, "BEACH","Lay_Bac_Loop",4.1, 0, 1, 1, 1, 1, 1);
        }
        case 3: {
            ApplyAnimation_UI(playerid, "BEACH","ParkSit_W_loop",4.1, 0, 1, 1, 1, 1, 1);
        }
        case 4: {
            ApplyAnimation_UI(playerid, "BEACH","SitnWait_loop_W",4.1, 0, 1, 1, 1, 1, 1);
        }
        case 5: {
            ApplyAnimation_UI(playerid, "BEACH","SitnWait_loop_W",4.1, 0, 1, 1, 1, 1, 1);
        }
        case 6: {
            ApplyAnimation_UI(playerid, "BEACH", "ParkSit_M_loop", 4.1, 0, 1, 1, 1, 1, 1);
        }
        default: {
            return SendClientMessage(playerid,COLOR_WHITE,"USE: /sit [1-5]");
        }
    }
    return 1;
}

CMD:sleep(playerid,params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/sleep <1-2>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID) {
        case 1: ApplyAnimation_UI(playerid, "CRACK", "crckdeth4", 4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid, "CRACK", "crckidle2", 4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/sleep <1-2>");
        }
    }
    return 1;
}

CMD:cheer(playerid,params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/cheer <1-8>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid,"ON_LOOKERS","shout_01", 4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid,"ON_LOOKERS","shout_02", 4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid,"ON_LOOKERS","shout_in", 4.1, 0, 1, 1, 1, 1, 1);
        case 4: ApplyAnimation_UI(playerid,"RIOT","RIOT_ANGRY_B", 4.1, 0, 1, 1, 1, 1, 1);
        case 5: ApplyAnimation_UI(playerid,"RIOT","RIOT_CHANT", 4.1, 0, 1, 1, 1, 1, 1);
        case 6: ApplyAnimation_UI(playerid,"RIOT","RIOT_shout", 4.1, 0, 1, 1, 1, 1, 1);
        case 7: ApplyAnimation_UI(playerid,"STRIP","PUN_HOLLER", 4.1, 0, 1, 1, 1, 1, 1);
        case 8: ApplyAnimation_UI(playerid,"OTB","wtchrace_win", 4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/cheer <1-8>");
        }
    }
    return 1;
}

CMD:urinate(playerid,params[]) {
    SetPlayerSpecialAction_UI(playerid, 68);
    return 1;
}

CMD:dj(playerid,params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/dj <1-4>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid, "SCRATCHING", "scdldlp", 4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid, "SCRATCHING", "scdlulp", 4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid, "SCRATCHING", "scdrdlp", 4.1, 0, 1, 1, 1, 1, 1);
        case 4: ApplyAnimation_UI(playerid, "SCRATCHING", "scdrulp", 4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/dj <1-4>");
        }
    }
    return 1;
}

CMD:breathless(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/breathless <1-2>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid,"PED","IDLE_tired",4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid,"FAT","IDLE_tired",4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/breathless <1-2>");
        }
    }
    return 1;
}

CMD:poli(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/poli <1-2>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1:ApplyAnimation_UI(playerid,"POLICE","CopTraf_Come",4.1, 0, 1, 1, 1, 1, 1);
        case 2:ApplyAnimation_UI(playerid,"POLICE","CopTraf_Stop",4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/poli <1-2>");
        }
    }
    return 1;
}

CMD:seat(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/seat <1-7>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid,"Attractors","Stepsit_in",4.1, 0, 1, 1, 1, 1, 1);// Not looping
        case 2: ApplyAnimation_UI(playerid,"CRIB","PED_Console_Loop",4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid,"INT_HOUSE","LOU_In",4.1, 0, 1, 1, 1, 1, 1); // Not looping
        case 4: ApplyAnimation_UI(playerid,"MISC","SEAT_LR",4.1, 0, 1, 1, 1, 1, 1);
        case 5: ApplyAnimation_UI(playerid,"MISC","Seat_talk_01",4.1, 0, 1, 1, 1, 1, 1);
        case 6: ApplyAnimation_UI(playerid,"MISC","Seat_talk_02",4.1, 0, 1, 1, 1, 1, 1);
        case 7: ApplyAnimation_UI(playerid,"ped","SEAT_down",4.1, 0, 1, 1, 1, 1, 1); // Not looping
        default: {
            return SendSyntaxMsg(playerid, "/seat <1-7>");
        }
    }
    return 1;
}

CMD:dance(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/dance <1-3>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: SetPlayerSpecialAction_UI(playerid, SPECIAL_ACTION_DANCE1);
        case 2: SetPlayerSpecialAction_UI(playerid, SPECIAL_ACTION_DANCE2);
        case 3: SetPlayerSpecialAction_UI(playerid, SPECIAL_ACTION_DANCE3);
        case 4: SetPlayerSpecialAction_UI(playerid, SPECIAL_ACTION_DANCE4);
        default: {
            return SendSyntaxMsg(playerid, "/dance <1-3>");
        }
    }
    return 1;
}

CMD:cross(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/cross <1-5>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid, "COP_AMBIENT", "Coplook_loop", 4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid, "DEALER", "DEALER_IDLE", 4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid, "DEALER", "DEALER_IDLE_01", 4.1, 0, 1, 1, 1, 1, 1);
        case 4: ApplyAnimation_UI(playerid, "GRAVEYARD", "mrnM_loop", 4.1, 0, 1, 1, 1, 1, 1);
        case 5: ApplyAnimation_UI(playerid, "GRAVEYARD", "prst_loopa", 4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/cross <1-5>");
        }
    }
    return 1;
}

CMD:jiggy(playerid,params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/jiggy <1-10>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid,"DANCING","DAN_Down_A",4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid,"DANCING","DAN_Left_A",4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid,"DANCING","DAN_Loop_A",4.1, 0, 1, 1, 1, 1, 1);
        case 4: ApplyAnimation_UI(playerid,"DANCING","DAN_Right_A",4.1, 0, 1, 1, 1, 1, 1);
        case 5: ApplyAnimation_UI(playerid,"DANCING","DAN_Up_A",4.1, 0, 1, 1, 1, 1, 1);
        case 6: ApplyAnimation_UI(playerid,"DANCING","dnce_M_a",4.1, 0, 1, 1, 1, 1, 1);
        case 7: ApplyAnimation_UI(playerid,"DANCING","dnce_M_b",4.1, 0, 1, 1, 1, 1, 1);
        case 8: ApplyAnimation_UI(playerid,"DANCING","dnce_M_c",4.1, 0, 1, 1, 1, 1, 1);
        case 9: ApplyAnimation_UI(playerid,"DANCING","dnce_M_c",4.1, 0, 1, 1, 1, 1, 1);
        case 10: ApplyAnimation_UI(playerid,"DANCING","dnce_M_d",4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/jiggy <1-10>");
        }
    }
    return 1;
}

CMD:ped(playerid,params[]) {
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/ped <1-26>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid, "PED", "JOG_femaleA", 4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid, "PED", "JOG_maleA", 4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid, "PED", "WOMAN_walkfatold", 4.1, 0, 1, 1, 1, 1, 1);
        case 4: ApplyAnimation_UI(playerid, "PED", "run_fat", 4.1, 0, 1, 1, 1, 1, 1);
        case 5: ApplyAnimation_UI(playerid, "PED", "run_fatold", 4.1, 0, 1, 1, 1, 1, 1);
        case 6: ApplyAnimation_UI(playerid, "PED", "run_old", 4.1, 0, 1, 1, 1, 1, 1);
        case 7: ApplyAnimation_UI(playerid, "PED", "Run_Wuzi", 4.1, 0, 1, 1, 1, 1, 1);
        case 8: ApplyAnimation_UI(playerid, "PED", "swat_run", 4.1, 0, 1, 1, 1, 1, 1);
        case 9: ApplyAnimation_UI(playerid, "PED", "WALK_fat", 4.1, 0, 1, 1, 1, 1, 1);
        case 10: ApplyAnimation_UI(playerid, "PED", "WALK_fatold", 4.1, 0, 1, 1, 1, 1, 1);
        case 11: ApplyAnimation_UI(playerid, "PED", "WALK_gang1", 4.1, 0, 1, 1, 1, 1, 1);
        case 12: ApplyAnimation_UI(playerid, "PED", "WALK_gang2", 4.1, 0, 1, 1, 1, 1, 1);
        case 13: ApplyAnimation_UI(playerid, "PED", "WALK_old", 4.1, 0, 1, 1, 1, 1, 1);
        case 14: ApplyAnimation_UI(playerid, "PED", "WALK_shuffle", 4.1, 0, 1, 1, 1, 1, 1);
        case 15: ApplyAnimation_UI(playerid, "PED", "woman_run", 4.1, 0, 1, 1, 1, 1, 1);
        case 16: ApplyAnimation_UI(playerid, "PED", "WOMAN_runbusy", 4.1, 0, 1, 1, 1, 1, 1);
        case 17: ApplyAnimation_UI(playerid, "PED", "WOMAN_runfatold", 4.1, 0, 1, 1, 1, 1, 1);
        case 18: ApplyAnimation_UI(playerid, "PED", "woman_runpanic", 4.1, 0, 1, 1, 1, 1, 1);
        case 19: ApplyAnimation_UI(playerid, "PED", "WOMAN_runsexy", 4.1, 0, 1, 1, 1, 1, 1);
        case 20: ApplyAnimation_UI(playerid, "PED", "WOMAN_walkbusy", 4.1, 0, 1, 1, 1, 1, 1);
        case 21: ApplyAnimation_UI(playerid, "PED", "WOMAN_walkfatold", 4.1, 0, 1, 1, 1, 1, 1);
        case 22: ApplyAnimation_UI(playerid, "PED", "WOMAN_walknorm", 4.1, 0, 1, 1, 1, 1, 1);
        case 23: ApplyAnimation_UI(playerid, "PED", "WOMAN_walkold", 4.1, 0, 1, 1, 1, 1, 1);
        case 24: ApplyAnimation_UI(playerid, "PED", "WOMAN_walkpro", 4.1, 0, 1, 1, 1, 1, 1);
        case 25: ApplyAnimation_UI(playerid, "PED", "WOMAN_walksexy", 4.1, 0, 1, 1, 1, 1, 1);
        case 26: ApplyAnimation_UI(playerid, "PED", "WOMAN_walkshop", 4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/ped <1-26>");
        }
    }
    return 1;
}

CMD:rap(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/rap <1-3>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid, "RAPPING","RAP_A_Loop", 4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid, "RAPPING","RAP_B_Loop", 4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid, "RAPPING","RAP_C_Loop", 4.1, 0, 1, 1, 1, 1, 1);
        default: return SendSyntaxMsg(playerid, "/rap <1-3>");
    }
    return 1;
}

CMD:gesture(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/gesture <1-15>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid, "GHANDS", "gsign1", 4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid, "GHANDS", "gsign1LH", 4.1, 0, 1, 1, 1, 1, 1);
        case 3: ApplyAnimation_UI(playerid, "GHANDS", "gsign2", 4.1, 0, 1, 1, 1, 1, 1);
        case 4: ApplyAnimation_UI(playerid, "GHANDS", "gsign2LH", 4.1, 0, 1, 1, 1, 1, 1);
        case 5: ApplyAnimation_UI(playerid, "GHANDS", "gsign3", 4.1, 0, 1, 1, 1, 1, 1);
        case 6: ApplyAnimation_UI(playerid, "GHANDS", "gsign3LH", 4.1, 0, 1, 1, 1, 1, 1);
        case 7: ApplyAnimation_UI(playerid, "GHANDS", "gsign4", 4.1, 0, 1, 1, 1, 1, 1);
        case 8: ApplyAnimation_UI(playerid, "GHANDS", "gsign4LH", 4.1, 0, 1, 1, 1, 1, 1);
        case 9: ApplyAnimation_UI(playerid, "GHANDS", "gsign5", 4.1, 0, 1, 1, 1, 1, 1);
        case 10: ApplyAnimation_UI(playerid, "GHANDS", "gsign5", 4.1, 0, 1, 1, 1, 1, 1);
        case 11: ApplyAnimation_UI(playerid, "GHANDS", "gsign5LH", 4.1, 0, 1, 1, 1, 1, 1);
        case 12: ApplyAnimation_UI(playerid, "GANGS", "Invite_No", 4.1, 0, 1, 1, 1, 1, 1);
        case 13: ApplyAnimation_UI(playerid, "GANGS", "Invite_Yes", 4.1, 0, 1, 1, 1, 1, 1);
        case 14: ApplyAnimation_UI(playerid, "GANGS", "prtial_gngtlkD", 4.1, 0, 1, 1, 1, 1, 1);
        case 15: ApplyAnimation_UI(playerid, "GANGS", "smkcig_prtl", 4.1, 0, 1, 1, 1, 1, 1);
        default: {
            return SendSyntaxMsg(playerid, "/gesture <1-15>");
        }
    }
    return 1;
}

CMD:smoke(playerid,params[]){
    if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/smoke <1-2>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID){
        case 1: ApplyAnimation_UI(playerid,"SMOKING","M_smk_in",4.1, 0, 1, 1, 1, 1, 1);
        case 2: ApplyAnimation_UI(playerid,"SMOKING","M_smklean_loop",4.1, 0, 1, 1, 1, 1, 1);
        default: return SendSyntaxMsg(playerid, "/smoke <1-2>");
    }
    return 1;
}

CMD:chora(playerid,params[])  {
	ApplyAnimation_UI(playerid, "COP_AMBIENT", "Coplook_watch",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:relax(playerid,params[])  {
	ApplyAnimation_UI(playerid, "CRACK", "crckidle1",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:crabs(playerid,params[])  {
	ApplyAnimation_UI(playerid,"MISC","Scratchballs_01",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:greeting(playerid,params[])  {
	ApplyAnimation_UI(playerid,"ON_LOOKERS","Pointup_loop",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:stop(playerid,params[])  {
	ApplyAnimation_UI(playerid,"PED","endchat_01",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:wash(playerid,params[])  {
	ApplyAnimation_UI(playerid,"BD_FIRE","wash_up",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:mourn(playerid,params[])  {
	ApplyAnimation_UI(playerid,"GRAVEYARD","mrnF_loop",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:followme(playerid,params[])  {
	ApplyAnimation_UI(playerid,"WUZI","Wuzi_follow",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:still(playerid,params[])  {
	ApplyAnimation_UI(playerid,"WUZI","Wuzi_stand_loop", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:hitch(playerid,params[])  {
	ApplyAnimation_UI(playerid,"MISC","Hiker_Pose", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:palmbitch(playerid,params[])  {
	ApplyAnimation_UI(playerid,"MISC","bitchslap",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:cpranim(playerid,params[])  {
	ApplyAnimation_UI(playerid,"MEDIC","CPR",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:giftgiving(playerid,params[])  {
	ApplyAnimation_UI(playerid,"KISSING","gift_give",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:slap2(playerid,params[])  {
	ApplyAnimation_UI(playerid,"SWEET","sweet_ass_slap",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:drunk(playerid,params[])  {
	ApplyAnimation_UI(playerid,"PED","WALK_DRUNK",4.1, 0, 1, 1, 1, 1, 1);
	return  1;
}

CMD:pump(playerid,params[]) {
	ApplyAnimation_UI(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:tosteal(playerid,params[])  {
	ApplyAnimation_UI(playerid,"ped", "ARRESTgun", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:laugh(playerid,params[])  {
	ApplyAnimation_UI(playerid, "RAPPING", "Laugh_01", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:lookout(playerid,params[])   {
	ApplyAnimation_UI(playerid, "SHOP", "ROB_Shifty", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:robman(playerid,params[])  {
	ApplyAnimation_UI(playerid, "SHOP", "ROB_Loop_Threat", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:hide(playerid,params[])  {
	ApplyAnimation_UI(playerid, "ped", "cower",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:vomit(playerid,params[])  {
	ApplyAnimation_UI(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:eat(playerid,params[])  {
	ApplyAnimation_UI(playerid, "FOOD", "EAT_Burger", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:crack(playerid,params[])  {
	ApplyAnimation_UI(playerid, "CRACK", "crckdeth2", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:fuck(playerid,params[])  {
	ApplyAnimation_UI(playerid,"PED","fucku",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:taichi(playerid,params[])  {
	ApplyAnimation_UI(playerid,"PARK","Tai_Chi_Loop", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:entrenar(playerid,params[])  {
	ApplyAnimation_UI(playerid,"PARK","Tai_Chi_Loop", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:kiss(playerid,params[])  {
	ApplyAnimation_UI(playerid,"KISSING","Playa_Kiss_01",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:carjacked(playerid, params[]) {

	if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/carjacked <1-2>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

	switch(animID) {
		case 1: {
			ApplyAnimation_UI(playerid,"PED","CAR_jackedLHS",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 2: {
			ApplyAnimation_UI(playerid,"PED","CAR_jackedRHS",4.1, 0, 1, 1, 1, 1, 1);
		}
		default: return SendSyntaxMsg(playerid, "/carjacked <1-2>");
	}
	return 1;
}

CMD:handsup(playerid, params[]) {
	ApplyAnimation_UI(playerid, "ROB_BANK","SHP_HandsUp_Scr",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:cellin(playerid, params[]) {
    SetPlayerSpecialAction_UI(playerid, SPECIAL_ACTION_USECELLPHONE);
    return 1;
}

CMD:cellout(playerid, params[]) {
    SetPlayerSpecialAction_UI(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
    return 1;
}

CMD:bomb(playerid, params[]) {
	ApplyAnimation_UI(playerid, "BOMBER","BOM_Plant_Loop",4.1, 0, 1, 1, 1, 1, 1); // Place Bomb
	return 1;
}

CMD:getarrested(playerid, params[]) {
	ApplyAnimation_UI(playerid,"ped", "ARRESTgun", 4.1, 0, 1, 1, 1, 1, 1); // Gun Arrest
	return 1;
}

CMD:crossarms(playerid, params[]) {
	ApplyAnimation_UI(playerid, "COP_AMBIENT", "Coplook_loop", 4.1, 0, 1, 1, 1, 1, 1); // Arms crossed
	return 1;
}

CMD:lay(playerid, params[]) {
	ApplyAnimation_UI(playerid,"BEACH", "bather",4.1, 0, 1, 1, 1, 1, 1); // Lay down
	return 1;
}

CMD:foodeat(playerid, params[]) {
	ApplyAnimation_UI(playerid, "FOOD", "EAT_Burger", 4.1, 0, 1, 1, 1, 1, 1); // Eat Burger
	return 1;
}

CMD:wave(playerid, params[]) {
	ApplyAnimation_UI(playerid, "ON_LOOKERS", "wave_loop", 4.1, 0, 1, 1, 1, 1, 1); // Wave
	return 1;
}

CMD:slapass(playerid, params[]) {
	ApplyAnimation_UI(playerid, "SWEET", "sweet_ass_slap", 4.1, 0, 1, 1, 1, 1, 1); // Ass Slapping
 	return 1;
}

CMD:dealer(playerid, params[]) {
	ApplyAnimation_UI(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 1, 1, 1, 1, 1); // Deal Drugs
	return 1;
}

CMD:groundsit(playerid, params[]) {
	ApplyAnimation_UI(playerid,"BEACH", "ParkSit_M_loop", 4.1, 0, 1, 1, 1, 1, 1); // Sit
	return 1;
}

CMD:chat(playerid, params[]) {
	if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/chat <1-2>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

	switch(animID) {
		case 1: {
			ApplyAnimation_UI(playerid,"PED","IDLE_CHAT",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 2: {
			ApplyAnimation_UI(playerid,"MISC","Idle_Chat_02",4.1, 0, 1, 1, 1, 1, 1);
		}
		default: {
			return SendSyntaxMsg(playerid, "/chat <1-2>");
		}
	}
    return 1;
}

CMD:fucku(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","fucku",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:chairsit(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","SEAT_idle",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:fall(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","KO_skid_front",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:fallback(playerid, params[]) {
	ApplyAnimation_UI(playerid, "PED","FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:injured(playerid, params[]) {
	ApplyAnimation_UI(playerid, "SWEET", "Sweet_injuredloop", 4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:sup(playerid, params[]) {
	if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/sup <1-3>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

	switch(animID) {

		case 1: {
			ApplyAnimation_UI(playerid,"GANGS","hndshkba",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 2: {
 			ApplyAnimation_UI(playerid,"GANGS","hndshkda",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 3: {
			ApplyAnimation_UI(playerid,"GANGS","hndshkfa_swt",4.1, 0, 1, 1, 1, 1, 1);
		}
		default: {
			return SendSyntaxMsg(playerid, "/sup <1-3>");
		}
	}
   	return 1;
}

CMD:push(playerid, params[]) {
	ApplyAnimation_UI(playerid,"GANGS","shake_cara",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:akick(playerid, params) {
	ApplyAnimation_UI(playerid,"POLICE","Door_Kick",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:lowbodypush(playerid, params[]) {
	ApplyAnimation_UI(playerid,"GANGS","shake_carSH",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:spray(playerid, params[]) {
	ApplyAnimation_UI(playerid,"SPRAYCAN","spraycan_full",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:headbutt(playerid, params[]) {
	ApplyAnimation_UI(playerid,"WAYFARER","WF_Fwd",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:medic(playerid, params[]) {
	ApplyAnimation_UI(playerid,"MEDIC","CPR",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:koface(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","KO_shot_face",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:kostomach(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","KO_shot_stom",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:lifejump(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","EV_dive",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:exhaust(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","IDLE_tired",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:leftslap(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","BIKE_elbowL",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:rollfall(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","BIKE_fallR",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:carlock(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","CAR_doorlocked_LHS",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:rcarjack1(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","CAR_pulloutL_LHS",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:lcarjack1(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","CAR_pulloutL_RHS",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:rcarjack2(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","CAR_pullout_LHS",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:lcarjack2(playerid, params[]) {
	ApplyAnimation_UI(playerid,"PED","CAR_pullout_RHS",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:hoodfrisked(playerid, params[]) {
	ApplyAnimation_UI(playerid,"POLICE","crm_drgbst_01",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:lightcig(playerid, params[]) {
	ApplyAnimation_UI(playerid,"SMOKING","M_smk_in",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:tapcig(playerid, params[]) {
	ApplyAnimation_UI(playerid,"SMOKING","M_smk_tap",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:bat(playerid, params[]) {
	ApplyAnimation_UI(playerid,"BASEBALL","Bat_IDLE",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:box(playerid, params[]) {
	ApplyAnimation_UI(playerid,"GYMNASIUM","GYMshadowbox",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:lay2(playerid, params[]) {
	ApplyAnimation_UI(playerid,"SUNBATHE","Lay_Bac_in",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:chant(playerid, params[]) {
	ApplyAnimation_UI(playerid,"RIOT","RIOT_CHANT",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:finger(playerid, params[]) {
	ApplyAnimation_UI(playerid,"RIOT","RIOT_FUKU",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:shouting(playerid, params[]) {
	ApplyAnimation_UI(playerid,"RIOT","RIOT_shout",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:cop(playerid,params[]) {
	ApplyAnimation_UI(playerid,"SWORD","sword_block",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:elbow(playerid, params[]) {
	ApplyAnimation_UI(playerid,"FIGHT_D","FightD_3",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:kneekick(playerid, params[]) {
	ApplyAnimation_UI(playerid,"FIGHT_D","FightD_2",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:fstance(playerid, params[]) {
	ApplyAnimation_UI(playerid,"FIGHT_D","FightD_IDLE",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:gpunch(playerid, params[]) {
	ApplyAnimation_UI(playerid,"FIGHT_B","FightB_G",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:airkick(playerid, params[]) {
	ApplyAnimation_UI(playerid,"FIGHT_C","FightC_M",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:gkick(playerid, params[]) {
	ApplyAnimation_UI(playerid,"FIGHT_D","FightD_G",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:lowthrow(playerid, params[]) {
	ApplyAnimation_UI(playerid,"GRENADE","WEAPON_throwu",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:highthrow(playerid, params[]) {
	ApplyAnimation_UI(playerid,"GRENADE","WEAPON_throw",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:dealstance(playerid, params[]) {
	ApplyAnimation_UI(playerid,"DEALER","DEALER_IDLE",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:pee(playerid, params[]) {
	SetPlayerSpecialAction_UI(playerid, 68);
    return 1;
}

CMD:knife(playerid, params[]) {
	if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/knife <1-4>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

	switch(animID) {
		case 1: {
			ApplyAnimation_UI(playerid,"KNIFE","KILL_Knife_Ped_Damage",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 2: {
			ApplyAnimation_UI(playerid,"KNIFE","KILL_Knife_Ped_Die",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 3: {
			ApplyAnimation_UI(playerid,"KNIFE","KILL_Knife_Player",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 4: {
			ApplyAnimation_UI(playerid,"KNIFE","KILL_Partial",4.1, 0, 1, 1, 1, 1, 1);
		}
		default: {
			return SendSyntaxMsg(playerid, "/knife <1-4>");
		}
	}
	return 1;
}

CMD:basket(playerid, params[]) {
	if(isnull(params)) {
        return SendSyntaxMsg(playerid, "/basket <1-6>");
    }

    if(!isnumeric(params)) {
        return SendErrorMsg(playerid, "Only numerical values allowed.");
    }

    new
        animID = strval(params);

    switch(animID)	{
		case 1: {
			ApplyAnimation_UI(playerid,"BSKTBALL","BBALL_idleloop",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 2: {
			ApplyAnimation_UI(playerid,"BSKTBALL","BBALL_Jump_Shot",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 3: {
			ApplyAnimation_UI(playerid,"BSKTBALL","BBALL_pickup",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 4: {
			ApplyAnimation_UI(playerid,"BSKTBALL","BBALL_run",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 5: {
			ApplyAnimation_UI(playerid,"BSKTBALL","BBALL_def_loop",4.1, 0, 1, 1, 1, 1, 1);
		}
		case 6: {
			ApplyAnimation_UI(playerid,"BSKTBALL","BBALL_Dnk",4.1, 0, 1, 1, 1, 1, 1);
		}
		default: {
			return SendSyntaxMsg(playerid, "/basket <1-6>");
		}
	}
   	return 1;
}

CMD:reload(playerid, params[])//88
{
	new result[128];
	if(sscanf(params, "s[24]", result)) return SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /reload [deagle/smg/ak/m4]");
    if(strcmp(result,"deagle", true) == 0)
	{
		ApplyAnimation_UI(playerid,"COLT45","colt45_reload",4.1, 0, 1, 1, 1, 1, 1);
    }
    else if(strcmp(result,"smg", true) == 0)
    {
		ApplyAnimation_UI(playerid,"UZI","UZI_reload",4.1, 0, 1, 1, 1, 1, 1);
    }
	else if(strcmp(result,"ak", true) == 0)
	{
		ApplyAnimation_UI(playerid,"UZI","UZI_reload",4.1, 0, 1, 1, 1, 1, 1);
    }
	else if(strcmp(result,"m4", true) == 0)
	{
		ApplyAnimation_UI(playerid,"UZI","UZI_reload",4.1, 0, 1, 1, 1, 1, 1);
    }
   	else { SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /reload [deagle/smg/ak/m4]"); }
   	return 1;
}

CMD:gwalk(playerid, params[])//89
{
	new ssr;
	if(sscanf(params, "i", ssr)) return SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /gwalk [1/2]");
	if(ssr < 1 || ssr > 2) { SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /gwalk [1/2]"); }
	if (ssr == 1) { ApplyAnimation_UI(playerid,"PED","WALK_gang1",4.1, 0, 1, 1, 1, 1, 1); }
 	if (ssr == 2) { ApplyAnimation_UI(playerid,"PED","WALK_gang2",4.1, 0, 1, 1, 1, 1, 1); }
   	return 1;
}

CMD:aim(playerid, params[])//90
{
	new lmb;
	if(sscanf(params, "i", lmb)) return SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /aim [1-3]");
	if(lmb == 1) { ApplyAnimation_UI(playerid,"PED","gang_gunstand",4.1, 0, 1, 1, 1, 1, 1); }
    if(lmb == 2) { ApplyAnimation_UI(playerid,"PED","Driveby_L",4.1, 0, 1, 1, 1, 1, 1); }
    if(lmb == 3) { ApplyAnimation_UI(playerid,"PED","Driveby_R",4.1, 0, 1, 1, 1, 1, 1); }
    else { SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /aim [1-3]"); }
    return 1;
}

CMD:lean(playerid, params[])//91
{
	new mj;
	if(sscanf(params, "i", mj)) return SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /lean [1-2]");
	if(mj < 1 || mj > 2) { SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /lean [1-2]"); }
    if(mj == 1) { ApplyAnimation_UI(playerid,"GANGS","leanIDLE",4.1, 0, 1, 1, 1, 1, 1); }
	if(mj == 2) { ApplyAnimation_UI(playerid,"MISC","Plyrlean_loop",4.1, 0, 1, 1, 1, 1, 1); }
   	return 1;
}

CMD:clearanim(playerid, params[]) {//92
    ApplyAnimation_UI(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0, 0);
    return 1;
}

CMD:strip(playerid, params[])//93
{
	new kj;
    if(sscanf(params, "i", kj)) return SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /strip [1-7]");
	if(kj < 1 || kj > 7) { SendClientMessage(playerid,0xEFEFF7AA,"USAGE: /strip [1-7]"); }
	if(kj == 1) { ApplyAnimation_UI(playerid,"STRIP", "strip_A", 4.1, 0, 1, 1, 1, 1, 1 ); }
	if(kj == 2) { ApplyAnimation_UI(playerid,"STRIP", "strip_B", 4.1, 0, 1, 1, 1, 1, 1 ); }
    if(kj == 3) { ApplyAnimation_UI(playerid,"STRIP", "strip_C", 4.1, 0, 1, 1, 1, 1, 1 ); }
    if(kj == 4) { ApplyAnimation_UI(playerid,"STRIP", "strip_D", 4.1, 0, 1, 1, 1, 1, 1 ); }
    if(kj == 5) { ApplyAnimation_UI(playerid,"STRIP", "strip_E", 4.1, 0, 1, 1, 1, 1, 1 ); }
    if(kj == 6) { ApplyAnimation_UI(playerid,"STRIP", "strip_F", 4.1, 0, 1, 1, 1, 1, 1 ); }
    if(kj == 7) { ApplyAnimation_UI(playerid,"STRIP", "strip_G", 4.1, 0, 1, 1, 1, 1, 1 ); }
 	return 1;
}

CMD:inbedright(playerid, params[])//94
{
	ApplyAnimation_UI(playerid,"INT_HOUSE","BED_Loop_R",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:inbedleft(playerid, params[])//95
{
	ApplyAnimation_UI(playerid,"INT_HOUSE","BED_Loop_L",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:wank(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /wank [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"PAULNMAC","wank_in",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"PAULNMAC","wank_loop",4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}
CMD:sexy(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /sexy [1-8]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKING_IDLEW",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKING_IDLEP",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKINGW",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKINGP",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "5", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKEDW",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "6", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKEDP",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "7", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKING_ENDW",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "8", true) == 0)
	{
		ApplyAnimation_UI(playerid,"SNM","SPANKING_ENDP",4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}

CMD:bj(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /bj [1-4]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"BLOWJOBZ","BJ_COUCH_START_P",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"BLOWJOBZ","BJ_COUCH_START_W",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation_UI(playerid,"BLOWJOBZ","BJ_COUCH_LOOP_P",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation_UI(playerid,"BLOWJOBZ","BJ_COUCH_LOOP_W",4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}

CMD:stand(playerid, params[])
{
	ApplyAnimation_UI(playerid,"WUZI","Wuzi_stand_loop", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:follow(playerid, params[])
{
	ApplyAnimation_UI(playerid,"WUZI","Wuzi_follow",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:getup(playerid, params[])
{
	ApplyAnimation_UI(playerid,"PED","getup",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:slapped(playerid, params[])
{
	ApplyAnimation_UI(playerid,"SWEET","ho_ass_slapped",4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}

CMD:win(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /win [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"CASINO","cards_win", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"CASINO","Roulette_win", 4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}

CMD:celebrate(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /celebrate [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"benchpress","gym_bp_celebrate", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"GYMNASIUM","gym_tread_celebrate", 4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}

CMD:yes(playerid, params[])
{
	ApplyAnimation_UI(playerid,"CLOTHES","CLO_Buy", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:deal(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /deal [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"DEALER","DRUGS_BUY", 4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}

CMD:thankyou(playerid, params[])
{
	ApplyAnimation_UI(playerid,"FOOD","SHP_Thank", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:invite1(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /invite1 [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"GANGS","Invite_Yes",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"GANGS","Invite_No",4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}

CMD:scratch(playerid, params[])
{
	ApplyAnimation_UI(playerid,"MISC","Scratchballs_01", 4.1, 0, 1, 1, 1, 1, 1);
    return 1;
}
CMD:checkout(playerid, params[])
{
	ApplyAnimation_UI(playerid, "GRAFFITI", "graffiti_Chkout", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:nod(playerid, params[])
{
	ApplyAnimation_UI(playerid,"COP_AMBIENT","Coplook_nod",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:cry(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /cry [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"GRAVEYARD","mrnF_loop", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"GRAVEYARD","mrnM_loop", 4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}
CMD:bed(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /bed [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"INT_HOUSE","BED_In_L",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"INT_HOUSE","BED_In_R",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation_UI(playerid,"INT_HOUSE","BED_Loop_L", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation_UI(playerid,"INT_HOUSE","BED_Loop_R", 4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}
CMD:carsmoke(playerid, params[])
{
	ApplyAnimation_UI(playerid,"PED","Smoke_in_car", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:angry(playerid, params[])
{
	ApplyAnimation_UI(playerid,"RIOT","RIOT_ANGRY",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:benddown(playerid, params[])
{
	ApplyAnimation_UI(playerid, "BAR", "Barserve_bottle", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:shakehead(playerid, params[])
{
	ApplyAnimation_UI(playerid, "MISC", "plyr_shkhead", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:cockgun(playerid, params[])
{
	ApplyAnimation_UI(playerid, "SILENCED", "Silence_reload", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:bar(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /bar [1-4]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid, "BAR", "Barcustom_get", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid,"GHANDS","gsign2LH",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid, "BAR", "Barcustom_order", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation_UI(playerid, "BAR", "Barserve_give", 4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation_UI(playerid, "BAR", "Barserve_glass", 4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}
CMD:liftup(playerid, params[])
{
	ApplyAnimation_UI(playerid, "CARRY", "liftup", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:putdown(playerid, params[])
{
	ApplyAnimation_UI(playerid, "CARRY", "putdwn", 4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}

CMD:joint(playerid, params[])
{
	ApplyAnimation_UI(playerid,"GANGS","smkcig_prtl",4.1, 0, 1, 1, 1, 1, 1);
	return 1;
}
CMD:die(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendClientMessage(playerid, COLOR_WHITE, "USAGE: /die [1-2]");
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation_UI(playerid,"KNIFE","KILL_Knife_Ped_Die",4.1, 0, 1, 1, 1, 1, 1);

	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation_UI(playerid, "PARACHUTE", "FALL_skyDive_DIE", 4.1, 0, 1, 1, 1, 1, 1);

	}
	return 1;
}

CMD:lranim(playerid, params[])
{

	new 
		vehicleid = GetPlayerVehicleID(playerid),
		modelid = GetVehicleModel(vehicleid),
		bool:isLowerRider = false;

	switch(modelid) {
		case 536, 575, 567: {
			isLowerRider = true;
		}
	}

	if(isLowerRider)
	{
		new choice;
		if(sscanf(params, "i", choice))
		{
			SendClientMessage(playerid, COLOR_WHITE, "USAGE: /lranim");
			SendClientMessage(playerid, COLOR_WHITE, "Available options: 0-36");
			return 1;
		}
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
		    SendClientMessage(playerid, COLOR_WHITE, "  You cannot be the driver of the vehicle!");
		    return 1;
		}
		switch(choice)
		{
		    case 0:
		    {
				ApplyAnimation_UI(playerid, "LOWRIDER", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 1:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_bdbnce", 4.0, 0, 0, 0, 1, 0, 1);
		    }
		    case 2:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_hair", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 3:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_hurry", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 4:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_idleloop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 5:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_idle_to_l0", 4.0, 0, 0, 0, 1, 0, 1);
		    }
		    case 6:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l0_bnce", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 7:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l0_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 8:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l0_to_l1", 4.0, 0, 0, 0, 1, 0, 1);
		    }
		    case 9:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l12_to_l0", 4.0, 0, 0, 0, 1, 0, 1);
		    }
		    case 10:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l1_bnce", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 11:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l1_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 12:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l1_to_l2", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 13:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l2_bnce", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 14:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l2_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 15:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l2_to_l3", 4.0, 0, 0, 0, 1, 0, 1);
		    }
		    case 16:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l345_to_l1", 4.0, 0, 0, 0, 1, 0, 1);
		    }
		    case 17:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l3_bnce", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 18:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l3_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 19:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l3_to_l4", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 20:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l4_bnce", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 21:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l4_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 22:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l4_to_l5", 4.0, 0, 0, 0, 1, 0, 1);
		    }
		    case 23:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l5_bnce", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 24:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "lrgirl_l5_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 25:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 26:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "prtial_gngtlkB", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 27:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "prtial_gngtlkC", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 28:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "prtial_gngtlkD", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 29:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "prtial_gngtlkF", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 30:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "prtial_gngtlkG", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 31:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "prtial_gngtlkH", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 32:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "RAP_A_Loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 33:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "RAP_B_Loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 34:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "RAP_C_Loop", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 35:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "Sit_relaxed", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		    case 36:
		    {
		        ApplyAnimation_UI(playerid, "LOWRIDER", "Tap_hand", 4.0, 1, 0, 0, 0, 0, 1);
		    }
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "  You must be in a compatible lowrider to use this command!");
	}
	return 1;
}