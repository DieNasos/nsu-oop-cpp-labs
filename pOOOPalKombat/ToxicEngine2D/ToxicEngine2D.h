/* TOXIC ENGINE 2D */
/* VER. 0.1 */
/* BY ZHELTOG-2 */
/* FOR GENIAL GAMES ONLY!!! */

#pragma once

#include "TE2DBasicIncludes.h"

class TE2DScene;

class TE2DAudio
{
protected:

	float volume;
	bool loop;

public:

	// CONSTRUCTOR
	TE2DAudio();

	// VIRTUAL FUNCTIONS
	virtual void loadSource(string sourceFilename) = 0;
	virtual void setVolume(float volume) = 0;
	virtual void setLoop(bool loop) = 0;
	virtual void play() = 0;
	virtual void pause() = 0;
	virtual void stop() = 0;
};

class TE2DMusic : public TE2DAudio
{

	Music music;

public:

	// CONSTRUCTOR
	TE2DMusic();

	// VIRTUAL FUNCTIONS FROM TE2DAudio
	void loadSource(string sourceFilename);
	void setVolume(float volume);
	void setLoop(bool loop);
	void play();
	void pause();
	void stop();
};

class TE2DSound : public TE2DAudio
{
private:

	// PRIVATE MEMBERS
	SoundBuffer buffer;
	Sound sound;

public:

	// CONSTRUCTOR
	TE2DSound();

	// VIRTUAL FUNCTIONS FROM TE2DAudio
	void loadSource(string sourceFilename);
	void setVolume(float volume);
	void setLoop(bool loop);
	void play();
	void pause();
	void stop();
};

class TE2DDrawable
{
protected:

	Vector2f pos;
	bool isDrawable;
	int index;

	// for scale animation
	Vector2f minScale;
	Vector2f maxScale;
	Vector2f zoomStep;
	bool isZooming;

	// for advanced move
	Vector2f currentVelocity;
	Vector2f direction;
	float acceleration;
	float maxVelocity;
	float multiplier;
	float drag;

	float jumpHeight;
	float jumpSpeed;
	float currJumpSpeed;
	float fallSpeed;
	float currFallSpeed;
	float gravityStrength;

	bool isOnGround;
	bool isJumping;

public:

	// CONSTRUCTOR
	TE2DDrawable();

	// GETTERS
	Vector2f getPosition();
	bool getIsDrawable();
	int getIndex();
	bool intersects(TE2DDrawable* drawable);
	float getJumpHeight();
	float getJumpSpeed();
	float getCurrJumpSpeed();
	float getGravityStrength();
	bool getIsOnGround();
	bool getIsJumping();

	// SETTERS
	void setIsDrawable(bool isDrawable);
	void setIndex(int index);
	void setScaleAnimationParams(
		float minScaleX,
		float minScaleY,
		float maxScaleX,
		float maxScaleY,
		float zoomStepX,
		float zoomStepY,
		bool isZooming
	);
	void setMoveParams(
		float acceleration,
		float maxVelocity,
		float multiplier,
		float drag
	);
	void setInCenter();
	void setJumpHeight(float jumpHeight);
	void setJumpSpeed(float jumpSpeed);
	void setCurrJumpSpeed(float currJumpSpeed);
	void setFallSpeed(float fallSpeed);
	void setGravityStrength(float gravityStrength);
	void setIsOnGround(bool isOnGround);
	void setIsJumping(bool isJumping);
	void copyCommonParameters(TE2DDrawable drawable);

	// VIRTUAL FUNCTIONS
	virtual Drawable& getDrawable();
	virtual void setPosition(float x, float y);
	virtual Vector2f getCenter();
	virtual FloatRect getGlobalBounds();
	virtual Vector2f getScale();
	virtual void setScale(float x, float y);
	virtual float getRotation();
	virtual void setRotation(float rotation);

	// OTHER FUNCTIONS
	void move(float offsetX, float offsetY);
	void advancedMove(TE2DScene scene, TE2D_DIRECTION direction);
	void zoom(float offsetX, float offsetY);
	void makeScaleAnimationStep();
	void rotate(float offset);
	void jump();
	void fall(TE2DScene scene);
};

