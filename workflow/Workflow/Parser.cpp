#include "Parser.h"

map <int, pair<string, vector<string>>> Parser::parse(BlockFactory* bf, string schemeFilename)
{
	ifstream schemeFile;
	string currString;
	map <int, pair<string, vector<string>>> blocks;

	/*
	for example:
	"0 = ReadfileBlock in.txt" =>
	blocks[0] = <"ReadfileBlock", vector[0] == "in.txt">
	*/

	int currID;
	string currBlockName;
	vector<string> currParams;

	schemeFile.open(schemeFilename);

	if (!schemeFile.is_open())
		throw std::exception("ERROR: scheme-file is not opened");

	schemeFile >> currString;	// getting symbols before 1st space in file

	while (true)
	{
		currParams.clear();	// deleting previous params list
		schemeFile >> currString;

		if (currString == "csed")
			break;	// the end of blocks' description

		currID = stoi(currString);	// converting id to int
		schemeFile >> currString;	// skipping '='
		schemeFile >> currString;	// after '=' there stands block's name
		currBlockName = currString;

		Worker* block;
		block = bf->createNewBlock(currBlockName);
		int currNumOfParams = block->getNrOfParams();
		delete block;

		for (auto i = 1; i <= currNumOfParams; i++)
		{
			schemeFile >> currString;	// getting next param
			currParams.push_back(currString);	// pushing it to list
		}

		blocks[currID] = make_pair(currBlockName, currParams);
	}

	schemeFile.close();

	return blocks;
}