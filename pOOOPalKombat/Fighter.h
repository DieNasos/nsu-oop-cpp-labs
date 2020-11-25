#pragma once

#include "PKBasicIncludes.h"

class Fighter
{
protected:

	TE2DSprite* sprite;
	TE2D_DIRECTION side;
	PK_FIGHTER_TYPE fighterType;
	PK_TEXTURE_TYPE textureType;
	int health;
	int damage;
	int maxUltLevel;
	int currUltLevel;
	int ultStep;
	bool isUlt;
	float lastAttackTime;
	Clock clock;

public:

	// CONSTRUCTOR
	Fighter(const Fighter&) = delete;
	Fighter & operator = (const Fighter&) = delete;

	Fighter();
	~Fighter() { delete sprite; }

	// GETTERS
	TE2DSprite* getSprite();
	int getHealth();

	// SETTERS
	// void setFighterType(PK_FIGHTER_TYPE type, TE2DScene scene);
	void setSide(TE2D_DIRECTION side, TE2DScene scene);
	void setHealth(int health);
	void setDamage(int damage);
	void setMaxUltLevel(int ultLevel);
	void setCurrUltLevel(int ultLevel);
	void setUltStep(int ultStep);
	void setMoveParams(
		float acceleration,
		float maxVelocity,
		float multiplier,
		float drag
	);

	// OTHER FUNCTIONS
	void move(TE2DScene scene, TE2D_DIRECTION direction);
	void jump();
	void attack(
		TE2DScene* scene, Fighter* fighter,
		TE2DRectangleShape* healthBar, TE2DRectangleShape* ultBar
	);
};