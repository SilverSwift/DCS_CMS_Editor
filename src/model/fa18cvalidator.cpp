#include "fa18cvalidator.h"

using namespace model;

void FA18CValidator::incChaff(quint8& value)
{
    value < 100 ? value++ : value = 0;
}

void FA18CValidator::incFlare(quint8& value)
{
    value < 100 ? value++ : value = 0;
}

void FA18CValidator::incIntrv(quint8& value)
{
    value < 5.0/0.25 ? value++ : value = 1;
}

void FA18CValidator::incCycle(quint8& value)
{
    value < 24 ? value++ : value = 1;
}

void FA18CValidator::decChaff(quint8& value)
{
    value > 0 ? value-- : value = 100;
}

void FA18CValidator::decFlare(quint8& value)
{
    value > 0 ? value-- : value = 100;
}

void FA18CValidator::decIntrv(quint8& value)
{
    value > 1 ? value-- : value = 5.0/0.25;
}

void FA18CValidator::decCycle(quint8& value)
{
    value > 1 ? value-- : value = 24;
}
