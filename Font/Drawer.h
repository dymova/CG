#pragma once
#include "Figure.h"
#include <QObject>

class Drawer : public QObject
{
	Q_OBJECT
private:
    const int BYTES_IN_PIXEL = 3;

public:
	Drawer(QObject *parent = 0);
	void drawFigure(QImage* pBackBuffer, Figure* c);
    void drawFocus(QImage* pBackBuffer, int y0, int x0);
    void drawAxis(QImage* pBackBuffer);
	void drawPoint(QImage* image, int x, int y, QColor c);


    static long long square(long long x);
    static long long min(long long a, long long b, long long c);



};


