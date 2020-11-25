#include "Executor.h"

int Executor::execute(string schemeFilename)
{
	BlockFactory& bf = BlockFactory::Instance();
	Parser parser;
	map <int, pair<string, vector<string>>> blocks = parser.parse(&bf, schemeFilename);
	Validator validator;
	vector<int> chain = validator.getChain(schemeFilename);
	int isGood = validator.check(&bf, schemeFilename, blocks);

	if (isGood != 0)
		throw std::exception("ERROR: scheme is invalid");

	string* text = new string("");
	Worker* block;
	vector<string> params;

	for (auto i = 0; i < chain.size(); i++)
	{
		block = bf.createNewBlock(blocks[chain[i]].first);
		block->work(text, blocks[chain[i]].second);
		delete block;
	}

	delete text;
	return 0;
}