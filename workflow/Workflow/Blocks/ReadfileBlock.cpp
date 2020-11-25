#include "ReadfileBlock.h"

static BlockMaker<ReadfileBlock> readfileBlockMaker("ReadfileBlock");

void ReadfileBlock::work(string* text, vector<string> params)
{
	// params[0] == filename

	if (params.size() == 0)
		throw std::exception("ERROR: no parameters");

	ifstream inputFile;
	inputFile.open(params[0]);

	if (!inputFile.is_open())
		throw std::exception("ERROR: input-file is not opened");

	inputFile.seekg(0, std::ios::end);
	size_t size = inputFile.tellg();
	string fileContent(size, ' ');
	inputFile.seekg(0);
	inputFile.read(&fileContent[0], size);	// getting file's full content in string

	if (fileContent.size() == 0)
		throw std::exception("ERROR: file has no content");

	inputFile.close();

	*text = fileContent;
}

BLOCK_TYPE ReadfileBlock::getType()
{
	return BLOCK_TYPE::IN;
}

Worker* ReadfileBlock::createCopy()
{
	return new ReadfileBlock();
}

int ReadfileBlock::getNrOfParams()
{
	return 1;
}