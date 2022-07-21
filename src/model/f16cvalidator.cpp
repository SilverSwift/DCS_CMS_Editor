#include "f16cvalidator.h"
#include "numericutills.h"

using namespace model;

bool F16CValidator::boundChaffBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 99);
}

bool F16CValidator::boundChaffBrstItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(20, value, 10000);
}

bool F16CValidator::boundChaffSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 99);
}

bool F16CValidator::boundChaffSeqItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(50, value, 15000);
}

bool F16CValidator::boundFlareBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 99);
}

bool F16CValidator::boundFlareBrstItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(20, value, 10000);
}

bool F16CValidator::boundFlareSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 99);
}

bool F16CValidator::boundFlareSeqItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(50, value, 15000);
}

void F16CValidator::incChaffBrstQty(qint16& value)
{
    value < 99 ? value++ : value = 0;
}

void F16CValidator::incChaffBrstItrv(qint16& value)
{
    value < 10000 ? value += 20 : value = 20;
}

void F16CValidator::incChaffSeqQty(qint16& value)
{
    value < 99 ? value++ : value = 0;
}

void F16CValidator::incChaffSeqItrv(qint16& value)
{
    value < 15000 ? value += 50 : value = 50;
}

void F16CValidator::incFlareBrstQty(qint16& value)
{
    value < 99 ? value++ : value = 0;
}

void F16CValidator::incFlareBrstItrv(qint16& value)
{
    value < 10000 ? value += 20 : value = 20;
}

void F16CValidator::incFlareSeqItrv(qint16& value)
{
    value < 15000 ? value += 50 : value = 50;
}

void F16CValidator::incFlareSeqQty(qint16& value)
{
    value < 99 ? value++ : value = 0;
}

void F16CValidator::decChaffBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 99;
}

void F16CValidator::decChaffBrstItrv(qint16& value)
{
    value > 20 ? value -= 20 : value = 10000;
}

void F16CValidator::decChaffSeqQty(qint16& value)
{
    value > 0 ? value-- : value = 99;
}

void F16CValidator::decChaffSeqItrv(qint16& value)
{
    value > 50 ? value -= 50 : value = 15000;
}

void F16CValidator::decFlareBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 99;
}

void F16CValidator::decFlareBrstItrv(qint16& value)
{
    value > 20 ? value -= 20 : value = 10000;
}

void F16CValidator::decFlareSeqItrv(qint16& value)
{
    value > 50 ? value -= 50 : value = 15000;
}

void F16CValidator::decFlareSeqQty(qint16& value)
{
    value > 0 ? value-- : value = 99;
}
