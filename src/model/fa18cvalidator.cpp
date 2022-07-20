#include "fa18cvalidator.h"

using namespace model;

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
