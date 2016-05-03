#pragma once
#include <QJsonObject>
#include <QPair>
#include <QList>
#include "Point.h"

class Figure
{
private:
    QList<Point*> points;

    const QString KEY_FIGURE= "figure";


public:
    Figure(QList<Point*> points);
    Figure();
    ~Figure();


    void read(const QJsonObject &json, int i);
	void write(QJsonObject &json) const;

    QList<Point *> getPoints() const;
};

