#include "Drawer.h"
#include <QImage>
#include <QColor>
#include <cmath>
#include "Lemniscate.h"

Drawer::Drawer(QObject *parent) :
QObject(parent)
{
}

QPair<int,int> Drawer::getFirstPoint(Lemniscate* l)
{
    int x1 = l->getX1();
    int x2 = l->getX2();
    int y1 = l->getY1();
    int y2 = l->getY2();

    int xEnd = x2 + (x2 - x1);
    int yEnd = y2 + (y2 - y1);

    int xStart = x2;
    int yStart = y2;


    // 16*((x - x1)^2 + (y - y1)^2)((x - x2)^2 + (y - y2)^2) = ((x2 - x1)^2 + (y2 - y1)^2))^2
    int k = ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))*((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    int xMiddle;
    int yMiddle;

    int param;

    int xFirstPoint;
    int yFirstPoint;

    while(true)
    {
         xMiddle = (xStart + xEnd) >> 1;
         yMiddle = (yStart + yEnd) >> 1;

         param = ((xMiddle - x1)*(xMiddle - x1) + (yMiddle - y1)*(yMiddle - y1))*
                 ((xMiddle - x2)*(xMiddle - x2) + (yMiddle - y2)*(yMiddle - y2)) << 4;

         if(param  < k) {
             xStart = xMiddle;
             yStart = yMiddle;

         } else {
             xEnd = xMiddle;
             yEnd = yMiddle;
         }

         int xDelta = abs(xStart - xEnd);
         int yDelta = abs(yStart- yEnd);

         if(xDelta <= 1 && yDelta <=1)
         {
             int paramStart = ((xStart - x1)*(xStart- x1) + (yStart- y1)*(yStart- y1))*
                     ((xStart- x2)*(xStart- x2) + (yStart- y2)*(yStart- y2)) << 4;
             int paramEnd= ((xEnd- x1)*(xEnd- x1) + (yEnd- y1)*(yEnd- y1))*
                     ((xEnd- x2)*(xEnd- x2) + (yEnd- y2)*(yEnd- y2)) << 4;

             if(abs(paramStart - k) < abs(paramEnd - k))
             {
                 xFirstPoint = xStart;
                 yFirstPoint = yStart;
             } else {
                 xFirstPoint = xEnd;
                 yFirstPoint = yEnd;
             }
             break;
         }
    }
    return qMakePair(xFirstPoint, yFirstPoint);
}

void Drawer::drawLemniscate(QImage* image, Lemniscate* l)
{
    if (!image)
    {
        return;
    }

    QPair<int, int> firstPoint = getFirstPoint(l);


}

void Drawer::drawFocus(QImage *image, int y0, int x0)
{
    int r = 2;
    QColor blackColor(0, 0, 0);

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
                drawPoint(image, x1, y1, blackColor);
            }
        }
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
