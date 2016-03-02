#pragma once
#include "Configuration.h"

class ConsoleModeController
{
public:
	ConsoleModeController();
	~ConsoleModeController();

    void run(QString pathToConfigFile, QString pathToOutputFile);
};

