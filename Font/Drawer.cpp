#include "Drawer.h"
#include <QImage>
#include <QColor>
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
    int centerX = config->getPositionX();
    int centerY = config->getPositionY();
    Figure* figure = config->getFigure();
    QList<Point *> points =  scaleCoordinates(figure->getPoints(), config->getScale());
    Point* prev = points.first();
    int len = points.length();
    for(int i = 1; i <= len; i++)
    {
        Point* curr = points.at((i + len) % len);
        if(!prev->isOncurve() && !curr->isOncurve())
        {
            throw IncorrectConfigFileException("outline shold be closed");
        }
        if(prev->isOncurve() && curr->isOncurve())
        {
            double x0 = prev->getX() + centerX;
            double y0 = prev->getY() + centerY;
            double x1 = curr->getX() + centerX;
            double y1 = curr->getY() + centerY;
            drawLine(image, x0, y0, x1, y1, color);
        }
        else if(!prev->isOncurve() && curr->isOncurve())
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
    static int count = 0;
    count++;
    int centerX = config->getPositionX();
    int centerY = config->getPositionY();
    Point* middlePoint = getPointOnCurve(p0, p1, p2, 0.5);
    double distToLine = distanceToLine(middlePoint, p0, p2);
    if(count == 128) {
        int tmp = 9;
    }
    if(distToLine > ERROR)
    {
        drawBezierCurve(image, config, middlePoint, getNewNonOncurvePoint(p1, p2), p2, color);
        drawBezierCurve(image, config, p0, getNewNonOncurvePoint(p0, p1), middlePoint, color);
    }
    else
    {
        double x0 = p0->getX() + centerX;
        double y0 = p0->getY() + centerY;
        double x1 = p1->getX() + centerX;
        double y1 = p1->getY() + centerY;
        double x2 = p2->getX() + centerX;
        double y2 = p2->getY() + centerY;
        drawLine(image, x0, y0, x1, y1, color);
        drawLine(image, x1, y1, x2, y2, color);
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

QList<Point *> Drawer::scaleCoordinates(QList<Point *> points, double scale)
{
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
        res.append(new Point(x*k, y*k, p->isOncurve()));
    }
    return res;
}

