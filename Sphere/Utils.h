#ifndef UTILS_H
#define UTILS_H
#include<QString>
#include<QJsonObject>


class Utils
{
public:
    static void checkValue(QString key, QJsonValue jsonValue);
};

#endif // UTILS_H
