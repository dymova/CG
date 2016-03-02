#pragma once
#include <QtCore/qlist.h>
#include "Lemniscate.h"
#include "Panel.h"

class Configuration
{
private:
    Lemniscate* lemniscate;
	Panel* panel;
public:
    Configuration(Lemniscate* c, Panel* p);
	~Configuration();


    Lemniscate* getLemniscate() const;
	Panel* getPanel() const;


};

