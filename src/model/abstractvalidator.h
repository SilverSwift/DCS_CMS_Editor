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

        virtual void incChaff(quint8& value) = 0;
        virtual void incFlare(quint8& value) = 0;
        virtual void incIntrv(quint8& value) = 0;
        virtual void incCycle(quint8& value) = 0;
        virtual void decChaff(quint8& value) = 0;
        virtual void decFlare(quint8& value) = 0;
        virtual void decIntrv(quint8& value) = 0;
        virtual void decCycle(quint8& value) = 0;

    };
}
#endif // ABSTRACTVALIDATOR_H
