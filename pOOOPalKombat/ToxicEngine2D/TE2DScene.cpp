#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DScene::TE2DScene()
{
	this->groundLevel = -1;
	this->borders.push_back(-1);
	this->borders.push_back(-1);
	this->borders.push_back(-1);
	this->borders.push_back(-1);
}

// WINDOW

void TE2DScene::createWindow(int sizeX, int sizeY, string title, int style)
{
	this->window = new TE2DWindow(sizeX, sizeY, title, style);
}

void TE2DScene::clearWindow()
{
	this->window->clear(this->backgroundColor);
}

void TE2DScene::displayWindow()
{
	this->window->display();
}

void TE2DScene::closeWindow()
{
	this->window->close();
}

void TE2DScene::setFramerateLimit(int framerateLimit)
{
	this->window->setFramerateLimit(framerateLimit);
}

void TE2DScene::setCursorVisible(bool isVisible)
{
	this->window->setCursorVisible(isVisible);
}

Vector2i TE2DScene::getWindowSize()
{
	return this->window->getSize();
}

// DRAWABLES

void TE2DScene::addDrawable(TE2DDrawable* drawable)
{
	drawable->setIndex(this->drawables.size());

	this->drawables.push_back(drawable);
}

void TE2DScene::deleteDrawable(TE2DDrawable drawable)
{
	this->drawables.erase(this->drawables.begin() + drawable.getIndex());

	for (auto i = drawable.getIndex(); i < drawables.size(); i++)
		this->drawables[i]->setIndex(this->drawables[i]->getIndex() - 1);
}

void TE2DScene::clearDrawables()
{
	int size = this->drawables.size();

	for (auto i = 0; i < size; i++)
		this->drawables.pop_back();
}

void TE2DScene::swapDrawables(TE2DDrawable drawable1, TE2DDrawable drawable2)
{
	return;	// realisation is coming...
}

void TE2DScene::drawTE2DDrawable(TE2DDrawable drawable)
{
	this->window->draw(this->drawables[drawable.getIndex()]->getDrawable());
}

void TE2DScene::drawSFMLDrawable(Drawable& drawable)
{
	this->window->draw(drawable);
}

void TE2DScene::drawScene()
{
	this->window->clear(this->backgroundColor);

	for (auto i = 0; i < this->drawables.size(); i++)
	{
		if (this->drawables[i]->getIsJumping())
		{
			if (this->drawables[i]->getPosition().y
				- this->drawables[i]->getCurrJumpSpeed()
				< abs(this->groundLevel - this->drawables[i]->getJumpHeight()))
			{
				this->drawables[i]->setPosition(
					this->drawables[i]->getPosition().x,
					this->groundLevel - this->drawables[i]->getJumpHeight()
				);

				this->drawables[i]->setIsJumping(false);
				this->drawables[i]->setCurrJumpSpeed(
					this->drawables[i]->getJumpSpeed()
				);
			}
			else if (this->drawables[i]->getCurrJumpSpeed() <= 0.f)
			{
				this->drawables[i]->setIsJumping(false);
				this->drawables[i]->setCurrJumpSpeed(
					this->drawables[i]->getJumpSpeed()
				);
			}
			else
			{
				this->drawables[i]->move(0, -this->drawables[i]->getCurrJumpSpeed());
				this->drawables[i]->setCurrJumpSpeed(
					this->drawables[i]->getCurrJumpSpeed()
					- this->drawables[i]->getGravityStrength()
				);
			}
		}
		else
		{
			if ((this->drawables[i]->getPosition().y
				+ this->drawables[i]->getGlobalBounds().height
				< this->groundLevel)
				&& (this->drawables[i]->getIsOnGround()))
				this->drawables[i]->setIsOnGround(false);
			else if (!this->drawables[i]->getIsOnGround())
			{
				if (this->groundLevel > -1)
					this->drawables[i]->fall(*this);
			}
		}

		if (this->drawables[i]->getIsDrawable())
			this->drawTE2DDrawable(*this->drawables[i]);
	}

	this->window->display();
}

