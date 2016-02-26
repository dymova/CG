#include "Panel.h"
#include "JsonParserException.h"


Panel::Panel()
{
}

Panel::Panel(int x, int y) : sizeX(x), sizeY(y)
{
}

Panel::~Panel()
{
}

int Panel::getSizeX() const
{
	return sizeX;
}

int Panel::getSizeY() const
{
	return sizeY;
}

void Panel::setSizeX(int size_x)
{
	sizeX = size_x;
}

void Panel::setSizeY(int size_y)
{
	sizeY = size_y;
}

void Panel::read(const QJsonObject& jsonObject)
{
	QJsonValue panelValue = jsonObject["panel"];
	checkValue(KEY_PANEL, panelValue);
	QJsonObject jsonPanel = panelValue.toObject();

	QJsonValue panelSizeValue = jsonPanel["size"];
	checkValue(KEY_SIZE, panelSizeValue);

	QJsonObject jsonPanelSize = panelSizeValue.toObject();

	QJsonValue panelSizeXValue = jsonPanelSize["x"];
	checkValue(KEY_X, panelSizeXValue);
	sizeX = panelSizeXValue.toInt();

	QJsonValue panelSizeYValue = jsonPanelSize["y"];
	checkValue(KEY_Y, panelSizeXValue);
	sizeY = panelSizeYValue.toInt();
}

void Panel::write(QJsonObject& json) const
{
	QJsonObject sizeObj;
	sizeObj[KEY_X] = sizeX;
	sizeObj[KEY_Y] = sizeY;
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

