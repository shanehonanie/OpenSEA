#include "readinputfile.h"


ReadInput::ReadInput()
{}


ReadInput::~ReadInput()
{}


void ReadInput::setData(istream& infile)
{
	int encloseBracketCount = 0;
	vector<string> theList;
	string discard;
	string prevString = "";
	string curString = "";
	int legalKeywordVal = -1;
	bool directList = false;
	char ignoreChars[2];
	ignoreChars[0] = ';';
	ignoreChars[1] = '\"';

	for(;;)
	{
		infile >> curString; //curSring is the current string in the text file

		if (infile.eof()) break; //End of File, end parsing

		legalKeywordVal = legalKeyword(curString); 

		if (curString == SEAFILE) //ignore the seafile object
		{
			infile.ignore(MAX_IGNORE, '}'); //need to make const
			if (infile.eof()) break; 
		}
		else if (curString.find(COMMENT_LINE) != std::string::npos)
		{
			infile.ignore(MAX_IGNORE, EOL);
			if (infile.eof()) break; 
		}
		else if (curString == COMMENT_BLOCK_BEGIN)
		{
			for(;;)
			{
				infile >> curString;
				if (infile.eof()) break;

				if(curString == COMMENT_BLOCK_END)
				{
					break;
				}
			}
		}
		//else if(curString == QUOTE)
		//{
		//	infile.ignore(MAX_IGNORE, '\"'); //Need to make const
		//	if (infile.eof()) break;
		//}
		else if(legalKeywordVal > UNDEFINED_KEYWORD)
		{
			prevString = curString;
			infile >> curString;
			if (infile.eof()) break; 

			for(int i = 0; i < 2; i++)
				curString.erase(std::remove(curString.begin(), curString.end(), ignoreChars[i]), curString.end());

			bool done = keywordHandler(legalKeywordVal, prevString, curString); //is a legal keyword so pass to handler

			if (curString == LIST_BEGIN) //check if is a list
			{
				while(curString != LIST_END)
				{
					infile >> curString;

					int index = curString.find(KEY_VAL_SEPERATOR);

					if ((curString != LIST_END) && (index != std::string::npos))
					{
						directList = true;
						string key = curString.substr(0, index);
						string val = curString.substr((index+1));
						theList.push_back(key);
						theList.push_back(val);
					}
					else if(curString != LIST_END)
						theList.push_back(curString);
							
					if (infile.eof()) 
					{
						cerr << "ERROR: ILLEGAL LIST FORMAT" << endl;
							break;
					}
				}
				done = keywordHandler(legalKeywordVal, theList, directList);
				directList = false;
				theList.clear();
		}

		if (infile.eof()) break; //End of File, end parsing
		}
	}
}
