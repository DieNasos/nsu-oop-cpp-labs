#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DDrawable::TE2DDrawable()
{
	this->isDrawable = true;
	
	this->jumpHeight = 0.f;
	this->jumpSpeed = 0.f;
	this->fallSpeed = 0.f;
	this->gravityStrength = 0.f;

	this->isJumping = false;
	this->isOnGround = true;
}

// GETTERS

Vector2f TE2DDrawable::getPosition()
{
	return this->pos;
}

bool TE2DDrawable::getIsDrawable()
{
	return this->isDrawable;
}

int TE2DDrawable::getIndex()
{
	return this->index;
}

bool TE2DDrawable::intersects(TE2DDrawable* drawable)
{
	return this->getGlobalBounds().intersects(drawable->getGlobalBounds());
}

float TE2DDrawable::getJumpHeight()
{
	return this->jumpHeight;
}

float TE2DDrawable::getJumpSpeed()
{
	return this->jumpSpeed;
}

float TE2DDrawable::getCurrJumpSpeed()
{
	return this->currJumpSpeed;
}

float TE2DDrawable::getGravityStrength()
{
	return this->gravityStrength;
}

bool TE2DDrawable::getIsOnGround()
{
	return this->isOnGround;
}

bool TE2DDrawable::getIsJumping()
{
	return this->isJumping;
}

// SETTERS

void TE2DDrawable::setIsDrawable(bool isDrawable)
{
	this->isDrawable = isDrawable;
}

void TE2DDrawable::setIndex(int index)
{
	this->index = index;
}

void TE2DDrawable::setScaleAnimationParams(
	float minScaleX,
	float minScaleY,
	float maxScaleX,
	float maxScaleY,
	float zoomStepX,
	float zoomStepY,
	bool isZooming
)
{
	this->minScale.x = minScaleX;
	this->minScale.y = minScaleY;
	this->maxScale.x = maxScaleX;
	this->maxScale.y = maxScaleY;
	this->zoomStep.x = zoomStepX;
	this->zoomStep.y = zoomStepY;
	this->isZooming = isZooming;
}

void TE2DDrawable::setMoveParams(
	float acceleration,
	float maxVelocity,
	float multiplier,
	float drag
)
{
	this->acceleration = acceleration;
	this->maxVelocity = maxVelocity;
	this->multiplier = multiplier;
	this->drag = drag;
}

void TE2DDrawable::setInCenter()
{
	this->setPosition
	(
		sf::VideoMode::getDesktopMode().width / 2 - this->getGlobalBounds().width / 2,
		sf::VideoMode::getDesktopMode().height / 2 - this->getGlobalBounds().height / 2
	);
}

void TE2DDrawable::setJumpHeight(float jumpHeight)
{
	this->jumpHeight = jumpHeight;
}

void TE2DDrawable::setJumpSpeed(float jumpSpeed)
{
	this->jumpSpeed = jumpSpeed;
	this->currJumpSpeed = jumpSpeed;
}

void TE2DDrawable::setCurrJumpSpeed(float currJumpSpeed)
{
	this->currJumpSpeed = currJumpSpeed;
}

void TE2DDrawable::setFallSpeed(float fallSpeed)
{
	this->fallSpeed = fallSpeed;
	this->currFallSpeed = fallSpeed;
}

void TE2DDrawable::setGravityStrength(float gravityStrength)
{
	this->gravityStrength = gravityStrength;
}

void TE2DDrawable::setIsOnGround(bool isOnGround)
{
	this->isOnGround = isOnGround;
}

void TE2DDrawable::setIsJumping(bool isJumping)
{
	this->isJumping = isJumping;
}

void TE2DDrawable::copyCommonParameters(TE2DDrawable drawable)
{
	this->pos = drawable.pos;
	this->isDrawable = drawable.isDrawable;
	this->minScale = drawable.minScale;
	this->maxScale = drawable.maxScale;
	this->zoomStep = drawable.zoomStep;
	this->isZooming = drawable.isZooming;
	this->currentVelocity = drawable.currentVelocity;
	this->direction = drawable.direction;
	this->acceleration = drawable.acceleration;
	this->maxVelocity = drawable.maxVelocity;
	this->multiplier = drawable.multiplier;
	this->drag = drawable.drag;
}

// VIRTUAL FUNCTIONS

Drawable& TE2DDrawable::getDrawable()
{
	Sprite sprite = *new Sprite;

	return sprite;
}

void TE2DDrawable::setPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

Vector2f TE2DDrawable::getCenter()
{
	return Vector2f();
}

FloatRect TE2DDrawable::getGlobalBounds()
{
	return FloatRect();
}

Vector2f TE2DDrawable::getScale()
{
	return Vector2f();
}

void TE2DDrawable::setScale(float x, float y)
{
	return;
}

float TE2DDrawable::getRotation()
{
	return 0.f;
}

void TE2DDrawable::setRotation(float rotation)
{
	return;
}

// OTHER FUNCTIONS

void TE2DDrawable::move(float offsetX, float offsetY)
{
	this->setPosition(this->pos.x + offsetX, this->pos.y + offsetY);
}

