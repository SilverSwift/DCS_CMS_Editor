#include "numericutills.h"
#include <cmath>
#include <limits>

qint16 NumericUtills::parseInt16(QVariant value, bool* ok)
{
    qint16 result = 0;
    bool isOk = false;
    int parsed = value.toInt(&isOk);

    isOk = isOk && !(parsed > std::numeric_limits<decltype(result)>::max() ||
                     parsed < std::numeric_limits<decltype(result)>::min());


    if(!isOk)
    {
        qDebug()<<value;
    }

    if (ok)
        *ok = isOk;

    if (isOk)
        result = parsed;

    return result;
}

float NumericUtills::parseFloat(QVariant value, bool* ok)
{
    float result = value.toFloat(ok);
    if (ok)
        return *ok ? result : .0f;
    return result;
}

qint16 NumericUtills::parseInterval(QVariant value, float accuracy, bool* ok)
{
    qint16 result = 0;

    bool isOk = false;
    float fValue = NumericUtills::parseFloat(value, &isOk);

    if (ok)
        *ok = isOk;

    if (!isOk)
        return result;

    result = qRound(fValue/accuracy);
    return result;
}

QString NumericUtills::intervalToString(qint16 intv, float precision)
{
    return QString::number(precision*intv, 'f', std::log10(1/precision));
}

QString NumericUtills::fiveDigitsIntLiteral(qint16 value)
{
    return QStringLiteral("%1").arg(value, 5, 10, QLatin1Char(' '));
}

QString NumericUtills::fiveDigitsDoubleLiteral(double value, float precision)
{
    return QStringLiteral("%1").arg(value*precision, 6, 'f', std::log10(1/precision), QLatin1Char(' '));
}


