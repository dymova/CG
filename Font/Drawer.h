#pragma once
#include "Configuration.h"
#include <QObject>

class Drawer : public QObject
{
	Q_OBJECT
private:
    const int BYTES_IN_PIXEL = 3;
    const double ERROR = 0.001;

    Point* getPointOnCurve(Point *p0, Point *p1, Point *p2, double t);
    double distanceToLine(Point* point, Point * onLinePoint1, Point *onLinePoint2);
    Point* getNewNonOncurvePoint(Point* p0, Point* p1);
//    QList<Point *> scaleCoordinates(QList<Point *> points, double scale);
    QList<Point *> transformCoordinates(QList<Point *> points, Configuration* config);
    bool isLine(Point* prev, Point* curr);
    bool isCurve(Point* prev, Point* curr);
    QPair<double, double> findYLimits(QList<Point *> points);
    void computeCrossPointWithLine(Point* prev, Point* curr, int y, QList<Point *>& crossPoints);
    void computeCrossPointWithCurve(Point *p0, Point *p1, Point *p2, int y, QList<Point *> &crossPoints);
    static bool compareByXValue(const Point* a, const Point* b);
    bool isCrossingLines(double a1, double b1, double a2, double b2);
    bool isTangentLine(Point *p0, Point *p1, Point *p2, double t, double a1, double b1);


public:
	Drawer(QObject *parent = 0);
    void drawOutline(QImage* pBackBuffer, Configuration* config, QColor color);
    void drawFill(QImage* pBackBuffer, Configuration* config, QColor color);
    void drawFocus(QImage* pBackBuffer, int y0, int x0);
    void drawAxis(QImage* pBackBuffer);
	void drawPoint(QImage* image, int x, int y, QColor c);
    void drawLine(QImage* image, double x0, double y0, double x1, double y1, QColor color);
    void drawBezierCurve(QImage* image, Configuration* config, Point* p0, Point* p1, Point* p2, QColor color);

};

class IncorrectConfigFileException : public std::runtime_error
{
public:
    explicit IncorrectConfigFileException(std::string message)  :
            std::runtime_error("Drawer error: " + message)
    {
    }
};
