#include <utils_fix>
#include <utils_cmd>
#include <utils_colours>
#include <utils_vehicles>
#include <utils_player>


#include <logger>
//extras
stock LOGGER_FIELD:_p(const field[], playerid) {
    new result[MAX_FIELD_NAME + 1 + MAX_FIELD_VALUE];
    formatex(result, sizeof(result), "%s=\"%p\"", field, playerid);
    return LOGGER_FIELD:result;
}

stock IsNumeric(const string[])
{
    new
        ch, i;
    while ((ch = string[i++])) if (!('0' <= ch <= '9')) {
        return 0;
    }
    return 1;
}

