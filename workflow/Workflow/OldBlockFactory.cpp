#include "OldBlockFactory.h"

Worker* OldBlockFactory::createBlock(string blockName)
{
	if (blockName == "ReadfileBlock")
		return new ReadfileBlock();
	else if (blockName == "WritefileBlock")
		return new WritefileBlock();
	else if (blockName == "ReplaceBlock")
		return new ReplaceBlock();
	else if (blockName == "GrepBlock")
		return new GrepBlock();
	else if (blockName == "SortBlock")
		return new SortBlock();
	else if (blockName == "DumpBlock")
		return new DumpBlock();
}

int OldBlockFactory::getNumOfParams(string blockName)
{
	if (blockName == "ReadfileBlock")
		return 1;
	else if (blockName == "WritefileBlock")
		return 1;
	else if (blockName == "ReplaceBlock")
		return 2;
	else if (blockName == "GrepBlock")
		return 1;
	else if (blockName == "SortBlock")
		return 0;
	else if (blockName == "DumpBlock")
		return 2;
}