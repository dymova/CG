#include "Drawer.h"
#include <QImage>
#include <QColor>
#include <stdlib.h>
#include <QDebug>
#include "Lemniscate.h"

Drawer::Drawer(QObject *parent) :
QObject(parent)
{
    neighborhood = QList<QPair<int, int>>({qMakePair(-1, 1),
                                        qMakePair(0, 1),
                                        qMakePair(1, 1),
                                        qMakePair(1, 0),
                                        qMakePair(1, -1),
                                        qMakePair(0, -1),
                                        qMakePair(-1, -1),
                                        qMakePair(-1, 0)});
}

long long Drawer::computeParam(long long x, long long y, Lemniscate* l) {
    long long x1 = l->getX1();
    long long x2 = l->getX2();
    long long y1 = l->getY1();
    long long y2 = l->getY2();

    long long res = (square(x- x1) + square(y - y1)) *
            (square(x - x2) + square(y - y2)) << 4;

    return res;
}

QPair<int,int> Drawer::getExtremePoint(Lemniscate* l, long long k, int xStart, int yStart, int xEnd, int yEnd)
{
    int xMiddle;
    int yMiddle;

    long long param;

    int xFirstPoint;
    int yFirstPoint;

    while(true)
    {
         xMiddle = (xStart + xEnd) >> 1;
         yMiddle = (yStart + yEnd) >> 1;

         param = computeParam(xMiddle, yMiddle, l);

         if(param  < k) {
             xStart = xMiddle;
             yStart = yMiddle;

         } else {
             xEnd = xMiddle;
             yEnd = yMiddle;
         }

         int xDelta = llabs(xStart - xEnd);
         int yDelta = llabs(yStart- yEnd);

         if(xDelta <= 1 && yDelta <=1)
         {
             long long paramStart = computeParam(xStart, yStart, l);
             long long paramEnd = computeParam(xEnd, yEnd, l);

             if( llabs(paramStart - k) < llabs(paramEnd - k))
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

int Drawer::getSecondPoint(Lemniscate* l, long long k, int &yCurr, int &xCurr, bool rightDirection)
{
    int delta;
    if(rightDirection){
        delta = 1;
    }
    else
    {
        delta = -1;
    }

    int xPrevNeighbor = neighborhood.first().first;
    int yPrevNeighbor = neighborhood.first().second;
    for(int position = 0; ; position += delta)
    {
        position = (position + 8) % 8;
        QPair<int, int> point = neighborhood.at(position);

        long long param1 = computeParam(xPrevNeighbor + xCurr, yPrevNeighbor + yCurr, l);
        long long param2 = computeParam(point.first + xCurr, point.second + yCurr, l);

         if((param1 <= k && param2 > k)
            || (param1 > k && param2 <= k)
             || (param1 < k && param2 >= k)
             || (param1 >= k && param2 < k))
         {
                  if(llabs(param2 - k) < llabs(param1 - k)) {
                      xCurr = point.first + xCurr;
                      yCurr = point.second + yCurr;

                  }
                  else
                  {
                      xCurr = xPrevNeighbor + xCurr;
                      yCurr = yPrevNeighbor + yCurr;
                      position += -delta;

                  }
                  return (position + 8) % 8;
         }

         xPrevNeighbor = point.first;
         yPrevNeighbor = point.second;
    }
}

void Drawer::drawSide(QPair<int, int> firstPoint, QPair<int, int> lastPoint,
                      Lemniscate* l, long long k, QImage* image, int position,  QPair<int, int> currPoint)
{
    QColor blackColor(0, 0, 0);

    long long xCurr = currPoint.first;
    long long yCurr = currPoint.second;
    int count = 0;

    long long xSymmAxis = firstPoint.first - lastPoint.first;
    long long ySymmAxis = firstPoint.second - lastPoint.second;

    long long prevDirection = xSymmAxis*(yCurr - lastPoint.second) - ySymmAxis*(xCurr - lastPoint.first);
    long long direction;
    while(true)
    {
        int pos1 = (position - 1 + 8) % 8;
        int pos3 = (position + 1 + 8) % 8;
        QPair<int, int> point1 = neighborhood.at(pos1);
        QPair<int, int> point2 = neighborhood.at(position);
        QPair<int, int> point3 = neighborhood.at(pos3);

        long long param1 = llabs(computeParam(point1.first + xCurr, point1.second + yCurr, l) - k);
        long long param2 = llabs(computeParam(point2.first + xCurr, point2.second + yCurr, l) - k);
        long long param3 = llabs(computeParam(point3.first + xCurr, point3.second + yCurr, l) - k );

        long long minParam = min(param1, param2, param3);

        if(minParam == param1) {
            xCurr = point1.first + xCurr;
            yCurr = point1.second + yCurr;
            position = pos1;
        }
        else if(minParam == param2)
        {
            xCurr = point2.first + xCurr;
            yCurr = point2.second + yCurr;
        }
        else if(minParam == param3)
        {
            xCurr = point3.first + xCurr;
            yCurr = point3.second + yCurr;
            position = pos3;
        }
        drawPoint(image, xCurr , yCurr, blackColor);

        direction = xSymmAxis*(yCurr - lastPoint.second) - ySymmAxis*(xCurr - lastPoint.first);
        count++;


        if ((prevDirection <= 0 || direction <= 0)
              && (prevDirection >= 0 || direction >= 0))
        {
            break;
        }
        prevDirection = direction;
    }
}

void Drawer::drawLemniscate(QImage* image, Lemniscate* l)
{
    QColor blackColor(0, 0, 0);
    long long x1 = l->getX1();
    long long x2 = l->getX2();
    long long y1 = l->getY1();
    long long y2 = l->getY2();


    if (!image)
    {
        return;
    }

    long long k = square(square(x2 - x1) + square(y2 - y1));

    QPair<int, int> firstPoint = getExtremePoint(l, k, x2, y2, x2 + (x2 - x1),  y2 + (y2 - y1));
    QPair<int, int> lastPoint = getExtremePoint(l, k, x1 ,y1,x1 + (x1 - x2),  y1 + (y1 - y2));

    drawPoint(image, firstPoint.first, firstPoint.second, blackColor);
    drawPoint(image, lastPoint.first, lastPoint.second, blackColor);

    long long distanceX = abs(firstPoint.first + lastPoint.first) >> 2;
    long long distanceY = abs(firstPoint.second + lastPoint.second) >> 2;
    if(distanceX <= 0 && distanceY <= 0){
        return;
    }

    int xCurr = firstPoint.first;
    int yCurr = firstPoint.second;

    int position = getSecondPoint( l,  k, yCurr, xCurr, true);
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(firstPoint, lastPoint, l, k, image, position, qMakePair(xCurr, yCurr));


    xCurr = firstPoint.first;
    yCurr = firstPoint.second;
    position = getSecondPoint(l,  k, yCurr, xCurr, false);
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(firstPoint, lastPoint, l, k, image, position, qMakePair(xCurr, yCurr));

    xCurr = lastPoint.first;
    yCurr = lastPoint.second;
    position = getSecondPoint(l,  k, yCurr, xCurr, true);
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(lastPoint, firstPoint, l, k, image, position, qMakePair(xCurr, yCurr));

    xCurr = lastPoint.first;
    yCurr = lastPoint.second;
    position = getSecondPoint(l,  k, yCurr, xCurr, false);
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(lastPoint, firstPoint, l, k, image, position, qMakePair(xCurr, yCurr));

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
