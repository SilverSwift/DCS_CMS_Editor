#ifndef FA18CVALIDATOR_H
#define FA18CVALIDATOR_H

#include "abstractvalidator.h"
namespace model{
    class FA18CValidator : public AbstractValidator
    {
    public:
        ~FA18CValidator() override = default;
        virtual void incChaff(qint16& value)override;
        virtual void incFlare(qint16& value)override;
        virtual void incIntrv(qint16& value)override;
        virtual void incCycle(qint16& value)override;
        virtual void decChaff(qint16& value)override;
        virtual void decFlare(qint16& value)override;
        virtual void decIntrv(qint16& value)override;
        virtual void decCycle(qint16& value)override;
    };
}
#endif // FA18CVALIDATOR_H
