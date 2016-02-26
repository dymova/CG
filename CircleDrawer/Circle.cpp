#include "Circle.h"
#include "ConfigParser.h"
#include "JsonParserException.h"


Circle::Circle()
{
}

Circle::Circle(int r, int x, int y) : radius(r), positionX(x), positionY(y)
{
}

Circle::~Circle()
{
}

int Circle::getR() const
{
	return radius;
}

void Circle::setR(int r)
{
	radius = r;
}

void Circle::setPositionX(int x)
{
	positionX = x;
}

void Circle::setPositionY(int y)
{
	positionY = y;
}

void Circle::read(const QJsonObject& jsonCircle)
{
	QJsonValue positionValue;
	QJsonValue sizeXValue;
	QJsonValue sizeYValue;
	QJsonValue rValue;
	QJsonObject jsonePosition;

	rValue = jsonCircle["R"];
	checkValue(saveAndLoadConfig::KEY_R, rValue);
	radius = rValue.toInt();

	positionValue = jsonCircle["position"];
	checkValue(saveAndLoadConfig::KEY_POSITION, positionValue);
	jsonePosition = positionValue.toObject();

	sizeXValue = jsonePosition["x"];
	checkValue(saveAndLoadConfig::KEY_X, sizeXValue);
	positionX = sizeXValue.toInt();

	sizeYValue = jsonePosition["y"];
	checkValue(saveAndLoadConfig::KEY_Y, sizeYValue);
	positionY = sizeYValue.toInt();
}

void Circle::checkValue(QString key, QJsonValue jsonValue)
{
	if (jsonValue == QJsonValue::Undefined)
	{
		QString msg = "key """ + key + """ doesn't exist";
		throw JsonParserException(msg.toLocal8Bit().constData());
	}
}

void Circle::write(QJsonObject& circleObj) const
{
	QJsonObject positionObj;
	positionObj[saveAndLoadConfig::KEY_X] = positionX;
	positionObj[saveAndLoadConfig::KEY_Y] = positionY;

	circleObj[saveAndLoadConfig::KEY_R] = radius;
	circleObj[saveAndLoadConfig::KEY_POSITION] = positionObj;
}

int Circle::getPositionX() const
{
	return positionX;
}

int Circle::getPositionY() const
{
	return positionY;
}


