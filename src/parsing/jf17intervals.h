#ifndef JF17INTERVALS_H
#define JF17INTERVALS_H
#include <QMap>

namespace parsing{
//yep... that's weird, but that's Deka's implementation
//                              ||
//                              \/
static const QMap<qint16, qint16> flareBurstIntervals =
     {{0, 0}, {1, 20}, {2, 50}, {3, 75}, {4, 100}};
static const QMap<qint16, qint16> chaffBurstIntervals =
     {{0, 0}, {1, 20}, {2, 50}, {4, 75}, {5, 100}};

static const QMap<qint16, qint16> sequenceIntervals =
    { {0,20}, {1,50}, {2,100}, {3,200}, {4,300}, {5,450}, {6,500} };

static const float precision = 0.01;

enum ProgramType{
    ChaffOnly = 0,
    FlareOnly,
    ChaffFlare
};

}
#endif // JF17INTERVALS_H
