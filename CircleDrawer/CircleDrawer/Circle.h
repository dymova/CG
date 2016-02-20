#pragma once
#include <QJsonObject>


class Circle
{
private:
	int radius;
	int positionX;
	int positionY;
public:
	Circle();
	~Circle();
	int getR() const;
	int getPositionX() const;
	int getPositionY() const;

	void setR(int r);
	void setPositionX(int x);
	void setPositionY(int y);

	void read(const QJsonObject &json);
	void checkValue(QString key, QJsonValue jsonValue);
	void write(QJsonObject &json) const;

};

