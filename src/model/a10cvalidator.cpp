#include "a10cvalidator.h"

using namespace model;

void A10CValidator::incChaff(quint8& value)
{
    value++;
}

void A10CValidator::incFlare(quint8& value)
{
    value++;
}

void A10CValidator::incIntrv(quint8& value)
{
    value < 5.0/0.25 ? value++ : value = 1;
}

void A10CValidator::incCycle(quint8& value)
{
    value < 99 ?  value++ : value = 1;
}

void A10CValidator::decChaff(quint8& value)
{
    value--;
}

void A10CValidator::decFlare(quint8& value)
{
    value--;
}

void A10CValidator::decIntrv(quint8& value)
{
    value > 1 ? value-- : value = 5.0/0.25;
}

void A10CValidator::decCycle(quint8& value)
{
    value > 1 ? value-- : value = 99;
}
