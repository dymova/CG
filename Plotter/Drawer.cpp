#include "Drawer.h"
#include <QImage>
#include <QColor>
#include <cmath>
#include <limits.h>
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

    return (square(x- x1) + square(y - y1)) *
           (square(x - x2) + square(y - y2)) << 4;
}

QPair<int,int> Drawer::getExtremePoint(Lemniscate* l, long long k, int xStart, int yStart, int xEnd, int yEnd)
//QPair<int,int> Drawer::getExtremePoint(Lemniscate* l, long k)
{
    int x1 = l->getX1();
    int x2 = l->getX2();
    int y1 = l->getY1();
    int y2 = l->getY2();
    int xSymmAxis = x1 - x2;
    int ySymmAxis = y1 - y2;


    int xMiddle;
    int yMiddle;

    long long param;

    int xFirstPoint;
    int yFirstPoint;
    int direction;

    while(true)
    {
         xMiddle = (xStart + xEnd) >> 1;
         yMiddle = (yStart + yEnd) >> 1;

         direction = xSymmAxis*(yMiddle - y2) - ySymmAxis*(xMiddle - x2);
         param = computeParam(xMiddle, yMiddle, l);

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
             long long paramStart = computeParam(xStart, yStart, l);
             long long paramEnd = computeParam(xEnd, yEnd, l);

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

void Drawer::findCenter(QList<QPair<int, int> > &center, Lemniscate* l)
{
    int x1 = l->getX1();
    int x2 = l->getX2();
    int y1 = l->getY1();
    int y2 = l->getY2();

    int x = (x2 + x1) >> 1;
    int y = (y2 + y1) >> 1;

    if((x2 + x1) % 2 == 0 && (y2 + y1) % 2 == 0)
    {
        center.append(qMakePair(x, y));
    }
    else
    {
        if ((y2 + y1) % 2 != 0)
        {
            center.append(qMakePair(x, y+1));
            center.append(qMakePair(x, y));
        }
        if((x2 + x1) % 2 != 0)
        {
            center.append(qMakePair(x+1, y+1));
            center.append(qMakePair(x+1, y));
        }
    }

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
        position = (position + 8) % 8; //todo % to << and -
        QPair<int, int> point = neighborhood.at(position);

        long param1 = computeParam(xPrevNeighbor + xCurr, yPrevNeighbor + yCurr, l);
        long param2 = computeParam(point.first + xCurr, point.second + yCurr, l);

         if((param1 <= k && param2 > k)
            || (param1 > k && param2 <= k)
             || (param1 < k && param2 >= k)
             || (param1 >= k && param2 < k))
         {
                  if(abs(param2 - k) < abs(param1 - k)) {
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

bool Drawer::isCenter(int xCurr, int yCurr, QList<QPair<int, int>> center)
{
    for(QPair<int, int> point : center)
    {
        if(xCurr == point.first && yCurr == point.second)
        {
            return true;
        }
    }
    return false;
}

void Drawer::drawSide(QPair<int, int> firstPoint, QPair<int, int> lastPoint,
                      Lemniscate* l, long long k, QList<QPair<int, int>> center, QImage* image, int position,  QPair<int, int> currPoint)
{
    QColor blackColor(0, 0, 0);
    long long x1 = l->getX1();
    long long x2 = l->getX2();
    long long y1 = l->getY1();
    long long y2 = l->getY2();

    int xCurr = currPoint.first;
    int yCurr = currPoint.second;
    int count = 0;


    bool isEnded  = false;
    if(isCenter(xCurr, yCurr, center))
    {
        return;
    }

    int xSymmAxis = firstPoint.first - lastPoint.first;
    int ySymmAxis = firstPoint.second - lastPoint.second;

//    for(int y = -image->height()/2; y < image->height()/2; y++)
//    {
//        for(int x = -(image->width()/2); x < image->width()/2; x++)
//        {
//            int k = xSymmAxis*(y - lastPoint.second) - ySymmAxis*(x - lastPoint.first);
////            int k = xSymmAxis*(y - y2) - ySymmAxis*(x - x2);
//            if(k >= 0)
//            {
//                drawPoint(image, x, y, QColor(50, 0,0));
//            }
//            else
//            {
//                drawPoint(image, x, y, QColor(0, 50,0));
//            }
//        }
//    }
//    drawFocus(image, firstPoint.first, firstPoint.second);
//    drawFocus(image, lastPoint.first, lastPoint.second);

    int prevDirection = xSymmAxis*(yCurr - lastPoint.second) - ySymmAxis*(xCurr - lastPoint.first);
    int direction;
    while(!isEnded)
    {
        int pos1 = (position - 1 + 8) % 8;
        int pos3 = (position + 1 + 8) % 8;
        QPair<int, int> point1 = neighborhood.at(pos1);
        QPair<int, int> point2 = neighborhood.at(position);
        QPair<int, int> point3 = neighborhood.at(pos3);

        long long param1 = abs(computeParam(point1.first + xCurr, point1.second + yCurr, l) - k);
        long long param2 = abs(computeParam(point2.first + xCurr, point2.second + yCurr, l) - k);
        long long param3 = abs(computeParam(point3.first + xCurr, point3.second + yCurr, l) - k );

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

//        if(count == 7000)
//        {
//            break;
//        }
        if(isCenter(xCurr, yCurr, center))
        {
            break;
        }

        if (!(
                    prevDirection > 0 && direction > 0
                || prevDirection < 0 && direction < 0
//                prevDirection >= 0 && direction >= 0
//                || prevDirection <= 0 && direction <= 0
                || count == 1)) //todo
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

    QList<QPair<int, int>> center;
    findCenter(center, l);

    int xCurr = firstPoint.first;
    int yCurr = firstPoint.second;
    drawPoint(image, xCurr, yCurr, blackColor);
    if(isCenter(xCurr, yCurr, center))
    {
        return;
    }

    int position = getSecondPoint( l,  k, yCurr, xCurr, true);
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(firstPoint, lastPoint, l, k, center, image, position, qMakePair(xCurr, yCurr));
    xCurr = firstPoint.first;
    yCurr = firstPoint.second;
    position = getSecondPoint(l,  k, yCurr, xCurr, false);
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(firstPoint, lastPoint, l, k, center, image, position, qMakePair(xCurr, yCurr));
    xCurr = lastPoint.first;
    yCurr = lastPoint.second;
    position = getSecondPoint(l,  k, yCurr, xCurr, true); //понять почему не всегда меняется направление
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(lastPoint, firstPoint, l, k, center, image, position, qMakePair(xCurr, yCurr));
    xCurr = lastPoint.first;
    yCurr = lastPoint.second;
    position = getSecondPoint(l,  k, yCurr, xCurr, false);
    drawPoint(image, xCurr , yCurr, blackColor);
    drawSide(lastPoint, firstPoint, l, k, center, image, position, qMakePair(xCurr, yCurr));

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

long long Drawer::min(int a, int b, int c)
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
