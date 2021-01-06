#include <sscanf2>

//ALT
#define ALTCMD:%1(%2); CMD:%1(playerid, params[]) return cmd_%2(playerid, params);

// NORMAL
#define CMD:%1(%2) forward cmd_%1(%2); public cmd_%1(%2)

// ADMIN
_@ACMD_CHECK_ADM(playerid, const cmd[], const params[], const level) {
    if(Admin_GetPlayerLevel(playerid) < level) {
        return false;
    }
    SendAdminCmdUsage(playerid, cmd, params);
    return true;
}
#define @ACMD_PARAMS_REPLACE:%0[] %0
#define ACMD:[%0]%1(%2,%3) CMD:%1(%2,%3)if(!_@ACMD_CHECK_ADM(%2,#%1,@ACMD_PARAMS_REPLACE:%3,%0))return 0;else

// TESTER
#define TCMD:%1(%2,%3) CMD:%1(%2,%3) if (!GetPlayerTester(%2) && Admin_GetPlayerLevel(%2) == 0) return 0; else

#if defined OnPlayerCommandReceived
    forward OnPlayerCommandReceived(playerid, cmd[]);
#endif

#if defined OnPlayerCommandPerformed
    forward OnPlayerCommandPerformed(playerid, cmd[], success);
#endif

public OnPlayerCommandText(playerid, cmdtext[])
{
    static prefix[4] = {'c', 'm', 'd', '_'}, cmd[28];
    static params[126];

    params = "\1";
    sscanf(cmdtext[1], "s[28]s[126]", cmd, params);

    for (new i = strlen(cmd); --i != -1;)
    {
        cmd[i] |= 0x20;
    }

    #if defined OnPlayerCommandReceived
        if (!OnPlayerCommandReceived(playerid, cmd)) return 1;
    #endif

    #if defined OnPlayerCommandPerformed
        return OnPlayerCommandPerformed(playerid, cmd, CallLocalFunction(prefix, "is", playerid, (params[0] != '\0') ? (params) :("\1")));
    #else
        return CallLocalFunction(prefix, "is", playerid, (params[0] != '\0') ? (params) :("\1"));
    #endif
}

stock CommandExecute(playerid, const cmd[], const params[] = "\1", {GLOBAL_TAG_TYPTES, _}:...) {
    if(!CommandExists(cmd)) {
        return 0;
    }

    new
        prefix[] = "cmd_",
        cmd_name[28];

    strcat(cmd_name, prefix);
    strcat(cmd_name, cmd);

    new
        tmp[32];
    formatex(tmp, sizeof(tmp), params, ___(3));
    CallLocalFunction(cmd_name, "ds", playerid, tmp);
    return 1;
}

stock CommandExists(const cmd[]) {
    new
        prefix[] = "cmd_",
        cmd_name[28];

    strcat(cmd_name, prefix);
    strcat(cmd_name, cmd);

    return (funcidx(cmd_name) != -1);
}
