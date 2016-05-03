#include "Configuration.h"
#include "Utils.h"
#include "JsonParserException.h"
#include <QJsonArray>


int Configuration::getPositionX() const
{
    return positionX;
}

int Configuration::getPositionY() const
{
    return positionY;
}

int Configuration::getScale() const
{
    return scale;
}


void Configuration::setPositionX(int value)
{
    positionX = value;
}

void Configuration::setPositionY(int value)
{
    positionY = value;
}

void Configuration::setScale(int value)
{
    scale = value;
}


Filter Configuration::getFilterType() const
{
    return filterType;
}

void Configuration::setFilterType(const Filter &value)
{
    filterType = value;
}

QString Configuration::getSource() const
{
    return source;
}

void Configuration::setSource(const QString &value)
{
    source = value;
}

Configuration::Configuration()
{
}

Configuration::Configuration(Panel *p, int x, int y, int scale, const Filter &value, QString source)
    : panel(p),
      positionX(x), positionY(y),
      scale(scale), filterType(value), source(source)
{

}

Configuration::~Configuration()
{
}

void Configuration::read(const QJsonObject &json)
{
    QJsonValue positionValue = json[KEY_POSITION];
    Utils::checkValue(KEY_POSITION, positionValue);
    QJsonObject jsonPosition = positionValue.toObject();

    QJsonValue positionXValue = jsonPosition[KEY_X];
    Utils::checkValue(KEY_X, positionXValue);
    positionX = positionXValue.toInt();

    QJsonValue positionYValue = jsonPosition[KEY_Y];
    Utils::checkValue(KEY_Y, positionYValue);
    positionY = positionYValue.toInt();

    QJsonValue scaleValue = json[KEY_SCALE];
    Utils::checkValue(KEY_SCALE, scaleValue);
    scale = scaleValue.toInt();

    QJsonValue filterValue = json[KEY_FILTER];
    Utils::checkValue(KEY_FILTER, filterValue);

    if(0 == filterValue.toString().compare(KEY_BILINEAR))
    {
        filterType = BILINEAR;
    }
    else if(0 == filterValue.toString().compare(KEY_NEAREST))
    {
        filterType = NEAREST;
    }
    else
    {
        QString msg = "unknown filter " + filterValue.toString();
        throw JsonParserException(msg.toLocal8Bit().constData());
    }

    QJsonValue sourceValue = json[KEY_SOURCE];
    Utils::checkValue(KEY_SOURCE, sourceValue);
    source = sourceValue.toString();

    panel = new Panel();
    panel->read(json);

}

void Configuration::write(QJsonObject &json) const
{
    QJsonObject positionObj;
    positionObj[KEY_X] = positionX;
    positionObj[KEY_Y] = positionY;
    json[KEY_POSITION] = positionObj;

    json[KEY_SCALE] = scale;
    if(filterType == NEAREST)
    {
        json[KEY_FILTER] = KEY_NEAREST;
    }
    else
    {
        json[KEY_FILTER] = KEY_BILINEAR;
    }

    json[KEY_SOURCE] = source;

    QJsonObject panelObj;
    panel->write(panelObj);
    json[KEY_PANEL] = panelObj;
}


Panel* Configuration::getPanel() const
{
	return panel;
}

