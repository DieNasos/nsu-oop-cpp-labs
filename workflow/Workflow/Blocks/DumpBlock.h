#pragma once

#include "ReplaceBlock.h"

class DumpBlock: public Worker
{
public:

	void work(string* text, vector<string> params);
	BLOCK_TYPE getType();
	Worker* createCopy();
	int getNrOfParams();
};