class TE2DText : public TE2DDrawable
{
private:

	Text text;
	vector<Font> fonts;
	vector<Color> colors;
	vector<string> strings;
	int size;
	int currStrIndex;

public:

	// CONSTRUCTOR
	TE2DText();

	// GETTERS
	Text getText();
	int getCurrentStringIndex();

	// SETTERS
	void addFont(string sourceFilename);
	void deleteFont(int index);
	void setFont(int index);
	void addColor(Color color);
	void deleteColor(int index);
	void setFillColor(int index);
	void setOutlineColor(int index);
	void setOutlineThickness(float thickness);
	void addString(string string);
	void deleteString(int index);
	void setString(int index);
	void setSize(int size);
	void copyParameters(TE2DText text);

	// VIRTUAL FUNCTIONS FROM TE2DDrawable
	Drawable& getDrawable();
	void setPosition(float x, float y);
	Vector2f getCenter();
	FloatRect getGlobalBounds();
	Vector2f getScale();
	void setScale(float x, float y);
	float getRotation();
	void setRotation(float rotation);
};

class TE2DRectangleShape : public TE2DDrawable
{
protected:

	RectangleShape shape;
	vector<Color> colors;

public:

	// CONSTRUCTOR
	TE2DRectangleShape();

	// GETTERS
	Color getFillColor();
	Color getOutlineColor();
	float getOutlineThickness();
	Vector2f getSize();

	// SETTERS
	void addColor(Color color);
	void deleteColor(int index);
	void setFillColor(int index);
	void setOutlineColor(int index);
	void setOutlineThickness(float thickness);
	void setSize(float sizeX, float sizeY);
	void copyParameters(TE2DRectangleShape shape);

	// VIRTUAL FUNCTIONS FROM TE2DDrawable
	Drawable& getDrawable();
	void setPosition(float x, float y);
	FloatRect getGlobalBounds();
	Vector2f getCenter();
	Vector2f getScale();
	void setScale(float x, float y);
	float getRotation();
	void setRotation(float rotation);
};

class TE2DRectangleButton : public TE2DRectangleShape
{
private:

	TE2DText* text;
	int defaultFillColorIndex;
	int activeFillColorIndex;
	int defaultOutlineColorIndex;
	int activeOutlineColorIndex;
	float defaultOutlineThickness;
	float activeOutlineThickness;
	bool is_active;

public:

	// CONSTRUCTOR
	TE2DRectangleButton();

	// GETTERS
	bool isActive(TE2DScene scene);
	bool isPressed(TE2DScene scene, Mouse::Button button);
	Color getActiveFillColor();
	Color getActiveOutlineColor();
	float getActiveOutlineThickness();
	Color getDefaultFillColor();
	Color getDefaultOutlineColor();
	float getDefaultOutlineThickness();

	// SETTERS
	void setText(TE2DText* text);
	void setActiveFillColor(int index);
	void setActiveOutlineColor(int index);
	void setActiveOutlineThickness(float thickness);
	void setDefaultFillColor(int index);
	void setDefaultOutlineColor(int index);
	void setDefaultOutlineThickness(float thickness);
	void copyParameters(TE2DRectangleButton button);

	// VIRTUAL FUNCTIONS FROM TE2DDrawable
	Drawable& getDrawable();
	void setPosition(float x, float y);
	FloatRect getGlobalBounds();
	Vector2f getCenter();
	Vector2f getScale();
	void setScale(float x, float y);
	float getRotation();
	void setRotation(float rotation);
};

class TE2DAnimation
{
private:

	vector<int> animation;
	int currTexIndex;
	float delay;

public:

	// CONSTRUCTOR
	TE2DAnimation();

	// GETTERS
	int getSize();
	int getCurrTexIndex();
	float getDelay();

	// SETTERS
	void addTexture(int textureIndex);
	void deleteTexture(int textureIndex);
	void clear();
	void setCurrTexIndex(int index);
	void incCurrTexIndex();
	void setDelay(float seconds);
};

