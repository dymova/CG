#include "Utils.h"
#include "JsonParserException.h"


void Utils::checkValue(QString key, QJsonValue jsonValue)
{
    if (jsonValue == QJsonValue::Undefined)
    {
        QString msg = "key """ + key + """ doesn't exist";
        throw JsonParserException(msg.toLocal8Bit().constData());
    }
}
