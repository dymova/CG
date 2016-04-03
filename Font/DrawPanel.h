#pragma once
#include <QWidget>
#include "Drawer.h"
//#include "GuiModeController.h"
#include "Configuration.h"

//class Configuration;
class GuiModeController;

class DrawPanel : public QWidget
{
	Q_OBJECT
public:
    explicit DrawPanel(Configuration* config, GuiModeController* controller);
	~DrawPanel();
	void setConfig(Configuration* config);

public slots :


protected:
	void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    Drawer*  drawer;
	Configuration* config;
    GuiModeController* controller;

    QPoint dragStartPosition;
    bool dragStart = false;

};
