#include "Drawer.h"
#include <QImage>
#include <QColor>
#include "Lemniscate.h"

Drawer::Drawer(QObject *parent) :
QObject(parent)
{
}

void Drawer::drawLemniscate(QImage* image, Lemniscate* l)
{
    if (!image)
    {
        return;
    }

    int x1 = l->getX1();
    int x2 = l->getX2();
    int y1 = l->getY1();
    int y2 = l->getY2();

    int xEndPoint = x2 + (x2 - x1);
    int yEndPoint = y2 + (y2 - y1);




}

void Drawer::drawAxis(QImage *image)
{
    int x = image->width()/2;
    int y = image->height()/2;

    int const blackColor = 0;
    memset(image->bits() + y * image->bytesPerLine(), blackColor, image->bytesPerLine());

    unsigned char *point;
    for(int i = 0; i < image->height(); i++)
    {
         point = image->bits() + (i * image->bytesPerLine()) + x*BYTES_IN_PIXEL;
         memset(point, blackColor, BYTES_IN_PIXEL);
    }
}

void Drawer::drawPoint(QImage* image, int x, int y, QColor color)
{
    int newX;
    int newY;
    unsigned char *point;
	


    newX = ((image->width() / 2) + x)*BYTES_IN_PIXEL;

    newY = (image->height() / 2) - y;

	
    point = image->bits() + ((newY) * image->bytesPerLine()) + newX;

    *point = color.red();
    *++point = color.green();
    *++point = color.blue();

}
