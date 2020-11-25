#pragma once

#include "GrepBlock.h"

class SortBlock: public Worker
{
private:

	void swap(string* str1, string* str2);
	bool isBigger(string str1, string str2);

public:

	void work(string* text, vector<string> params);
	BLOCK_TYPE getType();
	Worker* createCopy();
	int getNrOfParams();
};