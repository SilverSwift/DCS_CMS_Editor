#include "m2000cvalidator.h"
#include "numericutills.h"

using namespace model;

bool M2000CValidator::boundChaffBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 234);
}

bool M2000CValidator::boundFlareBrstQty(qint16& value)
{
     return NumericUtills::bound<qint16>(0, value, 64);
}

bool M2000CValidator::boundFlareBrstItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 500);
}

bool M2000CValidator::boundFlareSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 10);
}

bool M2000CValidator::boundFlareSeqItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(5, value, 2000);
}

void M2000CValidator::incChaffBrstQty(qint16& value)
{
    value < 234 ? value++ : value = 0;
}

void M2000CValidator::incFlareBrstQty(qint16& value)
{
    value < 64 ? value++ : value = 0;
}

void M2000CValidator::incFlareBrstItrv(qint16& value)
{
    value < 500 ? value += 5 : value = 0;
}

void M2000CValidator::incFlareSeqItrv(qint16& value)
{
    value < 2000 ? value += 5 : value = 5;
}

void M2000CValidator::incFlareSeqQty(qint16& value)
{
    value < 10 ? value++ : value = 1;
}

void M2000CValidator::decChaffBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 234;
}

void M2000CValidator::decFlareBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 64;
}

void M2000CValidator::decFlareBrstItrv(qint16& value)
{
    value > 0 ? value -= 5 : value = 500;
}

void M2000CValidator::decFlareSeqItrv(qint16& value)
{
    value > 5 ? value -= 5 : value = 2000;
}

void M2000CValidator::decFlareSeqQty(qint16& value)
{
    value > 1 ? value-- : value = 10;
}

