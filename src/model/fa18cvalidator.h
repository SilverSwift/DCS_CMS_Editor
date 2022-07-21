#ifndef FA18CVALIDATOR_H
#define FA18CVALIDATOR_H

#include "abstractvalidator.h"
namespace model{

class FA18CValidator : public AbstractValidator
{
public:
    ~FA18CValidator() override = default;

    virtual bool boundChaffBrstQty(qint16& value) override;
    virtual bool boundChaffBrstItrv(qint16& /*value*/) override {return false;};
    virtual bool boundChaffSeqQty(qint16& /*value*/) override {return false;};
    virtual bool boundChaffSeqItrv(qint16& /*value*/) override {return false;};

    virtual bool boundFlareBrstQty(qint16& value) override;
    virtual bool boundFlareBrstItrv(qint16& /*value*/) override {return false;};
    virtual bool boundFlareSeqQty(qint16& value) override;
    virtual bool boundFlareSeqItrv(qint16& value) override;

    virtual void incChaffBrstQty(qint16& value)override;
    virtual void incChaffBrstItrv(qint16& /*value*/) override {};
    virtual void incChaffSeqQty(qint16& /*value*/) override {};
    virtual void incChaffSeqItrv(qint16& /*value*/) override {};

    virtual void incFlareBrstQty(qint16& value)override;
    virtual void incFlareBrstItrv(qint16& /*value*/) override {};
    virtual void incFlareSeqItrv(qint16& value)override;
    virtual void incFlareSeqQty(qint16& value)override;

    virtual void decChaffBrstQty(qint16& value)override;
    virtual void decChaffBrstItrv(qint16& /*value*/) override {};
    virtual void decChaffSeqQty(qint16& /*value*/) override {};
    virtual void decChaffSeqItrv(qint16& /*value*/) override {};

    virtual void decFlareBrstQty(qint16& value)override;
    virtual void decFlareBrstItrv(qint16& /*value*/) override {};
    virtual void decFlareSeqItrv(qint16& value)override;
    virtual void decFlareSeqQty(qint16& value)override;
};

}
#endif // FA18CVALIDATOR_H
