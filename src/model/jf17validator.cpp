#include "jf17validator.h"
#include "jf17intervals.h"
#include "numericutills.h"

using namespace model;

JF17Validator::JF17Validator()
{

}

bool JF17Validator::boundChaffBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 6);
}

bool JF17Validator::boundChaffBrstItrv(qint16& value)
{
    return boundInterval(value, parsing::chaffBurstIntervals);
}

bool JF17Validator::boundChaffSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 4);
}

bool JF17Validator::boundChaffSeqItrv(qint16& value)
{
    return boundInterval(value, parsing::sequenceIntervals);
}

bool JF17Validator::boundFlareBrstQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 6 );
}

bool JF17Validator::boundFlareBrstItrv(qint16& value)
{
    return boundInterval(value, parsing::flareBurstIntervals);
}

bool JF17Validator::boundFlareSeqQty(qint16& value)
{
    return NumericUtills::bound<qint16>(0, value, 4);
}

bool JF17Validator::boundFlareSeqItrv(qint16& value)
{
    return boundInterval(value, parsing::sequenceIntervals);
}

void JF17Validator::incChaffBrstQty(qint16& value)
{
    value < 6 ? value++ : value = 0;
}

void JF17Validator::incChaffBrstItrv(qint16& value)
{
    incInterval(value, parsing::chaffBurstIntervals);
}

void JF17Validator::incChaffSeqQty(qint16& value)
{
    value < 4 ? value++ : value = 0;
}

void JF17Validator::incChaffSeqItrv(qint16& value)
{
    incInterval(value, parsing::sequenceIntervals);
}

void JF17Validator::incFlareBrstQty(qint16& value)
{
    value < 6 ? value++ : value = 0;
}

void JF17Validator::incFlareBrstItrv(qint16& value)
{
    incInterval(value, parsing::flareBurstIntervals);
}

void JF17Validator::incFlareSeqQty(qint16& value)
{
    value < 4 ? value++ : value = 0;
}

void JF17Validator::incFlareSeqItrv(qint16& value)
{
    incInterval(value, parsing::sequenceIntervals);
}

void JF17Validator::decChaffBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 6;
}

void JF17Validator::decChaffBrstItrv(qint16& value)
{
    decInterval(value, parsing::chaffBurstIntervals);
}

void JF17Validator::decChaffSeqQty(qint16& value)
{
    value > 0 ? value-- : value = 4;
}

void JF17Validator::decChaffSeqItrv(qint16& value)
{
    decInterval(value, parsing::sequenceIntervals);
}

void JF17Validator::decFlareBrstQty(qint16& value)
{
    value > 0 ? value-- : value = 6;
}

void JF17Validator::decFlareBrstItrv(qint16& value)
{
    decInterval(value, parsing::flareBurstIntervals);
}

void JF17Validator::decFlareSeqQty(qint16& value)
{
    value > 0 ? value-- : value = 4;
}

void JF17Validator::decFlareSeqItrv(qint16& value)
{
    decInterval(value, parsing::sequenceIntervals);
}

void JF17Validator::incInterval(qint16& value, const QMap<qint16, qint16> intervals)
{
    auto valueList = intervals.values();
    auto index = valueList.indexOf(value);
    value = valueList.value(index + 1, valueList.first());
}

void JF17Validator::decInterval(qint16& value, const QMap<qint16, qint16> intervals)
{
    auto valueList = intervals.values();
    auto index = valueList.indexOf(value);
    value = valueList.value(index - 1, valueList.last());
}

bool JF17Validator::boundInterval(qint16& value, const QMap<qint16, qint16> intervals)
{
    bool isValid = intervals.values().contains(value);

    if (!isValid)
        value = intervals[0];

    return !isValid;
}
