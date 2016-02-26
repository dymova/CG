#pragma once
#include <QJsonObject>
class Panel
{
private:
	int sizeX;
	int sizeY;

	void checkValue(QString key, QJsonValue jsonValue);

public:
	Panel();
	Panel(int x, int y);
	~Panel();

	const QString KEY_X = "x";
	const QString KEY_Y = "y";
	const QString KEY_SIZE = "size";
	const QString KEY_PANEL = "panel";


	int getSizeX() const;
	int getSizeY() const;


	void setSizeX(int size_x);
	void setSizeY(int size_y);
	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
};

