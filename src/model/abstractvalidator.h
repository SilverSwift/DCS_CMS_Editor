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

        virtual void incChaff(qint16& value) = 0;
        virtual void incFlare(qint16& value) = 0;
        virtual void incIntrv(qint16& value) = 0;
        virtual void incCycle(qint16& value) = 0;
        virtual void decChaff(qint16& value) = 0;
        virtual void decFlare(qint16& value) = 0;
        virtual void decIntrv(qint16& value) = 0;
        virtual void decCycle(qint16& value) = 0;
    };
}
#endif // ABSTRACTVALIDATOR_H
