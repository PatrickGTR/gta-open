#include <sscanf2>
#include <YSI\y_va>
#include <discord-connector>

#define DCCMD:%1(%2) 				forward discord_%1(%2); public discord_%1(%2)
//CommandsSection
public DCC_OnMessageCreate(DCC_Message:message)
{

	new 
		DCC_Channel: channel,
		DCC_User: author,
		params[32],
		bool:is_bot;

	DCC_GetMessageChannel(message, channel);
	DCC_GetMessageAuthor(message, author);
	DCC_GetMessageContent(message, params, sizeof(params));
	DCC_IsUserBot(author, is_bot);

	if(is_bot) {
		return 0;
	}
	
	if (params[0] == '!')
	{
		new functiona[32], posi = 0;
		while (params[++posi] > ' ') 
		{
			functiona[posi - 1] = tolower(params[posi]);
		}
		format(functiona, sizeof(functiona), "discord_%s", functiona);
		while(params[posi] == ' ') 
		{
			posi++;
		}
		if (!params[posi]) 
		{
			CallLocalFunction(functiona, "dds", _: channel, _: author, "\1");
		}
		else
		{
			CallLocalFunction(functiona, "dds", _: channel, _: author, params[posi]);
		}
	}
	return 1;
}

