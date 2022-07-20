#ifndef M2000CVALIDATOR_H
#define M2000CVALIDATOR_H

#include "abstractvalidator.h"
namespace model{

class M2000CValidator : public AbstractValidator
{
public:
    virtual ~M2000CValidator() override = default;

    virtual void incChaffBrstQty(qint16& value) override;
    virtual void incChaffBrstItrv(qint16& /*value*/) override {};
    virtual void incChaffSeqQty(qint16& /*value*/) override {};
    virtual void incChaffSeqItrv(qint16& /*value*/) override {};

    virtual void incFlareBrstQty(qint16& value) override;
    virtual void incFlareBrstItrv(qint16& value) override;
    virtual void incFlareSeqItrv(qint16& value) override;
    virtual void incFlareSeqQty(qint16& value) override;

    virtual void decChaffBrstQty(qint16& value) override;
    virtual void decChaffBrstItrv(qint16& /*value*/) override {};
    virtual void decChaffSeqQty(qint16& /*value*/) override {};
    virtual void decChaffSeqItrv(qint16& /*value*/) override {};

    virtual void decFlareBrstQty(qint16& value) override;
    virtual void decFlareBrstItrv(qint16& value) override;
    virtual void decFlareSeqItrv(qint16& value) override;
    virtual void decFlareSeqQty(qint16& value) override;
};

}
#endif // M2000CVALIDATOR_H
