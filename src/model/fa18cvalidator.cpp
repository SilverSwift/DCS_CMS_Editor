#include "fa18cvalidator.h"

using namespace model;

void FA18CValidator::incChaff(qint16& value)
{
    value < 100 ? value++ : value = 0;
}

void FA18CValidator::incFlare(qint16& value)
{
    value < 100 ? value++ : value = 0;
}

void FA18CValidator::incIntrv(qint16& value)
{
    value < 5.0/0.25 ? value++ : value = 1;
}

void FA18CValidator::incCycle(qint16& value)
{
    value < 24 ? value++ : value = 1;
}

void FA18CValidator::decChaff(qint16& value)
{
    value > 0 ? value-- : value = 100;
}

void FA18CValidator::decFlare(qint16& value)
{
    value > 0 ? value-- : value = 100;
}

void FA18CValidator::decIntrv(qint16& value)
{
    value > 1 ? value-- : value = 5.0/0.25;
}

void FA18CValidator::decCycle(qint16& value)
{
    value > 1 ? value-- : value = 24;
}
