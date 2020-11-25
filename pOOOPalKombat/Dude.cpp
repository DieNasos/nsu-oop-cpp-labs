#include "Dude.h"

Dude::Dude()
{
	this->sprite->addTexture("Files/Images/dude1l.png");
	this->sprite->addTexture("Files/Images/dude1r.png");
	this->sprite->addTexture("Files/Images/dude2l.png");
	this->sprite->addTexture("Files/Images/dude2r.png");
	this->sprite->addTexture("Files/Images/dude3l.png");
	this->sprite->addTexture("Files/Images/dude3r.png");
	this->sprite->addTexture("Files/Images/dude4l.png");
	this->sprite->addTexture("Files/Images/dude4r.png");

	this->sprite->setFallSpeed(1.f);
	this->sprite->setJumpSpeed(10.f);
	this->sprite->setJumpHeight(768);
	this->sprite->setGravityStrength(0.1f);
}