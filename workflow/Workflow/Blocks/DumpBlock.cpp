#include "DumpBlock.h"

static BlockMaker<DumpBlock> dumpBlockMaker("DumpBlock");

void DumpBlock::work(string* text, vector<string> params)
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

	outputFile << text;	// writing text
	outputFile.close();
}

BLOCK_TYPE DumpBlock::getType()
{
	return BLOCK_TYPE::INOUT;
}

Worker* DumpBlock::createCopy()
{
	return new DumpBlock();
}

int DumpBlock::getNrOfParams()
{
	return 1;
}