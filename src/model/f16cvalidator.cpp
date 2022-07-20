#include "f16cvalidator.h"

using namespace model;

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
