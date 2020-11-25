#pragma once

#include "BlockFactory.h"

template <typename T>
class BlockMaker: public IBlockMaker
{
public:
	
	BlockMaker(std::string key)
	{
		BlockFactory::Instance().registerNewBlock(key, this);
	}

	virtual Worker* create() const
	{
		return new T();
	}
};