#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DWindow::TE2DWindow(int sizeX, int sizeY, string title, int style)
{
	this->size.x = sizeX;
	this->size.y = sizeY;
	this->title = title;
	this->style = style;
	this->window = new RenderWindow(sf::VideoMode(sizeX, sizeY), title, style);
}

// GETTERS

bool TE2DWindow::isOpen()
{
	return this->window->isOpen();
}

bool TE2DWindow::pollEvent()
{
	return this->window->pollEvent(this->event);
}

bool TE2DWindow::shouldClose()
{
	return this->event.type == Event::Closed;
}

Vector2i TE2DWindow::getSize()
{
	return this->size;
}

// SETTERS

void TE2DWindow::setFramerateLimit(int framerateLimit)
{
	this->framerateLimit = framerateLimit;

	this->window->setFramerateLimit(framerateLimit);
}

void TE2DWindow::setCursorVisible(bool isVisible)
{
	this->window->setMouseCursorVisible(isVisible);
}

void TE2DWindow::setView(View* view)
{
	this->window->setView(*view);
}

void TE2DWindow::setDefaultView()
{
	this->window->setView(this->window->getDefaultView());
}

// OTHER FUNCTIONS

void TE2DWindow::close()
{
	this->window->close();
}

void TE2DWindow::clear(const Color color)
{
	this->window->clear(color);
}

void TE2DWindow::draw(const Drawable& drawable)
{
	this->window->draw(drawable);
}

void TE2DWindow::display()
{
	this->window->display();
}

Vector2f TE2DWindow::mapPixelToCoords(Vector2i pixelPos)
{
	Vector2f v2f = this->window->mapPixelToCoords(pixelPos);
	return this->window->mapPixelToCoords(pixelPos);
}

Vector2i TE2DWindow::mapCoordsToPixel(Vector2f point)
{
	return this->window->mapCoordsToPixel(point);
}