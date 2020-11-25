#include "Validator.h"

vector<int> Validator::getChain(string schemeFilename)
{
	/*
	for example:
	"0 -> 2 -> 4 -> 3 -> 1" =>
	chain[0] == 0
	chain[1] == 2
	chain[2] == 4
	etc.
	*/

	ifstream schemeFile;
	vector<int> chain;
	int currSymbolIndex;

	schemeFile.open(schemeFilename);

	schemeFile.seekg(0, std::ios::end);
	size_t size = schemeFile.tellg();
	string schemeFileContent(size, ' ');
	schemeFile.seekg(0);
	schemeFile.read(&schemeFileContent[0], size);	// getting file's full content in string

	for (auto i = 0; i < size; i++)
	{
		if ((schemeFileContent[i] == '>') && (schemeFileContent[i - 1]))
		{
			currSymbolIndex = i - 3;	// found first '>' => first index stands before
			break;
		}
	}

	while (currSymbolIndex < size)
	{
		if (
			(schemeFileContent[currSymbolIndex] != ' ')
			&& (schemeFileContent[currSymbolIndex] != '-')
			&& (schemeFileContent[currSymbolIndex] != '>')
			)
			// converting to int and pushing to chain
			chain.push_back(stoi(to_string(schemeFileContent[currSymbolIndex])) - 48);

		currSymbolIndex++;
	}

	schemeFile.close();

	return chain;
}

int Validator::check(BlockFactory* bf, string schemeFilename, map <int, pair<string, vector<string>>> blocks)
{
	if (blocks.size() == 0)
		throw std::exception("ERROR: no info about blocks");

	vector<int> chain = this->getChain(schemeFilename);
	int isGood = 0;
	Worker* block = bf->createNewBlock(blocks[chain[0]].first);

	if (block->getType() != BLOCK_TYPE::IN)
		isGood = 1;

	delete block;

	block = bf->createNewBlock(blocks[chain[chain.size() - 1]].first);

	if (block->getType() != BLOCK_TYPE::OUT)
		isGood = 3;

	delete block;

	for (auto i = 1; i < chain.size() - 1; i++)
	{
		block = bf->createNewBlock(blocks[chain[i]].first);

		if (block->getType() != BLOCK_TYPE::INOUT)
			isGood = 2;

		delete block;
	}
	
	return isGood;
}