// VIEWS

int TE2DScene::getCurrentViewIndex()
{
	return this->currViewIndex;
}

View* TE2DScene::getView(int index)
{
	return this->views[index];
}

void TE2DScene::setView(int index)
{
	this->currViewIndex = index;

	if (index == TE2D_DEFAULT_VIEW)
		this->window->setDefaultView();
	else
		this->window->setView(this->views[index]);
}

void TE2DScene::addView(int sizeX, int sizeY, int cntrX, int cntrY)
{
	View* view = new View;
	view->setSize(sizeX, sizeY);
	view->setCenter(cntrX, cntrY);

	this->views.push_back(view);
}

void TE2DScene::deleteView(int index)
{
	this->views.erase(this->views.begin() + index);
}

Vector2f TE2DScene::getViewCenter(int index)
{
	if (index == TE2D_DEFAULT_VIEW)
		return Vector2f(0.f, 0.f);
	else
		return this->views[index]->getCenter();
}

Vector2i TE2DScene::getViewSize(int index)
{
	if (index == TE2D_DEFAULT_VIEW)
		return this->getWindowSize();
	else
		return
			Vector2i((int)this->views[index]->getSize().x,
				(int)this->views[index]->getSize().y);
}

void TE2DScene::setViewCenter(int index, int cntrX, int cntrY)
{
	this->views[index]->setCenter(cntrX, cntrY);
	this->setView(index);
}

// COLOR

Color TE2DScene::getBackgroundColor()
{
	return this->backgroundColor;
}

void TE2DScene::setBackgroundColor(Color color)
{
	this->backgroundColor = color;
}

// CONTROL

bool TE2DScene::isKeyPressed(Keyboard::Key key)
{
	return Keyboard::isKeyPressed(key);
}

bool TE2DScene::isMouseButtonPressed(Mouse::Button button)
{
	return Mouse::isButtonPressed(button);
}

Vector2i TE2DScene::getMousePosition()
{
	return Mouse::getPosition();
}

Vector2f TE2DScene::mapPixelToCoords(Vector2i pixelPos)
{
	return this->window->mapPixelToCoords(pixelPos);
}

Vector2i TE2DScene::mapCoordsToPixel(Vector2f point)
{
	return this->window->mapCoordsToPixel(point);
}

// MOVE

float TE2DScene::getDt()
{
	return this->dt;
}

void TE2DScene::updateDt()
{
	this->dt = this->clock.restart().asSeconds();
}

int TE2DScene::getGroundLevel()
{
	return this->groundLevel;
}

void TE2DScene::setGroundLevel(int groundLevel)
{
	this->groundLevel = groundLevel;
}

float TE2DScene::getBorder(TE2D_DIRECTION direction)
{
	switch (direction)
	{
	case TE2D_LEFT:
		return this->borders[0];
		break;
	case TE2D_RIGHT:
		return this->borders[1];
		break;
	case TE2D_UP:
		return this->borders[2];
		break;
	case TE2D_DOWN:
		return this->borders[3];
		break;
	default:
		break;
	}
}

void TE2DScene::setBorders(float left, float right, float up, float down)
{
	this->deleteBorders();

	this->borders.push_back(left);
	this->borders.push_back(right);
	this->borders.push_back(up);
	this->borders.push_back(down);
}

void TE2DScene::deleteBorders()
{
	if (this->borders.size() == 0)
		return;

	for (auto i = 0; i < 4; i++)
		this->borders.pop_back();
}

// OTHER

bool TE2DScene::isWorking()
{
	if (this->window->isOpen())
	{
		while (this->window->pollEvent())
			if (this->window->shouldClose())
				this->window->close();

		this->updateDt();

		return true;
	}
	else
		return false;
}

Vector2i TE2DScene::getScreenResolution()
{
	return Vector2i(
		sf::VideoMode::getDesktopMode().width,
		sf::VideoMode::getDesktopMode().height);
}