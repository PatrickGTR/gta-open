#include <YSI_Coding\y_hooks>

const
    CHANGE_SKILL_PRICE  = 15_000;

hook OnGameModeInit() {
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_YES~"C_WHITE" to change skill", COLOR_WHITE, 359.7139, 173.5916, 1009.3893, 40.0, 26, false);
    new BotAnna = CreateActor(141, 359.7139, 173.5916, 1008.3893, 271.1871);
    SetActorVirtualWorld(BotAnna, 26);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_YES)) {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, 359.7139, 173.5916, 1008.3893)) {
            Cityhall_ChangeSkill(playerid);
        }
    }
    return 1;
}

void:Cityhall_ChangeSkill(playerid) {
    inline const _response(response, listitem, string:inputtext[]) {
        #pragma unused listitem, inputtext
        if(!response) {
            return;
        }

        if(GetPlayerMoney(playerid) < CHANGE_SKILL_PRICE) {
            SendErrorMsg(playerid, "Change Skill denied, Not enough money");
            return;
        }

        Player_ShowJobMenu(playerid);
        GivePlayerMoney(playerid, CHANGE_SKILL_PRICE);
    }

    new
        string[64 + 24];

    format(
        string,
        sizeof(string),
        "Are you sure you want to change your skill?\n\n\
        Skill Change Charge: "C_GREEN"%m",
        CHANGE_SKILL_PRICE
    );

    Dialog_ShowCallback(
        playerid,
        using inline _response,
        DIALOG_STYLE_MSGBOX,
        "Change Skill",
        string,
        "I'm sure",
        "No"
    );
}