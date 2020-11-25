#pragma once

#include "Blocks/DumpBlock.h"

class Parser
{
public:

	map <int, pair<string, vector<string>>> parse(BlockFactory* bf, string schemeFilename);
};