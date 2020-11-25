#include "ReplaceBlock.h"

static BlockMaker<ReplaceBlock> replaceBlockMaker("ReplaceBlock");

void ReplaceBlock::replace(std::string* inputStr, const std::string& src, const std::string& dst)
{
	string result(*inputStr);

	size_t pos = result.find(src);
	while (pos != string::npos)
	{
		result.replace(pos, src.size(), dst);
		pos = result.find(src, pos);
	}

	*inputStr =  result;
}

void ReplaceBlock::work(string* text, vector<string> params)
{
	// params[0] == word 1
	// params[1] == word 2

	if (params.size() == 0)
		throw std::exception("ERROR: no parameters");

	if (text->size() == 0)
		throw std::exception("ERROR: text is empty");

	if (params[0] == "")
		throw std::exception("ERROR: replacing string shouldn't be empty");

	if (params[0].size() != params[1].size())
		throw std::exception("ERROR: strings don't have same size");

	this->replace(text, params[0], params[1]);
}

BLOCK_TYPE ReplaceBlock::getType()
{
	return BLOCK_TYPE::INOUT;
}

Worker* ReplaceBlock::createCopy()
{
	return new ReplaceBlock();
}

int ReplaceBlock::getNrOfParams()
{
	return 2;
}