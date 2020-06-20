#include <sscanf2>
#include <YSI\y_va>
#include <discord-connector>

#define DC_CMD:%0(DCC_User:%1,%2)          \
			forward dc_cmd_%0(DCC_User:%1, %2); \
			public dc_cmd_%0(DCC_User:%1, %2)

			
//CallBacks
forward OnDCCommandPerformed(const args[], success);		
forward SendDC(const channel[], const fmat[], va_args<>);

//Functions

public SendDC(const channel[], const fmat[], va_args<>)
{
    new
        str[145];
    va_format(str, sizeof (str), fmat, va_start<2>);
	new 
		DCC_Channel:BotChannel = DCC_FindChannelById(channel);
    return DCC_SendChannelMessage(BotChannel, str);
}
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
	
	new dmsg[10][128];
	explode(dmsg, params, " ", 2); // Used so we can see if the arguments next to command are empty or have value.

	new command[32], args[128];
	sscanf(params, "s[32]s[128]", command, args); // Sperate message in COMMAND and arguments.
	if(strfind(command, CMD_PREFIX, true) != -1) // Check if command have prefix defined above.
	{
		new funcdc[32];
		strdel(command, 0, 1);
		format(funcdc, sizeof(funcdc), "dc_cmd_%s", command); // Format function.
	
		if(isnull(dmsg[1])) {
			CallLocalFunction("OnDCCommandPerformed", "si", params, CallLocalFunction(funcdc, "is", _:author, "\1"));
		} else CallLocalFunction("OnDCCommandPerformed", "si", params, CallLocalFunction(funcdc, "is", _:author, args));
	}
	return 1;
}
//Explode
stock explode(aExplode[][], const sSource[], const sDelimiter[] = " ", iVertices = sizeof aExplode, iLength = sizeof aExplode[])
{
	new
		iNode,
		iPointer,
		iPrevious = -1,
		iDelimiter = strlen(sDelimiter);

	while(iNode < iVertices)
	{
		iPointer = strfind(sSource, sDelimiter, false, iPointer);

		if(iPointer == -1)
		{
			strmid(aExplode[iNode], sSource, iPrevious, strlen(sSource), iLength);
			break;
		}
		else
		{
			strmid(aExplode[iNode], sSource, iPrevious, iPointer, iLength);
		}

		iPrevious = (iPointer += iDelimiter);
		++iNode;
	}

	return iPrevious;
}