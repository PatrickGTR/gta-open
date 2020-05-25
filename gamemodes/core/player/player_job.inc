#include <YSI_Coding\y_hooks>

static 
    PlayerJob[MAX_PLAYERS],
    Statement:stmt_savePlayerJob;

static const JOB_LIST[] = "\
    Drug Dealer\n\
    Weapon Dealer\n\
    Hitman\n\
    Terrorist\n\
    Rapist"
;

// Hook
hook OnMySQLConnected() {
    stmt_savePlayerJob = MySQL_PrepareStatement(MySQL_GetHandle(), "UPDATE players SET job_id = ? WHERE u_id = ?");
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerJob[playerid] = TYPE_NO_JOB;
}

// Functions
Player_SetJob(playerid, jobid, bool:save = false) {


    if(save) {
        MySQL_BindInt(stmt_savePlayerJob, 0, jobid);
        MySQL_BindInt(stmt_savePlayerJob, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerJob);
    }

    PlayerJob[playerid] = jobid;
    return 1;
}

Player_GetJob(playerid) {
    return PlayerJob[playerid];
}

Player_ShowJobMenu(playerid) {
    if (Player_GetJob(playerid) != TYPE_NO_JOB)
        return 0;
    
    new jobID;
    inline _response(ply_id, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused ply_id, dialogid, inputtext
        if (!response) {
            SendErrorMsg(playerid, "You have to select a job!");
            return Player_ShowJobMenu(playerid);
        }

        switch(listitem) {
            case TYPE_DRUGDEALER:  {
                MessageBox_Show(playerid, TYPE_INFORMATION, "Drug Dealer", "Your objective is to create drugs and sell them to earn profit!", 1000 * 10);
                jobID = TYPE_DRUGDEALER;
            }
            case TYPE_WEAPONDEALER: {
                MessageBox_Show(playerid, TYPE_INFORMATION, "Weapon Dealer", "Your objective is to sell any kind of weapons and sell them to earn profit!", 1000 * 10);
                jobID = TYPE_WEAPONDEALER;
            }
            case TYPE_HITMAN: {
                MessageBox_Show(playerid, TYPE_INFORMATION, "Hitman", "Your objective is to kill players with contract and earn a big amount of money!", 1000 * 10);
                jobID = TYPE_HITMAN;
            }
            case TYPE_TERRORIST: {
                MessageBox_Show(playerid, TYPE_INFORMATION, "Terrorist", "Your objective is to plant bombs in cars, explode bank and prison entrances!", 1000 * 10);
                jobID = TYPE_TERRORIST;
            }
            case TYPE_RAPIST: {
                MessageBox_Show(playerid, TYPE_INFORMATION, "Rapist", "Your objective is to infect players with different sexually transmitted disseases!", 1000 * 10);
                jobID = TYPE_RAPIST;
            }
            case TYPE_MECHANIC: {
                MessageBox_Show(playerid, TYPE_INFORMATION, "Mechanic", "Being mechanic allows you to repair your own vehicle and other player's vehicle!", 1000 * 10);
                jobID = TYPE_MECHANIC;
            }
        }
        Player_SetJob(playerid, jobID, true);
        Player_GiveJobWeapons(playerid);
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, "Job Menu", JOB_LIST , "Choose", "Cancel");
    return 1;
}

stock Player_GetJobName(playerid, jobname[], len = sizeof(jobname)) {
    switch(GetPlayerJob(playerid)) {
        case TYPE_DRUGDEALER: {
            strcpy(jobName, "Drug Dealer", len);
        }
        case TYPE_WEAPONDEALER: {
            strcpy(jobName, "Weapon Dealer", len);
        }
        case TYPE_HITMAN: {
            strcpy(jobName, "Hitman", len);
        }
        case TYPE_TERRORIST: {
            strcpy(jobName, "Terrorist", len);
        }
        case TYPE_RAPIST: {
            strcpy(jobName, "Rapist", len);
        }
        case TYPE_MECHANIC: { 
            strcpy(jobName, "Mechanic", len);
        }
    }
}

stock Player_GiveJobWeapons(playerid) {
    switch(Player_GetJob(playerid)) {
        case TYPE_DRUGDEALER: {
            GivePlayerWeapon(playerid, WEAPON_COLT45,   200);
            GivePlayerWeapon(playerid, WEAPON_SHOTGUN,  200);
        }
        case TYPE_WEAPONDEALER: {
            GivePlayerWeapon(playerid, WEAPON_M4,       200);
            GivePlayerWeapon(playerid, WEAPON_SHOTGSPA, 200);
        }
        case TYPE_HITMAN: {
            GivePlayerWeapon(playerid, WEAPON_KNIFE,    1);
            GivePlayerWeapon(playerid, WEAPON_SILENCED, 200);
            GivePlayerWeapon(playerid, WEAPON_SNIPER,   200);
        }
        case TYPE_TERRORIST: {
            GivePlayerWeapon(playerid, WEAPON_RIFLE,    200);
            GivePlayerWeapon(playerid, WEAPON_AK47,     200);
        }
        case TYPE_RAPIST: {
            GivePlayerWeapon(playerid, WEAPON_DILDO,    1);
            GivePlayerWeapon(playerid, WEAPON_COLT45,   200);
            GivePlayerWeapon(playerid, WEAPON_SNIPER,   200);
        }
        case TYPE_MECHANIC: {
            GivePlayerWeapon(playerid, WEAPON_AK47, 200);
            GivePlayerWeapon(playerid, WEAPON_SHOTGSPA, 200);
            GivePlayerWeapon(playerid, WEAPON_COLT45, 200);
        }
    }
    return 1;
}