#ifndef POINT_H
#define POINT_H
#include<QString>
#include<QJsonObject>

class Point
{
private:
    double x;
    double y;
    bool oncurve;

    const QString KEY_X = "x";
    const QString KEY_Y = "y";
    const QString KEY_POSITION = "position";
    const QString KEY_ONCURVE = "oncurve";
public:
    Point();
    Point(double x, double y, bool oncurve);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    double getX() const;
    double getY() const;
    bool isOncurve() const;
    void setX(double value);
    void setY(double value);
};

#endif // POINT_H
