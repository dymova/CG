#include "Drawer.h"
#include <QImage>
#include <QColor>
#include <stdlib.h>
#include <QDebug>
#include "Figure.h"

Drawer::Drawer(QObject *parent) :
QObject(parent)
{
//    neighborhood = QList<QPair<int, int>>({qMakePair(-1, 1),
//                                        qMakePair(0, 1),
//                                        qMakePair(1, 1),
//                                        qMakePair(1, 0),
//                                        qMakePair(1, -1),
//                                        qMakePair(0, -1),
//                                        qMakePair(-1, -1),
//                                        qMakePair(-1, 0)});
}



void Drawer::drawFigure(QImage* image, Figure* l)
{
//    QColor blackColor(0, 0, 0);
//    long long x1 = l->getX1();
//    long long x2 = l->getX2();
//    long long y1 = l->getY1();
//    long long y2 = l->getY2();


//    if (!image)
//    {
//        return;
//    }

//    long long k = square(square(x2 - x1) + square(y2 - y1));

//    QPair<int, int> firstPoint = getExtremePoint(l, k, x2, y2, x2 + (x2 - x1),  y2 + (y2 - y1));
//    QPair<int, int> lastPoint = getExtremePoint(l, k, x1 ,y1,x1 + (x1 - x2),  y1 + (y1 - y2));

//    drawPoint(image, firstPoint.first, firstPoint.second, blackColor);
//    drawPoint(image, lastPoint.first, lastPoint.second, blackColor);

//    long long distanceX = abs(firstPoint.first + lastPoint.first) >> 2;
//    long long distanceY = abs(firstPoint.second + lastPoint.second) >> 2;
//    if(distanceX <= 0 && distanceY <= 0){
//        return;
//    }

//    int xCurr = firstPoint.first;
//    int yCurr = firstPoint.second;

//    int position = getSecondPoint( l,  k, yCurr, xCurr, true);
//    drawPoint(image, xCurr , yCurr, blackColor);
//    drawSide(firstPoint, lastPoint, l, k, image, position, qMakePair(xCurr, yCurr));


//    xCurr = firstPoint.first;
//    yCurr = firstPoint.second;
//    position = getSecondPoint(l,  k, yCurr, xCurr, false);
//    drawPoint(image, xCurr , yCurr, blackColor);
//    drawSide(firstPoint, lastPoint, l, k, image, position, qMakePair(xCurr, yCurr));

//    xCurr = lastPoint.first;
//    yCurr = lastPoint.second;
//    position = getSecondPoint(l,  k, yCurr, xCurr, true);
//    drawPoint(image, xCurr , yCurr, blackColor);
//    drawSide(lastPoint, firstPoint, l, k, image, position, qMakePair(xCurr, yCurr));

//    xCurr = lastPoint.first;
//    yCurr = lastPoint.second;
//    position = getSecondPoint(l,  k, yCurr, xCurr, false);
//    drawPoint(image, xCurr , yCurr, blackColor);
//    drawSide(lastPoint, firstPoint, l, k, image, position, qMakePair(xCurr, yCurr));

}

void Drawer::drawFocus(QImage *image, int x0, int y0)
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

        for (; y1 <= y2; y1++)
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

            for (; x1<=x2; x1++)
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

    newX = ((image->width() / 2) + x);

    newY = (image->height() / 2) - y;

    if (newX <= (image->width() - 1) && newY < (image->height()) && newX >=0 && newY >= 0 )
    {
        point = image->bits() + ((newY) * image->bytesPerLine()) + newX*BYTES_IN_PIXEL;

        *point = color.red();
        *++point = color.green();
        *++point = color.blue();
    }

}

long long Drawer::square(long long x)
{
    return x*x;
}

long long Drawer::min(long long a, long long b, long long c)
{
    if(a <= b && a <= c)
    {
        return a;
    }
    else if (b <= a && b <=c)
    {
        return b;
    }
    else
    {
        return c;
    }
}
