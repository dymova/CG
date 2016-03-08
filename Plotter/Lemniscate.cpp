#include "Lemniscate.h"
#include "ConfigParser.h"
#include "JsonParserException.h"


Lemniscate::Lemniscate()
{
}

Lemniscate::Lemniscate(int x1, int y1, int x2, int y2)
    :x1(x1), y1(y1), x2(x2), y2(y2)
{
}


Lemniscate::~Lemniscate()
{
}

void Lemniscate::read(const QJsonObject& jsonObject)
{
    QJsonValue lemniscateValue = jsonObject[KEY_LEMNISCATE];
    checkValue(KEY_LEMNISCATE, lemniscateValue);
    QJsonObject jsonLemniscate = lemniscateValue.toObject();

    QJsonValue focus1Value = jsonLemniscate[KEY_FOCUS1];
    checkValue(KEY_FOCUS1, focus1Value);
    QJsonObject jsonFocus1= focus1Value.toObject();

    QJsonValue focus2Value = jsonLemniscate[KEY_FOCUS2];
    checkValue(KEY_FOCUS2, focus2Value);
    QJsonObject jsonFocus2= focus2Value.toObject();

    QJsonValue x1Value = jsonFocus1[KEY_X];
    checkValue(KEY_X, x1Value);
    x1 = x1Value.toInt();
    QJsonValue y1Value = jsonFocus1[KEY_Y];
    checkValue(KEY_Y, y1Value);
    y1 = y1Value.toInt();

    QJsonValue x2Value = jsonFocus2[KEY_X];
    checkValue(KEY_X, x2Value);
    x2 = x2Value.toInt();
    QJsonValue y2Value = jsonFocus2[KEY_Y];
    checkValue(KEY_Y, y2Value);
    y2 = y2Value.toInt();
}

int Lemniscate::getX1() const
{
    return x1;
}

void Lemniscate::setX1(int value)
{
    x1 = value;
}

int Lemniscate::getY1() const
{
    return y1;
}

void Lemniscate::setY1(int value)
{
    y1 = value;
}

int Lemniscate::getX2() const
{
    return x2;
}

void Lemniscate::setX2(int value)
{
    x2 = value;
}

int Lemniscate::getY2() const
{
    return y2;
}

void Lemniscate::setY2(int value)
{
    y2 = value;
}

void Lemniscate::checkValue(QString key, QJsonValue jsonValue)
{
    if (jsonValue == QJsonValue::Undefined)
	{
		QString msg = "key """ + key + """ doesn't exist";
		throw JsonParserException(msg.toLocal8Bit().constData());
	}
}

void Lemniscate::write(QJsonObject& circleObj) const
{
    QJsonObject focus1Obj;
    focus1Obj[KEY_X] = x1;
    focus1Obj[KEY_Y] = y1;

    QJsonObject focus2Obj;
    focus2Obj[KEY_X] = x2;
    focus2Obj[KEY_Y] = y2;

    circleObj[KEY_FOCUS1] = focus1Obj;
    circleObj[KEY_FOCUS2] = focus2Obj;

}



