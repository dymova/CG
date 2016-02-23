#pragma once
#include "Circle.h"
#include <QObject>

class Drawer : public QObject
{
	Q_OBJECT

public:
	Drawer(QObject *parent = 0);
	void drawCircle(QImage* pBackBuffer, Circle* c);
	void drawPoint(QImage* image, int x, int y, QColor c);
};


