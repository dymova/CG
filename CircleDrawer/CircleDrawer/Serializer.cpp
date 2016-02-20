#include "Serializer.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "JsonParserException.h"
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
			QJsonObject circleObj;
			circle->write(circleObj);
			circlesArr.append(circleObj);
		}
		QJsonObject jsonObject;
		jsonObject[KEY_CIRCLES] = circlesArr;

		QJsonObject panelObj;
		config->getPanel()->write(panelObj);
		jsonObject[KEY_PANEL] = panelObj;

		QJsonDocument jsonDocument(jsonObject);
		QFile jsonFile(file);
		if (!jsonFile.exists())
		{
			throw ConfigSerializerException("file doesn't exist");
		}
		if (!jsonFile.open(QIODevice::WriteOnly))
		{
			throw JsonParserException("error opening file for writing");
		}
		if (-1 == jsonFile.write(jsonDocument.toJson()))
		{
			throw JsonParserException("error writing to file");
		}
	}
}

