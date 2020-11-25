#include "pOOOPalKombat.h"

// CONSTRUCTOR
Fighter::Fighter()
{
	this->sprite = new TE2DSprite();
	this->isUlt = false;
	this->clock.restart().asMilliseconds();
	this->lastAttackTime = clock.getElapsedTime().asMilliseconds();
}

// GETTERS

TE2DSprite* Fighter::getSprite()
{
	return this->sprite;
}

int Fighter::getHealth()
{
	return this->health;
}

// SETTERS

void Fighter::setSide(TE2D_DIRECTION side, TE2DScene scene)
{
	this->side = side;

	switch (side)
	{
	case TE2D_LEFT:
		this->textureType = DEFAULT_RIGHT;
		this->sprite->setTexture(DEFAULT_RIGHT);
		this->sprite->setPosition(0, 0);
		break;
	case TE2D_RIGHT:
		this->textureType = DEFAULT_LEFT;
		this->sprite->setTexture(DEFAULT_LEFT);
		this->sprite->setPosition(
			scene.getWindowSize().x - this->sprite->getGlobalBounds().width, 0);
		break;
	default:
		break;
	}
}

void Fighter::setHealth(int health)
{
	this->health = health;
}

void Fighter::setDamage(int damage)
{
	this->damage = damage;
}

void Fighter::setMaxUltLevel(int ultLevel)
{
	this->maxUltLevel = ultLevel;
}

void Fighter::setCurrUltLevel(int ultLevel)
{
	this->currUltLevel = ultLevel;
}

void Fighter::setUltStep(int ultStep)
{
	this->ultStep = ultStep;
}

void Fighter::setMoveParams(
	float acceleration,
	float maxVelocity,
	float multiplier,
	float drag
)
{
	this->sprite->setMoveParams(
		acceleration,
		maxVelocity,
		multiplier,
		drag
	);
}

// OTHER FUNCTIONS

void Fighter::move(TE2DScene scene, TE2D_DIRECTION direction)
{
	if (this->isUlt)
	{
		if ((direction == TE2D_RIGHT) && (this->textureType == ULT_DEFAULT_LEFT))
		{
			this->textureType = ULT_DEFAULT_RIGHT;
			this->sprite->setTexture(ULT_DEFAULT_RIGHT);
		}
		else if ((direction == TE2D_LEFT) && (this->textureType == ULT_DEFAULT_RIGHT))
		{
			this->textureType = ULT_DEFAULT_LEFT;
			this->sprite->setTexture(ULT_DEFAULT_LEFT);
		}
	}
	else
	{
		if ((direction == TE2D_RIGHT) && (this->textureType == DEFAULT_LEFT))
		{
			this->textureType = DEFAULT_RIGHT;
			this->sprite->setTexture(DEFAULT_RIGHT);
		}
		else if ((direction == TE2D_LEFT) && (this->textureType == DEFAULT_RIGHT))
		{
			this->textureType = DEFAULT_LEFT;
			this->sprite->setTexture(DEFAULT_LEFT);
		}
	}

	this->sprite->advancedMove(scene, direction);
}

void Fighter::jump()
{
	this->sprite->jump();
}

void Fighter::attack(TE2DScene* scene, Fighter* fighter,
	TE2DRectangleShape* healthBar, TE2DRectangleShape* ultBar)
{
	if (this->clock.getElapsedTime().asMilliseconds()
		- this->lastAttackTime < 500)
		return;

	this->lastAttackTime = this->clock.getElapsedTime().asMilliseconds();

	if (this->sprite->intersects(fighter->getSprite()))
	{
		this->currUltLevel += ultStep;

		if (this->currUltLevel == this->maxUltLevel)
		{
			this->isUlt = true;
			this->damage *= 2;
			ultBar->setFillColor(2);

			switch (this->textureType)
			{
			case DEFAULT_LEFT:
				this->textureType = ULT_DEFAULT_LEFT;
				this->sprite->setTexture(ULT_DEFAULT_LEFT);
				break;
			case DEFAULT_RIGHT:
				this->textureType = ULT_DEFAULT_RIGHT;
				this->sprite->setTexture(ULT_DEFAULT_RIGHT);
				break;
			default:
				break;
			};
		}

		healthBar->setSize(
			healthBar->getSize().x / fighter->getHealth() * (fighter->getHealth() - this->damage),
			healthBar->getSize().y
		);

		if (!this->isUlt)
			ultBar->setSize(
				ultBar->getSize().x + (int)scene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x
				* this->ultStep * 5,
				ultBar->getSize().y
			);

		fighter->health -= this->damage;
		
		switch (this->side)
		{
		case TE2D_LEFT:
			healthBar->setPosition(
				scene->getWindowSize().x / 2
				+ (int)scene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
				(int)scene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
			);
			if (!this->isUlt)
				ultBar->setPosition(
					ultBar->getPosition().x
					- (int)scene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x
					* this->ultStep * 5,
					ultBar->getPosition().y
				);
			break;
		case TE2D_RIGHT:
			healthBar->setPosition(
				scene->getWindowSize().x / 2 - healthBar->getGlobalBounds().width
				- (int)scene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
				(int)scene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
			);
			break;
		default:
			break;
		}
	}

	switch (this->textureType)
	{
	case DEFAULT_LEFT:
		this->sprite->setTexture(ATTACK_LEFT);
		scene->drawScene();
		Sleep(10);
		this->sprite->setTexture(DEFAULT_LEFT);
		break;
	case DEFAULT_RIGHT:
		this->sprite->setTexture(ATTACK_RIGHT);
		scene->drawScene();
		Sleep(10);
		this->sprite->setTexture(DEFAULT_RIGHT);
		break;
	case ULT_DEFAULT_LEFT:
		this->sprite->setTexture(ULT_ATTACK_LEFT);
		scene->drawScene();
		Sleep(10);
		this->sprite->setTexture(ULT_DEFAULT_LEFT);
		break;
	case ULT_DEFAULT_RIGHT:
		this->sprite->setTexture(ULT_ATTACK_RIGHT);
		scene->drawScene();
		Sleep(10);
		this->sprite->setTexture(ULT_DEFAULT_RIGHT);
		break;
	default:
		break;
	}

	scene->drawScene();
}