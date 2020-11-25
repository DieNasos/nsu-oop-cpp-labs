#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DMusic::TE2DMusic()
{
	//this->music = *new Music;
}

// VIRTUAL FUNCTIONS FROM TE2DAudio

void TE2DMusic::loadSource(string sourceFilename)
{
	this->music.openFromFile(sourceFilename);
}

void TE2DMusic::setVolume(float volume)
{
	this->music.setVolume(volume);
}

void TE2DMusic::setLoop(bool loop)
{
	this->music.setLoop(loop);
}

void TE2DMusic::play()
{
	this->music.play();
}

void TE2DMusic::pause()
{
	this->music.pause();
}

void TE2DMusic::stop()
{
	this->music.stop();
}