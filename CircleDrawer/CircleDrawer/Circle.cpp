#include "Circle.h"


Circle::Circle(int r, int x, int y) : radius(r), positionX(x), positionY(y)
{
}

Circle::~Circle()
{
}

int Circle::getR() const
{
	return radius;
}

void Circle::setR(int r)
{
	radius = r;
}

void Circle::setPositionX(int x)
{
	positionX = x;
}

void Circle::setPositionY(int y)
{
	positionY = y;
}

int Circle::getPositionX() const
{
	return positionX;
}

int Circle::getPositionY() const
{
	return positionY;
}


