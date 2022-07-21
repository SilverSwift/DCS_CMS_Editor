#ifndef ABSTRACTVALIDATOR_H
#define ABSTRACTVALIDATOR_H

#include <QtGlobal>

namespace model{
/*
 * AbstractValidator class provides interface
 * for parameter changing within allowed range
 */
class AbstractValidator{
public:
    virtual ~AbstractValidator() = default;
    //bounds input, returns true if input was outbounded
    virtual bool boundChaffBrstQty(qint16& value) = 0;
    virtual bool boundChaffBrstItrv(qint16& value) = 0;
    virtual bool boundChaffSeqQty(qint16& value) = 0;
    virtual bool boundChaffSeqItrv(qint16& value) = 0;

    virtual bool boundFlareBrstQty(qint16& value) = 0;
    virtual bool boundFlareBrstItrv(qint16& value) = 0;
    virtual bool boundFlareSeqQty(qint16& value) = 0;
    virtual bool boundFlareSeqItrv(qint16& value) = 0;

    //increments input value, keeping it within bounds
    virtual void incChaffBrstQty(qint16& value) = 0;
    virtual void incChaffBrstItrv(qint16& value) = 0;
    virtual void incChaffSeqQty(qint16& value) = 0;
    virtual void incChaffSeqItrv(qint16& value) = 0;

    virtual void incFlareBrstQty(qint16& value) = 0;
    virtual void incFlareBrstItrv(qint16& value) = 0;
    virtual void incFlareSeqQty(qint16& value) = 0;
    virtual void incFlareSeqItrv(qint16& value) = 0;

    //decrements input value, keeping it within bounds
    virtual void decChaffBrstQty(qint16& value) = 0;
    virtual void decChaffBrstItrv(qint16& value) = 0;
    virtual void decChaffSeqQty(qint16& value) = 0;
    virtual void decChaffSeqItrv(qint16& value) = 0;

    virtual void decFlareBrstQty(qint16& value) = 0;
    virtual void decFlareBrstItrv(qint16& value) = 0;
    virtual void decFlareSeqQty(qint16& value) = 0;
    virtual void decFlareSeqItrv(qint16& value) = 0;
};
}
#endif // ABSTRACTVALIDATOR_H
