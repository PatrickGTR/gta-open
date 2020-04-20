enum E_COLOUR_EMBED_DATA 
{
	ce_char,
	ce_colour[9]
}

static embedColours[8][E_COLOUR_EMBED_DATA] = 
{
	{'r', C_RED},
	{'g', C_GREEN},
	{'b', C_BLUE},
	{'y', C_YELLOW},
	{'p', C_PINK},
	{'w', C_WHITE},
	{'o', C_ORANGE},
	{'n', C_NAVY}
};

ExpandMentions(const input[], output[], outCap, colour) 
{
	new
		inLen = strlen(input),
		outLen = 0,
		index,
		numTags,
		mentionID,
		mentionName[MAX_PLAYER_NAME+17],
		mentionColour[9],
		endColour[9],
		colourEmbed,
		bool:skip;

	format(endColour, sizeof(endColour), "{%06x}", colour >>> 8);

	for( ; index < inLen && outLen < outCap; ++index) 
	{
		if(input[index] == '@' && numTags < 3) 
		{
			if(_mentions_isNumeric(input[index + 1])) 
			{
				mentionID = strval(input[index + 1]);
				if(IsPlayerConnected(mentionID)) 
				{
					GetPlayerName(mentionID, mentionName, MAX_PLAYER_NAME);
					format(mentionColour, sizeof(mentionColour), "{%06x}", GetPlayerColor(mentionID) >>> 8);

					// concatenate the player's colour code, their name and then reset the colour
					strcat(output, mentionColour, outCap);
					strcat(output, mentionName, outCap);
					strcat(output, endColour, outCap);

					// update the output string length
					outLen += 8 + strlen(mentionName) + 8;

					numTags++;
					skip = true;
				}
			}
		} 
		else if(input[index] == '&' && numTags < 3) 
		{
			if(_mentions_isAlphabetic(input[index + 1])) 
			{
				colourEmbed = _mentions_getEmbedColourIdx(input[index + 1]);
				if(colourEmbed != -1) 
				{
					strcat(output, embedColours[colourEmbed][ce_colour], outCap);

					// update the output string length
					outLen += 8;

					numTags++;
					skip = true;
				}
			}
		} else 
		{
			if(skip) 
			{
				skip = false;
				continue;
			}

			output[outLen++] = input[index];
		}
	}

	return numTags;
}

_mentions_getEmbedColourIdx(ch) {
	for(new i; i < sizeof(embedColours); i++) 
	{
		if(ch == embedColours[i][ce_char]) 
		{
			return i;
		}
	}
	return -1;
}

_mentions_isNumeric(ch) 
{
	if(ch >= '0' && ch <= '9') 
	{
		return true;
	}
	return false;
}

_mentions_isAlphabetic(ch) 
{
	if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return true;
	}
	return false;
}

