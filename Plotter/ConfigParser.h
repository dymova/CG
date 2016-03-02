#pragma once
#include "Configuration.h"

namespace saveAndLoadConfig
{
	class ConfigParser
	{
	public:
		ConfigParser();
		~ConfigParser();

//		Lemniscate* parseCircles(QJsonObject jsonObject);
		Configuration* parse(QString pathToFile);
    private:
        void checkValue(QString key, QJsonValue jsonValue);
	};
}
