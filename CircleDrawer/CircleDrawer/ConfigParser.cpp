#include "ConfigParser.h"
#include <QtCore/qiodevice.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <iostream>

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
			qDebug() << msg;
			throw ConfigParserException(msg.toLocal8Bit().constData());
		}
	}

	QList<Circle*> ConfigParser::parseCircles(QJsonObject jsonObject)
	{
		QJsonValue jsonValue = jsonObject.value(KEY_CIRCLES);

		checkValue(KEY_CIRCLES, jsonValue);
		if (!jsonValue.isArray())
		{
			qDebug() << """circles"" should be array";
			throw ConfigParserException("""circles"" should be array");
		}
		QJsonArray jsonArray = jsonValue.toArray();

		QList<Circle*> circles;
		int r = 0;
		int sizeX = 0;
		int sizeY = 0;
		QJsonValue positionValue;
		QJsonValue sizeXValue;
		QJsonValue sizeYValue;
		QJsonValue rValue;
		QJsonObject jsoneCircle;
		QJsonObject jsonePosition;
		foreach(const QJsonValue & value, jsonArray)
			{
				jsoneCircle = value.toObject();
				rValue = jsoneCircle["R"];
				checkValue(KEY_R, rValue);
				r = rValue.toInt();

				positionValue = jsoneCircle["position"];
				checkValue(KEY_POSITION, positionValue);
				jsonePosition = positionValue.toObject();

				sizeXValue = jsonePosition["x"];
				checkValue(KEY_X, sizeXValue);
				sizeX = sizeXValue.toInt();

				sizeYValue = jsonePosition["y"];
				checkValue(KEY_Y, sizeYValue);
				sizeY = sizeYValue.toInt();

				circles.append(new Circle(r, sizeX, sizeY));
			}
		return circles;
	}

	Panel* ConfigParser::parsePanel(QJsonObject jsonObject)
	{
		QJsonValue panelValue = jsonObject["panel"];
		checkValue(KEY_PANEL, panelValue);
		QJsonObject jsonPanel = panelValue.toObject();

		QJsonValue panelSizeValue = jsonPanel["size"];
		checkValue(KEY_SIZE, panelSizeValue);

		QJsonObject jsonPanelSize = panelSizeValue.toObject();

		QJsonValue panelSizeXValue = jsonPanelSize["x"];
		checkValue(KEY_X, panelSizeXValue);
		int sizeX = panelSizeXValue.toInt();

		QJsonValue panelSizeYValue = jsonPanelSize["y"];
		checkValue(KEY_Y, panelSizeXValue);
		int sizeY = panelSizeYValue.toInt();

		return new Panel(sizeX, sizeY);
	}

	Configuration* ConfigParser::parse(QString pathToFile) 
	{
		QFile file(pathToFile);

		if (!file.exists())
		{
			qDebug() << "file doesn't exist";
			throw ConfigParserException("file doesn't exist");
		}

		if (!file.open(QIODevice::ReadOnly))
		{
			qDebug() << "error opening file for reading";
			throw ConfigParserException("error opening file for reading");
		}


		QString text = file.readAll();
		file.close();

		if (text.isEmpty())
		{
			qDebug() << "empty config file";
			throw ConfigParserException("empty config file");
		}

		QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());
		if (!doc.isObject())
		{
			qDebug() << "incorrect config file (document isn't json object)";
			throw ConfigParserException("incorrect config file (document isn't json object)");
		}
		QJsonObject jsonObject = doc.object();

		QList<Circle*> circles = parseCircles(jsonObject);
		Panel* panel = parsePanel(jsonObject);


		return new Configuration(circles, panel);
	}
}

