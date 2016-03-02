#include "DrawPanel.h"
#include <QPainter>
#include "Lemniscate.h"
#include "ConfigParser.h"


DrawPanel::DrawPanel(Configuration* c)
{
	config = c;
    drawer = new Drawer(this);
}

DrawPanel::~DrawPanel()
{
}

void DrawPanel::setConfig(Configuration* config) 
{
	this->config = config;
}


void DrawPanel::paintEvent(QPaintEvent*)
{
//	resize(config->getPanel()->getSizeX(), config->getPanel()->getSizeY());
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer)
    {
        return;
    }
    int const whiteColor = 255;

    memset(pubBuffer, whiteColor, backBuffer.byteCount());

    Lemniscate* l = config->getLemniscate();
    drawer->drawAxis(&backBuffer);
    drawer->drawFocus(&backBuffer, l->getX1(), l->getY1());
    drawer->drawFocus(&backBuffer, l->getX2(), l->getY2());
    drawer->drawLemniscate(&backBuffer, l);

//	QList<Lemniscate*> circles = config->getLemniscate();
//	if (!circles.isEmpty())
//	{
//		Lemniscate* c = circles.first();
//		if (circleDrawer)
//		{
//			circleDrawer->drawLemniscate(&backBuffer, c);
//		}
//	}


    painter.drawImage(0, 0, backBuffer);
}

