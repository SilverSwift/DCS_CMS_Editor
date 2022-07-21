#include "a10cvalidator.h"
#include "numericutills.h"

using namespace model;

bool A10CValidator::boundChaffBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 999);
}

bool A10CValidator::boundFlareBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 999);
}

bool A10CValidator::boundFlareSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 99);
}

bool A10CValidator::boundFlareSeqItrv(qint16& value)
{
    //have to use 20 here instead of 25
    //because of typo in program 'C'
    return NumericUtills::bound<qint16>(20, value, 500);
}

void A10CValidator::incChaffBrstQty(qint16& value)
{
    value < 999 ? value++ : value = 0;
}

void A10CValidator::incFlareBrstQty(qint16& value)
{
    value < 999 ? value++ : value = 0;
}

void A10CValidator::incFlareSeqItrv(qint16& value)
{
    value < 500 ? value += 25 : value = 25;
}

void A10CValidator::incFlareSeqQty(qint16& value)
{
    value < 99 ?  value++ : value = 1;
}

void A10CValidator::decChaffBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 999;
}

void A10CValidator::decFlareBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 999;
}

void A10CValidator::decFlareSeqItrv(qint16& value)
{
    value > 25 ? value-=25 : value = 500;
}

void A10CValidator::decFlareSeqQty(qint16& value)
{
    value > 1 ? value-- : value = 99;
}
