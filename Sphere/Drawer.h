#pragma once
#include "Configuration.h"
#include <QObject>

class Drawer : public QObject
{
	Q_OBJECT
private:
    const int BYTES_IN_PIXEL = 3;
    const double R = 256;
    const double ERROR = 0.001;

    double normalizeShift(int shift);
    double scale(double scale, double value);
    QPair<double, double> getSphericalCoordinates(double x,double y,double z, double r);
    QColor getPixelColor(QImage* image, double u, double v, Filter filterType);
    unsigned char* getPixel(QImage* image, int x, int y);

public:
	Drawer(QObject *parent = 0);
    void drawSphere(QImage* image, Configuration* config);

    void drawFocus(QImage* pBackBuffer, int y0, int x0);
    void drawAxis(QImage* pBackBuffer);
	void drawPoint(QImage* image, int x, int y, QColor c);

};

class IncorrectConfigFileException : public std::runtime_error
{
public:
    explicit IncorrectConfigFileException(std::string message)  :
            std::runtime_error("Drawer error: " + message)
    {
    }
};
