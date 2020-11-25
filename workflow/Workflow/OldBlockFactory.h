#pragma once

#include "Blocks/DumpBlock.h"

class OldBlockFactory
{
public:

	Worker* createBlock(string blockName);
	int getNumOfParams(string blockName);
};