#pragma once
#include "Lemniscate.h"
#include <QObject>

class Drawer : public QObject
{
	Q_OBJECT

public:
	Drawer(QObject *parent = 0);
	void drawLemniscate(QImage* pBackBuffer, Lemniscate* c);
	void drawPoint(QImage* image, int x, int y, QColor c);
};


