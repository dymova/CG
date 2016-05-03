#pragma once
#include <QtCore/qlist.h>
#include "Figure.h"
#include "Panel.h"

enum Filter {
    NEAREST,
    BILINEAR
};

class Configuration
{
private:
	Panel* panel;
    int positionX;
    int positionY;
    int scale;
    Filter filterType;
    QString source;

    const QString KEY_PANEL = "panel";
    const QString KEY_POSITION = "position";
    const QString KEY_X = "x";
    const QString KEY_Y = "y";
    const QString KEY_SCALE = "scale";
    const QString KEY_FILTER = "filter";
    const QString KEY_NEAREST = "nearest";
    const QString KEY_BILINEAR = "bilinear";
    const QString KEY_SOURCE= "source";



public:
    Configuration();
    Configuration(Panel* p, int x, int y, int scale,const Filter &value, QString source);
	~Configuration();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    QList<Figure*> getFigures() const;
	Panel* getPanel() const;
    int getPositionX() const;
    int getPositionY() const;
    int getScale() const;
    Filter getFilterType() const;


    void setPositionX(int value);
    void setPositionY(int value);
    void setScale(int value);
    void setFilterType(const Filter &value);
    QString getSource() const;
    void setSource(const QString &value);
};

