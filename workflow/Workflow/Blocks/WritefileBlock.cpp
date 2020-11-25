#include "WritefileBlock.h"

static BlockMaker<WritefileBlock> writefileBlockMaker("WritefileBlock");

void WritefileBlock::work(string* text, vector<string> params)
{
	// params[0] == filename

	if (params.size() == 0)
		throw std::exception("ERROR: no parameters");

	ofstream outputFile;
	outputFile.open(params[0]);

	if (!outputFile.is_open())
		throw std::exception("ERROR: output-file is not opened");

	if (text->size() == 0)
		throw std::exception("ERROR: nothing to write in file");

	outputFile << *text;	// writing text
	outputFile.close();
}

BLOCK_TYPE WritefileBlock::getType()
{
	return BLOCK_TYPE::OUT;
}

Worker* WritefileBlock::createCopy()
{
	return new WritefileBlock();
}

int WritefileBlock::getNrOfParams()
{
	return 1;
}