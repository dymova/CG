#include "Drawer.h"
#include <QImage>
#include <QColor>
#include "Circle.h"

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

	int r = c->getR();
	int x0 = c->getPositionX();
	int y0 = c->getPositionY();
	QColor blueColor(0, 204, 204);
 
	int y1 = y0 - r;
	int y2 = y0 + r;

	if (y2 > ((image->height()) / 2))
	{
		y2 = (image->height()) / 2;
	}


	if (y1 <= -(image->height()/2))
	{
		y1 = 1 - (image->height()/2);
	}

	for (y1; y1 <= y2; y1++)
	{
		int bound = (int)(sqrt((double)(r*r - (y1 - y0) * (y1 - y0))));
		int x1 = -bound + x0;
		int x2 = bound + x0;
		if (x1 < -image->width()/2)
		{
			x1 = -image->width() / 2;
		}
		if (x2 >= image->width() / 2)
		{
			x2 = (image->width() / 2) - 1;
		}

		for (x1; x1<=x2; x1++)
		{
			drawPoint(image, x1, y1, blueColor);
		}
	}

}

void Drawer::drawPoint(QImage* image, int x, int y, QColor color)
{
	int newX;
	int newY;
	unsigned char *point;
	
	const int BYTES_IN_PIXEL = 3;

	newX = ((image->width() / 2) + x)*BYTES_IN_PIXEL;

	newY = (image->height() / 2) - y;

	
	point = image->bits() + ((newY) * image->bytesPerLine()) + newX;

	*point = color.red();
	*++point = color.green();
	*++point = color.blue();

}
