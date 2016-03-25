#ifndef POINT_H
#define POINT_H
#include<QString>
#include<QJsonObject>

class Point
{
private:
    int x;
    int y;
    bool oncurve;

    const QString KEY_X = "x";
    const QString KEY_Y = "y";
    const QString KEY_POSITION = "position";
    const QString KEY_ONCURVE = "oncurve";
public:
    Point();
    Point(int x, int y, bool oncurve);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // POINT_H