class TE2DSprite : public TE2DDrawable
{
private:

	Sprite sprite;
	vector<Texture> textures;
	vector<TE2DAnimation> animations;
	int currentAnimation;

	Clock clock;

public:

	// CONSTRUCTOR
	TE2DSprite();

	// GETTERS

	// SETTERS
	void addTexture(string sourceFileName);
	void deleteTexture(int index);
	void setTexture(int index);
	void addAnimation();
	void addToAnimation(int animationIndex, int textureIndex);
	void deleteFromAnimation(int animationIndex, int textureIndex);
	void clearAnimation(int animationIndex);
	void setAnimationDelay(int animationIndex, float seconds);
	void setAnimation(int index);
	void copyParameters(TE2DSprite sprite);

	// VIRTUAL FUNCTIONS FROM TE2DDrawable
	Drawable& getDrawable();
	void setPosition(float x, float y);
	Vector2f getCenter();
	FloatRect getGlobalBounds();
	Vector2f getScale();
	void setScale(float x, float y);
	float getRotation();
	void setRotation(float rotation);
};

class TE2DWindow
{
private:

	RenderWindow* window;
	Vector2i size;
	string title;
	int style;
	int framerateLimit;
	Event event;

public:

	// CONSTRUCTOR
	TE2DWindow(int sizeX, int sizeY, string title, int style);

	// GETTERS
	bool isOpen();
	bool pollEvent();
	bool shouldClose();
	Vector2i getSize();

	// SETTERS
	void setFramerateLimit(int framerateLimit);
	void setCursorVisible(bool isVisible);
	void setView(View* view);
	void setDefaultView();

	// OTHER FUNCTIONS
	void close();
	void clear(const Color color);
	void draw(const Drawable& drawable);
	void display();
	Vector2f mapPixelToCoords(Vector2i pixelPos);
	Vector2i mapCoordsToPixel(Vector2f point);
};

class TE2DScene
{
private:

	// PRIVATE MEMBERS
	TE2DWindow* window;
	vector<TE2DDrawable*> drawables;
	vector<View*> views;
	int currViewIndex;
	Color backgroundColor;
	Clock clock;
	float dt;	// delta time
	int groundLevel;
	vector<float> borders;

public:

	// CONSTRUCTOR
	TE2DScene();

	// WINDOW
	void createWindow(int sizeX, int sizeY, string title, int style);
	void clearWindow();
	void displayWindow();
	void closeWindow();
	void setFramerateLimit(int framerateLimit);
	void setCursorVisible(bool isVisible);
	Vector2i getWindowSize();

	// DRAWABLES
	void addDrawable(TE2DDrawable* drawable);
	void deleteDrawable(TE2DDrawable drawable);
	void clearDrawables();
	void swapDrawables(TE2DDrawable drawable1, TE2DDrawable drawable2);
	void drawTE2DDrawable(TE2DDrawable drawable);
	void drawSFMLDrawable(Drawable& drawable);
	void drawScene();

	// VIEWS
	int getCurrentViewIndex();
	View* getView(int index);
	void setView(int index);
	void addView(int sizeX, int sizeY, int cntrX, int cntrY);
	void deleteView(int index);
	Vector2f getViewCenter(int index);
	Vector2i getViewSize(int index);
	void setViewCenter(int index, int cntrX, int cntrY);

	// COLOR
	Color getBackgroundColor();
	void setBackgroundColor(Color color);

	// CONTROL
	bool isKeyPressed(Keyboard::Key key);
	bool isMouseButtonPressed(Mouse::Button button);
	Vector2i getMousePosition();
	Vector2f mapPixelToCoords(Vector2i pixelPos);
	Vector2i mapCoordsToPixel(Vector2f point);

	// MOVE
	float getDt();
	void updateDt();
	int getGroundLevel();
	void setGroundLevel(int groundLevel);
	float getBorder(TE2D_DIRECTION direction);
	void setBorders(float left, float right, float up, float down);
	void deleteBorders();

	// OTHER
	bool isWorking();
	Vector2i getScreenResolution();
};