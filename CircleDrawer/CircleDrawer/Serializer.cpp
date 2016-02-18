#include "Serializer.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "ConfigParser.h"

namespace saveAndLoadConfig
{
	Serializer::Serializer()
	{
	}


	Serializer::~Serializer()
	{
	}

	void Serializer::serialize(QString file, Configuration* config)
	{
		QList<Circle*> circles = config->getCircles();

		QJsonArray circlesArr;
		for (auto circle : circles)
		{
			int r = circle->getR();
			int x = circle->getPositionX();
			int y = circle->getPositionY();

			QJsonObject positionObj;
			positionObj[KEY_X] = x;
			positionObj[KEY_Y] = y;

			QJsonObject circleObj;
			circleObj[KEY_R] = r;
			circleObj[KEY_POSITION] = positionObj;

			circlesArr.append(circleObj);
		}

		int sizeX = config->getPanel()->getSizeX();
		int sizeY = config->getPanel()->getSizeY();
		QJsonObject sizeObj;
		sizeObj[KEY_X] = sizeX;
		sizeObj[KEY_Y] = sizeY;
		QJsonObject panelObj;
		panelObj[KEY_SIZE] = sizeObj;

		QJsonObject jsonObject;
		jsonObject[KEY_CIRCLES] = circlesArr;
		jsonObject[KEY_PANEL] = panelObj;

		QJsonDocument jsonDocument(jsonObject);
		QFile jsonFile(file);
		if (!jsonFile.exists())
		{
			throw ConfigSerializerException("file doesn't exist");
		}
		if (!jsonFile.open(QIODevice::WriteOnly))
		{
			throw ConfigParserException("error opening file for writing");
		}
		if (-1 == jsonFile.write(jsonDocument.toJson()))
		{
			throw ConfigParserException("error writing to file");
		}
	}
}

