#include "m2000cvalidator.h"

using namespace model;

void M2000CValidator::incChaffBrstQty(qint16& value)
{
    value < 20 ? value++ : value = 0;
}

void M2000CValidator::incFlareBrstQty(qint16& value)
{
    value < 32 ? value++ : value = 0;
}

void M2000CValidator::incFlareBrstItrv(qint16& value)
{
    value < 75 ? value += 5 : value = 0;
}

void M2000CValidator::incFlareSeqItrv(qint16& value)
{
    value < 200 ? value += 5 : value = 5;
}

void M2000CValidator::incFlareSeqQty(qint16& value)
{
    value < 3 ? value++ : value = 1;
}

void M2000CValidator::decChaffBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 20;
}

void M2000CValidator::decFlareBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 32;
}

void M2000CValidator::decFlareBrstItrv(qint16& value)
{
    value > 0 ? value -= 5 : value = 75;
}

void M2000CValidator::decFlareSeqItrv(qint16& value)
{
    value > 5 ? value -= 5 : value = 200;
}

void M2000CValidator::decFlareSeqQty(qint16& value)
{
    value > 1 ? value-- : value = 3;
}

