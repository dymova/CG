#pragma once
#include "Configuration.h"
#include <QtCore/qabstractanimation.h>

namespace saveAndLoadConfig
{
	const QString KEY_CIRCLES = "circles";
	const QString KEY_POSITION = "position";
	const QString KEY_R = "R";
	const QString KEY_X = "x";
	const QString KEY_Y = "y";
	const QString KEY_PANEL = "panel";
	const QString KEY_SIZE = "size";

	class ConfigParser
	{
	public:
		ConfigParser();
		~ConfigParser();
		void checkValue(QString key, QJsonValue jsonValue);
		QList<Circle*> parseCircles(QJsonObject jsonObject);
		Panel * parsePanel(QJsonObject jsonObject);
		Configuration* parse(QString pathToFile);
	};

	class ConfigParserException : public std::runtime_error
	{
	public:
		explicit ConfigParserException(std::string message) :
			std::runtime_error("Config parser error: " + message)
		{
			}
	};
}