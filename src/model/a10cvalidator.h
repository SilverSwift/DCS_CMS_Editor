#ifndef A10CVALIDATOR_H
#define A10CVALIDATOR_H

#include "abstractvalidator.h"
namespace model{
    class A10CValidator : public AbstractValidator{
    public:
        virtual ~A10CValidator() override = default;
        virtual void incChaff(qint16& value) override;
        virtual void incFlare(qint16& value) override;
        virtual void incIntrv(qint16& value) override;
        virtual void incCycle(qint16& value) override;
        virtual void decChaff(qint16& value) override;
        virtual void decFlare(qint16& value) override;
        virtual void decIntrv(qint16& value) override;
        virtual void decCycle(qint16& value) override;
    };
}

#endif // A10CVALIDATOR_H
