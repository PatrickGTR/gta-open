#include <discord-connector>

new DCC_Channel:tester_Discord_Chat;
new DCC_Channel:admin_Discord_Chat;
new DCC_Channel:cmdlogs_Discord_Chat;

hook OnGameModeInit()
{
    tester_Discord_Chat = DCC_FindChannelById("723648604945776721");
    admin_Discord_Chat = DCC_FindChannelById("723669039708241941");
    cmdlogs_Discord_Chat = DCC_FindChannelById("723674514025742528");
}