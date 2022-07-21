#ifndef NUMERICUTILLS_H
#define NUMERICUTILLS_H

#include <QtGlobal>
#include <QVariant>

class NumericUtills
{
    NumericUtills() = delete;
public:
    static qint16 parseInt16(QVariant value, bool* ok = nullptr);
    static float parseFloat(QVariant value, bool* ok = nullptr);
    static qint16 parseInterval(QVariant value, float accuracy,
                                bool *ok = nullptr);
    static QString intervalToString(qint16 intv, float precision);
    static QString fiveDigitsIntLiteral(qint16 value);
    static QString fiveDigitsDoubleLiteral(double value, float precision);

    template <typename Type>
    static bool bound(Type min, Type& value, Type max){
        qint16 bound = qBound(min, value, max);
        bool modified = (value != bound);
        value = bound;
        return modified;
    }
};

#endif // NUMERICUTILLS_H
