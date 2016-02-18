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
	void setRValue(int r);
	void setXPositionValue(int x);
	void setYPositionValue(int y);

protected:
	void paintEvent(QPaintEvent *event);

private:
	Drawer*  circleDrawer;
	Configuration* config;
	

};
