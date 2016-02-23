#pragma once
#include <QtCore/qlist.h>
#include "Circle.h"
#include "Panel.h"

class Configuration
{
private:
	QList<Circle*> circles;
	Panel* panel;
public:
	Configuration(QList<Circle*> c, Panel* p);
	~Configuration();


	QList<Circle*> getCircles() const;
	Panel* getPanel() const;


};

