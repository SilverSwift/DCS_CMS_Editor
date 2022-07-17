#include "fa18cvalidator.h"

using namespace model;

void FA18CValidator::incChaff(quint8& value)
{
    if (value < 100) value++;
}

void FA18CValidator::incFlare(quint8& value)
{
    if (value < 100) value++;
}

void FA18CValidator::incIntrv(quint8& value)
{
    if (value < 24) value++;
}

void FA18CValidator::incCycle(quint8& value)
{
    if (value < 5.0/0.25) value++;
}

void FA18CValidator::decChaff(quint8& value)
{
    if (value > 0) value--;
}

void FA18CValidator::decFlare(quint8& value)
{
    if (value > 0) value--;
}

void FA18CValidator::decIntrv(quint8& value)
{
    if (value > 1) value--;
}

void FA18CValidator::decCycle(quint8& value)
{
    if (value > 1) value--;
}
