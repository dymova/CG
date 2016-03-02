#pragma once
#include <QJsonObject>
#include <QPair>

class Lemniscate
{
private:
    int x1;
    int y1;
    int x2;
    int y2;

    const QString KEY_LEMNISCATE= "lemniscate";
    const QString KEY_FOCUS1 = "focus1";
    const QString KEY_FOCUS2 = "focus2";
    const QString KEY_X = "x";
    const QString KEY_Y = "y";

    void checkValue(QString key, QJsonValue jsonValue);

public:
    Lemniscate();
    Lemniscate(int x1, int y1, int x2, int y2);
    ~Lemniscate();


	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;

    int getX1() const;
    void setX1(int value);
    int getY1() const;
    void setY1(int value);
    int getX2() const;
    void setX2(int value);
    int getY2() const;
    void setY2(int value);
};

