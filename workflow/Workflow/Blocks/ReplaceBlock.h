#pragma once

#include "SortBlock.h"

class ReplaceBlock : public Worker
{
private:

	void replace(std::string* inputStr, const std::string& src, const std::string& dst);

public:

	void work(string* text, vector<string> params);
	BLOCK_TYPE getType();
	Worker* createCopy();
	int getNrOfParams();
};