#include "Serializer.h"
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
        QJsonObject jsonObject;
        config->write(jsonObject);

		QJsonDocument jsonDocument(jsonObject);
		QFile jsonFile(file);
		if (!jsonFile.exists())
		{
			jsonFile.setFileName(file + ".json");
		}
		if (!jsonFile.open(QIODevice::WriteOnly))
		{
			throw ConfigSerializerException("error opening file for writing");
		}
		if (-1 == jsonFile.write(jsonDocument.toJson()))
		{
			throw ConfigSerializerException("error writing to file");
		}
	}
}

