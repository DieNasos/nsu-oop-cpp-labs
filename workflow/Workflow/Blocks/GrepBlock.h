#pragma once

#include "WritefileBlock.h"

class GrepBlock: public Worker
{
private:

	bool containsWord(string str, string word);

public:

	void work(string* text, vector<string> params);
	BLOCK_TYPE getType();
	Worker* createCopy();
	int getNrOfParams();
};