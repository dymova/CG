#include "Panel.h"
#include "JsonParserException.h"


Panel::Panel()
{
}

Panel::Panel(int x, int y) : width(x), height(y)
{
}

Panel::~Panel()
{
}

int Panel::getWidth() const
{
    return width;
}

int Panel::getHeight() const
{
    return height;
}

void Panel::setWidth(int width)
{
    width = width;
}

void Panel::setHeight(int height)
{
    height = height;
}

void Panel::read(const QJsonObject& jsonObject)
{
    QJsonValue panelValue = jsonObject[KEY_PANEL];
    checkValue(KEY_PANEL, panelValue);
	QJsonObject jsonPanel = panelValue.toObject();

    QJsonValue panelSizeValue = jsonPanel[KEY_SIZE];
    checkValue(KEY_SIZE, panelSizeValue);
	QJsonObject jsonPanelSize = panelSizeValue.toObject();

    QJsonValue panelSizeXValue = jsonPanelSize[KEY_WIDTH];
    checkValue(KEY_WIDTH, panelSizeXValue);
    width = panelSizeXValue.toInt();

    QJsonValue panelSizeYValue = jsonPanelSize[KEY_HEIGHT];
    checkValue(KEY_HEIGHT, panelSizeXValue);
    height = panelSizeYValue.toInt();
}

void Panel::write(QJsonObject& json) const
{
	QJsonObject sizeObj;
    sizeObj[KEY_WIDTH] = width;
    sizeObj[KEY_HEIGHT] = height;
    json[KEY_SIZE] = sizeObj;
}

void Panel::checkValue(QString key, QJsonValue jsonValue)
{
	if (jsonValue == QJsonValue::Undefined)
	{
		QString msg = "key """ + key + """ doesn't exist";
		throw JsonParserException(msg.toLocal8Bit().constData());
	}
}

