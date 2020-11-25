#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DRectangleButton::TE2DRectangleButton()
{
	this->is_active = false;
}

// GETTERS

bool TE2DRectangleButton::isActive(TE2DScene scene)
{
	if (
		((scene.getCurrentViewIndex() == TE2D_DEFAULT_VIEW)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).x
			- (scene.getScreenResolution().x / 2 - scene.getWindowSize().x / 2)
			> this->shape.getPosition().x)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).x
			- (scene.getScreenResolution().x / 2 - scene.getWindowSize().x / 2)
			< this->shape.getPosition().x
			+ this->shape.getGlobalBounds().width)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).y
			- (scene.getScreenResolution().y / 2 - scene.getWindowSize().y / 2)
			> this->shape.getPosition().y)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).y
			- (scene.getScreenResolution().y / 2 - scene.getWindowSize().y / 2)
			< this->shape.getPosition().y
			+ this->shape.getGlobalBounds().height))

		|| ((scene.getCurrentViewIndex() != TE2D_DEFAULT_VIEW)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).x
			- (scene.getScreenResolution().x / 2 - scene.getWindowSize().x / 2)
			> this->shape.getPosition().x)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).x
			- (scene.getScreenResolution().x / 2 - scene.getWindowSize().x / 2)
			< this->shape.getPosition().x
			+ this->shape.getGlobalBounds().width)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).y
			- (scene.getScreenResolution().y / 2 - scene.getWindowSize().y / 2)
			> this->shape.getPosition().y)
		&& (scene.mapPixelToCoords(scene.getMousePosition()).y
			- (scene.getScreenResolution().y / 2 - scene.getWindowSize().y / 2)
			< this->shape.getPosition().y
			+ this->shape.getGlobalBounds().height))
	)
	{
		if (!this->is_active)
		{
			this->setFillColor(this->activeFillColorIndex);
			this->setOutlineColor(this->activeOutlineColorIndex);
			this->setOutlineThickness(this->activeOutlineThickness);

			this->is_active = true;
		}

		return true;
	}
	else
	{
		if (this->is_active)
		{
			this->shape.setFillColor(this->colors[this->defaultFillColorIndex]);
			this->shape.setOutlineColor(this->colors[this->defaultOutlineColorIndex]);
			this->shape.setOutlineThickness(this->defaultOutlineThickness);

			this->is_active = false;
		}

		return false;
	}
}

bool TE2DRectangleButton::isPressed(TE2DScene scene, Mouse::Button button)
{
	return
		(this->isActive(scene))
		&& (scene.isMouseButtonPressed(button));
}

Color TE2DRectangleButton::getActiveFillColor()
{
	return this->colors[this->activeFillColorIndex];
}

Color TE2DRectangleButton::getActiveOutlineColor()
{
	return this->colors[this->activeOutlineColorIndex];
}

float TE2DRectangleButton::getActiveOutlineThickness()
{
	return this->activeOutlineThickness;
}

Color TE2DRectangleButton::getDefaultFillColor()
{
	return this->colors[this->defaultFillColorIndex];
}

Color TE2DRectangleButton::getDefaultOutlineColor()
{
	return this->colors[this->defaultOutlineColorIndex];
}

float TE2DRectangleButton::getDefaultOutlineThickness()
{
	return this->defaultOutlineThickness;
}

// SETTERS

void TE2DRectangleButton::setText(TE2DText* text)
{
	this->text = text;
}

void TE2DRectangleButton::setActiveFillColor(int index)
{
	this->activeFillColorIndex = index;
}

void TE2DRectangleButton::setActiveOutlineColor(int index)
{
	this->activeOutlineColorIndex = index;
}

void TE2DRectangleButton::setActiveOutlineThickness(float thickness)
{
	this->activeOutlineThickness = thickness;
}

void TE2DRectangleButton::setDefaultFillColor(int index)
{
	this->defaultFillColorIndex = index;
	this->setFillColor(index);
}

void TE2DRectangleButton::setDefaultOutlineColor(int index)
{
	this->defaultOutlineColorIndex = index;
	this->setOutlineColor(index);
}

void TE2DRectangleButton::setDefaultOutlineThickness(float thickness)
{
	this->defaultOutlineThickness = thickness;
	this->setOutlineThickness(thickness);
}

void TE2DRectangleButton::copyParameters(TE2DRectangleButton button)
{
	// TE2DDrawable
	this->copyCommonParameters(button);

	// TE2DRectangleShape
	this->shape = button.shape;
	this->colors = button.colors;

	// TE2DRectangleButton
	this->text = button.text;
	this->defaultFillColorIndex = button.defaultFillColorIndex;
	this->activeFillColorIndex = button.activeFillColorIndex;
	this->defaultOutlineColorIndex = button.defaultOutlineColorIndex;
	this->activeOutlineColorIndex = button.activeOutlineColorIndex;
	this->defaultOutlineThickness = button.defaultOutlineThickness;
	this->activeOutlineThickness = button.activeOutlineThickness;
}

// VIRTUAL FUNCTIONS FROM TE2DDrawable

Drawable& TE2DRectangleButton::getDrawable()
{
	return this->shape;
}

void TE2DRectangleButton::setPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->shape.setPosition(x, y);
	this->text->setPosition(
		this->getCenter().x - this->text->getGlobalBounds().width / 2,
		this->getCenter().y - this->text->getGlobalBounds().height / 2
	);
}

FloatRect TE2DRectangleButton::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

Vector2f TE2DRectangleButton::getCenter()
{
	Vector2f cntr;
	cntr.x = this->pos.x +
		this->shape.getGlobalBounds().width / 2;
	cntr.y = this->pos.y +
		this->shape.getGlobalBounds().height / 2;
	return cntr;
}

Vector2f TE2DRectangleButton::getScale()
{
	return this->shape.getScale();
}

void TE2DRectangleButton::setScale(float x, float y)
{
	this->shape.setScale(Vector2f(x, y));
	this->text->setScale(x, y);
}

float TE2DRectangleButton::getRotation()
{
	return this->shape.getRotation();
}

void TE2DRectangleButton::setRotation(float rotation)
{
	this->shape.setRotation(rotation);
	this->text->setRotation(rotation);
}