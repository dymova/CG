#pragma once
#include "Configuration.h"

namespace saveAndLoadConfig
{
	const QString KEY_CIRCLES = "circles";
	const QString KEY_POSITION = "position";
	const QString KEY_R = "R";
	const QString KEY_X = "x";
	const QString KEY_Y = "y";
	const QString KEY_SIZE = "size";
	const QString KEY_PANEL = "panel";

	class ConfigParser
	{
	public:
		ConfigParser();
		~ConfigParser();
		void checkValue(QString key, QJsonValue jsonValue);
		QList<Circle*> parseCircles(QJsonObject jsonObject);
		Configuration* parse(QString pathToFile);
	};
	}