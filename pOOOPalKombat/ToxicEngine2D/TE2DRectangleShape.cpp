#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DRectangleShape::TE2DRectangleShape()
{
	this->shape = RectangleShape();
}

// GETTERS

Color TE2DRectangleShape::getFillColor()
{
	return this->shape.getFillColor();
}

Color TE2DRectangleShape::getOutlineColor()
{
	return this->shape.getOutlineColor();
}

float TE2DRectangleShape::getOutlineThickness()
{
	return this->shape.getOutlineThickness();
}

Vector2f TE2DRectangleShape::getSize()
{
	return this->shape.getSize();
}

// SETTERS

void TE2DRectangleShape::addColor(Color color)
{
	this->colors.push_back(color);
}

void TE2DRectangleShape::deleteColor(int index)
{
	this->colors.erase(this->colors.begin() + index);
}

void TE2DRectangleShape::setFillColor(int index)
{
	this->shape.setFillColor(this->colors[index]);
}

void TE2DRectangleShape::setOutlineColor(int index)
{
	this->shape.setOutlineColor(this->colors[index]);
}

void TE2DRectangleShape::setOutlineThickness(float thickness)
{
	this->shape.setOutlineThickness(thickness);
}

void TE2DRectangleShape::setSize(float sizeX, float sizeY)
{
	this->shape.setSize(Vector2f(sizeX, sizeY));
}

void TE2DRectangleShape::copyParameters(TE2DRectangleShape shape)
{
	// TE2DDrawable
	this->copyCommonParameters(shape);

	// TE2DRectangleShape
	this->shape = shape.shape;
	this->colors = shape.colors;
}

// VIRTUAL FUNCTIONS FROM TE2DDrawable

Drawable& TE2DRectangleShape::getDrawable()
{
	return this->shape;
}

void TE2DRectangleShape::setPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;

	this->shape.setPosition(x, y);
}

FloatRect TE2DRectangleShape::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

Vector2f TE2DRectangleShape::getCenter()
{
	Vector2f cntr;

	cntr.x = this->pos.x +
		this->shape.getGlobalBounds().width / 2;
	cntr.y = this->pos.y +
		this->shape.getGlobalBounds().height / 2;

	return cntr;
}

Vector2f TE2DRectangleShape::getScale()
{
	return this->shape.getScale();
}

void TE2DRectangleShape::setScale(float x, float y)
{
	this->shape.setScale(Vector2f(x, y));
}

float TE2DRectangleShape::getRotation()
{
	return this->shape.getRotation();
}

void TE2DRectangleShape::setRotation(float rotation)
{
	this->shape.setRotation(rotation);
}