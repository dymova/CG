#include "Drawer.h"
#include <QImage>
#include <QColor>
#include "Circle.h"
#include <stdlib.h> 

Drawer::Drawer(QObject *parent) :
QObject(parent)
{
}

void Drawer::drawCircle(QImage* image, Circle* c)
{
	if (!image)
	{
		return;
	}
	uchar* pubBuffer = image->bits();

	int r = c->getR();
	int x0 = c->getPositionX();
	int y0 = c->getPositionY();
	QColor blueColor(0, 204, 204);


	for (int y = y0-r; y <= y0+r; y++)
	{
		for (int x = x0-r; x <= x0+r; x++)
		{
			if (((x-x0) * (x-x0)) + ((y-y0) * (y-y0)) <= (r * r))
			{
				drawPoint(image, x, y, blueColor);
			}
		}
	}
	
}

void Drawer::drawPoint(QImage* image, int x, int y, QColor color)
{
	int newX;
	int newY;
	unsigned char *point;
	
	const int BYTES_IN_PIXEL = 3;

	newX = (image->bytesPerLine() / 2) + x*BYTES_IN_PIXEL;
	newY = (image->height() / 2) + y;

	if (newX <= (image->bytesPerLine() - 3) && newY < (image->height()) && newX >=0 && newY >= 0 )
	{
		point = image->bits() + ((image->height() - newY) * image->bytesPerLine()) + newX;

		*point = color.red();
		*++point = color.green();
		*++point = color.blue();
	}

}

