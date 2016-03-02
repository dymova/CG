#include "Configuration.h"


Configuration::Configuration(Lemniscate* c, Panel* p) : lemniscate(c), panel(p)
{
}

Configuration::~Configuration()
{
}

Lemniscate* Configuration::getLemniscate() const
{
    return lemniscate;
}

Panel* Configuration::getPanel() const
{
	return panel;
}

