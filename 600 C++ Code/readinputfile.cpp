#include "readinputfile.h"


ReadInput::ReadInput()
{

}


ReadInput::~ReadInput()
{

}


void ReadInput::setData(istream& infile)
{
	
	int encloseBracketCount = 0;
	vector<string> theList;
	string discard;
	string prevString = "";
	string curString = "";
	int legalKeywordVal = -1;


	for(;;)
	{
		infile >> curString; //curSring is the current string in the text file

		if (infile.eof()) break; //End of File, end parsing

		legalKeywordVal = legalKeyword(curString); 

		if (curString == SEAFILE) //ignore the seafile object
		{
			infile.ignore(MAX_IGNORE, '}');
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
		else if(legalKeywordVal > UNDEFINED_KEYWORD)
		{
			prevString = curString;
			infile >> curString;
			if (infile.eof()) break; 

			bool done = keywordHandler(legalKeywordVal, prevString, curString); //is a legal keyword so pass to handler

			if (curString == LIST_BEGIN) //check if is a list
			{
				while(curString != LIST_END)
				{
					infile >> curString;

					if(curString != LIST_END)
						theList.push_back(curString);
							
					if (infile.eof()) 
					{
						cerr << "ERROR: ILLEGAL LIST FORMAT" << endl;
							break;
					}
				}
				done = keywordHandler(legalKeywordVal, theList);
				theList.clear();
		}

		if (infile.eof()) break; //End of File, end parsing
		}
		//else
		//{
		//	cerr << "ERROR: UNDEFINED KEYWORD VALUE" << endl;
		//	//break;
		//}
	}
}
