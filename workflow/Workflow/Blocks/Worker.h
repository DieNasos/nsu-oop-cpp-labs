#pragma once

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

enum class BLOCK_TYPE
{
	IN,
	OUT,
	INOUT
};

class Worker
{
public:

	virtual void work(string* text, vector<string> params) = 0;
	virtual BLOCK_TYPE getType() = 0;
	virtual Worker* createCopy() = 0;
	virtual int getNrOfParams() = 0;
};