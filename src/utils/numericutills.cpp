#include "numericutills.h"

quint8 NumericUtills::parseUint8(QVariant value, bool* ok)
{
    quint8 result = 0;
    uint parsed = value.toUInt(ok);
    *ok = *ok && (parsed <= 0xFF);

    if (*ok)
        result = parsed;

    return result;
}
