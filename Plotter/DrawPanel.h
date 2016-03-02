#pragma once

#include <QWidget>
#include "Drawer.h"

class Configuration;

class DrawPanel : public QWidget
{
	Q_OBJECT
public:
	explicit DrawPanel(Configuration* config);
	~DrawPanel();
	void setConfig(Configuration* config);

public slots :


protected:
	void paintEvent(QPaintEvent *event);

private:
	Drawer*  circleDrawer;
	Configuration* config;
	

};
