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

bool Configuration::isFill() const
{
    return fill;
}

bool Configuration::isOutline() const
{
    return outline;
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

void Configuration::setFill(bool value)
{
    fill = value;
}

void Configuration::setOutline(bool value)
{
    outline = value;
}

Configuration::Configuration()
{
}

Configuration::Configuration(Figure *f, Panel *p, int x, int y, int scale, bool fill, bool outline)
    : figure(f), panel(p),
      positionX(x), positionY(y),
      scale(scale), fill(fill), outline(outline)
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

    QJsonValue fillValue = json[KEY_FILL];
    Utils::checkValue(KEY_FILL, fillValue);
    fill = fillValue.toInt();

    QJsonValue outlineValue = json[KEY_OUTLINE];
    Utils::checkValue(KEY_OUTLINE, outlineValue);
    outline = outlineValue.toInt();

    QJsonValue glyphsValue = json[KEY_GLYPHS];
    Utils::checkValue(KEY_GLYPHS, glyphsValue);
    if (!glyphsValue.isArray())
    {
        throw JsonParserException("""glyphs"" should be array");
    }
    QJsonArray figuresArray = glyphsValue.toArray();

    figure = new Figure();
    figure->read(figuresArray.first().toObject());

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
    json[KEY_FILL] = fill;
    json[KEY_OUTLINE] = outline;

    QJsonObject figureObj;
    figure->write(figureObj);
    QJsonArray glyphsArray;
    glyphsArray.append(figureObj);
    json[KEY_GLYPHS] = glyphsArray;

    QJsonObject panelObj;
    panel->write(panelObj);
    json[KEY_PANEL] = panelObj;
}

Figure* Configuration::getFigure() const
{
    return figure;
}

Panel* Configuration::getPanel() const
{
	return panel;
}

