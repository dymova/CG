#include "DrawPanel.h"
#include <QPainter>
#include "Figure.h"
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
    QPainter painter(this);
    QImage image(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = image.bits();
    if (!pubBuffer)
    {
        return;
    }
    int const whiteColor = 255;

    memset(pubBuffer, whiteColor, image.byteCount());

    QColor black(0, 0, 0);

    Figure* figure = config->getFigure();

    drawer->drawAxis(&image);

    if(config->isOutline())
    {
        drawer->drawOutline(&image, config, black);
    }

    painter.drawImage(0, 0, image);
}

