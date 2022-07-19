#include "a10cvalidator.h"

using namespace model;

void A10CValidator::incChaff(qint16& value)
{
    value < 999 ? value++ : value = 0;
}

void A10CValidator::incFlare(qint16& value)
{
    value < 999 ? value++ : value = 0;
}

void A10CValidator::incIntrv(qint16& value)
{
    value < 5.0/0.25 ? value++ : value = 1;
}

void A10CValidator::incCycle(qint16& value)
{
    value < 99 ?  value++ : value = 1;
}

void A10CValidator::decChaff(qint16& value)
{
    value > 0 ? value-- : value = 999;
}

void A10CValidator::decFlare(qint16& value)
{
    value > 0 ? value-- : value = 999;
}

void A10CValidator::decIntrv(qint16& value)
{
    value > 1 ? value-- : value = 5.0/0.25;
}

void A10CValidator::decCycle(qint16& value)
{
    value > 1 ? value-- : value = 99;
}
