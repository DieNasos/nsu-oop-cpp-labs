#include "Game.h"

Fighter* Game::createFighter(PK_FIGHTER_TYPE type)
{
	if (type == PK_FIGHTER_TYPE::STEPAN)
		return new Stepan();

	if (type == PK_FIGHTER_TYPE::DUDE)
		return new Dude();

	return new Fighter();
}

int Game::pauseFoo(TE2DScene* mainScene)
{
	TE2DScene pauseScene;
	pauseScene.createWindow(
		pauseScene.getScreenResolution().x,
		pauseScene.getScreenResolution().y,
		"pOOOPal Kombat",
		Style::Fullscreen
	);
	pauseScene.setFramerateLimit(100);
	pauseScene.setCursorVisible(true);
	pauseScene.setBackgroundColor(Color::Green);

	TE2DText pauseText;
	pauseText.addFont("Files/Fonts/3952.ttf");
	pauseText.setFont(0);
	pauseText.addColor(Color::White);
	pauseText.addColor(Color::Black);
	pauseText.setFillColor(0);
	pauseText.setOutlineThickness(5.f);
	pauseText.setOutlineColor(1);
	pauseText.setSize(
		(int)pauseScene.getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 42
	);
	pauseText.addString("PAUSE");
	pauseText.setString(0);
	pauseText.setPosition(
		pauseScene.getScreenResolution().x / 2 - pauseText.getGlobalBounds().width / 2,
		pauseScene.getScreenResolution().y / 4 - pauseText.getGlobalBounds().height / 2
	);
	pauseText.setScale(1.f, 1.f);
	pauseText.setScaleAnimationParams(
		pauseText.getScale().x, pauseText.getScale().y,
		2.f, 2.f,
		0.01f, 0.01f,
		true
	);

	TE2DText continueText;
	continueText.addFont("Files/Fonts/3952.ttf");
	continueText.setFont(0);
	continueText.addColor(Color::White);
	continueText.addColor(Color::Black);
	continueText.setFillColor(0);
	continueText.setOutlineThickness(3.f);
	continueText.setOutlineColor(1);
	continueText.setSize(
		(int)pauseScene.getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	continueText.addString("CONTINUE");
	continueText.setString(0);

	TE2DRectangleButton continueButton;
	continueButton.addColor(Color::Red);
	continueButton.addColor(Color::Blue);
	continueButton.addColor(Color::Black);
	continueButton.setDefaultFillColor(0);
	continueButton.setDefaultOutlineColor(2);
	continueButton.setDefaultOutlineThickness(5.f);
	continueButton.setActiveFillColor(1);
	continueButton.setActiveOutlineColor(2);
	continueButton.setActiveOutlineThickness(7.f);
	continueButton.setSize(
		pauseScene.getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		pauseScene.getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	continueButton.setText(&continueText);
	continueButton.setPosition(
		pauseScene.getWindowSize().x / 2 - continueButton.getGlobalBounds().width / 2,
		pauseScene.getScreenResolution().y / 2
	);

	TE2DText exitText;
	exitText.copyParameters(continueText);
	exitText.addString("MENU");
	exitText.setString(1);

	TE2DRectangleButton exitButton;
	exitButton.copyParameters(continueButton);
	exitButton.setText(&exitText);
	exitButton.setPosition(
		pauseScene.getWindowSize().x / 2 - exitButton.getGlobalBounds().width / 2,
		pauseScene.getScreenResolution().y / 3 * 2
	);

	pauseScene.addDrawable(&pauseText);
	pauseScene.addDrawable(&continueButton);
	pauseScene.addDrawable(&continueText);
	pauseScene.addDrawable(&exitButton);
	pauseScene.addDrawable(&exitText);

	while (pauseScene.isWorking())
	{
		pauseText.makeScaleAnimationStep();
		pauseText.setPosition(
			pauseScene.getScreenResolution().x / 2 - pauseText.getGlobalBounds().width / 2,
			pauseScene.getScreenResolution().y / 4 - pauseText.getGlobalBounds().height / 2
		);

		if (continueButton.isPressed(pauseScene, Mouse::Button::Left))
		{
			pauseScene.closeWindow();
			return 0;
		}

		if (exitButton.isPressed(pauseScene, Mouse::Button::Left))
		{
			pauseScene.closeWindow();
			return 1;
		}

		pauseScene.drawScene();
	}
}

void Game::fightAnimate(TE2DText* fightText)
{
	fightText->makeScaleAnimationStep();
	fightText->setInCenter();
}

void Game::mainScenePVEFoo(
	TE2DScene* mainScene,
	PK_FIGHTER_TYPE fighter1Type,
	PK_FIGHTER_TYPE fighter2Type,
	PK_DIFFICULTY difficulty
)	// versus bot
{
	mainScene->setCursorVisible(false);
	mainScene->setGroundLevel(mainScene->getScreenResolution().y);
	mainScene->setBorders(0, mainScene->getWindowSize().x, 0, mainScene->getWindowSize().y);

	TE2DText fightText;
	fightText.addFont("Files/Fonts/3952.ttf");
	fightText.setFont(0);
	fightText.addColor(Color::White);
	fightText.addColor(Color::Black);
	fightText.setFillColor(0);
	fightText.setOutlineThickness(5.f);
	fightText.setOutlineColor(1);
	fightText.setSize(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 42
	);
	fightText.addString("5");
	fightText.addString("4");
	fightText.addString("3");
	fightText.addString("2");
	fightText.addString("1");
	fightText.addString("FIGHT!");
	fightText.setString(0);
	fightText.setInCenter();
	fightText.setScale(1.f, 1.f);
	fightText.setScaleAnimationParams(
		fightText.getScale().x, fightText.getScale().y,
		2.f, 2.f,
		0.01f, 0.01f,
		true
	);

	unique_ptr<Fighter> fighter1Ptr(this->createFighter(fighter1Type));
	Fighter &fighter1 = *fighter1Ptr;
	// fighter1.setFighterType(fighter1Type, *mainScene);
	fighter1.getSprite()->setScale(
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 2,
		mainScene->getScreenResolution().y / TE2D_HD_SCREEN_SIZE.y * 2
	);
	fighter1.setSide(TE2D_LEFT, *mainScene);

	unique_ptr<Fighter> fighter2Ptr(this->createFighter(fighter2Type));
	Fighter &fighter2 = *fighter2Ptr;
	// fighter2.setFighterType(fighter2Type, *mainScene);
	fighter2.getSprite()->setScale(
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 2,
		mainScene->getScreenResolution().y / TE2D_HD_SCREEN_SIZE.y * 2
	);
	fighter2.setSide(TE2D_RIGHT, *mainScene);

	switch (difficulty)
	{
	case EASY:
		fighter1.setHealth(120);
		fighter1.setDamage(4);
		fighter1.setMaxUltLevel(50);
		fighter1.setCurrUltLevel(0);
		fighter1.setUltStep(5);
		fighter1.setMoveParams(1.f, 25.f, 50.f, 0.9f);
		fighter2.setHealth(80);
		fighter2.setDamage(2);
		fighter2.setMaxUltLevel(120);
		fighter2.setCurrUltLevel(0);
		fighter2.setUltStep(4);
		fighter2.setMoveParams(1.f, 25.f, 18.f, 0.9f);
		break;
	case NORMAL:
		fighter1.setHealth(100);
		fighter1.setDamage(2);
		fighter1.setMaxUltLevel(100);
		fighter1.setCurrUltLevel(0);
		fighter1.setUltStep(4);
		fighter1.setMoveParams(1.f, 25.f, 50.f, 0.9f);
		fighter2.setHealth(100);
		fighter2.setDamage(2);
		fighter2.setMaxUltLevel(100);
		fighter2.setCurrUltLevel(0);
		fighter2.setUltStep(4);
		fighter2.setMoveParams(1.f, 25.f, 50.f, 0.9f);
		break;
	case HARD:
		fighter1.setHealth(80);
		fighter1.setDamage(2);
		fighter1.setMaxUltLevel(120);
		fighter1.setCurrUltLevel(0);
		fighter1.setUltStep(4);
		fighter1.setMoveParams(1.f, 25.f, 18.f, 0.9f);
		fighter2.setHealth(120);
		fighter2.setDamage(4);
		fighter2.setMaxUltLevel(50);
		fighter2.setCurrUltLevel(0);
		fighter2.setUltStep(5);
		fighter2.setMoveParams(1.f, 25.f, 50.f, 0.9f);
		break;
	default:
		break;
	}

	TE2DRectangleShape healthBar1;
	healthBar1.addColor(Color::Red);
	healthBar1.addColor(Color::Black);
	healthBar1.setFillColor(0);
	healthBar1.setOutlineColor(1);
	healthBar1.setOutlineThickness(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 5
	);
	healthBar1.setSize(
		(float)fighter1.getHealth()
		* (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 5,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);
	healthBar1.setPosition(
		mainScene->getWindowSize().x / 2
		- healthBar1.getGlobalBounds().width
		- (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	TE2DRectangleShape ultBar1;
	ultBar1.addColor(Color::Yellow);
	ultBar1.addColor(Color::Black);
	ultBar1.addColor(Color::Blue);
	ultBar1.setFillColor(0);
	ultBar1.setOutlineColor(1);
	ultBar1.setOutlineThickness(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 5
	);
	ultBar1.setSize(
		0.f,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);
	ultBar1.setPosition(
		mainScene->getWindowSize().x / 2
		- ultBar1.getGlobalBounds().width
		- (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
		+ healthBar1.getSize().y
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	TE2DRectangleShape healthBar2;
	healthBar2.copyParameters(healthBar1);
	healthBar2.setPosition(
		mainScene->getWindowSize().x / 2
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	TE2DRectangleShape ultBar2;
	ultBar2.copyParameters(ultBar1);
	ultBar2.setPosition(
		mainScene->getWindowSize().x / 2
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
		+ healthBar2.getSize().y
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	TE2DText winText;
	winText.addFont("Files/Fonts/3952.ttf");
	winText.setFont(0);
	winText.addColor(Color::White);
	winText.addColor(Color::Black);
	winText.setFillColor(0);
	winText.setOutlineThickness(5.f);
	winText.setOutlineColor(1);
	winText.setSize(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 42
	);
	winText.setScale(1.f, 1.f);
	winText.setScaleAnimationParams(
		winText.getScale().x, winText.getScale().y,
		2.f, 2.f,
		0.01f, 0.01f,
		true
	);
	winText.addString("YOU WIN!");
	winText.addString("BOT WINS!");

	TE2DText againText;
	againText.addFont("Files/Fonts/3952.ttf");
	againText.setFont(0);
	againText.addColor(Color::White);
	againText.addColor(Color::Black);
	againText.setFillColor(0);
	againText.setOutlineThickness(3.f);
	againText.setOutlineColor(1);
	againText.setSize(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	againText.addString("AGAIN");
	againText.setString(0);

	TE2DRectangleButton againButton;
	againButton.addColor(Color::Red);
	againButton.addColor(Color::Blue);
	againButton.addColor(Color::Black);
	againButton.setDefaultFillColor(0);
	againButton.setDefaultOutlineColor(2);
	againButton.setDefaultOutlineThickness(5.f);
	againButton.setActiveFillColor(1);
	againButton.setActiveOutlineColor(2);
	againButton.setActiveOutlineThickness(7.f);
	againButton.setSize(
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	againButton.setText(&againText);
	againButton.setPosition(
		mainScene->getWindowSize().x / 2 - againButton.getGlobalBounds().width / 2,
		mainScene->getScreenResolution().y / 2
	);

	TE2DText exitText;
	exitText.copyParameters(againText);
	exitText.addString("MENU");
	exitText.setString(1);

	TE2DRectangleButton exitButton;
	exitButton.copyParameters(againButton);
	exitButton.setText(&exitText);
	exitButton.setPosition(
		mainScene->getWindowSize().x / 2 - exitButton.getGlobalBounds().width / 2,
		mainScene->getScreenResolution().y / 3 * 2
	);

	mainScene->addDrawable(&fightText);
	mainScene->addDrawable(&healthBar1);
	mainScene->addDrawable(&healthBar2);
	mainScene->addDrawable(&ultBar1);
	mainScene->addDrawable(&ultBar2);
	mainScene->addDrawable(fighter1.getSprite());
	mainScene->addDrawable(fighter2.getSprite());

	int fightTextCurrentStringIndex = 1;
	Clock clock;

	while (mainScene->isWorking())
	{
		while (fightText.getCurrentStringIndex() != 5)
		{
			clock.restart().asMilliseconds();

			while (clock.getElapsedTime().asMilliseconds() < 1000)
			{
				fightAnimate(&fightText);
				mainScene->drawScene();
			}

			fightText.setString(fightTextCurrentStringIndex);
			fightText.setInCenter();
			fightTextCurrentStringIndex++;
			mainScene->drawScene();
		}

		if (mainScene->isKeyPressed(Keyboard::Key::Escape))
		{
			mainScene->setCursorVisible(true);
			int retVal = pauseFoo(mainScene);
			mainScene->setCursorVisible(false);

			if (retVal == 1)
			{
				mainScene->clearDrawables();
				mainScene->deleteBorders();
				menuSceneFoo(mainScene);
				return;
			}
		}

		if (mainScene->isKeyPressed(Keyboard::Key::A))
			fighter1.move(*mainScene, TE2D_LEFT);

		if (mainScene->isKeyPressed(Keyboard::Key::D))
			fighter1.move(*mainScene, TE2D_RIGHT);

		if (mainScene->isKeyPressed(Keyboard::Key::W))
			fighter1.jump();

		if (mainScene->isKeyPressed(Keyboard::Key::S))
			fighter1.attack(mainScene, &fighter2, &healthBar2, &ultBar1);

		if (
			(fighter2.getSprite()->getPosition().x
				< fighter1.getSprite()->getPosition().x)
			&& (clock.getElapsedTime().asMilliseconds() > 10)
			)
		{
			fighter2.move(*mainScene, TE2D_RIGHT);
			clock.restart().asMilliseconds();
		}
		else if (
			(fighter2.getSprite()->getPosition().x
			> fighter1.getSprite()->getPosition().x)
			&& (clock.getElapsedTime().asMilliseconds() > 10)
			)
		{
			fighter2.move(*mainScene, TE2D_LEFT);
			clock.restart().asMilliseconds();
		}

		if (fighter2.getSprite()->getPosition().y
			> fighter1.getSprite()->getPosition().y)
			fighter2.jump();

		if (fighter2.getSprite()->intersects(fighter1.getSprite()))
			fighter2.attack(mainScene, &fighter1, &healthBar1, &ultBar2);

		if ((fighter1.getHealth() <= 0) || (fighter2.getHealth() <= 0))
		{
			mainScene->clearDrawables();
			mainScene->setCursorVisible(true);

			if (fighter1.getHealth() <= 0)
				winText.setString(1);
			else
				winText.setString(0);

			winText.setPosition(
				mainScene->getScreenResolution().x / 2 - winText.getGlobalBounds().width / 2,
				mainScene->getScreenResolution().y / 4 - winText.getGlobalBounds().height / 2
			);

			mainScene->addDrawable(&winText);
			mainScene->addDrawable(&againButton);
			mainScene->addDrawable(&againText);
			mainScene->addDrawable(&exitButton);
			mainScene->addDrawable(&exitText);

			while (mainScene->isWorking())
			{
				winText.makeScaleAnimationStep();
				winText.setPosition(
					mainScene->getScreenResolution().x / 2 - winText.getGlobalBounds().width / 2,
					mainScene->getScreenResolution().y / 4 - winText.getGlobalBounds().height / 2
				);

				if (againButton.isPressed(*mainScene, Mouse::Button::Left))
				{
					mainScene->clearDrawables();
					pvpFightersChoiceFoo(mainScene);
					return;
				}

				if (exitButton.isPressed(*mainScene, Mouse::Button::Left))
				{
					mainScene->clearDrawables();
					mainScene->deleteBorders();
					menuSceneFoo(mainScene);
					return;
				}

				mainScene->drawScene();
			}
		}

		fightAnimate(&fightText);

		mainScene->drawScene();
	}
}

void Game::pveFightersChoiceFoo(TE2DScene* menuScene, PK_DIFFICULTY difficulty)
{
	PK_FIGHTER_TYPE fighter1Type = DUDE;
	PK_FIGHTER_TYPE fighter2Type = DUDE;

	TE2DText playText;
	playText.addFont("Files/Fonts/3952.ttf");
	playText.setFont(0);
	playText.addColor(Color::White);
	playText.addColor(Color::Black);
	playText.setFillColor(0);
	playText.setOutlineThickness(3.f);
	playText.setOutlineColor(1);
	playText.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	playText.addString("PLAY");
	playText.setString(0);

	TE2DRectangleButton playButton;
	playButton.addColor(Color::Red);
	playButton.addColor(Color::Blue);
	playButton.addColor(Color::Black);
	playButton.setDefaultFillColor(0);
	playButton.setDefaultOutlineColor(2);
	playButton.setDefaultOutlineThickness(5.f);
	playButton.setActiveFillColor(1);
	playButton.setActiveOutlineColor(2);
	playButton.setActiveOutlineThickness(7.f);
	playButton.setSize(
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	playButton.setText(&playText);
	playButton.setPosition(
		menuScene->getWindowSize().x / 2 - playButton.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText backText;
	backText.copyParameters(playText);
	backText.addString("BACK");
	backText.setString(1);

	TE2DRectangleButton backButton;
	backButton.copyParameters(playButton);
	backButton.setText(&backText);
	backButton.setPosition(
		menuScene->getWindowSize().x / 2 - backButton.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 3 * 2
	);

	TE2DText fighter1Text;
	fighter1Text.copyParameters(playText);
	fighter1Text.addString("YOU: ");
	fighter1Text.setString(1);
	fighter1Text.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	fighter1Text.setScale(1.f, 1.f);
	fighter1Text.setScaleAnimationParams(
		fighter1Text.getScale().x, fighter1Text.getScale().y,
		2.0f, 2.0f,
		0.01f, 0.01f,
		true
	);
	fighter1Text.setPosition(
		menuScene->getScreenResolution().x / 6
		- fighter1Text.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 5
		- fighter1Text.getGlobalBounds().height / 2
	);

	TE2DText stepanText1;
	stepanText1.copyParameters(fighter1Text);
	stepanText1.addString("STEPAN");
	stepanText1.setString(2);

	TE2DRectangleButton stepanButton1;
	stepanButton1.copyParameters(playButton);
	stepanButton1.addColor(Color::Yellow);
	stepanButton1.setSize(
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	stepanButton1.setText(&stepanText1);
	stepanButton1.setPosition(
		menuScene->getScreenResolution().x / 3,
		-stepanButton1.getGlobalBounds().height / 2
		+ fighter1Text.getPosition().y
		+ fighter1Text.getGlobalBounds().height / 2
	);

	TE2DText dudeText1;
	dudeText1.copyParameters(fighter1Text);
	dudeText1.addString("DUDE");
	dudeText1.setString(2);

	TE2DRectangleButton dudeButton1;
	dudeButton1.copyParameters(playButton);
	dudeButton1.addColor(Color::Yellow);
	dudeButton1.setSize(
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	dudeButton1.setText(&dudeText1);
	dudeButton1.setPosition(
		stepanButton1.getPosition().x + stepanButton1.getGlobalBounds().width
		+ (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20.f,
		-dudeButton1.getGlobalBounds().height / 2
		+ fighter1Text.getPosition().y
		+ fighter1Text.getGlobalBounds().height / 2
	);

	TE2DText fighter2Text;
	fighter2Text.copyParameters(playText);
	fighter2Text.addString("BOT: ");
	fighter2Text.setString(1);
	fighter2Text.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	fighter2Text.setScale(1.f, 1.f);
	fighter2Text.setScaleAnimationParams(
		fighter2Text.getScale().x, fighter2Text.getScale().y,
		2.0f, 2.0f,
		0.01f, 0.01f,
		true
	);
	fighter2Text.setPosition(
		menuScene->getScreenResolution().x / 6
		- fighter2Text.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 3
		- fighter2Text.getGlobalBounds().height / 2
	);

	TE2DText stepanText2;
	stepanText2.copyParameters(fighter2Text);
	stepanText2.addString("STEPAN");
	stepanText2.setString(2);

	TE2DRectangleButton stepanButton2;
	stepanButton2.copyParameters(stepanButton1);
	stepanButton2.setText(&stepanText2);
	stepanButton2.setPosition(
		menuScene->getScreenResolution().x / 3,
		-stepanButton2.getGlobalBounds().height / 2
		+ fighter2Text.getPosition().y
		+ fighter2Text.getGlobalBounds().height / 2
	);

	TE2DText dudeText2;
	dudeText2.copyParameters(fighter1Text);
	dudeText2.addString("DUDE");
	dudeText2.setString(2);

	TE2DRectangleButton dudeButton2;
	dudeButton2.copyParameters(dudeButton1);
	dudeButton2.setText(&dudeText2);
	dudeButton2.setPosition(
		stepanButton2.getPosition().x + stepanButton2.getGlobalBounds().width
		+ (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20.f,
		-dudeButton2.getGlobalBounds().height / 2
		+ fighter2Text.getPosition().y
		+ fighter2Text.getGlobalBounds().height / 2
	);

	menuScene->addDrawable(&playButton);
	menuScene->addDrawable(&playText);
	menuScene->addDrawable(&backButton);
	menuScene->addDrawable(&backText);
	menuScene->addDrawable(&fighter1Text);
	menuScene->addDrawable(&stepanButton1);
	menuScene->addDrawable(&stepanText1);
	menuScene->addDrawable(&dudeButton1);
	menuScene->addDrawable(&dudeText1);
	menuScene->addDrawable(&fighter2Text);
	menuScene->addDrawable(&stepanButton2);
	menuScene->addDrawable(&stepanText2);
	menuScene->addDrawable(&dudeButton2);
	menuScene->addDrawable(&dudeText2);

	while (menuScene->isWorking())
	{
		fighter1Text.makeScaleAnimationStep();
		fighter1Text.setPosition(
			menuScene->getScreenResolution().x / 6
			- fighter1Text.getGlobalBounds().width / 2,
			menuScene->getScreenResolution().y / 5
			- fighter1Text.getGlobalBounds().height / 2
		);

		fighter2Text.makeScaleAnimationStep();
		fighter2Text.setPosition(
			menuScene->getScreenResolution().x / 6
			- fighter2Text.getGlobalBounds().width / 2,
			menuScene->getScreenResolution().y / 3
			- fighter2Text.getGlobalBounds().height / 2
		);

		if (stepanButton1.isPressed(*menuScene, Mouse::Button::Left))
		{
			stepanButton1.setFillColor(3);
			fighter1Type = STEPAN;
		}

		if (dudeButton1.isPressed(*menuScene, Mouse::Button::Left))
		{
			dudeButton1.setFillColor(3);
			fighter1Type = DUDE;
		}

		if (stepanButton2.isPressed(*menuScene, Mouse::Button::Left))
		{
			stepanButton2.setFillColor(3);
			fighter2Type = STEPAN;
		}

		if (dudeButton2.isPressed(*menuScene, Mouse::Button::Left))
		{
			dudeButton2.setFillColor(3);
			fighter2Type = DUDE;
		}

		if (playButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			mainScenePVEFoo(menuScene, fighter1Type, fighter2Type, difficulty);
			return;
		}

		if (backButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			menuSceneFoo(menuScene);
			return;
		}

		menuScene->drawScene();
	}
}

void Game::mainScenePVPFoo(
	TE2DScene* mainScene,
	PK_FIGHTER_TYPE fighter1Type,
	PK_FIGHTER_TYPE fighter2Type
)	// versus person
{
	mainScene->setCursorVisible(false);
	mainScene->setGroundLevel(mainScene->getScreenResolution().y);
	mainScene->setBorders(0, mainScene->getWindowSize().x, 0, mainScene->getWindowSize().y);

	TE2DText fightText;
	fightText.addFont("Files/Fonts/3952.ttf");
	fightText.setFont(0);
	fightText.addColor(Color::White);
	fightText.addColor(Color::Black);
	fightText.setFillColor(0);
	fightText.setOutlineThickness(5.f);
	fightText.setOutlineColor(1);
	fightText.setSize(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 42
	);
	fightText.addString("5");
	fightText.addString("4");
	fightText.addString("3");
	fightText.addString("2");
	fightText.addString("1");
	fightText.addString("FIGHT!");
	fightText.setString(0);
	fightText.setInCenter();
	fightText.setScale(1.f, 1.f);
	fightText.setScaleAnimationParams(
		fightText.getScale().x, fightText.getScale().y,
		2.f, 2.f,
		0.01f, 0.01f,
		true
	);

	unique_ptr<Fighter> fighter1Ptr(this->createFighter(fighter1Type));
	Fighter &fighter1 = *fighter1Ptr;
	// fighter1.setFighterType(fighter1Type, *mainScene);
	fighter1.getSprite()->setScale(
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 2,
		mainScene->getScreenResolution().y / TE2D_HD_SCREEN_SIZE.y * 2
	);
	fighter1.setSide(TE2D_LEFT, *mainScene);
	fighter1.setHealth(100);
	fighter1.setDamage(2);
	fighter1.setMaxUltLevel(100);
	fighter1.setCurrUltLevel(0);
	fighter1.setUltStep(4);
	fighter1.setMoveParams(1.f, 25.f, 50, 0.9f);

	TE2DRectangleShape healthBar1;
	healthBar1.addColor(Color::Red);
	healthBar1.addColor(Color::Black);
	healthBar1.setFillColor(0);
	healthBar1.setOutlineColor(1);
	healthBar1.setOutlineThickness(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 5
	);
	healthBar1.setSize(
		(float)fighter1.getHealth()
		* (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 5,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);
	healthBar1.setPosition(
		mainScene->getWindowSize().x / 2
		- healthBar1.getGlobalBounds().width
		- (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	TE2DRectangleShape ultBar1;
	ultBar1.addColor(Color::Yellow);
	ultBar1.addColor(Color::Black);
	ultBar1.addColor(Color::Blue);
	ultBar1.setFillColor(0);
	ultBar1.setOutlineColor(1);
	ultBar1.setOutlineThickness(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 5
	);
	ultBar1.setSize(
		0.f,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);
	ultBar1.setPosition(
		mainScene->getWindowSize().x / 2
		- ultBar1.getGlobalBounds().width
		- (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
		+ healthBar1.getSize().y
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	unique_ptr<Fighter> fighter2Ptr(this->createFighter(fighter2Type));
	Fighter &fighter2 = *fighter2Ptr;
	// fighter2.setFighterType(fighter2Type, *mainScene);
	fighter2.getSprite()->setScale(
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 2,
		mainScene->getScreenResolution().y / TE2D_HD_SCREEN_SIZE.y * 2
	);
	fighter2.setSide(TE2D_RIGHT, *mainScene);
	fighter2.setHealth(100);
	fighter2.setDamage(2);
	fighter2.setMaxUltLevel(100);
	fighter2.setCurrUltLevel(0);
	fighter2.setUltStep(4);
	fighter2.setMoveParams(1.f, 25.f, 50, 0.9f);

	TE2DRectangleShape healthBar2;
	healthBar2.copyParameters(healthBar1);
	healthBar2.setPosition(
		mainScene->getWindowSize().x / 2
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	TE2DRectangleShape ultBar2;
	ultBar2.copyParameters(ultBar1);
	ultBar2.setPosition(
		mainScene->getWindowSize().x / 2
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20,
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
		+ healthBar2.getSize().y
		+ (int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20
	);

	TE2DText winText;
	winText.addFont("Files/Fonts/3952.ttf");
	winText.setFont(0);
	winText.addColor(Color::White);
	winText.addColor(Color::Black);
	winText.setFillColor(0);
	winText.setOutlineThickness(5.f);
	winText.setOutlineColor(1);
	winText.setSize(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 42
	);
	winText.setScale(1.f, 1.f);
	winText.setScaleAnimationParams(
		winText.getScale().x, winText.getScale().y,
		2.f, 2.f,
		0.01f, 0.01f,
		true
	);
	winText.addString("FIGHTER 1 WINS!");
	winText.addString("FIGHTER 2 WINS!");

	TE2DText againText;
	againText.addFont("Files/Fonts/3952.ttf");
	againText.setFont(0);
	againText.addColor(Color::White);
	againText.addColor(Color::Black);
	againText.setFillColor(0);
	againText.setOutlineThickness(3.f);
	againText.setOutlineColor(1);
	againText.setSize(
		(int)mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	againText.addString("AGAIN");
	againText.setString(0);

	TE2DRectangleButton againButton;
	againButton.addColor(Color::Red);
	againButton.addColor(Color::Blue);
	againButton.addColor(Color::Black);
	againButton.setDefaultFillColor(0);
	againButton.setDefaultOutlineColor(2);
	againButton.setDefaultOutlineThickness(5.f);
	againButton.setActiveFillColor(1);
	againButton.setActiveOutlineColor(2);
	againButton.setActiveOutlineThickness(7.f);
	againButton.setSize(
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		mainScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	againButton.setText(&againText);
	againButton.setPosition(
		mainScene->getWindowSize().x / 2 - againButton.getGlobalBounds().width / 2,
		mainScene->getScreenResolution().y / 2
	);

	TE2DText exitText;
	exitText.copyParameters(againText);
	exitText.addString("MENU");
	exitText.setString(1);

	TE2DRectangleButton exitButton;
	exitButton.copyParameters(againButton);
	exitButton.setText(&exitText);
	exitButton.setPosition(
		mainScene->getWindowSize().x / 2 - exitButton.getGlobalBounds().width / 2,
		mainScene->getScreenResolution().y / 3 * 2
	);

	mainScene->addDrawable(&fightText);
	mainScene->addDrawable(&healthBar1);
	mainScene->addDrawable(&healthBar2);
	mainScene->addDrawable(&ultBar1);
	mainScene->addDrawable(&ultBar2);
	mainScene->addDrawable(fighter1.getSprite());
	mainScene->addDrawable(fighter2.getSprite());

	int fightTextCurrentStringIndex = 1;
	Clock clock;

	while (mainScene->isWorking())
	{
		while (fightText.getCurrentStringIndex() != 5)
		{
			fightText.setString(fightTextCurrentStringIndex);
			fightText.setInCenter();
			fightTextCurrentStringIndex++;
			mainScene->drawScene();

			clock.restart().asSeconds();

			while (clock.getElapsedTime().asSeconds() < 1)
			{
				fightAnimate(&fightText);
				mainScene->drawScene();
			}
		}

		if (mainScene->isKeyPressed(Keyboard::Key::Escape))
		{
			mainScene->setCursorVisible(true);
			int retVal = pauseFoo(mainScene);
			mainScene->setCursorVisible(false);

			if (retVal == 1)
			{
				mainScene->clearDrawables();
				mainScene->deleteBorders();
				menuSceneFoo(mainScene);
				return;
			}
		}

		if (mainScene->isKeyPressed(Keyboard::Key::A))
			fighter1.move(*mainScene, TE2D_LEFT);

		if (mainScene->isKeyPressed(Keyboard::Key::D))
			fighter1.move(*mainScene, TE2D_RIGHT);

		if (mainScene->isKeyPressed(Keyboard::Key::W))
			fighter1.jump();

		if (mainScene->isKeyPressed(Keyboard::Key::S))
			fighter1.attack(mainScene, &fighter2, &healthBar2, &ultBar1);

		if (mainScene->isKeyPressed(Keyboard::Key::H))
			fighter2.move(*mainScene, TE2D_LEFT);

		if (mainScene->isKeyPressed(Keyboard::Key::K))
			fighter2.move(*mainScene, TE2D_RIGHT);

		if (mainScene->isKeyPressed(Keyboard::Key::U))
			fighter2.jump();

		if (mainScene->isKeyPressed(Keyboard::Key::J))
			fighter2.attack(mainScene, &fighter1, &healthBar1, &ultBar2);

		if ((fighter1.getHealth() <= 0) || (fighter2.getHealth() <= 0))
		{
			mainScene->clearDrawables();
			mainScene->setCursorVisible(true);

			if (fighter1.getHealth() <= 0)
				winText.setString(1);
			else
				winText.setString(0);

			winText.setPosition(
				mainScene->getScreenResolution().x / 2 - winText.getGlobalBounds().width / 2,
				mainScene->getScreenResolution().y / 4 - winText.getGlobalBounds().height / 2
			);

			mainScene->addDrawable(&winText);
			mainScene->addDrawable(&againButton);
			mainScene->addDrawable(&againText);
			mainScene->addDrawable(&exitButton);
			mainScene->addDrawable(&exitText);

			while (mainScene->isWorking())
			{
				winText.makeScaleAnimationStep();
				winText.setPosition(
					mainScene->getScreenResolution().x / 2 - winText.getGlobalBounds().width / 2,
					mainScene->getScreenResolution().y / 4 - winText.getGlobalBounds().height / 2
				);

				if (againButton.isPressed(*mainScene, Mouse::Button::Left))
				{
					mainScene->clearDrawables();
					pvpFightersChoiceFoo(mainScene);
					return;
				}

				if (exitButton.isPressed(*mainScene, Mouse::Button::Left))
				{
					mainScene->clearDrawables();
					mainScene->deleteBorders();
					menuSceneFoo(mainScene);
					return;
				}

				mainScene->drawScene();
			}
		}

		fightAnimate(&fightText);

		mainScene->drawScene();
	}
}

void Game::pvpFightersChoiceFoo(TE2DScene* menuScene)
{
	PK_FIGHTER_TYPE fighter1Type = DUDE;
	PK_FIGHTER_TYPE fighter2Type = DUDE;

	TE2DText playText;
	playText.addFont("Files/Fonts/3952.ttf");
	playText.setFont(0);
	playText.addColor(Color::White);
	playText.addColor(Color::Black);
	playText.setFillColor(0);
	playText.setOutlineThickness(3.f);
	playText.setOutlineColor(1);
	playText.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	playText.addString("PLAY");
	playText.setString(0);

	TE2DRectangleButton playButton;
	playButton.addColor(Color::Red);
	playButton.addColor(Color::Blue);
	playButton.addColor(Color::Black);
	playButton.setDefaultFillColor(0);
	playButton.setDefaultOutlineColor(2);
	playButton.setDefaultOutlineThickness(5.f);
	playButton.setActiveFillColor(1);
	playButton.setActiveOutlineColor(2);
	playButton.setActiveOutlineThickness(7.f);
	playButton.setSize(
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	playButton.setText(&playText);
	playButton.setPosition(
		menuScene->getWindowSize().x / 2 - playButton.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText backText;
	backText.copyParameters(playText);
	backText.addString("BACK");
	backText.setString(1);

	TE2DRectangleButton backButton;
	backButton.copyParameters(playButton);
	backButton.setText(&backText);
	backButton.setPosition(
		menuScene->getWindowSize().x / 2 - backButton.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 3 * 2
	);

	TE2DText fighter1Text;
	fighter1Text.copyParameters(playText);
	fighter1Text.addString("FIGHTER 1: ");
	fighter1Text.setString(1);
	fighter1Text.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	fighter1Text.setScale(1.f, 1.f);
	fighter1Text.setScaleAnimationParams(
		fighter1Text.getScale().x, fighter1Text.getScale().y,
		2.0f, 2.0f,
		0.01f, 0.01f,
		true
	);
	fighter1Text.setPosition(
		menuScene->getScreenResolution().x / 6
		- fighter1Text.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 5
		- fighter1Text.getGlobalBounds().height / 2
	);

	TE2DText stepanText1;
	stepanText1.copyParameters(fighter1Text);
	stepanText1.addString("STEPAN");
	stepanText1.setString(2);

	TE2DRectangleButton stepanButton1;
	stepanButton1.copyParameters(playButton);
	stepanButton1.addColor(Color::Yellow);
	stepanButton1.setSize(
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	stepanButton1.setText(&stepanText1);
	stepanButton1.setPosition(
		menuScene->getScreenResolution().x / 3,
		-stepanButton1.getGlobalBounds().height / 2
		+ fighter1Text.getPosition().y
		+ fighter1Text.getGlobalBounds().height / 2
	);

	TE2DText dudeText1;
	dudeText1.copyParameters(fighter1Text);
	dudeText1.addString("DUDE");
	dudeText1.setString(2);

	TE2DRectangleButton dudeButton1;
	dudeButton1.copyParameters(playButton);
	dudeButton1.addColor(Color::Yellow);
	dudeButton1.setSize(
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	dudeButton1.setText(&dudeText1);
	dudeButton1.setPosition(
		stepanButton1.getPosition().x + stepanButton1.getGlobalBounds().width
		+ (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20.f,
		-dudeButton1.getGlobalBounds().height / 2
		+ fighter1Text.getPosition().y
		+ fighter1Text.getGlobalBounds().height / 2
	);

	TE2DText fighter2Text;
	fighter2Text.copyParameters(playText);
	fighter2Text.addString("FIGHTER 2: ");
	fighter2Text.setString(1);
	fighter2Text.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	fighter2Text.setScale(1.f, 1.f);
	fighter2Text.setScaleAnimationParams(
		fighter2Text.getScale().x, fighter2Text.getScale().y,
		2.0f, 2.0f,
		0.01f, 0.01f,
		true
	);
	fighter2Text.setPosition(
		menuScene->getScreenResolution().x / 6
		- fighter2Text.getGlobalBounds().width / 2,
		menuScene->getScreenResolution().y / 3
		- fighter2Text.getGlobalBounds().height / 2
	);

	TE2DText stepanText2;
	stepanText2.copyParameters(fighter2Text);
	stepanText2.addString("STEPAN");
	stepanText2.setString(2);

	TE2DRectangleButton stepanButton2;
	stepanButton2.copyParameters(stepanButton1);
	stepanButton2.setText(&stepanText2);
	stepanButton2.setPosition(
		menuScene->getScreenResolution().x / 3,
		-stepanButton2.getGlobalBounds().height / 2
		+ fighter2Text.getPosition().y
		+ fighter2Text.getGlobalBounds().height / 2
	);

	TE2DText dudeText2;
	dudeText2.copyParameters(fighter1Text);
	dudeText2.addString("DUDE");
	dudeText2.setString(2);

	TE2DRectangleButton dudeButton2;
	dudeButton2.copyParameters(dudeButton1);
	dudeButton2.setText(&dudeText2);
	dudeButton2.setPosition(
		stepanButton2.getPosition().x + stepanButton2.getGlobalBounds().width
		+ (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 20.f,
		-dudeButton2.getGlobalBounds().height / 2
		+ fighter2Text.getPosition().y
		+ fighter2Text.getGlobalBounds().height / 2
	);

	menuScene->addDrawable(&playButton);
	menuScene->addDrawable(&playText);
	menuScene->addDrawable(&backButton);
	menuScene->addDrawable(&backText);
	menuScene->addDrawable(&fighter1Text);
	menuScene->addDrawable(&stepanButton1);
	menuScene->addDrawable(&stepanText1);
	menuScene->addDrawable(&dudeButton1);
	menuScene->addDrawable(&dudeText1);
	menuScene->addDrawable(&fighter2Text);
	menuScene->addDrawable(&stepanButton2);
	menuScene->addDrawable(&stepanText2);
	menuScene->addDrawable(&dudeButton2);
	menuScene->addDrawable(&dudeText2);

	while (menuScene->isWorking())
	{
		fighter1Text.makeScaleAnimationStep();
		fighter1Text.setPosition(
			menuScene->getScreenResolution().x / 6
			- fighter1Text.getGlobalBounds().width / 2,
			menuScene->getScreenResolution().y / 5
			- fighter1Text.getGlobalBounds().height / 2
		);

		fighter2Text.makeScaleAnimationStep();
		fighter2Text.setPosition(
			menuScene->getScreenResolution().x / 6
			- fighter2Text.getGlobalBounds().width / 2,
			menuScene->getScreenResolution().y / 3
			- fighter2Text.getGlobalBounds().height / 2
		);

		if (stepanButton1.isPressed(*menuScene, Mouse::Button::Left))
		{
			stepanButton1.setFillColor(3);
			fighter1Type = STEPAN;
		}

		if (dudeButton1.isPressed(*menuScene, Mouse::Button::Left))
		{
			dudeButton1.setFillColor(3);
			fighter1Type = DUDE;
		}

		if (stepanButton2.isPressed(*menuScene, Mouse::Button::Left))
		{
			stepanButton2.setFillColor(3);
			fighter2Type = STEPAN;
		}

		if (dudeButton2.isPressed(*menuScene, Mouse::Button::Left))
		{
			dudeButton2.setFillColor(3);
			fighter2Type = DUDE;
		}

		if (playButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			mainScenePVPFoo(menuScene, fighter1Type, fighter2Type);
			return;
		}

		if (backButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			menuSceneFoo(menuScene);
			return;
		}

		menuScene->drawScene();
	}
}

void Game::pkAnimate(
	TE2DScene* menuScene,
	TE2DText* pkText
)
{
	pkText->makeScaleAnimationStep();
	pkText->setPosition(
		menuScene->getScreenResolution().x / 2 - pkText->getGlobalBounds().width / 2,
		pkText->getPosition().y
	);
}

void Game::menuSceneFoo(TE2DScene* menuScene)
{
	menuScene->setCursorVisible(true);

	TE2DText pkText;
	pkText.addFont("Files/Fonts/3952.ttf");
	pkText.setFont(0);
	pkText.addColor(Color::White);
	pkText.addColor(Color::Black);
	pkText.setFillColor(0);
	pkText.setOutlineThickness(5.f);
	pkText.setOutlineColor(1);
	pkText.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 42
	);
	pkText.addString("pOOOPal Kombat");
	pkText.setString(0);
	pkText.setPosition(
		menuScene->getScreenResolution().x / 2 - pkText.getGlobalBounds().width / 2,
		-pkText.getGlobalBounds().height
	);
	pkText.setScale(1.f, 1.f);
	pkText.setScaleAnimationParams(
		pkText.getScale().x, pkText.getScale().y,
		2.f, 2.f,
		0.01f, 0.01f,
		true
	);

	TE2DText versionText;
	versionText.addFont("Files/Fonts/3952.ttf");
	versionText.setFont(0);
	versionText.addColor(Color::White);
	versionText.addColor(Color::Black);
	versionText.setFillColor(0);
	versionText.setOutlineThickness(2.f);
	versionText.setOutlineColor(1);
	versionText.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 18
	);
	versionText.addString("version	" + versionString);
	versionText.setString(0);
	versionText.setPosition(
		menuScene->getScreenResolution().x - versionText.getGlobalBounds().width,
		0
	);
	versionText.setScale(1.f, 1.f);

	TE2DText startText;
	startText.addFont("Files/Fonts/3952.ttf");
	startText.setFont(0);
	startText.addColor(Color::White);
	startText.addColor(Color::Black);
	startText.setFillColor(0);
	startText.setOutlineThickness(3.f);
	startText.setOutlineColor(1);
	startText.setSize(
		(int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	startText.addString("START	GAME");
	startText.setString(0);

	TE2DRectangleButton startButton;
	startButton.addColor(Color::Red);
	startButton.addColor(Color::Blue);
	startButton.addColor(Color::Black);
	startButton.setDefaultFillColor(0);
	startButton.setDefaultOutlineColor(2);
	startButton.setDefaultOutlineThickness(5.f);
	startButton.setActiveFillColor(1);
	startButton.setActiveOutlineColor(2);
	startButton.setActiveOutlineThickness(7.f);
	startButton.setSize(
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 250.f,
		menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 74.f
	);
	startButton.setText(&startText);
	startButton.setPosition(
		-startButton.getGlobalBounds().width
		- 10 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText pvpText;
	pvpText.copyParameters(startText);
	pvpText.addString("PVP");
	pvpText.setString(1);

	TE2DRectangleButton pvpButton;
	pvpButton.copyParameters(startButton);
	pvpButton.setText(&pvpText);
	pvpButton.setPosition(
		-startButton.getGlobalBounds().width
		- 10 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText pveText;
	pveText.copyParameters(startText);
	pveText.addString("PVE");
	pveText.setString(1);

	TE2DRectangleButton pveButton;
	pveButton.copyParameters(startButton);
	pveButton.setText(&pveText);
	pveButton.setPosition(
		-startButton.getGlobalBounds().width
		- 10 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x
		- pvpButton.getGlobalBounds().width
		- 20 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText hardText;
	hardText.copyParameters(startText);
	hardText.addString("HARD");
	hardText.setString(1);

	TE2DRectangleButton hardButton;
	hardButton.copyParameters(startButton);
	hardButton.setText(&hardText);
	hardButton.setPosition(
		-hardButton.getGlobalBounds().width
		- 10 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText normalText;
	normalText.copyParameters(startText);
	normalText.addString("NORMAL");
	normalText.setString(1);

	TE2DRectangleButton normalButton;
	normalButton.copyParameters(startButton);
	normalButton.setText(&normalText);
	normalButton.setPosition(
		-hardButton.getGlobalBounds().width
		- 10 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x
		- normalButton.getGlobalBounds().width
		- 20 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText easyText;
	easyText.copyParameters(startText);
	easyText.addString("EASY");
	easyText.setString(1);

	TE2DRectangleButton easyButton;
	easyButton.copyParameters(startButton);
	easyButton.setText(&easyText);
	easyButton.setPosition(
		-hardButton.getGlobalBounds().width
		- 10 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x
		- normalButton.getGlobalBounds().width
		- 10 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x
		- easyButton.getGlobalBounds().width
		- 30 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x,
		menuScene->getScreenResolution().y / 2
	);

	TE2DText exitText;
	exitText.copyParameters(startText);
	exitText.addString("EXIT	GAME");
	exitText.setString(1);

	TE2DRectangleButton exitButton;
	exitButton.copyParameters(startButton);
	exitButton.setText(&exitText);
	exitButton.setPosition(
		menuScene->getScreenResolution().x,
		menuScene->getScreenResolution().y / 3 * 2
	);

	menuScene->addDrawable(&pkText);
	menuScene->addDrawable(&versionText);
	menuScene->addDrawable(&startButton);
	menuScene->addDrawable(&startText);
	menuScene->addDrawable(&pvpButton);
	menuScene->addDrawable(&pvpText);
	menuScene->addDrawable(&pveButton);
	menuScene->addDrawable(&pveText);
	menuScene->addDrawable(&hardButton);
	menuScene->addDrawable(&hardText);
	menuScene->addDrawable(&normalButton);
	menuScene->addDrawable(&normalText);
	menuScene->addDrawable(&easyButton);
	menuScene->addDrawable(&easyText);
	menuScene->addDrawable(&exitButton);
	menuScene->addDrawable(&exitText);

	while (menuScene->isWorking())
	{
		if (pkText.getPosition().y
			< menuScene->getScreenResolution().y / 4)
			pkText.move(0, 2.f);
		if (exitText.getPosition().x
			> menuScene->getScreenResolution().x / 2
			- exitText.getGlobalBounds().width / 2)
			exitButton.move(-8.f, 0.f);
		if (startText.getPosition().x
			< menuScene->getScreenResolution().x / 2
			- startText.getGlobalBounds().width / 2)
			startButton.move(8.f, 0.f);

		if (startButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			while (pvpButton.getPosition().x
				< menuScene->getScreenResolution().x / 2
				+ 5 * (int)menuScene->getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x)
			{
				startButton.move(8.f, 0.f);
				pvpButton.move(8.f, 0.f);
				pveButton.move(8.f, 0.f);

				pkAnimate(menuScene, &pkText);

				menuScene->drawScene();
			}
		}
		else if (pvpButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			pvpFightersChoiceFoo(menuScene);
			return;
		}
		else if (pveButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			while (normalButton.getPosition().x
				+ normalButton.getGlobalBounds().width / 2
				< menuScene->getScreenResolution().x / 2)
			{
				pvpButton.move(8.f, 0.f);
				pveButton.move(8.f, 0.f);
				hardButton.move(8.f, 0.f);
				normalButton.move(8.f, 0.f);
				easyButton.move(8.f, 0.f);

				pkAnimate(menuScene, &pkText);

				menuScene->drawScene();
			}
		}
		else if (hardButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			pveFightersChoiceFoo(menuScene, HARD);
			return;
		}
		else if (normalButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			pveFightersChoiceFoo(menuScene, NORMAL);
			return;
		}
		else if (easyButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->clearDrawables();
			pveFightersChoiceFoo(menuScene, EASY);
			return;
		}
		else if (exitButton.isPressed(*menuScene, Mouse::Button::Left))
		{
			menuScene->closeWindow();
			return;
		}

		pkAnimate(menuScene, &pkText);

		menuScene->drawScene();
	}
}

void Game::introSceneFoo()
{
	TE2DScene introScene;
	introScene.createWindow(
		introScene.getScreenResolution().x,
		introScene.getScreenResolution().y,
		"pOOOPal Kombat",
		Style::Fullscreen
	);
	introScene.setFramerateLimit(100);
	introScene.setCursorVisible(false);
	introScene.setBackgroundColor(Color::Green);

	TE2DSprite zheltogSprite;
	zheltogSprite.addTexture("Files/Images/young_circle.png");
	zheltogSprite.addTexture("Files/Images/old_circle.png");
	zheltogSprite.setTexture(0);
	zheltogSprite.setScale(
		introScene.getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x,
		introScene.getScreenResolution().y / TE2D_HD_SCREEN_SIZE.y
	);
	zheltogSprite.setPosition(
		introScene.getScreenResolution().x / 2 - zheltogSprite.getGlobalBounds().width / 2,
		-zheltogSprite.getGlobalBounds().height
	);
	zheltogSprite.addAnimation();
	zheltogSprite.addToAnimation(0, 0);
	zheltogSprite.addToAnimation(0, 1);
	zheltogSprite.setAnimationDelay(0, 0.5f);
	zheltogSprite.setAnimation(0);

	TE2DText zheltogText;
	zheltogText.addFont("Files/Fonts/3952.ttf");
	zheltogText.setFont(0);
	zheltogText.addColor(Color::White);
	zheltogText.addColor(Color::Black);
	zheltogText.setFillColor(0);
	zheltogText.setOutlineThickness(3.f);
	zheltogText.setOutlineColor(1);
	zheltogText.setSize(
		(int)introScene.getScreenResolution().x / TE2D_HD_SCREEN_SIZE.x * 34
	);
	zheltogText.addString("Zheltog-2	presents");
	zheltogText.setString(0);
	zheltogText.setPosition(
		introScene.getScreenResolution().x / 2 - zheltogText.getGlobalBounds().width / 2,
		introScene.getScreenResolution().y
	);

	introScene.addDrawable(&zheltogSprite);
	introScene.addDrawable(&zheltogText);

	while (introScene.isWorking())
	{
		if (zheltogSprite.getPosition().y
			< introScene.getScreenResolution().y / 2 - zheltogSprite.getGlobalBounds().height)
			zheltogSprite.move(0, 4.f);
		else
		{
			if (zheltogText.getPosition().y
			> introScene.getScreenResolution().y / 2 + zheltogText.getGlobalBounds().height)
				zheltogText.move(0, -4.f);
			else
			{
				Sleep(1000);
				introScene.clearDrawables();
				menuSceneFoo(&introScene);
				return;
			}
		}

		introScene.drawScene();
	}
}

void Game::play()
{
	introSceneFoo();
}