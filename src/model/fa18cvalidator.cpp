#include "fa18cvalidator.h"
#include "numericutills.h"

using namespace model;

bool FA18CValidator::boundChaffBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 100);
}

bool FA18CValidator::boundFlareBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 100);
}

bool FA18CValidator::boundFlareSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 24);
}

bool FA18CValidator::boundFlareSeqItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(25, value, 500);
}

void FA18CValidator::incChaffBrstQty(qint16& value)
{
    value < 100 ? value++ : value = 0;
}

void FA18CValidator::incFlareBrstQty(qint16& value)
{
    value < 100 ? value++ : value = 0;
}

void FA18CValidator::incFlareSeqItrv(qint16& value)
{
    value < 500 ? value += 25 : value = 25;
}

void FA18CValidator::incFlareSeqQty(qint16& value)
{
    value < 24 ? value++ : value = 1;
}

void FA18CValidator::decChaffBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 100;
}

void FA18CValidator::decFlareBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 100;
}

void FA18CValidator::decFlareSeqItrv(qint16& value)
{
    value > 25 ? value -= 25 : value = 500;
}

void FA18CValidator::decFlareSeqQty(qint16& value)
{
    value > 1 ? value-- : value = 24;
}
