#include "ConfigParser.h"
#include <QtCore/qiodevice.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <iostream>
#include "JsonParserException.h"

namespace saveAndLoadConfig
{
	ConfigParser::ConfigParser()
	{
	}


	ConfigParser::~ConfigParser()
	{
	}

	void ConfigParser::checkValue(QString key, QJsonValue jsonValue)
	{
		if (jsonValue == QJsonValue::Undefined)
		{
			QString msg = "key """ + key + """ doesn't exist";
			throw JsonParserException(msg.toLocal8Bit().constData());
		}
	}


	Configuration* ConfigParser::parse(QString pathToFile) 
	{
		QFile file(pathToFile);

		if (!file.exists())
		{
			throw JsonParserException("file doesn't exist");
		}

		if (!file.open(QIODevice::ReadOnly))
		{
			throw JsonParserException("error opening file for reading");
		}


		QString text = file.readAll();
		file.close();

		if (text.isEmpty())
		{
			qDebug() << "empty config file";
			throw JsonParserException("empty config file");
		}

		QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());
		if (!doc.isObject())
		{
			throw JsonParserException("incorrect config file (document isn't json object)");
		}
		QJsonObject jsonObject = doc.object();

//        QList<Lemniscate*> circles = parseCircles(jsonObject);

        Lemniscate* lemniscate = new Lemniscate();
        lemniscate->read(jsonObject);

		Panel* panel = new Panel();
		panel->read(jsonObject);


        return new Configuration(lemniscate, panel);
	}
}

