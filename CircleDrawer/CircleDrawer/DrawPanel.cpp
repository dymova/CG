#include "DrawPanel.h"
#include <QPainter>
#include <QImage>
#include "Circle.h"
#include "ConfigParser.h"


DrawPanel::DrawPanel(Configuration* c)
{
	config = c;
	circleDrawer = new Drawer(this);
	int sizeX = config->getPanel()->getSizeX();
	int sizeY = config->getPanel()->getSizeY();
	setMinimumSize(sizeX, sizeY);
}

DrawPanel::~DrawPanel()
{
}

void DrawPanel::setConfig(Configuration* config)
{
	this->config = config;
	int sizeX = config->getPanel()->getSizeX();
	int sizeY = config->getPanel()->getSizeY();
	setMinimumSize(sizeX, sizeY);
}

void DrawPanel::setRValue(int r)
{
	config->getCircles().first()->setR(r);
	update();
}

void DrawPanel::setXPositionValue(int x)
{
	config->getCircles().first()->setPositionX(x);
	update();
}

void DrawPanel::setYPositionValue(int y)
{
	config->getCircles().first()->setPositionY(y);
	update();
}

void DrawPanel::paintEvent(QPaintEvent*/*event*/)
{
	resize(config->getPanel()->getSizeX(), config->getPanel()->getSizeY());
	QPainter painter(this);
	QImage backBuffer(width(), height(), QImage::Format_RGB888);

	uchar* pubBuffer = backBuffer.bits();
	if (!pubBuffer)
	{
		return;
	}
	int const whiteColor = 255;
	memset(pubBuffer, whiteColor, backBuffer.byteCount());

	QList<Circle*> circles = config->getCircles();
	if (!circles.isEmpty())
	{
		Circle* c = circles.first();
		if (circleDrawer)
		{
			circleDrawer->drawCircle(&backBuffer, c);
		}
	}


	painter.drawImage(0, 0, backBuffer);
}

