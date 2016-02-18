#include "Configuration.h"


Configuration::Configuration(QList<Circle*> c, Panel* p) : circles(c), panel(p)
{
}

Configuration::~Configuration()
{
}

QList<Circle*> Configuration::getCircles() const
{
	return circles;
}

Panel* Configuration::getPanel() const
{
	return panel;
}

