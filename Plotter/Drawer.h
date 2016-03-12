#pragma once
#include "Lemniscate.h"
#include <QObject>

class Drawer : public QObject
{
	Q_OBJECT
private:
        const int BYTES_IN_PIXEL = 3;
        QList<QPair<int, int>> neighborhood;

        long long  computeParam(long long  x, long long y, Lemniscate* l);
//        QPair<int, int> getExtremePoint(Lemniscate* l, long long k);
        QPair<int, int> getExtremePoint(Lemniscate* l, long long  k, int xEnd, int yEnd, int xStart, int yStart);
    void findCenter(QList<QPair<int, int> > &center, Lemniscate* l);
    int getSecondPoint(Lemniscate* l, long long k, int &yCurr, int &xCurr, bool rightDirection);
    bool isCenter(int xCurr, int yCurr, QList<QPair<int, int>> center);
    void drawSide(QPair<int, int> firstPoint,QPair<int, int> lastPoint, Lemniscate* l,
                  long long k, QList<QPair<int, int>> center, QImage* image, int position,  QPair<int, int> );
public:
	Drawer(QObject *parent = 0);
	void drawLemniscate(QImage* pBackBuffer, Lemniscate* c);
    void drawFocus(QImage* pBackBuffer, int y0, int x0);
    void drawAxis(QImage* pBackBuffer);
	void drawPoint(QImage* image, int x, int y, QColor c);


    static long long square(long long x);
    static long long min(int a,int b,int c);



};


