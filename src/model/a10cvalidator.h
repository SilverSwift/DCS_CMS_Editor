#ifndef A10CVALIDATOR_H
#define A10CVALIDATOR_H

#include "abstractvalidator.h"
namespace model{
    class A10CValidator : public AbstractValidator{
    public:
        virtual ~A10CValidator() override = default;
        virtual void incChaff(quint8& value) override;
        virtual void incFlare(quint8& value) override;
        virtual void incIntrv(quint8& value) override;
        virtual void incCycle(quint8& value) override;
        virtual void decChaff(quint8& value) override;
        virtual void decFlare(quint8& value) override;
        virtual void decIntrv(quint8& value) override;
        virtual void decCycle(quint8& value) override;
    };
}

#endif // A10CVALIDATOR_H
