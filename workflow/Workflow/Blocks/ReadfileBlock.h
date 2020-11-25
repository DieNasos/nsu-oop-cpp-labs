#pragma once

#include "BlockMaker.h"

class ReadfileBlock: public Worker
{
public:

	void work(string* text, vector<string> params);
	BLOCK_TYPE getType();
	Worker* createCopy();
	int getNrOfParams();
};