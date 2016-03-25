#include "Figure.h"
#include "ConfigParser.h"
#include "JsonParserException.h"
#include <QJsonArray>
#include "Utils.h"


Figure::Figure()
{
}


Figure::~Figure()
{
}

void Figure::read(const QJsonObject& jsonObject)
{
    QJsonValue figureValue = jsonObject[KEY_FIGURE];
    Utils::checkValue(KEY_FIGURE, figureValue);

    if (!figureValue.isArray())
    {
        throw JsonParserException("""figure1"" should be array");
    }
    QJsonArray jsonArray = figureValue.toArray();

    QJsonObject jsonPoint;

    foreach(const QJsonValue & value, jsonArray)
    {
        jsonPoint = value.toObject();
        Point* point = new Point();
        point->read(jsonPoint);
        points.append(point);
    }
}


QList<Point *> Figure::getPoints() const
{
    return points;
}


Figure::Figure(QList<Point *> points) : points(points)
{
}

void Figure::write(QJsonObject& pointsObj) const
{
    QJsonArray pointsArr;
    for (auto point : points)
    {
        QJsonObject pointObj;
        point->write(pointObj);
        pointsArr.append(pointObj);
    }
    pointsObj[KEY_FIGURE] = pointsArr;

}



