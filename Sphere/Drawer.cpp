#include "Drawer.h"
#include <QImage>
#include <QColor>
#include <QtAlgorithms>
#include <stdlib.h>
#include <QDebug>
#include <QVector3D>
#include <QMatrix4x4>
#include "Figure.h"
#include "Configuration.h"


Drawer::Drawer(QObject *parent) :
QObject(parent)
{
}

void Drawer::drawSphere(QImage *image, Configuration *config)
{
    QImage sourceImage;
    sourceImage.load(config->getSource());
    sourceImage = sourceImage.convertToFormat(QImage::Format_RGB888);

    double r = scale(config->getScale(), R);
    double z1 = -r;
    double z2 = r;

    if (z2 > ((image->height()) / 2))
    {
        z2 = (image->height()) / 2;
    }
    if (z1 <= -(image->height()/2))
    {
        z1 = 1 - (image->height()/2);
    }

    for(double z = z1; z <= z2; z++)
    {
        double bound = (sqrt(r*r - z*z));
        int x1 = -bound;
        int x2 = bound;
        if (x1 < -image->width()/2)
        {
            x1 = -image->width() / 2;
        }
        if (x2 >= image->width() / 2)
        {
            x2 = (image->width() / 2) - 1;
        }

        for (double x = x1; x <= x2; x++)
        {
            double d = r*r - x*x - z*z;
            if(d < 0)
            {
                continue;
            }
            double y = sqrt(d);

            double shiftX = normalizeShift(config->getPositionX());
            double shiftY = normalizeShift(config->getPositionY());

            //rotate around X
            double newY = y*cos(shiftY) - z*sin(shiftY);
            double newZ = y*sin(shiftY) + z*cos(shiftY);
            //rotate around Y
//            double newX = x*cos(shiftY) + newZ*sin(shiftY);
//            newZ = -x*sin(shiftY) + newZ*cos(shiftY);

            //rotate around Z
            double newX = x*cos(shiftX) - newY*sin(shiftX);
            newY = x*sin(shiftX) + newY*cos(shiftX);

            QPair<double, double> angles = getSphericalCoordinates(newX, newY, newZ, r);
//            QPair<double, double> angles = getSphericalCoordinates(x, y, z, r);
            double theta = angles.first;
            double phi = angles.second;

//            double umod = std::fmod(phi + M_PI/2 + shiftX, M_PI);
            double umod = std::fmod(phi + M_PI/2, M_PI);
            double u = umod/(M_PI);

            double vmod = std::fmod(theta, M_PI);
//            double vmod = std::fmod(theta + shiftY, M_PI);
            double v = vmod/(M_PI);

            u = 1 - u;
            v = 1 - v;

            QColor color = getPixelColor(&sourceImage, u, v, config->getFilterType());

            drawPoint(image, x, z, color);
        }
    }
}

double Drawer::normalizeShift(int shift)
{
    int tmp = (shift % 360 + 360)%360;
    double newShift = (double)tmp * M_PI/180;
    return newShift;
}

double Drawer::scale(double scale, double r)
{
    double k;
    if(scale <= 0){
        k = 1 + (scale/1000);
    }
    else
    {
        k = 1 + (scale / 100);
    }
    return r*k;
}

QPair<double, double> Drawer::getSphericalCoordinates(double x, double y, double z, double r)
{
    double theta = acos(z/r);

    double phi;
    if(x == 0 )
    {
        phi = M_PI/2;
    }
    else
    {
        phi = atan(y/x);
    }

    return qMakePair(theta, phi);
}

QColor Drawer::getPixelColor(QImage* image, double u, double v, Filter filterType)
{
    if(filterType == NEAREST)
    {
        int x = round(0.5 + u*image->width());
        int y = round(0.5 + v*image->height());

//        if (x <= (image->width() - 1) && y < (image->height()) && x >=0 && y >= 0 )
        {
            unsigned char *point = image->bits() + ((image->height()-y) * image->bytesPerLine()) + x*BYTES_IN_PIXEL;
            int r = *point;
            int g = *++point;
            int b = *++point;

            QColor color(r, g, b);

            return color;
        }
    }
    else {
        u *= image->width();
        v *= image->height();
        int x = floor(u);
        int y = floor(v);
        unsigned char *p1 = image->bits() + ((image->height()-y) * image->bytesPerLine()) + x*BYTES_IN_PIXEL;
        unsigned char *p2 = image->bits() + ((image->height()-y) * image->bytesPerLine()) + (x+1)*BYTES_IN_PIXEL;
        unsigned char *p3 = image->bits() + ((image->height()-(y+1)) * image->bytesPerLine()) + x*BYTES_IN_PIXEL;
        unsigned char *p4 = image->bits() + ((image->height()-(y+1)) * image->bytesPerLine()) + (x+1)*BYTES_IN_PIXEL;

        double divU = u - x;
        double divV = v - y;
        double oppositeU = 1 - divU;
        double oppositeV = 1 - divV;

        double r = (*p1   * oppositeU  + *p2   * divU) * oppositeV +
                (*p3 * oppositeU  + *p4 * divU) * divV;
        double g = (*++p1   * oppositeU  + *++p2   * divU) * oppositeV +
                (*++p3 * oppositeU  + *++p4 * divU) * divV;
        double b = (*++p1   * oppositeU  + *++p2   * divU) * oppositeV +
                (*++p3 * oppositeU  + *++p4 * divU) * divV;

        QColor color(r, g, b);
        return color;
    }

}

void Drawer::drawPoint(QImage* image, int x, int y, QColor color)
{
    int newX;
    int newY;
    unsigned char *point;

    newX = ((image->width() / 2) + x);

    newY = (image->height() / 2) - y;

//    if (newX <= (image->width() - 1) &&  newY < (image->height()) && newX >=0 && newY >= 0 )
    {
        point = image->bits() + ((newY) * image->bytesPerLine()) + newX*BYTES_IN_PIXEL;

        *point = color.red();
        *++point = color.green();
        *++point = color.blue();
    }   
}









