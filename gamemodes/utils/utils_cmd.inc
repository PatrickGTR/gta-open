#include <sscanf2>

//ALT
#define ALTCMD:%1(%2); CMD:%1(playerid, params[]) return cmd_%2(playerid, params);

// NORMAL
#define CMD:%1(%2) forward cmd_%1(%2); public cmd_%1(%2)

// ADMIN
#define ACMD:[%0]%1(%2,%3) CMD:%1(%2,%3) if (Admin_GetPlayerLevel(%2) < %0) return 0; else

// TESTER 
#define TCMD:%1(%2,%3) CMD:%1(%2,%3) if (!GetPlayerTester(%2) && Admin_GetPlayerLevel(%2) < 0) return 0; else

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
        return CallLocalFunction(prefix, "is", playerid, (params[0] != '\0') ? (params) :( "\1"));
    #endif
}

stock CommandExists(const cmd[])
{
    static prefix[4] = {'c', 'm', 'd', '_'}, cmd_name[28];

    strcpy(cmd_name, cmd);
    return (funcidx(prefix) != -1);
}
