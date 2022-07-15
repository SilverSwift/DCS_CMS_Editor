#include "numericutills.h"

quint8 NumericUtills::parseUint8(QVariant value, bool* ok)
{
    quint8 result = 0;
    bool isOk = false;
    uint parsed = value.toUInt(&isOk);

    isOk = isOk && (parsed <= 0xFF);
    if (isOk)
        result = parsed;
    if (ok)
        *ok = isOk;
    return result;
}

float NumericUtills::parseFloat(QVariant value, bool* ok)
{
    float result = value.toFloat(ok);
    if (ok)
        return *ok ? result : .0f;
    return result;
}

quint8 NumericUtills::parseInterval(QVariant value, bool* ok)
{
    quint8 result = 0;
    float fValue = NumericUtills::parseFloat(value, ok);
    if (ok && !*ok){
        return result;
    }

    result = qRound(fValue/0.25);
    return result;
}

QString NumericUtills::intervalToString(quint8 intv)
{
    return QString::number(.25f*intv, 'f', 2);
}
