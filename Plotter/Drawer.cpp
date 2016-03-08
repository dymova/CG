#include "Drawer.h"
#include <QImage>
#include <QColor>
#include <cmath>
#include "Lemniscate.h"

Drawer::Drawer(QObject *parent) :
QObject(parent)
{
}

int Drawer::computeParam(int x, int y, Lemniscate* l) {
    int x1 = l->getX1();
    int x2 = l->getX2();
    int y1 = l->getY1();
    int y2 = l->getY2();

    return ((x- x1)*(x - x1) + (y - y1)*(y - y1))*
           ((x - x2)*(x - x2) + (y - y2)*(y - y2)) << 4;
}

QPair<int,int> Drawer::getFirstPoint(Lemniscate* l, int k)
{
    int x1 = l->getX1();
    int x2 = l->getX2();
    int y1 = l->getY1();
    int y2 = l->getY2();

    int xEnd = x2 + (x2 - x1);
    int yEnd = y2 + (y2 - y1);

    int xStart = x2;
    int yStart = y2;



    int xMiddle;
    int yMiddle;

    int param;

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

         int xDelta = abs(xStart - xEnd);
         int yDelta = abs(yStart- yEnd);

         if(xDelta <= 1 && yDelta <=1)
         {
             int paramStart = computeParam(xStart, yStart, l);
             int paramEnd = computeParam(xEnd, yEnd, l);

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

void Drawer::updateNeighborhood(QList<QPair<int, int> > &neighborhood, int xStart, int yStart)
{
    while(xStart != neighborhood.first().first || yStart != neighborhood.first().second)
    {
        int xtmp = neighborhood.first().first;
        int ytmp = neighborhood.first().second;

        auto tmp = neighborhood.takeLast();
        neighborhood.push_front(tmp);
    }


    auto tmp = neighborhood.takeFirst();
    neighborhood.push_back(tmp);

}

void Drawer::drawLemniscate(QImage* image, Lemniscate* l)
{
    QColor blackColor(0, 0, 0);
    int x1 = l->getX1();
    int x2 = l->getX2();
    int y1 = l->getY1();
    int y2 = l->getY2();


    if (!image)
    {
        return;
    }

    // 16*((x - x1)^2 + (y - y1)^2)((x - x2)^2 + (y - y2)^2) = ((x2 - x1)^2 + (y2 - y1)^2))^2
    int k = ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))*((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));

    QPair<int, int> firstPoint = getFirstPoint(l, k);
    int xCurr = firstPoint.first;
    int yCurr = firstPoint.second;
    drawPoint(image, xCurr, yCurr, blackColor);

    QList<QPair<int, int>> neighborhood({qMakePair(-1, 1),
                                        qMakePair(0, 1),
                                        qMakePair(1, 1),
                                        qMakePair(1, 0),
                                        qMakePair(1, -1),
                                        qMakePair(0, -1),
                                        qMakePair(-1, -1),
                                        qMakePair(-1, 0)});
    int count = 0;


    int xPrev = neighborhood.first().first + xCurr;
    int yPrev = neighborhood.first().second + yCurr;

    while(true)//todo
    {
    int xPrevNeighbor = neighborhood.first().first;
    int yPrevNeighbor = neighborhood.first().second;

        for(QPair<int, int> point : neighborhood)
        {
//            int xtmp = point.first;
//            int ytmp = point.second;

            int param1 = computeParam(xPrevNeighbor + xCurr, yPrevNeighbor + yCurr, l);
            int param2 = computeParam(point.first + xCurr, point.second + yCurr, l);

             if((param1 <= k && param2 > k)
                || (param1 > k && param2 <= k)
                 || (param1 < k && param2 >= k)
                 || (param1 >= k && param2 < k))
             {
                 xPrev = xCurr;
                 yPrev = yCurr;

                  if(abs(param2 - k) < abs(param1 - k)) {
                      xCurr = point.first + xCurr;
                      yCurr = point.second + yCurr;

                  }
                  else
                  {
                      xCurr = xPrevNeighbor + xCurr;
                      yCurr = yPrevNeighbor + yCurr;
                  }
                  drawPoint(image, xCurr , yCurr, blackColor);
                  updateNeighborhood(neighborhood, xPrev - xCurr, yPrev- yCurr);
                  break;
             }

             xPrevNeighbor = point.first;
             yPrevNeighbor = point.second;
        }
        count++;
        if(xCurr == firstPoint.first && yCurr == firstPoint.second)
        {
            break;
        }
        if(count == 2000) //todo
            break;
    }


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
	


    newX = ((image->width() / 2) + x)*BYTES_IN_PIXEL;

    newY = (image->height() / 2) - y;

	
    point = image->bits() + ((newY) * image->bytesPerLine()) + newX;

    *point = color.red();
    *++point = color.green();
    *++point = color.blue();

}
