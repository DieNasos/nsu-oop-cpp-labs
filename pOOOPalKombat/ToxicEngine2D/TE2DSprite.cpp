#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DSprite::TE2DSprite()
{
	this->sprite = Sprite();

	this->currentAnimation = -1;
}

// GETTERS

// SETTERS

void TE2DSprite::addTexture(string sourceFileName)
{
	Texture texture;
	if (!texture.loadFromFile(sourceFileName))
		cout << "ERROR! TE2DSPRITE.CPP: COULD NOT LOAD TEXTURE FROM FILE "
		<< sourceFileName << "!" << endl;
	else
		this->textures.push_back(texture);
}

void TE2DSprite::deleteTexture(int index)
{
	this->textures.erase(this->textures.begin() + index);
}

void TE2DSprite::setTexture(int index)
{
	this->sprite.setTexture(this->textures[index]);
}

void TE2DSprite::addAnimation()
{
	this->animations.push_back(*new TE2DAnimation);
}

void TE2DSprite::addToAnimation(int animationIndex, int textureIndex)
{
	this->animations[animationIndex].addTexture(textureIndex);
}

void TE2DSprite::deleteFromAnimation(int animationIndex, int textureIndex)
{
	this->animations[animationIndex].deleteTexture(textureIndex);
}

void TE2DSprite::clearAnimation(int animationIndex)
{
	this->animations[animationIndex].clear();
}

void TE2DSprite::setAnimationDelay(int animationIndex, float seconds)
{
	this->animations[animationIndex].setDelay(seconds);
}

void TE2DSprite::setAnimation(int index)
{
	this->currentAnimation = index;
}

void TE2DSprite::copyParameters(TE2DSprite sprite)
{
	// TE2DDrawable
	this->copyCommonParameters(sprite);

	// TE2DSprite
	this->sprite = sprite.sprite;
	this->textures = sprite.textures;
	this->animations = sprite.animations;
	this->currentAnimation = sprite.currentAnimation;
}

// VIRTUAL FUNCTIONS FROM TE2DDrawable

Drawable& TE2DSprite::getDrawable()
{
	if ((this->currentAnimation == -1)
		|| (this->clock.getElapsedTime().asSeconds() <
			this->animations[this->currentAnimation].getDelay()))
		return this->sprite;
	else
	{
		this->sprite.setTexture(
			this->textures[this->animations[this->currentAnimation].getCurrTexIndex()]
		);

		this->animations[this->currentAnimation].incCurrTexIndex();

		if (this->animations[this->currentAnimation].getCurrTexIndex() ==
			this->animations[this->currentAnimation].getSize())
			this->animations[this->currentAnimation].setCurrTexIndex(0);

		this->clock.restart().asSeconds();
		return this->sprite;
	}
}

void TE2DSprite::setPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->sprite.setPosition(this->pos.x, this->pos.y);
}

Vector2f TE2DSprite::getCenter()
{
	Vector2f cntr;

	cntr.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	cntr.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;

	return cntr;
}

FloatRect TE2DSprite::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

Vector2f TE2DSprite::getScale()
{
	return this->sprite.getScale();
}

void TE2DSprite::setScale(float x, float y)
{
	this->sprite.setScale(Vector2f(x, y));
}

float TE2DSprite::getRotation()
{
	return this->sprite.getRotation();
}

void TE2DSprite::setRotation(float rotation)
{
	this->sprite.setRotation(rotation);
}