#ifndef FA18CVALIDATOR_H
#define FA18CVALIDATOR_H

#include "abstractvalidator.h"
namespace model{
    class FA18CValidator : public AbstractValidator
    {
    public:
        ~FA18CValidator() override = default;
        virtual void incChaff(quint8& value)override;
        virtual void incFlare(quint8& value)override;
        virtual void incIntrv(quint8& value)override;
        virtual void incCycle(quint8& value)override;
        virtual void decChaff(quint8& value)override;
        virtual void decFlare(quint8& value)override;
        virtual void decIntrv(quint8& value)override;
        virtual void decCycle(quint8& value)override;
    };
}
#endif // FA18CVALIDATOR_H
