#pragma once

#include "Parser.h"

class Validator
{
public:

	vector<int> getChain(string schemeFilename);
	int check(BlockFactory* bf, string schemeFilename, map <int, pair<string, vector<string>>> blocks);
};