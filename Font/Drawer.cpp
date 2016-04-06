#include "Drawer.h"
#include <QImage>
#include <QColor>
#include <QtAlgorithms>
#include <stdlib.h>
#include <QDebug>
#include "Figure.h"
#include "Configuration.h"

Drawer::Drawer(QObject *parent) :
QObject(parent)
{
}



void Drawer::drawOutline(QImage* image, Configuration* config, QColor color)
{
    Figure* figure = config->getFigure();
    QList<Point *> points =  transformCoordinates(figure->getPoints(), config);
    Point* prev = points.first();
    int len = points.length();
    for(int i = 1; i <= len; i++)
    {
        Point* curr = points.at((i + len) % len); //for connect last and first point
        if(!prev->isOncurve() && !curr->isOncurve())
        {
            throw IncorrectConfigFileException("outline shold be closed");
        }

        if(isLine(prev, curr))
        {
            drawLine(image, prev->getX(), prev->getY(), curr->getX(), curr->getY(), color);
        }
        else if(isCurve(prev, curr))
        {
            Point* firstOncurve = points.at((i - 2 + len) % len);
            if(!firstOncurve->isOncurve()){
                throw IncorrectConfigFileException("outline shold be closed");
            }
            drawBezierCurve(image, config, firstOncurve, prev, curr, color);
        }
        prev = curr;
    }
}
bool Drawer::isLine(Point* prev, Point* curr){
    return prev->isOncurve() && curr->isOncurve();
}
bool Drawer::isCurve(Point* prev, Point* curr){
    return !prev->isOncurve() && curr->isOncurve();
}

QPair<double, double> Drawer::findYLimits(QList<Point *> points)
{
    double maxY = points.first()->getY();
    double minY = maxY;

    for(Point* p : points)
    {
        if(p->getY() < minY)
        {
            minY = p->getY();
        }
        if(p->getY() > maxY)
        {
            maxY = p->getY();
        }
    }
    return qMakePair(minY, maxY);
}

bool Drawer::isCrossingLines(double a1, double b1, double a2, double b2) {
    double det = -b1*a2+b2*a1;
    return det != 0;
}

void Drawer::computeCrossPointWithLine(Point *prev, Point *curr, int y0, QList<Point *>& crossPoints)
{
    double x1 = prev->getX();
    double y1 = prev->getY();
    double x2 = curr->getX();
    double y2 = curr->getY();

    //line1: ax+by+c=0
    double a = y2 - y1;
    double b = x1 - x2;
    double c = y1*(x2-x1) - x1*(y2-y1);
    //line2: y = y0 -> 0x+1y-y0=0

    if(isCrossingLines(a, b, 0, 1))
    {
        if((y1 > y0 || y0 > y2)
            && (y2 > y0 || y0 > y1))
        {
            return;
        }
        int x = round((-b*y0 - c) / a);
        if((round(x1) <= x && x <= round(x2))
            || (round(x2) <= x && x <= round(x1)))
        {
            if(fabs(x - prev->getX()) >= ERROR || fabs(y0 - prev->getY()) >= ERROR)
            {
                crossPoints.append(new Point(x,y0, true));
            }
        }
    }
    else
    {
        //c1 == k*c2 => the same
        if(c == 0 && y0 == 0) {
            crossPoints.append(curr);
            return;
        }
        if(b == -c/y0) {
            crossPoints.append(curr);
        }
    }
}

bool Drawer::isTangentLine(Point *p0, Point *p1, Point *p2, double t)
{
    double a = 2*(t - 1)*p0->getY()+ 2*(1-2*t)*p1->getY() + 2*t*p2->getY();
    double b = -(2*(t - 1)*p0->getX()+ 2*(1-2*t)*p1->getX() + 2*t*p2->getX());
//    double c = -a*pt->getX() - b*pt->getY();

    return !isCrossingLines(a, b, 0, 1);
}

void Drawer::computeCrossPointWithCurve(Point *p0, Point *p1, Point *p2, int y, QList<Point *> &crossPoints)
{
    double p0y = p0->getY();
    double p1y = p1->getY();
    double p2y = p2->getY();

    double a = (p0y - 2*p1y + p2y);
    double t1;
    double t2;
    if(a != 0){
        double d = a*y + p1y*p1y - p0y*p2y;
        if(d < 0) {
            return;
        }
        t1 = (p0y - p1y + sqrt(d)) / a;
        t2 = (p0y - p1y - sqrt(d)) / a;
    }
    else {
        t1 = (y - p0y) / (2*p1y - 2*p0y);      
        t2 = t1;
    }


    if(t1 > 0 && (t1 - 1) < ERROR)
    {
        Point* point1 = getPointOnCurve(p0, p1, p2, t1);
        double x1 = point1->getX();

        if(fabs(p0->getX() - x1) >= ERROR || fabs(p0->getY() - y) >= ERROR)
        {
            crossPoints.append(new Point(x1, y, true));
        }
        if(t1 == t2 && !isTangentLine(p0, p1, p2, t1)) {
            return;
        }

    }

    if(t2 > 0 && (t2 - 1) < ERROR)
    {
        Point* point2 = getPointOnCurve(p0, p1, p2, t2);
        double x2 = point2->getX();
        crossPoints.append(new Point(x2, y, true));
    }

}



