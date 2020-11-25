#pragma once

#include "ReadfileBlock.h"

class WritefileBlock: public Worker
{
public:

	void work(string* text, vector<string> params);
	BLOCK_TYPE getType();
	Worker* createCopy();
	int getNrOfParams();
};