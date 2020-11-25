#include "BlockFactory.h"

// old

BlockFactory::~BlockFactory()
{
	this->registeredBlocks.clear();
}

Worker* BlockFactory::createBlock(string blockName)
{
	this->blockNames.push_back(blockName);
	return this->registeredBlocks[blockName]->createCopy();
}

int BlockFactory::getNumOfParams(string blockName)
{
	return this->registeredBlocks[blockName]->getNrOfParams();
}

void BlockFactory::registerBlock(Worker* block, string blockName)
{
	this->registeredBlocks[blockName] = block;
}

// new

BlockFactory& BlockFactory::Instance()
{
	static BlockFactory factory;
	return factory;
}

Worker* BlockFactory::createNewBlock(std::string blockName)
{
	auto block = this->_blockMap.find(blockName);
	IBlockMaker* blockMaker = block->second;
	return blockMaker->create();
}

void BlockFactory::registerNewBlock(std::string newBlockName, IBlockMaker* newBlock)
{
	if (this->_blockMap.find(newBlockName) != this->_blockMap.end())
	{
		throw new std::exception("ERROR: multiple makers for this block name");
	}
	this->_blockMap[newBlockName] = newBlock;
}