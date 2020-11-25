#pragma once

#include "IBlockMaker.h"

class BlockFactory
{
private:

	// old:
	vector<string> blockNames;
	map <string, Worker*> registeredBlocks;

	// new:
	std::map<std::string, IBlockMaker*> _blockMap;
	BlockFactory() = default;

public:

	// old:
	~BlockFactory();
	Worker* createBlock(string blockName);
	int getNumOfParams(string blockName);
	void registerBlock(Worker* block, string blockName);

	// new:
	BlockFactory(const BlockFactory&) = delete;
	BlockFactory& operator = (BlockFactory&) = delete;
	static BlockFactory& Instance();
	Worker* createNewBlock(std::string blockName);
	void registerNewBlock(std::string newBlockName, IBlockMaker* newBlock);
};