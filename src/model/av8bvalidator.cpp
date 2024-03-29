#include "av8bvalidator.h"
#include "numericutills.h"

using namespace model;

bool AV8BValidator::boundChaffBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 15);
}

bool AV8BValidator::boundChaffBrstItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 15);
}

bool AV8BValidator::boundChaffSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 15);
}

bool AV8BValidator::boundChaffSeqItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 15);
}

bool AV8BValidator::boundFlareSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 15);
}

bool AV8BValidator::boundFlareSeqItrv(qint16& value)
{
    return NumericUtills::bound<qint16>(1, value, 15);
}

void AV8BValidator::incChaffBrstQty(qint16& value)
{
    value < 15 ? value++ : value = 1;
}

void AV8BValidator::incChaffBrstItrv(qint16& value)
{
    value < 15 ? value++ : value = 1;
}

void AV8BValidator::incChaffSeqQty(qint16& value)
{
    value < 15 ? value++ : value = 1;
}

void AV8BValidator::incChaffSeqItrv(qint16& value)
{
    value < 15 ? value++ : value = 1;
}

void AV8BValidator::incFlareSeqQty(qint16& value)
{
    value < 15 ? value++ : value = 1;
}

void AV8BValidator::incFlareSeqItrv(qint16& value)
{
    value < 15 ? value++ : value = 1;
}

void AV8BValidator::decChaffBrstQty(qint16& value)
{
    value > 1 ? value-- : value = 15;
}

void AV8BValidator::decChaffBrstItrv(qint16& value)
{
    value > 1 ? value-- : value = 15;
}

void AV8BValidator::decChaffSeqQty(qint16& value)
{
    value > 1 ? value-- : value = 15;
}

void AV8BValidator::decChaffSeqItrv(qint16& value)
{
    value > 1 ? value-- : value = 15;
}

void AV8BValidator::decFlareSeqQty(qint16& value)
{
    value > 1 ? value-- : value = 15;
}

void AV8BValidator::decFlareSeqItrv(qint16& value)
{
    value > 1 ? value-- : value = 15;
}
