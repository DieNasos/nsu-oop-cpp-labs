#include "Stepan.h"

Stepan::Stepan()
{
	this->sprite->addTexture("Files/Images/stepan1l.png");
	this->sprite->addTexture("Files/Images/stepan1r.png");
	this->sprite->addTexture("Files/Images/stepan2l.png");
	this->sprite->addTexture("Files/Images/stepan2r.png");
	this->sprite->addTexture("Files/Images/stepan3l.png");
	this->sprite->addTexture("Files/Images/stepan3r.png");
	this->sprite->addTexture("Files/Images/stepan4l.png");
	this->sprite->addTexture("Files/Images/stepan4r.png");
	
	this->sprite->setFallSpeed(1.f);
	this->sprite->setJumpSpeed(10.f);
	this->sprite->setJumpHeight(768);
	this->sprite->setGravityStrength(0.1f);
}