void Drawer::drawFill(QImage *image, Configuration *config, QColor color)
{
    Figure* figure = config->getFigure();
    QList<Point *> points =  transformCoordinates(figure->getPoints(), config);
    QPair<double, double> limitsY = findYLimits(points);
    QList<Point *>  crossPoints;
    for(int y = limitsY.first; y < limitsY.second; y++){
        Point* prev = points.first();
        int len = points.length();

        for(int i = 1; i <= len; i++)
        {
            if(y == 13 && i == 9)
            {
                int k =1234;
            }
            Point* curr = points.at((i + len) % len); //for connect last and first point
            if(!prev->isOncurve() && !curr->isOncurve())
            {
                throw IncorrectConfigFileException("outline shold be closed");
            }

            if(isLine(prev, curr))
            {
                computeCrossPointWithLine(prev, curr, y, crossPoints);
            }
            else if(isCurve(prev, curr))
            {
                Point* firstOncurve = points.at((i - 2 + len) % len);
                if(!firstOncurve->isOncurve()){
                    throw IncorrectConfigFileException("outline shold be closed");
                }
                computeCrossPointWithCurve(firstOncurve, prev, curr, y, crossPoints);
            }
            prev = curr;
        }
        qSort(crossPoints.begin(), crossPoints.end(), compareByXValue);
        for(int i = 0; i < crossPoints.length(); i++)
        {
            if(i % 2 != 0) {
                Point* p0 = crossPoints.at(i - 1);
                Point* p1 = crossPoints.at(i);
                int x1 = p0->getX() < p1->getX() ? p0->getX() : p1->getX();
                int x2 = p0->getX() > p1->getX() ? p0->getX() : p1->getX();
                for(int x = x1; x  <= x2; x++){
                    drawPoint(image, x, y, color);
                }
            }
        }
        crossPoints.clear();
    }
}


bool Drawer::compareByXValue(const Point* a, const Point* b)
{
    return a->getX() > b->getX();
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

void Drawer::drawLine(QImage *image, double x0, double y0, double x1, double y1, QColor color)
{
    x0 = round(x0);
    x1 = round(x1);
    y0 = round(y0);
    y1 = round(y1);
    const int deltaX = fabs(x1 - x0);
    const int deltaY = fabs(y1 - y0);
    const int signX = x0 < x1 ? 1 : -1;
    const int signY = y0 < y1 ? 1 : -1;

    int error = deltaX - deltaY;

    drawPoint(image, x1, y1, color);
    while(x0 != x1 || y0 != y1) {
       drawPoint(image, x0, y0,color);
       const double error2 = error * 2;

       if(error2 > -deltaY) {
           error -= deltaY;
           x0 += signX;
       }
       if(error2 < deltaX) {
           error += deltaX;
           y0 += signY;
       }
    }
}

void Drawer::drawBezierCurve(QImage *image, Configuration* config, Point *p0, Point *p1, Point *p2, QColor color)
{
    Point* middlePoint = getPointOnCurve(p0, p1, p2, 0.5);
    double distToLine = distanceToLine(middlePoint, p0, p2);

    if(distToLine > ERROR)
    {
        drawBezierCurve(image, config, middlePoint, getNewNonOncurvePoint(p1, p2), p2, color);
        drawBezierCurve(image, config, p0, getNewNonOncurvePoint(p0, p1), middlePoint, color);
    }
    else
    {
        drawLine(image, p0->getX(), p0->getY(), p1->getX(), p1->getY(), color);
        drawLine(image, p1->getX(), p1->getY(), p2->getX(), p2->getY(), color);
    }
}

Point* Drawer::getPointOnCurve(Point *p0, Point *p1, Point *p2, double t)
{
    double x = (1-t)*(1-t)*p0->getX() + 2*t*(1-t)*p1->getX() + t*t*p2->getX();
    double y = (1-t)*(1-t)*p0->getY() + 2*t*(1-t)*p1->getY() + t*t*p2->getY();
    return new Point(x, y, true);
}


double Drawer::distanceToLine(Point *point, Point *linePoint1, Point *linePoint2)
{
    double x1 = linePoint1->getX();
    double y1 = linePoint1->getY();
    double x2 = linePoint2->getX();
    double y2 = linePoint2->getY();

    //line: ax+by+c=0
    double a = y2 - y1;
    double b = x1 - x2;
    double c = y1*(x2-x1) - x1*(y2-y1);

    double res = fabs(a*point->getX() + b*point->getY() + c) / sqrt(a*a + b*b);
    return res;
}

Point *Drawer::getNewNonOncurvePoint(Point *p0, Point *p1)
{
    double x = (p0->getX() + p1->getX()) / 2;
    double y = (p0->getY() + p1->getY()) / 2;
    return new Point(x, y, false);
}

QList<Point *> Drawer::transformCoordinates(QList<Point *> points, Configuration* config)
{
    double scale = config->getScale();
    double k;
    QList<Point *> res;
    for(Point* p : points) {
        double x = p->getX();
        double y = p->getY();
        if(scale <= 0){
            k = 1 + (scale/1000);
        }
        else
        {
            k = 1 + (scale / 100);
        }
        res.append(new Point(round((x + config->getPositionX())*k),
                             round((y + config->getPositionY())*k),
                             p->isOncurve()));
//        res.append(new Point((x + config->getPositionX())*k,
//                             (y + config->getPositionY())*k,
//                             p->isOncurve()));

    }
    return res;
}

