#pragma once

#include "Dude.h";

class Game
{
private:

	const string versionString = "0.1	(alpha)";

	Fighter* createFighter(PK_FIGHTER_TYPE type);
	int pauseFoo(TE2DScene* mainScene);
	void fightAnimate(TE2DText* fightText);
	void mainScenePVEFoo(
		TE2DScene* mainScene,
		PK_FIGHTER_TYPE fighter1Type,
		PK_FIGHTER_TYPE fighter2Type,
		PK_DIFFICULTY difficulty
	);
	void pveFightersChoiceFoo(TE2DScene* menuScene, PK_DIFFICULTY difficulty);
	void mainScenePVPFoo(
		TE2DScene* mainScene,
		PK_FIGHTER_TYPE fighter1Type,
		PK_FIGHTER_TYPE fighter2Type
	);
	void pvpFightersChoiceFoo(TE2DScene* menuScene);
	void pkAnimate(
		TE2DScene* menuScene,
		TE2DText* pkText
	);
	void menuSceneFoo(TE2DScene* menuScene);
	void introSceneFoo();

public:

	void play();
};