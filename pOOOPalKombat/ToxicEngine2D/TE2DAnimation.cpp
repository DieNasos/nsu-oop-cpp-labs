#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DAnimation::TE2DAnimation()
{
}

// GETTERS

int TE2DAnimation::getSize()
{
	return this->animation.size();
}

int TE2DAnimation::getCurrTexIndex()
{
	return this->currTexIndex;
}

float TE2DAnimation::getDelay()
{
	return this->delay;
}

// SETTERS

void TE2DAnimation::addTexture(int textureIndex)
{
	this->animation.push_back(textureIndex);
}

void TE2DAnimation::deleteTexture(int textureIndex)
{
	this->animation.erase(this->animation.begin() + textureIndex);
}

void TE2DAnimation::clear()
{
	for (auto i = 0; i < this->animation.size(); i++)
		this->animation.pop_back();
}

void TE2DAnimation::setCurrTexIndex(int index)
{
	this->currTexIndex = index;
}

void TE2DAnimation::incCurrTexIndex()
{
	this->currTexIndex++;
}

void TE2DAnimation::setDelay(float seconds)
{
	this->delay = seconds;
}