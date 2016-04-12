#include "DrawPanel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
#include "Figure.h"
#include "ConfigParser.h"
#include "GuiModeController.h"


DrawPanel::DrawPanel(Configuration* c, GuiModeController* controller)
{
	config = c;
    drawer = new Drawer(this);
    this->controller = controller;
}

DrawPanel::~DrawPanel()
{
}

void DrawPanel::setConfig(Configuration* config) 
{
	this->config = config;
}


void DrawPanel::paintEvent(QPaintEvent* )
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
    QColor blue(0, 77, 255);

    drawer->drawAxis(&image);

    if(config->isOutline())
    {
        drawer->drawOutline(&image, config, black);
    }

    if(config->isFill())
    {
        drawer->drawFill(&image, config, blue);
    }


    painter.drawImage(0, 0, image);
}

void DrawPanel::mousePressEvent(QMouseEvent* event)
{

    dragStartPosition = event->pos();
}

void DrawPanel::mouseMoveEvent(QMouseEvent* event)
{
    QPoint diff = event->pos() - dragStartPosition;

    if (diff.manhattanLength() >= QApplication::startDragDistance())
    {
        int x = config->getPositionX();
        int y = config->getPositionY();

        controller->setXValue(x + diff.x());
        controller->setYValue(y - diff.y());
        dragStartPosition = event->pos();

    }
}


