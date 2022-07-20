#include "a10cvalidator.h"

using namespace model;

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
