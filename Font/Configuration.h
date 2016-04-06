#pragma once
#include <QtCore/qlist.h>
#include "Figure.h"
#include "Panel.h"

class Configuration
{
private:
    Figure* figure;
	Panel* panel;
    int positionX;
    int positionY;
    int scale;
    bool fill;
    bool outline;

    const QString KEY_POSITION = "position";
    const QString KEY_X = "x";
    const QString KEY_Y = "y";
    const QString KEY_SCALE = "scale";
    const QString KEY_FILL = "fill";
    const QString KEY_OUTLINE = "outline";
    const QString KEY_GLYPHS = "glyphs";
    const QString KEY_PANEL = "panel";



public:
    Configuration();
    Configuration(Figure* f, Panel* p, int x, int y, int scale, bool fill, bool outline);
	~Configuration();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    Figure* getFigure() const;
	Panel* getPanel() const;
    int getPositionX() const;
    int getPositionY() const;
    int getScale() const;
    bool isFill() const;
    bool isOutline() const;
    void setPositionX(int value);
    void setPositionY(int value);
    void setScale(int value);
    void setFill(bool value);
    void setOutline(bool value);
};

