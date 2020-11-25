#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DSound::TE2DSound()
{
	this->buffer = SoundBuffer();
	this->sound = Sound();
}

// VIRTUAL FUNCTIONS FROM TE2DAudio

void TE2DSound::loadSource(string sourceFilename)
{
	// _getcwd(currentWorkDir, sizeof(currentWorkDir));
	// this->buffer.loadFromFile(currentWorkDir + sourceFilename);

	this->buffer.loadFromFile(sourceFilename);
	this->sound.setBuffer(this->buffer);
}

void TE2DSound::setVolume(float volume)
{
	this->sound.setVolume(volume);
}

void TE2DSound::setLoop(bool loop)
{
	this->sound.setLoop(loop);
}

void TE2DSound::play()
{
	this->sound.play();
}

void TE2DSound::pause()
{
	this->sound.pause();
}

void TE2DSound::stop()
{
	this->sound.stop();
}