void TE2DDrawable::advancedMove(TE2DScene scene, TE2D_DIRECTION direction)
{
	float dt = scene.getDt();
	this->direction = Vector2f(0.f, 0.f);

	switch (direction)
	{
	case TE2D_UP:
		this->direction.y = -1.f;
		if (this->currentVelocity.y > this->maxVelocity * -1)
			this->currentVelocity.y +=
			this->acceleration * this->direction.y * dt * this->multiplier;
		break;
	case TE2D_DOWN:
		this->direction.y = 1.f;
		if (this->currentVelocity.y < this->maxVelocity)
			this->currentVelocity.y +=
			this->acceleration * this->direction.y * dt * this->multiplier;
		break;
	case TE2D_LEFT:
		this->direction.x = -1.f;
		if (this->currentVelocity.x > this->maxVelocity * -1)
			this->currentVelocity.x +=
			this->acceleration * this->direction.x * dt * this->multiplier;
		break;
	case TE2D_RIGHT:
		this->direction.x = 1.f;
		if (this->currentVelocity.x < this->maxVelocity)
			this->currentVelocity.x +=
			this->acceleration * this->direction.x * dt * this->multiplier;
		break;
	}

	if (this->currentVelocity.x > 0.f)
	{
		this->currentVelocity.x -= this->drag * dt * this->multiplier;

		if (this->currentVelocity.x < 0.f)
			this->currentVelocity.x = 0.f;
	}
	else if (this->currentVelocity.x < 0.f)
	{
		this->currentVelocity.x += this->drag * dt * this->multiplier;

		if (this->currentVelocity.x > 0.f)
			this->currentVelocity.x = 0.f;
	}

	if (this->currentVelocity.y > 0.f)
	{
		this->currentVelocity.y -= this->drag * dt * this->multiplier;

		if (this->currentVelocity.y < 0.f)
			this->currentVelocity.y = 0.f;
	}
	else if (this->currentVelocity.y < 0.f)
	{
		this->currentVelocity.y += this->drag * dt * this->multiplier;

		if (this->currentVelocity.y > 0.f)
			this->currentVelocity.y = 0.f;
	}

	if (this->currentVelocity.x * dt * this->multiplier > 0)
	{
		if (
			(this->getPosition().x
				+ this->currentVelocity.x * dt * this->multiplier
				+ this->getGlobalBounds().width
				<= scene.getBorder(TE2D_RIGHT))
			|| (scene.getBorder(TE2D_RIGHT) == -1)
			)
			this->move(this->currentVelocity.x * dt * this->multiplier, 0);
		else
			this->setPosition(
				scene.getBorder(TE2D_RIGHT) - this->getGlobalBounds().width,
				this->getPosition().y);
	}
	else
	{
		if (
			(this->getPosition().x
				+ this->currentVelocity.x * dt * this->multiplier
				>= scene.getBorder(TE2D_LEFT))
			|| (scene.getBorder(TE2D_LEFT) == -1)
			)
			this->move(this->currentVelocity.x * dt * this->multiplier, 0);
		else
			this->setPosition(scene.getBorder(TE2D_LEFT), this->getPosition().y);
	}

	if ((this->getPosition().y
		+ this->currentVelocity.y * dt * this->multiplier
		+ this->getGlobalBounds().height
		> scene.getGroundLevel())
		&& (scene.getGroundLevel() != -1)
	)
		this->setPosition(
			this->getPosition().x,
			scene.getGroundLevel() - this->getGlobalBounds().height
		);
	else if (this->currentVelocity.y * dt * this->multiplier > 0)
	{
		if (
			(this->getPosition().y
				+ this->currentVelocity.y * dt * this->multiplier
				+ this->getGlobalBounds().height
				<= scene.getBorder(TE2D_DOWN))
			|| (scene.getBorder(TE2D_DOWN) == -1)
			)
			this->move(0, this->currentVelocity.y * dt * this->multiplier);
		else
			this->setPosition(
				this->getPosition().x,
				scene.getBorder(TE2D_DOWN) - this->getGlobalBounds().height);
	}
	else
	{
		if (
			(this->getPosition().y
				+ this->currentVelocity.y * dt * this->multiplier
				>= scene.getBorder(TE2D_UP))
			|| (scene.getBorder(TE2D_UP) == -1)
			)
			this->move(0, this->currentVelocity.y * dt * this->multiplier);
		else
			this->setPosition(this->getPosition().x, 0);
	}
}

void TE2DDrawable::zoom(float offsetX, float offsetY)
{
	this->setScale(this->getScale().x + offsetX, this->getScale().y + offsetY);
}

void TE2DDrawable::makeScaleAnimationStep()
{
	if (this->isZooming)
	{
		if (this->getScale().x < this->maxScale.x)
			this->zoom(this->zoomStep.x, this->zoomStep.y);
		else
			this->isZooming = false;
	}
	else
	{
		if (this->getScale().x > this->minScale.x)
			this->zoom(-this->zoomStep.x, -this->zoomStep.y);
		else
			this->isZooming = true;
	}
}

void TE2DDrawable::rotate(float offset)
{
	this->setRotation(this->getRotation() + offset);
}

void TE2DDrawable::jump()
{
	if (this->isOnGround)
	{
		this->isOnGround = false;
		this->isJumping = true;
	}
}

void TE2DDrawable::fall(TE2DScene scene)
{
	if (this->pos.y
		+ this->getGlobalBounds().height
		+ this->currFallSpeed
		> scene.getGroundLevel())
	{
		this->setPosition(
			this->getPosition().x,
			scene.getGroundLevel()
			- this->getGlobalBounds().height
		);
		this->isOnGround = true;
		this->currFallSpeed = this->fallSpeed;
	}
	else if (!this->isOnGround)
	{
		this->move(0.f, this->currFallSpeed);
		this->currFallSpeed += this->gravityStrength;
	}
}