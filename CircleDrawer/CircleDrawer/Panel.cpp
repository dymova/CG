#include "Panel.h"


Panel::Panel(int x, int y) : sizeX(x), sizeY(y)
{
}

Panel::~Panel()
{
}

int Panel::getSizeX() const
{
	return sizeX;
}

int Panel::getSizeY() const
{
	return sizeY;
}

