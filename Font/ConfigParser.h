#pragma once
#include "Configuration.h"

namespace saveAndLoadConfig
{
	class ConfigParser
	{
	public:
		ConfigParser();
		~ConfigParser();

		Configuration* parse(QString pathToFile);
	};
}
