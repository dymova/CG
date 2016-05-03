#pragma once
#include <QJsonObject>
class Panel
{
private:
    int width;
    int height;

    const QString KEY_WIDTH = "width";
    const QString KEY_HEIGHT = "height";

    const QString KEY_PANEL = "panel";
    const QString KEY_SIZE = "size";

    const int DEFAULT_WIDTH = 300;
    const int DEFAULT_HEIGHT = 300;


public:
	Panel();
    Panel(int x, int y);
	~Panel();

    int getWidth() const;
    int getHeight() const;

    void setWidth(int width);
    void setHeight(int height);

	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
};

