#ifndef NUMERICUTILLS_H
#define NUMERICUTILLS_H

#include <QtGlobal>
#include <QVariant>

class NumericUtills
{
public:
    static quint8 parseUint8(QVariant value, bool* ok);
};

#endif // NUMERICUTILLS_H
