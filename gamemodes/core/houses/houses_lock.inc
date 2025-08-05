#include <YSI_Coding\y_hooks>

static
    Statement:stmt_LockHouse,
    Statement:stmt_UnlockHouse,
    bool:HouseLockState[MAX_HOUSES];

hook OnMySQLConnected() {
    stmt_LockHouse = MySQL_PrepareStatement(MySQL_GetHandle(), "\
        INSERT INTO \
            house_settings(house_id, locked) \
        VALUES \
            (?, 1)\
    ");
    stmt_UnlockHouse = MySQL_PrepareStatement(MySQL_GetHandle(), "\
        DELETE FROM \
            house_settings \
        WHERE \
            house_id = ? \
    ");
    return 1;
}

House_IsLocked(houseid) {
    return House_IsValid(houseid) && HouseLockState[houseid];
}

House_Lock(houseid) {
    if (!House_IsValid(houseid)) {
        return 0;
    }

    new
        bool: ret;

    if(!House_IsLocked(houseid)) {
        MySQL_BindInt(stmt_LockHouse, 0, houseid);
        ret = MySQL_ExecuteThreaded(stmt_LockHouse);
    }
    else {
        MySQL_BindInt(stmt_UnlockHouse, 0, houseid);
        ret = MySQL_ExecuteThreaded(stmt_UnlockHouse);
    }
    // reverse the house lock state
    HouseLockState[houseid] = !HouseLockState[houseid];
    return ret;
}