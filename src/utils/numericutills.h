#ifndef NUMERICUTILLS_H
#define NUMERICUTILLS_H

#include <QtGlobal>
#include <QVariant>

class NumericUtills
{
    NumericUtills() = delete;
public:
    static quint8 parseUint8(QVariant value, bool* ok = nullptr);
    static float parseFloat(QVariant value, bool* ok = nullptr);
    static quint8 parseInterval(QVariant value, bool *ok = nullptr);
    static QString intervalToString(quint8 intv);
};

#endif // NUMERICUTILLS_H
