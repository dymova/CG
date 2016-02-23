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

	QList<Circle*> ConfigParser::parseCircles(QJsonObject jsonObject)
	{
		QJsonValue jsonValue = jsonObject[KEY_CIRCLES];
		checkValue(KEY_CIRCLES, jsonValue);

		if (!jsonValue.isArray())
		{
			throw JsonParserException("""circles"" should be array");
		}
		QJsonArray jsonArray = jsonValue.toArray();

		QList<Circle*> circles;
		int r = 0;
		int sizeX = 0;
		int sizeY = 0;

		QJsonObject jsonCircle;

		foreach(const QJsonValue & value, jsonArray)
			{
				jsonCircle = value.toObject();
				Circle* c = new Circle();
				c->read(jsonCircle);
				circles.append(c);
			}
		return circles;
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

		QList<Circle*> circles = parseCircles(jsonObject);

		Panel* panel = new Panel();
		panel->read(jsonObject);


		return new Configuration(circles, panel);
	}
}

