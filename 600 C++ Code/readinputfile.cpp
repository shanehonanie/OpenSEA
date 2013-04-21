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
	std::ostringstream sstream;
	

	for(int i = 0; i < HEADER_LENGTH; i++)
		getline(infile, discard);

	for(;;)
	{
		string prevString = "";
		string curString = "";
		int legalKeywordVal = -1;

		infile >> curString; //curSring is the current string in the text file

		if (infile.eof()) break; //End of File, end parsing

		if (curString == SEAFILE) //ignore the seafile object
		{
			infile.ignore(MAX_IGNORE, '}');
			infile >> curString;
			if (infile.eof()) break; 
		}

		//while (curString == COMMENT_LINE)  //ignore text on rest of line if it is a line comment
		//{
		//	infile.ignore(MAX_IGNORE, EOL);
		//	infile >> curString;
		//	if (infile.eof()) break; 
		

		while (curString.find(COMMENT_LINE) != std::string::npos)  //ignore text on rest of line if it is a line comment
		{
			infile.ignore(MAX_IGNORE, EOL);
			infile >> curString;
			if (infile.eof()) break; 
		}
	
		if(curString == COMMENT_BLOCK_BEGIN) // Ignore comment block 
			while(curString != COMMENT_BLOCK_END)
			{
				infile >> curString;
				if (infile.eof()) break;
			}
	
		legalKeywordVal = legalKeyword(curString); 

		if(legalKeywordVal > UNDEFINED_KEYWORD)
		{
			prevString = curString;
			infile >> curString;
			if (infile.eof()) break; //FIX??

			bool done = keywordHandler(legalKeywordVal, prevString, curString); //is a legal keyword so pass to handler

			//do {
					if (curString == LIST_BEGIN) //check if is a list
					{
						while(curString != LIST_END)
						{
							infile >> curString;

							if(curString != LIST_END)
								theList.push_back(curString);
							
							//infile >> curString; //populate theList with all string args in list
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
		//	}while(!done);
		}
		else
		{
			cerr << "ERROR: UNDEFINED KEYWORD VALUE" << endl;
			break;
		}
	}
}