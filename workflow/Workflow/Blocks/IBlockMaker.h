#pragma once

#include "Worker.h"

class IBlockMaker
{
public:

	virtual Worker* create() const = 0;
	virtual ~IBlockMaker() = default;
};