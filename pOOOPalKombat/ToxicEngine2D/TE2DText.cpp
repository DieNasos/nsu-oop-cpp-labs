#include "ToxicEngine2D.h"

// CONSTRUCTOR
TE2DText::TE2DText()
{
	this->text = Text();
}

// GETTERS

Text TE2DText::getText()
{
	return this->text;
}

int TE2DText::getCurrentStringIndex()
{
	return this->currStrIndex;
}

// SETTERS

void TE2DText::addFont(string sourceFilename)
{
	Font font;
	font.loadFromFile(sourceFilename);
	this->fonts.push_back(font);
}

void TE2DText::deleteFont(int index)
{
	this->fonts.erase(this->fonts.begin() + index);
}

void TE2DText::setFont(int index)
{
	this->text.setFont(this->fonts[index]);
}

void TE2DText::addColor(Color color)
{
	this->colors.push_back(color);
}

void TE2DText::deleteColor(int index)
{
	this->colors.erase(this->colors.begin() + index);
}

void TE2DText::setFillColor(int index)
{
	this->text.setFillColor(this->colors[index]);
}

void TE2DText::setOutlineColor(int index)
{
	this->text.setOutlineColor(this->colors[index]);
}

void TE2DText::setOutlineThickness(float thickness)
{
	this->text.setOutlineThickness(thickness);
}

void TE2DText::addString(string string)
{
	this->strings.push_back(string);
}

void TE2DText::deleteString(int index)
{
	this->strings.erase(this->strings.begin() + index);
}

void TE2DText::setString(int index)
{
	this->text.setString(this->strings[index]);

	this->currStrIndex = index;
}

void TE2DText::setSize(int size)
{
	this->text.setCharacterSize(size);
}

void TE2DText::copyParameters(TE2DText text)
{
	// TE2DDrawable
	this->copyCommonParameters(text);

	// TE2DText
	this->text = text.text;
	this->fonts = text.fonts;
	this->colors = text.colors;
	this->strings = text.strings;
	this->size = text.size;
	this->currStrIndex = text.currStrIndex;
}

// VIRTUAL FUNCTIONS FROM TE2DDrawable

Drawable& TE2DText::getDrawable()
{
	return this->text;
}

void TE2DText::setPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->text.setPosition(this->pos.x, this->pos.y);
}

Vector2f TE2DText::getCenter()
{
	Vector2f cntr;

	cntr.x = this->text.getPosition().x +
		this->text.getGlobalBounds().width / 2;
	cntr.y = this->text.getPosition().y +
		this->text.getGlobalBounds().height / 2;

	return cntr;
}

FloatRect TE2DText::getGlobalBounds()
{
	return this->text.getGlobalBounds();
}

Vector2f TE2DText::getScale()
{
	return this->text.getScale();
}

void TE2DText::setScale(float x, float y)
{
	this->text.setScale(Vector2f(x, y));
}

float TE2DText::getRotation()
{
	return this->text.getRotation();
}

void TE2DText::setRotation(float rotation)
{
	this->text.setRotation(rotation);
}